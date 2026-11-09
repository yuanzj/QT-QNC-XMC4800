/* 场景9严格解码：现行HMI五类工步；旧原生格式仅接收实际实现的组合。 */
#include "native_pset.h"
#if FPGA_SIM_SCENARIO == 9
#include <limits.h>
#include <string.h>
static uint16_t u16(const uint8_t *p){return (uint16_t)(p[0]|((uint16_t)p[1]<<8));}
static uint32_t u32(const uint8_t *p){return p[0]|((uint32_t)p[1]<<8)|((uint32_t)p[2]<<16)|((uint32_t)p[3]<<24);}
/* 现行UIO模式3逐字节保留HMI 96B工步。这里只接入独立模型实际执行的语义，
 * 不把未实现的普通工步交替方向静默丢弃。 */
static uint8_t hmi_step(const uint8_t *s,uint8_t seq,uint8_t count,FpgaProgramStep *step)
{
    uint32_t v[18];unsigned i,used;
    uint8_t action=s[23]&0x0fu,jump=s[23]>>4;
    for(i=0;i<18;i++)v[i]=u32(s+24+4*i);
    if(s[20]!=seq||s[22]<1||s[22]>(s[21]==1?4:2)||
       (s[21]==1?action!=0:(action<1||action>3))||
       (action==3?(jump==0||jump>count||jump==seq):jump!=0)||
       !u32(s)||u32(s)>FPGA_MODEL_MAX_RPM_MILLI/100U||
       u32(s+4)>60000||u32(s+8)>60000||
       (s[21]==1?u32(s+12)!=0:(!u32(s+12)||u32(s+12)>60000))||u32(s+16)>60000)return 0;
    step->direction=(uint8_t)(s[22]-1);step->failure_action=action;step->failure_jump_step=jump;
    step->speed_rpm_milli=u32(s)*100U;step->accel_time_ms=(uint16_t)u32(s+4);
    step->decel_time_ms=(uint16_t)u32(s+8);
    step->timeout_ms=u32(s+12);step->post_delay_ms=(uint16_t)u32(s+16);
    step->angle_reset=step->torque_reset=1;
    if(s[21]==1){
        used=4;
        if(!v[0]||v[0]>30000||!v[1]||v[1]>=307200||v[2]>600000||!v[3]||v[3]>15)return 0;
        step->kind=1;step->strategy=1;step->torque_mnm=(int32_t)v[0];step->angle_cdeg=(int32_t)v[1];
        /* 认帽低力保护与DC-08次数耗尽失败；不采用“次数到即OK”。 */
        step->max_torque_mnm=(int32_t)(v[0]*6U/5U);step->max_angle_cdeg=307199;
        step->engage_repeat_delay_ms=v[2];step->engage_repeat_count=(uint8_t)v[3];step->failure_action=2;
    }else if(s[21]==3){
        used=15;
        if(v[0]>3||v[10]>30000||v[11]>1||v[12]>1||v[13]>1||v[14]>1)return 0;
        step->kind=3;step->strategy=(uint8_t)(v[0]+1);
        step->torque_mnm=(int32_t)v[1];step->max_torque_mnm=(int32_t)v[2];step->min_torque_mnm=(int32_t)v[3];
        step->angle_threshold_mnm=v[4];step->min_angle_cdeg=(int32_t)v[5];step->max_angle_cdeg=(int32_t)v[6];
        step->safe_angle_cdeg=v[7];step->safe_torque_mnm=v[8];step->angle_cdeg=(int32_t)v[9];
        step->start_torque_mnm=v[10];
        step->torque_value_mode=(uint8_t)v[11];step->angle_value_mode=(uint8_t)v[12];
        step->angle_reset=(uint8_t)v[13];step->torque_reset=(uint8_t)v[14];
        if(v[1]>30000||v[2]>30000||v[3]>v[2]||v[4]>30000||v[5]>v[6]||v[6]>=307200||v[8]>30000||v[9]>=307200)return 0;
    }else if(s[21]==2){
        used=12;
        /* 下旋0扭矩/1角度；自动调节关闭时其三个比例槽不参与控制。 */
        if(v[0]>1||v[6]>1||v[7]>1||v[8]>1||v[9]>1000||v[10]>1000||v[11]>1000||
           (v[8]&&(!v[9]||!v[10]||!v[11]))||
           v[1]>=307200||v[2]>30000||v[3]>30000||v[4]>30000)return 0;
        step->kind=2;step->strategy=(uint8_t)(v[0]+1);step->angle_cdeg=(int32_t)v[1];step->angle_threshold_mnm=v[2];
        step->torque_mnm=(int32_t)v[3];step->safe_torque_mnm=v[4];step->safe_angle_cdeg=v[5];
        step->angle_reset=(uint8_t)v[6];step->torque_reset=(uint8_t)v[7];
        step->auto_adjust=(uint8_t)v[8];step->speed_adjust_ratio=(uint16_t)v[9];
        step->auto_sensitivity=(uint16_t)v[10];step->target_brake_ratio=(uint16_t)v[11];
        step->max_torque_mnm=30000;step->max_angle_cdeg=307199;
    }else if(s[21]==4){
        used=3;
        if(s[22]!=2||!v[0]||v[0]>30000||v[1]>30000||!v[2]||v[2]>=307200)return 0;
        step->kind=5;step->strategy=2;step->max_torque_mnm=(int32_t)v[0];
        step->angle_threshold_mnm=v[1];step->angle_cdeg=(int32_t)v[2];step->max_angle_cdeg=307199;
    }else if(s[21]==5){
        used=10;
        if(v[0]>1||!v[1]||v[1]>30000||v[2]>30000||v[7]>v[2]||v[3]>v[4]||v[4]>=307200||
           v[5]>30000||!v[6]||v[6]>=307200||v[8]>30000||v[9]>=307200)return 0;
        step->kind=7;step->strategy=(uint8_t)(v[0]+1);step->torque_mnm=(int32_t)v[1];
        step->max_torque_mnm=(int32_t)v[2];step->min_torque_mnm=(int32_t)v[7];
        step->min_angle_cdeg=(int32_t)v[3];step->max_angle_cdeg=(int32_t)v[4];
        step->safe_torque_mnm=v[5];step->angle_cdeg=(int32_t)v[6];step->angle_threshold_mnm=v[8];step->safe_angle_cdeg=v[9];
    }else return 0;
    for(i=used;i<18;i++)if(v[i]!=0)return 0;
    if(step->strategy!=2&&step->torque_mnm<=0)return 0;
    if(step->strategy!=1&&step->angle_cdeg<=0)return 0;
    if((step->strategy==1||step->strategy==4)&&step->safe_angle_cdeg>=307200)return 0;
    return 1;
}

