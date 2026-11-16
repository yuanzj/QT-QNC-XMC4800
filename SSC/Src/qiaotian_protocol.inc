/* SPDX-License-Identifier: BSD-3-Clause */
/* 本方配套定义：基础轴单位转换、表内记录及工艺兼容侧车分别处理。 */
#include <stdint.h>
#include <limits.h>
#include <string.h>
#include "qiaotian_nvm.inc"
static uint32_t qec_params[5][25];
static uint8_t qec_initialized;
/* Reserve maintenance before re-enabling the model ISR; START must remain blocked. */
static volatile bool qec_maintenance_busy;
static uint64_t qec_epoch_ms;
static qn_cal_t qec_staging;
static uint8_t qec_cal_type;
static int32_t qec_target_position,qec_target_velocity;
static int16_t qec_target_torque;
static int8_t qec_requested_mode=8;
static const uint8_t qec_widths[5][25]={
 {4,2,1,4,2,4,1,1},
 {4,2,2,2,1,1,1,1,1,1,1,4,4,4,4},
 {1,4,2,1,1,2,2,1,1,1,1,1,1,4,4,4,4,4,4,4,4,4,1,1,1},
 {4,2,2,2,1,4,4,4},
 {1,4,2,1,1,2,2,1,1,1,1,1,1,4,4,4,4,4,4,4,4,4,1,1,1}};
