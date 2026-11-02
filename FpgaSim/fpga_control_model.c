/* 场景9功能参考控制器：目标仅用于控制/判定；过程值只来自独立合成接头。
 * 不是客户FPGA实现，也不声称实体安全/精度已验证。测试故障码0x700x仅本模型使用。 */
#include "fpga_program.h"
#if FPGA_SIM_SCENARIO == 9
#include <limits.h>
#include <string.h>
enum { NOK_NONE=0,NOK_TORQUE=1,NOK_ANGLE=2,NOK_TIMEOUT=3,NOK_STOPPED=4 };
static int32_t magnitude(int32_t x){return x<0?-x:x;}
static void publish(FpgaProgramRun *r)
{
    int64_t angle=r->gate_open?(r->plant.position_q-r->angle_gate_q)/(MODEL_ANGLE_Q):0;
    int64_t raw_velocity=(int64_t)r->plant.velocity_rpm_milli*FPGA_MODEL_ENCODER*FPGA_MODEL_GEAR/60000;
    int16_t torque;int32_t position;
#if FPGA_SIM_INT64
    /* 位置失效仍发布独立有效速度，故障后的制动反馈不能冻结在上次采样。 */
    r->velocity_inc_s=raw_velocity;
#endif
    if(angle<INT32_MIN||angle>INT32_MAX||
#if !FPGA_SIM_INT64
       raw_velocity<INT32_MIN||raw_velocity>INT32_MAX||
#endif
       !FpgaProgram_Convert(r->plant.torque_mnm,(int32_t)angle,&torque,&position)){
        r->state=FPGA_SIM_FAULT;r->fault_code=0x7002;r->result=0;r->current_step=0;return;
    }
    r->torque_raw=torque;r->position_inc=position;r->velocity_inc_s=raw_velocity;
    /* 控制器读取与PDO相同的量化传感量，避免潜在值达标但上报值未达标。 */
    r->measured_torque_mnm=magnitude((int32_t)torque)*30;
    r->measured_angle_cdeg=magnitude((int32_t)angle);
}
static void begin(FpgaProgramRun *r,uint32_t now)
{
    const FpgaProgramStep *s=&r->program.steps[r->current_step-1];
    r->step_started_ms=now;r->pending_next=0;r->braking=0;r->completing=0;r->step_nok_reason=0;
    r->gate_open=s->angle_threshold_mnm==0;r->angle_gate_q=r->plant.position_q;
    r->peak_torque_mnm=0;r->peak_angle_cdeg=0;r->torque_hit=0;r->angle_hit=0;
    publish(r);
}
void FpgaProgram_Reset(FpgaProgramRun *r)
{
    memset(r,0,sizeof(*r));ModelPlant_Init(&r->plant,FPGA_MODEL_PROFILE);r->state=FPGA_SIM_IDLE;
}
uint8_t FpgaProgram_Load(FpgaProgramRun *r,const FpgaProgram *p)
{
    uint8_t i;
    if(!p||r->state==FPGA_SIM_RUNNING||r->plant.velocity_rpm_milli||!p->count||p->count>16||!p->pset_no)return 0;
    for(i=0;i<p->count;i++)if(p->steps[i].kind!=2&&p->steps[i].kind!=3&&p->steps[i].kind!=4&&p->steps[i].kind!=5)return 0;
    FpgaProgram_Reset(r);r->program=*p;r->state=FPGA_SIM_READY;return 1;
}
uint8_t FpgaProgram_Start(FpgaProgramRun *r,uint32_t now,uint8_t permitted)
{
    if(!permitted||!r->plant.valid||!r->program.count||r->plant.velocity_rpm_milli||(r->state!=FPGA_SIM_READY&&r->state!=FPGA_SIM_DONE&&r->state!=FPGA_SIM_STOPPED))return 0;
    /* 每次启动显式装入一个新的相同合成试件，工步之间不重置接头。 */
    ModelPlant_Init(&r->plant,FPGA_MODEL_PROFILE);r->state=FPGA_SIM_RUNNING;r->current_step=1;r->result=0;r->all_ok=1;r->fault_code=0;r->last_nok_reason=0;r->last_tick_ms=now;begin(r,now);return 1;
}
void FpgaProgram_Stop(FpgaProgramRun *r)
{
    r->state=FPGA_SIM_STOPPED;r->current_step=0;r->result=0;r->all_ok=0;r->pending_next=0;r->last_nok_reason=NOK_STOPPED;
    /* 不直接伪造速度=0；后续tick由独立接头模型给出制动速度。 */
}
static void fault(FpgaProgramRun *r,uint32_t code)
{
    r->state=FPGA_SIM_FAULT;r->fault_code=code;r->result=0;r->all_ok=0;r->current_step=0;r->pending_next=0;
}
static void close_step(FpgaProgramRun *r,uint32_t now)
{
    const FpgaProgramStep *s=&r->program.steps[r->current_step-1];uint8_t ok;
    int32_t torque=s->torque_value_mode?r->measured_torque_mnm:r->peak_torque_mnm;
    int32_t angle=s->angle_value_mode?r->measured_angle_cdeg:r->peak_angle_cdeg;
    if(s->kind==3&&!r->step_nok_reason){
        if(torque<s->min_torque_mnm||torque>s->max_torque_mnm)r->step_nok_reason=NOK_TORQUE;
        else if(angle<s->min_angle_cdeg||angle>s->max_angle_cdeg)r->step_nok_reason=NOK_ANGLE;
    }
    ok=r->step_nok_reason==0;r->result=ok;if(!ok){r->all_ok=0;r->last_nok_reason=r->step_nok_reason;}
    if((!ok&&s->failure_action==2)||r->current_step==r->program.count){r->state=FPGA_SIM_DONE;r->current_step=0;r->result=r->all_ok;}
    else{r->pending_next=1;r->finished_ms=now;}
}
static void complete_after_delay(FpgaProgramRun *r,uint32_t now)
{
    const FpgaProgramStep *s=&r->program.steps[r->current_step-1];
    if(!r->completing){r->completing=1;r->delay_started_ms=now;}
    if((uint32_t)(now-r->delay_started_ms)>=s->post_delay_ms)close_step(r,now);
}
static void tick_one(FpgaProgramRun *r,uint32_t now,uint8_t permitted)
{
    const FpgaProgramStep *s;int32_t command=0;uint32_t elapsed;uint8_t complete=0;
    if(!r->plant.valid){fault(r,0x700B);return;}
    if(r->state!=FPGA_SIM_RUNNING){ModelPlant_Tick(&r->plant,0,0,0);publish(r);return;}
    if(!permitted){fault(r,0x7004);ModelPlant_Tick(&r->plant,0,0,0);publish(r);return;}
    s=&r->program.steps[r->current_step-1];
    if(r->pending_next){
        ModelPlant_Tick(&r->plant,0,0,1);publish(r);
        if((uint32_t)(now-r->finished_ms)>=20U){++r->current_step;begin(r,now);}return;
    }
    if(s->kind!=4&&!r->braking)command=s->direction?-(int32_t)s->speed_rpm_milli:(int32_t)s->speed_rpm_milli;
    ModelPlant_Tick(&r->plant,command,s->accel_time_ms,1);publish(r);if(r->state!=FPGA_SIM_RUNNING)return;
    if(s->kind!=4){
        if(!r->gate_open && (s->kind==5 ? r->measured_torque_mnm<=(int32_t)s->angle_threshold_mnm : r->measured_torque_mnm>=(int32_t)s->angle_threshold_mnm)){r->gate_open=1;r->angle_gate_q=r->plant.position_q;publish(r);}
        if(r->measured_torque_mnm>r->peak_torque_mnm)r->peak_torque_mnm=r->measured_torque_mnm;
        if(r->measured_angle_cdeg>r->peak_angle_cdeg)r->peak_angle_cdeg=r->measured_angle_cdeg;
        /* 安全边界按客户四张图的适用策略监测；OR没有这两项。 */
        if((s->strategy==2||s->strategy==4)&&s->safe_torque_mnm&&r->measured_torque_mnm>=(int32_t)s->safe_torque_mnm){fault(r,0x7005);return;}
        if((s->strategy==1||s->strategy==4)&&s->safe_angle_cdeg&&r->measured_angle_cdeg>=(int32_t)s->safe_angle_cdeg){fault(r,0x7006);return;}
        if(r->measured_torque_mnm>s->max_torque_mnm){fault(r,0x7007);return;}
        if(r->gate_open&&r->measured_angle_cdeg>s->max_angle_cdeg){fault(r,0x7008);return;}
    }
    elapsed=now-r->step_started_ms;
    if(s->kind==4){if(elapsed>=s->duration_ms)complete_after_delay(r,now);return;}
    if(!r->braking){
        if(r->measured_torque_mnm>=s->torque_mnm)r->torque_hit=1;
        if(r->gate_open&&r->measured_angle_cdeg>=s->angle_cdeg)r->angle_hit=1;
        switch(s->strategy){case 1:complete=r->torque_hit;break;case 2:complete=r->angle_hit;break;case 3:complete=r->torque_hit||r->angle_hit;break;case 4:complete=r->torque_hit&&r->angle_hit;break;default:fault(r,0x7009);return;}
        if(elapsed>=s->timeout_ms){r->step_nok_reason=NOK_TIMEOUT;complete=1;}
        if(complete){r->braking=1;r->brake_started_ms=now;}
    }
    if(r->braking && r->plant.velocity_rpm_milli==0)complete_after_delay(r,now);
}
void FpgaProgram_Tick(FpgaProgramRun *r,uint32_t now,uint8_t permitted)
{
    uint32_t delta=now-r->last_tick_ms;
    /* 不把暂停调试器/漏时基伪装为正常高速完成；上限与证据一起声明。 */
    if(delta>1000){if(r->state==FPGA_SIM_RUNNING)fault(r,0x700A);r->last_tick_ms=now;return;}
    while(delta--){++r->last_tick_ms;tick_one(r,r->last_tick_ms,permitted);}
}
#endif