/* 在接受工艺前拒绝只沿失败跳转即可闭合的环。 */
static uint8_t failure_jumps_acyclic(const FpgaProgram *program)
{
    uint8_t start;
    for(start=1;start<=program->count;start++){
        uint16_t visited=0;
        uint8_t step=start;
        while(step!=0){
            uint16_t bit=(uint16_t)(1u<<(step-1u));
            if(visited&bit)return 0;
            visited|=bit;
            step=program->steps[step-1u].failure_jump_step;
        }
    }
    return 1;
}

uint8_t NativePset_Decode(const uint8_t *p,uint16_t length,FpgaProgram *program)
{
    FpgaProgram candidate;uint16_t cursor=3;uint8_t i;
    if(!p||!program||length<4||p[0]==0||p[0]==255||(p[1]!=2&&p[1]!=3)||p[2]==0||p[2]>16)return 0;
    memset(&candidate,0,sizeof(candidate));candidate.pset_no=p[0];candidate.count=p[2];
    if(p[1]==3){
        if(length!=3U+96U*candidate.count)return 0;
        for(i=0;i<candidate.count;i++)if(!hmi_step(p+3U+96U*i,(uint8_t)(i+1),candidate.count,&candidate.steps[i]))return 0;
        if(!failure_jumps_acyclic(&candidate))return 0;
        *program=candidate;return 1;
    }
    for(i=0;i<candidate.count;i++){
        const uint8_t *s;uint16_t size;FpgaProgramStep *step=&candidate.steps[i];
        if((uint32_t)cursor+3>length)return 0;
        s=p+cursor;size=u16(s+1);
        if((uint32_t)cursor+size>length)return 0;
        step->kind=s[0];
        if(s[0]==3){
            unsigned offset;
            if(size!=61||s[3]<1||s[3]>4||s[40]>1||s[47]>1||s[48]>1||s[49]!=1||s[50]!=1||s[55]!=2||s[56]<1||s[56]>2||s[57]!=0)return 0;
            for(offset=4;offset<=36;offset+=4)if(u32(s+offset)>INT32_MAX)return 0;
            step->strategy=s[3];step->torque_mnm=(int32_t)u32(s+4);step->max_torque_mnm=(int32_t)u32(s+8);step->min_torque_mnm=(int32_t)u32(s+12);
            step->angle_threshold_mnm=u32(s+16);step->safe_torque_mnm=u32(s+20);
            step->min_angle_cdeg=(int32_t)u32(s+24);step->max_angle_cdeg=(int32_t)u32(s+28);step->safe_angle_cdeg=u32(s+32);step->angle_cdeg=(int32_t)u32(s+36);
            step->direction=s[40];step->speed_rpm_milli=u32(s+41);step->accel_time_ms=u16(s+45);
            step->torque_value_mode=s[47];step->angle_value_mode=s[48];step->angle_reset=s[49];step->torque_reset=s[50];
            step->timeout_ms=u16(s+51);step->post_delay_ms=u16(s+53);step->failure_action=s[56];
            if(!step->speed_rpm_milli||step->speed_rpm_milli>FPGA_MODEL_MAX_RPM_MILLI||!step->timeout_ms||step->max_torque_mnm>30000||step->min_torque_mnm>step->max_torque_mnm||step->min_angle_cdeg>step->max_angle_cdeg||step->max_angle_cdeg>=307200||step->angle_cdeg>=307200)return 0;
            if(step->strategy!=2 && (step->torque_mnm<=0||step->torque_mnm>30000))return 0;
            if(step->strategy!=1 && step->angle_cdeg<=0)return 0;
            if((step->strategy==1||step->strategy==4) && step->safe_angle_cdeg>=307200)return 0;
            if((step->strategy==2||step->strategy==4) && step->safe_torque_mnm>30000)return 0;
        }else if(s[0]==2){
            /* 36B原生帧不携带扭矩模式所需的安全角度，先仅支持角度模式。 */
            if(size!=36||s[3]!=2||s[18]!=2||s[19]!=1||s[20]!=0||u32(s+24)>=307200||u32(s+28)>30000||u32(s+32)>30000)return 0;
            step->strategy=2;step->speed_rpm_milli=u32(s+4);step->accel_time_ms=u16(s+8);
            step->torque_mnm=(int32_t)u32(s+10);step->timeout_ms=u16(s+14);step->post_delay_ms=u16(s+16);
            step->angle_cdeg=(int32_t)u32(s+24);step->safe_torque_mnm=u32(s+28);step->angle_threshold_mnm=u32(s+32);
            step->angle_reset=1;step->torque_reset=1;step->failure_action=2;step->max_torque_mnm=30000;step->max_angle_cdeg=307199;
            if(!step->speed_rpm_milli||step->speed_rpm_milli>FPGA_MODEL_MAX_RPM_MILLI||!step->timeout_ms||!step->angle_cdeg)return 0;
        }else if(s[0]==5){
            if(size!=26||!u32(s+3)||u32(s+3)>30000||u32(s+7)>30000||!u32(s+11)||u32(s+11)>=307200||s[25]!=2)return 0;
            step->strategy=2;step->direction=1;step->max_torque_mnm=(int32_t)u32(s+3);step->max_angle_cdeg=307199;
            step->angle_threshold_mnm=u32(s+7);step->angle_cdeg=(int32_t)u32(s+11);step->speed_rpm_milli=u32(s+15);step->accel_time_ms=u16(s+19);
            step->timeout_ms=u16(s+21);step->post_delay_ms=u16(s+23);step->failure_action=2;step->angle_reset=1;step->torque_reset=1;
            if(!step->speed_rpm_milli||step->speed_rpm_milli>FPGA_MODEL_MAX_RPM_MILLI||!step->timeout_ms)return 0;
        }else if(s[0]==4){
            if(size!=13||s[3]!=0||s[6]!=0||s[7]!=0||!u16(s+4)||u16(s+4)>5000||u16(s+8)<u16(s+4)||s[12]<1||s[12]>2)return 0;
            step->duration_ms=u16(s+4);step->timeout_ms=u16(s+8);step->post_delay_ms=u16(s+10);step->failure_action=s[12];
        }else return 0;
        cursor=(uint16_t)(cursor+size);
    }
    if(cursor!=length)return 0;
    *program=candidate;return 1;
}
#endif