static const uint8_t qec_counts[]={8,15,25,8,25};
static void qec_defaults(void)
{
    if(qec_initialized)return;
    qec_initialized=1U;
    const uint32_t p[5][25]={
      {6000,40,0,1600,10,3000,1,0},
      {6000,40,1000,0,2,0,0,50,100,99,1,1600,1800,1600,0},
      {0,6000,40,1,1,1000,0,2,0,50,100,99,1,16000,30000,0,1600,30000,100,200,1000,150,0,1,2},
      {6000,40,1000,0,2,1600,3000,1600},
      {1,6000,40,1,1,1000,0,2,0,50,100,99,1,16000,30000,0,1600,30000,100,200,1000,150,0,1,2}};
    memcpy(qec_params,p,sizeof(p));qec_staging=qn_state.cal[0];
}
static void qec_put(uint8_t *p,uint64_t v,unsigned n){for(unsigned i=0;i<n;++i)p[i]=(uint8_t)(v>>(8U*i));}
static uint64_t qec_get(const uint8_t *p,unsigned n){uint64_t v=0U;for(unsigned i=0;i<n;++i)v|=(uint64_t)p[i]<<(8U*i);return v;}
static int32_t qec_position(void)
{
    int64_t value=(int64_t)Position_actual_value0x6064*36000;
    return (int32_t)(value/((int64_t)8388608*30));
}
static int32_t qec_velocity(void)
{
    return (int32_t)((SimulatedSlave_Velocity64*600)/((int64_t)8388608*30));
}
static unsigned qec_scope(uint8_t create)
{
    if(qec_cal_type==0U)return 0U;
    for(unsigned i=1U;i<QN_SCOPE_CAPACITY;++i)if(qn_state.cal[i].valid && qn_state.cal[i].pset==qec_staging.pset)return i;
    if(create)for(unsigned i=1U;i<QN_SCOPE_CAPACITY;++i)if(!qn_state.cal[i].valid)return i;
    return QN_SCOPE_CAPACITY;
}
static int16_t qec_torque(void)
{
    const qn_cal_t *cal=&qn_state.cal[0];uint16_t pset=(uint16_t)(pset_echo0x220B>>8);
    for(unsigned i=1U;i<QN_SCOPE_CAPACITY;++i)if(qn_state.cal[i].valid && qn_state.cal[i].pset==pset){cal=&qn_state.cal[i];break;}
    int64_t torque=(int64_t)Torque_actual_value0x6077*cal->k/1000+(int64_t)cal->b*1000/Tool_Spec0x2000.max_torque;
    return torque>INT16_MAX ? INT16_MAX : torque<INT16_MIN ? INT16_MIN : (int16_t)torque;
}
static void qec_pack(uint8_t p[46])
{
    uint32_t irq=__get_PRIMASK();__disable_irq();
    uint16_t statusword=Statusword0x6041;
    if(status_code0x2200==FPGA_SIM_TOOL_UNAVAILABLE)
        statusword=(uint16_t)((statusword & ~(0x006FU | 0x0400U)) | 0x0008U);
    qec_put(p,statusword,2);qec_put(p+2,Error_code0x603F,2);
    qec_put(p+4,(uint32_t)qec_position(),4);qec_put(p+8,(uint32_t)qec_velocity(),4);
    qec_put(p+12,(uint16_t)qec_torque(),2);qec_put(p+14,status_code0x2200,4);qec_put(p+18,status_code20x2201,4);
    qec_put(p+22,(uint32_t)Position_actual_value0x6064,4);qec_put(p+26,(uint64_t)SimulatedSlave_Velocity64,8);
    qec_put(p+34,pset_echo0x220B,2);p[36]=step_echo0x220C;p[37]=step_result0x220D;
    qec_put(p+38,(uint32_t)current_sample0x2208,4);qec_put(p+42,QEC_SIM_PAIRED_ID,4);__set_PRIMASK(irq);
}
UINT8 ECAT_Read_QEC_Callback(UINT16 index,UINT8 sub,UINT32 bytes,UINT16 MBXMEM *data,UINT8 ca)
{
    uint8_t *p=(uint8_t *)data;uint64_t value=0U;unsigned width=0U;qec_defaults();
    if(ca)return ABORTIDX_UNSUPPORTED_ACCESS;
    int group=index>=0x2400U && index<=0x2440U && !(index&15U)?(index-0x2400U)/16:-1;
    unsigned count=group>=0 ? qec_counts[group] : index==0x2300U ? 13U : index==0x2310U ? 6U : index==0x2500U ? 21U : index==0x2F00U ? 9U : index==0x2F10U ? 1U : 0U;
    if(count && !sub){if(bytes!=1U)return ABORTIDX_PARAM_LENGTH_ERROR;p[0]=(uint8_t)count;return 0;}
    if(index==0x6064U || index==0x606CU){if(sub)return ABORTIDX_SUBINDEX_NOT_EXISTING;value=(uint32_t)(index==0x6064U?qec_position():qec_velocity());width=4U;}
    else if(index==0x6077U){if(sub)return ABORTIDX_SUBINDEX_NOT_EXISTING;value=(uint16_t)qec_torque();width=2U;}
    else if(index==0x607AU || index==0x60FFU || index==0x6071U || index==0x6060U){
        if(sub)return ABORTIDX_SUBINDEX_NOT_EXISTING;
        width=index==0x6060U?1U:index==0x6071U?2U:4U;
        value=index==0x607AU?(uint32_t)qec_target_position:index==0x60FFU?(uint32_t)qec_target_velocity:index==0x6071U?(uint16_t)qec_target_torque:(uint8_t)qec_requested_mode;
    }
    else if(sub>count || !sub)return ABORTIDX_SUBINDEX_NOT_EXISTING;
    else if(group>=0){width=qec_widths[group][sub-1U];value=qec_params[group][sub-1U];}
    else if(index==0x2F00U){
        static const uint8_t widths[]={4,4,4,8,2,1,1,4,4};static const uint8_t offsets[]={14,18,22,26,34,36,37,38,42};
        uint8_t image[46];qec_pack(image);width=widths[sub-1U];
        if(bytes!=width)return ABORTIDX_PARAM_LENGTH_ERROR;
        memcpy(p,image+offsets[sub-1U],width);return 0;
    }
    else if(index==0x2300U){
        static const uint8_t widths[]={16,16,2,4,4,4,4,4,16,4,4,4,2};width=widths[sub-1U];
        if(bytes!=width)return ABORTIDX_PARAM_LENGTH_ERROR;
        if(sub==1U){memcpy(p,Tool_Spec0x2000.tool_sn,16U);return 0;}
        if(sub==2U || sub==9U){memset(p,0,16U);memcpy(p,sub==2U?"SIM-MOTOR-QNC":"SIM-ENC-23BIT",13U);return 0;}
        switch(sub){case 3:value=XMC_SIM_GEAR_RATIO*10U;break;case 4:value=Tool_Spec0x2000.max_torque;break;case 5:value=11000U;break;
        case 6:value=XMC_SIM_MAX_OUTPUT_DECI_RPM;break;case 7:value=XMC_SIM_MAX_MOTOR_DECI_RPM;break;case 8:value=1000U;break;
        case 10:value=qn_state.last_cal_epoch_ms/1000U;break;case 11:value=qn_state.ok;break;case 12:value=qn_state.period;break;case 13:value=4800U;break;}
    }
    else if(index==0x2310U){
        static const uint8_t widths[]={1,2,4,4,4,1};width=widths[sub-1U];
        switch(sub){case 1:value=qec_cal_type;break;case 2:value=qec_staging.pset;break;case 3:value=qec_staging.k;break;
        case 4:value=(uint32_t)qec_staging.b;break;case 5:value=qec_staging.limit;break;case 6:value=0U;break;}
    }
    else if(index==0x2500U){width=4U;switch(sub){case 0x10:value=qn_state.seconds;break;case 0x12:value=qn_state.ok;break;case 0x13:value=qn_state.nok;break;case 0x15:value=qn_state.cal[0].k;break;default:return ABORTIDX_SUBINDEX_NOT_EXISTING;}}
    else if(index==0x2F10U){width=8U;value=qec_epoch_ms;}
    if(bytes!=width)return ABORTIDX_PARAM_LENGTH_ERROR;
    qec_put(p,value,width);return 0;
}
static UINT8 qec_write_record(UINT16 index,UINT8 sub,UINT32 bytes,UINT16 MBXMEM *data,UINT8 ca)
{
    qec_defaults();if(ca || !sub)return ABORTIDX_UNSUPPORTED_ACCESS;
    /* 参数/标定只能在引擎停止时改。 */
    if(Pset_IsRunning())return ABORTIDX_IN_THIS_STATE_DATA_CANNOT_BE_READ_OR_STORED;
    int group=index>=0x2400U && index<=0x2440U && !(index&15U)?(index-0x2400U)/16:-1;
    if(group>=0){
        if(sub>qec_counts[group])return ABORTIDX_SUBINDEX_NOT_EXISTING;
        if(bytes!=qec_widths[group][sub-1U])return ABORTIDX_PARAM_LENGTH_ERROR;
        uint32_t value=(uint32_t)qec_get((uint8_t *)data,bytes);unsigned s=sub;
        bool range=false;
        if(group==0){range=s==1?value<=XMC_SIM_MAX_OUTPUT_DECI_RPM:s==3?value<=2U:s==4?value<=30000U:s==6?value<=18000000U:s==7?value>=1U&&value<=100U:s==8?value<=2U:true;}
        else if(group==1){range=s==1?value<=XMC_SIM_MAX_OUTPUT_DECI_RPM:s==5?value>=1U&&value<=3U:s==6||s==7?value<=1U:s==8?value<=100U:s==9?value<=200U:s==10?value>=50U&&value<=100U:s==11?value>=1U&&value<=2U:s==13?value<=18000000U:s>=12?value<=30000U:true;}
        else if(group==3){range=s==1?value<=XMC_SIM_MAX_OUTPUT_DECI_RPM:s==5?value>=1U&&value<=3U:s==7?value<=18000000U:s>=6?value<=30000U:true;}
        else {range=s==1||s==4||s==5||s==9||s==23||s==24?value<=1U:s==2?value<=XMC_SIM_MAX_OUTPUT_DECI_RPM:s==8||s==25?value>=1U&&value<=3U:s==10?value<=100U:s==11?value<=200U:s==12?value>=50U&&value<=100U:s==13?value>=1U&&value<=4U:s>=19&&s<=22?value<=18000000U:s>=14&&s<=18?value<=30000U:true;}
        if(!range)return ABORTIDX_VALUE_EXCEEDED;
        qec_params[group][sub-1U]=value;return 0;
    }
    if(index==0x2F10U){if(sub!=1U || bytes!=8U)return ABORTIDX_PARAM_LENGTH_ERROR;
        uint64_t v=qec_get((uint8_t *)data,8U);if(v/1000U>UINT32_MAX || v<946684800000ULL)return ABORTIDX_VALUE_EXCEEDED;qec_epoch_ms=v;return 0;}
    if(index!=0x2310U || sub>6U)return ABORTIDX_SUBINDEX_NOT_EXISTING;
    static const uint8_t widths[]={1,2,4,4,4,1};if(bytes!=widths[sub-1U])return ABORTIDX_PARAM_LENGTH_ERROR;
    uint32_t value=(uint32_t)qec_get((uint8_t *)data,bytes);
    switch(sub){
    case 1:if(value>1U)return ABORTIDX_VALUE_EXCEEDED;qec_cal_type=(uint8_t)value;break;
    case 2:if(value>254U)return ABORTIDX_VALUE_EXCEEDED;qec_staging.pset=(uint16_t)value;break;
    case 3:if(!value)return ABORTIDX_VALUE_EXCEEDED;qec_staging.k=value;break;
    case 4:qec_staging.b=value<=INT32_MAX?(int32_t)value:-1-(int32_t)(UINT32_MAX-value);break;
    case 5:qec_staging.limit=value;break;
    case 6:{
        if(value!=1U || !qec_epoch_ms || !qec_staging.k || (!qec_cal_type && qec_staging.pset) || (qec_cal_type && !qec_staging.pset))return ABORTIDX_VALUE_EXCEEDED;
        unsigned scope=qec_scope(1U);if(scope>=QN_SCOPE_CAPACITY)return ABORTIDX_VALUE_EXCEEDED;
        qn_cal_t old=qn_state.cal[scope];uint32_t oldperiod=qn_state.period;uint64_t oldtime=qn_state.last_cal_epoch_ms;

        if(old.valid && old.epoch_ms==qec_epoch_ms){return old.k==qec_staging.k && old.b==qec_staging.b && old.limit==qec_staging.limit?0:ABORTIDX_VALUE_EXCEEDED;}
        qn_state.cal[scope]=qec_staging;qn_state.cal[scope].valid=1U;qn_state.cal[scope].count=0U;qn_state.cal[scope].epoch_ms=qec_epoch_ms;
        qn_state.period=250000U;
        qn_state.last_cal_epoch_ms=qec_epoch_ms;
        if(!QEC_NvmCommit(scope)){qn_state.cal[scope]=old;qn_state.period=oldperiod;qn_state.last_cal_epoch_ms=oldtime;return ABORTIDX_IN_THIS_STATE_DATA_CANNOT_BE_READ_OR_STORED;}
        qec_staging=qn_state.cal[scope];break;}
    }
    return 0;
}

UINT8 ECAT_Write_QEC_Callback(UINT16 index,UINT8 sub,UINT32 bytes,UINT16 MBXMEM *data,UINT8 ca)
{
    uint32_t irq=__get_PRIMASK();
    __disable_irq();
    if(Pset_IsRunning() || App_JobCtrl_GetControl() || qn_write_busy || qec_maintenance_busy){
        __set_PRIMASK(irq);
        return ABORTIDX_IN_THIS_STATE_DATA_CANNOT_BE_READ_OR_STORED;
    }
    qec_maintenance_busy=true;
    __set_PRIMASK(irq);
    UINT8 result=qec_write_record(index,sub,bytes,data,ca);
    qec_maintenance_busy=false;
    return result;
}
