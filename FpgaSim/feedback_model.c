/* 参考行业接头扭矩-转角阶段的合成输入，不是经实物辨识的电机/接头数字孪生。 */
#include "feedback_model.h"
#include <string.h>
static int32_t absolute(int32_t x) { return x < 0 ? -x : x; }
void ModelPlant_Init(ModelPlantState *p, uint8_t profile)
{
    memset(p,0,sizeof(*p));
    if(profile<1||profile>4)return;
    p->valid=1;p->last_direction=1;
    p->config.seat_angle_cdeg=36000; p->config.drag_mnm=200;
    p->config.stiffness_mnm_per_deg=profile==2 ? 10 : 1000;
    p->config.capacity_mnm=30000; p->config.brake_rpm_milli_per_ms=2000;
    p->config.free_run=profile==3; p->config.jam=profile==4;
}
void ModelPlant_Tick(ModelPlantState *p, int32_t command, uint16_t accel_ms, uint8_t active)
{
    int32_t delta; int64_t torque, after_seat;
    if(!p->valid)return;
    if (!active) command=0;
    if (command==0) delta=p->config.brake_rpm_milli_per_ms;
    else delta=accel_ms ? (absolute(command)+(int32_t)accel_ms-1)/(int32_t)accel_ms : 1000000;
    if (p->velocity_rpm_milli < command) {
        int64_t v=(int64_t)p->velocity_rpm_milli+delta;
        p->velocity_rpm_milli=v>command?command:(int32_t)v;
    } else if(p->velocity_rpm_milli>command) {
        int64_t v=(int64_t)p->velocity_rpm_milli-delta;
        p->velocity_rpm_milli=v<command?command:(int32_t)v;
    }
    if(p->velocity_rpm_milli>0)p->last_direction=1;
    else if(p->velocity_rpm_milli<0)p->last_direction=-1;
    p->position_q+=(int64_t)p->velocity_rpm_milli*3*MODEL_ANGLE_Q/5000;
    if(p->config.jam && p->position_q>=500*MODEL_ANGLE_Q) {
        p->position_q=500*MODEL_ANGLE_Q;p->velocity_rpm_milli=0;
        p->torque_mnm=active && command ? p->config.capacity_mnm : 0;
        return;
    }
    after_seat=p->position_q-(int64_t)p->config.seat_angle_cdeg*MODEL_ANGLE_Q;
    torque=p->config.drag_mnm;
    if(after_seat>0 && !p->config.free_run)
        torque+=after_seat*p->config.stiffness_mnm_per_deg/(100*MODEL_ANGLE_Q);
    /* 超出合成驱动容量即停转，保留实际计算值，不静默夹成30Nm。 */
    if(torque>=p->config.capacity_mnm)p->velocity_rpm_milli=0;
    if(p->last_direction<0) torque=-torque;
    if(!active && p->velocity_rpm_milli==0) {
        /* 卸载变化由夹具常量决定，不按目标值生成结束读数。 */
        int32_t decay=1000;
        if(p->torque_mnm>decay)p->torque_mnm-=decay;
        else if(p->torque_mnm< -decay)p->torque_mnm+=decay;
        else p->torque_mnm=0;
    } else p->torque_mnm=(int32_t)torque;
}
