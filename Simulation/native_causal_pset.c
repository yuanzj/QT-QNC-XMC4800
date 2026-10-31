/* 严格接入场景9已实现的原生拧紧/WAIT；未实现的工步、自动调节和复位组合明确拒绝。 */
#include "native_pset.h"
#if FPGA_SIM_SCENARIO == 9
#include <limits.h>
#include <string.h>
static uint16_t u16(const uint8_t *p){return (uint16_t)(p[0]|((uint16_t)p[1]<<8));}
static uint32_t u32(const uint8_t *p){return p[0]|((uint32_t)p[1]<<8)|((uint32_t)p[2]<<16)|((uint32_t)p[3]<<24);}
uint8_t NativePset_Decode(const uint8_t *p,uint16_t length,FpgaProgram *program)
{
    FpgaProgram candidate;uint16_t cursor=3;uint8_t i;
    if(!p||!program||length<4||p[0]==0||p[0]==255||p[1]!=2||p[2]==0||p[2]>16)return 0;
    memset(&candidate,0,sizeof(candidate));candidate.pset_no=p[0];candidate.count=p[2];
    for(i=0;i<candidate.count;i++){
        const uint8_t *s;uint16_t size;FpgaProgramStep *step=&candidate.steps[i];
        if((uint32_t)cursor+3>length)return 0;s=p+cursor;size=u16(s+1);
        if((uint32_t)cursor+size>length)return 0;step->kind=s[0];
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
            if(!step->speed_rpm_milli||step->speed_rpm_milli>500000||!step->timeout_ms||step->max_torque_mnm>30000||step->min_torque_mnm>step->max_torque_mnm||step->min_angle_cdeg>step->max_angle_cdeg||step->max_angle_cdeg>=307200||step->angle_cdeg>=307200)return 0;
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
            if(!step->speed_rpm_milli||step->speed_rpm_milli>500000||!step->timeout_ms||!step->angle_cdeg)return 0;
        }else if(s[0]==5){
            if(size!=26||!u32(s+3)||u32(s+3)>30000||u32(s+7)>30000||!u32(s+11)||u32(s+11)>=307200||s[25]!=2)return 0;
            step->strategy=2;step->direction=1;step->max_torque_mnm=(int32_t)u32(s+3);step->max_angle_cdeg=307199;
            step->angle_threshold_mnm=u32(s+7);step->angle_cdeg=(int32_t)u32(s+11);step->speed_rpm_milli=u32(s+15);step->accel_time_ms=u16(s+19);
            step->timeout_ms=u16(s+21);step->post_delay_ms=u16(s+23);step->failure_action=2;step->angle_reset=1;step->torque_reset=1;
            if(!step->speed_rpm_milli||step->speed_rpm_milli>500000||!step->timeout_ms)return 0;
        }else if(s[0]==4){
            if(size!=13||s[3]!=0||s[6]!=0||s[7]!=0||!u16(s+4)||u16(s+4)>5000||u16(s+8)<u16(s+4)||s[12]<1||s[12]>2)return 0;
            step->duration_ms=u16(s+4);step->timeout_ms=u16(s+8);step->post_delay_ms=u16(s+10);step->failure_action=s[12];
        }else return 0;
        cursor=(uint16_t)(cursor+size);
    }
    if(cursor!=length)return 0;*program=candidate;return 1;
}
#endif
