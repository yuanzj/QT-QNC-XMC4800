/* 场景9功能参考控制器：目标仅用于控制/判定；过程值只来自独立合成接头。
 * 不是客户FPGA实现，也不声称实体安全/精度已验证。测试故障码0x700x仅本模型使用。 */
#include "fpga_program.h"
#if FPGA_SIM_SCENARIO == 9
#include <limits.h>
#include <string.h>
enum { NOK_NONE=0,NOK_TORQUE=1,NOK_ANGLE=2,NOK_TIMEOUT=3,NOK_STOPPED=4,NOK_ENGAGE=5,NOK_START_TORQUE=6 };
static int32_t magnitude(int32_t x){return x<0?-x:x;}
static int64_t step_angle_q(const FpgaProgramRun *r)
{
    return r->gate_open ? r->plant.position_q-r->angle_gate_q : 0;
}
static void publish(FpgaProgramRun *r)
{
    int64_t local_angle_q=step_angle_q(r);
    int64_t angle=local_angle_q/MODEL_ANGLE_Q;
    int64_t process_angle=(r->angle_carry_q+local_angle_q)/MODEL_ANGLE_Q;
    int64_t raw_velocity=(int64_t)r->plant.velocity_rpm_milli*FPGA_MODEL_ENCODER*FPGA_MODEL_GEAR/60000;
    int16_t torque;int32_t position;
#if FPGA_SIM_INT64
    /* 位置失效仍发布独立有效速度，故障后的制动反馈不能冻结在上次采样。 */
    r->velocity_inc_s=raw_velocity;
#endif
    if(angle<INT32_MIN||angle>INT32_MAX||process_angle< -INT32_MAX||process_angle>INT32_MAX||
#if !FPGA_SIM_INT64
       raw_velocity<INT32_MIN||raw_velocity>INT32_MAX||
#endif
       !FpgaProgram_Convert(r->plant.torque_mnm,(int32_t)angle,&torque,&position)){
        r->state=FPGA_SIM_FAULT;r->fault_code=0x7002;r->result=0;r->current_step=0;return;
    }
    r->torque_raw=torque;r->position_inc=position;r->velocity_inc_s=raw_velocity;
    /* PDO位置按DC-15每步归零。工艺累计角度单独保存，扭矩始终取量化实测值。 */
    r->measured_torque_mnm=magnitude((int32_t)torque)*30;
    r->measured_angle_cdeg=magnitude((int32_t)angle);
    r->process_angle_cdeg=magnitude((int32_t)process_angle);
}
static void begin(FpgaProgramRun *r,uint32_t now)
{
    const FpgaProgramStep *s=&r->program.steps[r->current_step-1];
    uint8_t configurable_reset=s->kind==2||s->kind==3;
    r->step_started_ms=now;r->pending_next=0;r->braking=0;r->completing=0;r->step_nok_reason=0;
    r->origin_hold=0;
    r->brake_duration_ms=0;r->brake_initial_velocity_rpm_milli=0;
    if(!configurable_reset||s->angle_reset){r->angle_carry_q=0;r->peak_angle_cdeg=0;}
    else r->angle_carry_q+=step_angle_q(r);
    /* 复位清监控峰值。传感器读数、启动门槛及安全联锁不做带载去皮。 */
    if(!configurable_reset||s->torque_reset)r->carried_torque_peak_mnm=0;
    else if(r->peak_torque_mnm>r->carried_torque_peak_mnm)r->carried_torque_peak_mnm=r->peak_torque_mnm;
    r->peak_torque_mnm=0;
    r->gate_open=s->angle_threshold_mnm==0;r->angle_gate_q=r->plant.position_q;
    r->start_torque_reached=s->kind!=3||s->start_torque_mnm==0;
    r->torque_hit=0;r->angle_hit=0;
    r->search_origin_q=r->plant.position_q;r->search_attempt=1;r->search_waiting=0;r->loosen_armed=0;
    publish(r);
}
void FpgaProgram_Reset(FpgaProgramRun *r)
{
    memset(r,0,sizeof(*r));ModelPlant_Init(&r->plant,FPGA_MODEL_PROFILE);r->state=FPGA_SIM_IDLE;
}
uint8_t FpgaProgram_Load(FpgaProgramRun *r,const FpgaProgram *p)
{
    uint8_t i;
    if(!p||r->state==FPGA_SIM_RUNNING||!r->plant.valid||r->fault_code==FPGA_SIM_TOOL_UNAVAILABLE||
       r->plant.velocity_rpm_milli||!p->count||p->count>16||!p->pset_no)return 0;
    for(i=0;i<p->count;i++)if(p->steps[i].kind!=1&&p->steps[i].kind!=2&&p->steps[i].kind!=3&&p->steps[i].kind!=4&&p->steps[i].kind!=5&&p->steps[i].kind!=7)return 0;
    FpgaProgram_Reset(r);r->program=*p;r->state=FPGA_SIM_READY;return 1;
}
uint8_t FpgaProgram_Start(FpgaProgramRun *r,uint32_t now,uint8_t permitted)
{
    if(!permitted||!r->plant.valid||!r->program.count||r->plant.velocity_rpm_milli||(r->state!=FPGA_SIM_READY&&r->state!=FPGA_SIM_DONE&&r->state!=FPGA_SIM_STOPPED))return 0;
    /* 每次启动显式装入一个新的相同合成试件，工步之间不重置接头。 */
    r->failure_jumps_taken=0;
    r->entry_fault_step=0;
    r->gate_open=0;r->angle_carry_q=0;r->peak_angle_cdeg=0;r->peak_torque_mnm=0;r->carried_torque_peak_mnm=0;
    ModelPlant_Init(&r->plant,FPGA_MODEL_PROFILE);r->state=FPGA_SIM_RUNNING;r->current_step=1;r->result=0;r->all_ok=1;r->fault_code=0;r->last_nok_reason=0;r->last_tick_ms=now;begin(r,now);return 1;
}
void FpgaProgram_Stop(FpgaProgramRun *r)
{
    if(r->fault_code==FPGA_SIM_TOOL_UNAVAILABLE)return;
    r->state=FPGA_SIM_STOPPED;r->current_step=0;r->result=0;r->all_ok=0;r->pending_next=0;r->last_nok_reason=NOK_STOPPED;
    /* 不直接伪造速度=0；后续tick由独立接头模型给出制动速度。 */
}
static void fault(FpgaProgramRun *r,uint32_t code)
{
    r->state=FPGA_SIM_FAULT;r->fault_code=code;r->result=0;r->all_ok=0;r->current_step=0;r->pending_next=0;
}
/* 每个采样按当前工步的保护条件检查，安全值先于工艺窗口。 */
static uint8_t monitor_sample(FpgaProgramRun *r,const FpgaProgramStep *s)
{
    int32_t monitored_angle=r->process_angle_cdeg>r->measured_angle_cdeg?r->process_angle_cdeg:r->measured_angle_cdeg;
    if(r->measured_torque_mnm>r->peak_torque_mnm)r->peak_torque_mnm=r->measured_torque_mnm;
    if(r->process_angle_cdeg>r->peak_angle_cdeg)r->peak_angle_cdeg=r->process_angle_cdeg;
    /* 拧紧按四张图的适用策略；下旋/拧松的两个安全值均为全程上限。 */
    if((s->kind==2||s->kind==7||s->strategy==2||s->strategy==4)&&s->safe_torque_mnm&&r->measured_torque_mnm>=(int32_t)s->safe_torque_mnm)fault(r,0x7005);
    else if((s->kind==2||s->kind==7||s->strategy==1||s->strategy==4)&&s->safe_angle_cdeg&&monitored_angle>=(int32_t)s->safe_angle_cdeg)fault(r,0x7006);
    else if(r->measured_torque_mnm>s->max_torque_mnm)fault(r,0x7007);
    else if(r->gate_open&&monitored_angle>s->max_angle_cdeg)fault(r,0x7008);
    return r->state==FPGA_SIM_RUNNING;
}
static void close_step(FpgaProgramRun *r,uint32_t now)
{
    const FpgaProgramStep *s=&r->program.steps[r->current_step-1];
    uint8_t ok,next=r->current_step<r->program.count?(uint8_t)(r->current_step+1u):0;
    int32_t torque_peak=r->peak_torque_mnm>r->carried_torque_peak_mnm?r->peak_torque_mnm:r->carried_torque_peak_mnm;
    int32_t torque=s->torque_value_mode?r->measured_torque_mnm:torque_peak;
    int32_t angle=s->angle_value_mode?r->process_angle_cdeg:r->peak_angle_cdeg;
    if((s->kind==3||s->kind==7)&&!r->step_nok_reason){
        if(torque<s->min_torque_mnm||torque>s->max_torque_mnm)r->step_nok_reason=NOK_TORQUE;
        else if(angle<s->min_angle_cdeg||angle>s->max_angle_cdeg)r->step_nok_reason=NOK_ANGLE;
    }
    ok=r->step_nok_reason==0;r->result=ok;if(!ok){r->all_ok=0;r->last_nok_reason=r->step_nok_reason;}
    if(!ok&&s->failure_action==2)next=0;
    if(!ok&&s->failure_action==3){
        uint16_t bit=(uint16_t)(1u<<(r->current_step-1u));
        next=s->failure_jump_step;
        /* 成功顺序与失败回跳也可能形成环。每条失败跳转在一颗中最多执行一次。 */
        if(next==0||next>r->program.count||next==r->current_step||(r->failure_jumps_taken&bit)){
            fault(r,FPGA_SIM_INVALID_FAILURE_JUMP);return;
        }
        r->failure_jumps_taken|=bit;
    }
    r->finished_ms=now;
    if(next==0){r->state=FPGA_SIM_DONE;r->current_step=0;r->result=r->all_ok;}
    else r->pending_next=next;
}
static void complete_after_delay(FpgaProgramRun *r,uint32_t now)
{
    const FpgaProgramStep *s=&r->program.steps[r->current_step-1];
    if(!r->completing){r->completing=1;r->delay_started_ms=now;}
    if((uint32_t)(now-r->delay_started_ms)>=s->post_delay_ms)close_step(r,now);
}
/* 正常结束的速度指令斜坡；零参数沿用原自然制动，停止/故障不经此慢斜坡。 */
static void begin_braking(FpgaProgramRun *r,uint32_t now)
{
    const FpgaProgramStep *s=&r->program.steps[r->current_step-1];
    uint32_t speed,natural;
    r->braking=1;r->brake_started_ms=now;
    r->brake_initial_velocity_rpm_milli=(int32_t)((int64_t)r->velocity_inc_s*60000/(FPGA_MODEL_ENCODER*FPGA_MODEL_GEAR));
    speed=(uint32_t)magnitude(r->brake_initial_velocity_rpm_milli);
    r->brake_duration_ms=0;
    if(!s->decel_time_ms||!speed)return;
    /* 时间按本步设定转速定义；未加速到设定转速时，维持同一减速梯度。 */
    r->brake_duration_ms=(uint32_t)(((uint64_t)speed*s->decel_time_ms+s->speed_rpm_milli-1)/s->speed_rpm_milli);
    natural=(speed+(uint32_t)r->plant.config.brake_rpm_milli_per_ms-1)/(uint32_t)r->plant.config.brake_rpm_milli_per_ms;
    if(r->brake_duration_ms<natural)r->brake_duration_ms=natural;
}
/* 扭矩来自同一固定接头；动作角度只决定每次搜索何时制动，不生成“套上”反馈。 */
static void engage_tick(FpgaProgramRun *r,const FpgaProgramStep *s,uint32_t now)
{
    int64_t distance=r->plant.position_q-r->search_origin_q;
    if(distance<0)distance=-distance;
    if(!r->braking){
        if(r->measured_torque_mnm>=s->torque_mnm){r->torque_hit=1;begin_braking(r,now);}
        else if(distance>=(int64_t)s->angle_cdeg*MODEL_ANGLE_Q)begin_braking(r,now);
    }
    if(!r->braking||r->plant.velocity_rpm_milli!=0)return;
    if(r->torque_hit){complete_after_delay(r,now);return;}
    if(r->search_attempt>=s->engage_repeat_count){r->step_nok_reason=NOK_ENGAGE;complete_after_delay(r,now);return;}
    if(!r->search_waiting){r->search_waiting=1;r->retry_started_ms=now;}
    if((uint32_t)(now-r->retry_started_ms)>=s->engage_repeat_delay_ms){
        ++r->search_attempt;r->search_origin_q=r->plant.position_q;r->search_waiting=0;r->braking=0;
    }
}
/* 下旋按实测峰值触发单向降速。提前刹车按剩余扭矩渐减，保留最低正向速度直到目标或保护停机。 */
static uint32_t rundown_speed(const FpgaProgramRun *r,const FpgaProgramStep *s)
{
    uint32_t speed=s->speed_rpm_milli;
    uint32_t peak=(uint32_t)r->peak_torque_mnm;
    uint32_t shift=(uint32_t)(FPGA_MODEL_FULL_SCALE_MNM*s->auto_sensitivity/1000U);
    uint32_t reduced=(uint32_t)(FPGA_MODEL_MAX_RPM_MILLI*s->speed_adjust_ratio/1000U);
    uint32_t target=(uint32_t)s->torque_mnm;
    uint32_t brake_at=(target*s->target_brake_ratio+999U)/1000U;
    if(peak>=shift&&reduced<speed)speed=reduced;
    if(brake_at<target&&peak>brake_at){
        uint32_t remaining=peak<target?target-peak:0;
        uint32_t crawl=speed<100U?speed:100U;
        speed=crawl+(uint32_t)((uint64_t)(speed-crawl)*remaining/(target-brake_at));
    }
    return speed;
}

static void tick_one(FpgaProgramRun *r,uint32_t now,uint32_t publish_now,uint8_t permitted)
{
    const FpgaProgramStep *s;int32_t command=0;uint32_t elapsed;uint8_t complete=0;
    if(!r->plant.valid||r->fault_code==FPGA_SIM_TOOL_UNAVAILABLE){
        ModelPlant_Tick(&r->plant,0,0,0);
        publish(r);
        fault(r,FPGA_SIM_TOOL_UNAVAILABLE);
        return;
    }
    if(r->state!=FPGA_SIM_RUNNING){
        /* 最终工步与中间工步共用结果窗口。零速保持期间仍由接头模型提供带载反馈，
         * 补跑时钟拍也不能把窗口后的卸载衰减归给已经结束的工步。 */
        uint8_t hold_load=r->state==FPGA_SIM_DONE&&
                          (uint32_t)(now-r->finished_ms)<FPGA_STEP_RESULT_WINDOW_MS;
        ModelPlant_Tick(&r->plant,0,0,hold_load);
        publish(r);
        return;
    }
    if(!permitted){fault(r,0x7004);ModelPlant_Tick(&r->plant,0,0,0);publish(r);return;}
    s=&r->program.steps[r->current_step-1];
    if(r->pending_next){
        ModelPlant_Tick(&r->plant,0,0,1);publish(r);
        if((uint32_t)(now-r->finished_ms)>=FPGA_STEP_RESULT_WINDOW_MS){
            r->current_step=r->pending_next;
            begin(r,now);
            if(r->program.steps[r->current_step-1].kind!=4){
                /* 从本次对外发布计时，补跑时钟拍不消耗零位观察窗口。 */
                r->origin_hold=1;
                r->step_started_ms=publish_now+FPGA_STEP_ORIGIN_WINDOW_MS;
            }
        }
        return;
    }
    elapsed=now-r->step_started_ms;
    /* 有限补跑范围内，先于预定起动时刻的无符号差落在高半区。 */
    uint8_t waiting_for_origin=r->origin_hold&&(elapsed==0U||elapsed>UINT32_MAX/2U);
    /* 零位等待时照常检查带载保护，实际第一拍运动仍先检查入口值。 */
    if((waiting_for_origin||elapsed==1U)&&s->kind!=4){
        uint8_t step=r->current_step;
        if(!monitor_sample(r,s)){
            r->entry_fault_step=step;
            return;
        }
    }
    if(waiting_for_origin){
        ModelPlant_Tick(&r->plant,0,0,1);
        publish(r);
        return;
    }
    r->origin_hold=0;
    /* 非零慢斜坡不能让运动超时失效；超时立即改用原夹具自然制动并保留NOK。 */
    if(s->kind!=1&&s->decel_time_ms&&r->braking&&!r->completing&&elapsed>=s->timeout_ms)r->step_nok_reason=NOK_TIMEOUT;
    if(s->kind!=4&&!r->braking){
        uint8_t reverse=s->direction;
        int32_t speed=(int32_t)(s->kind==2&&s->auto_adjust?rundown_speed(r,s):s->speed_rpm_milli);
        if(s->kind==1)reverse=(uint8_t)((s->direction&1U)^((s->direction>=2U)&&((r->search_attempt&1U)==0U)));
        command=reverse?-speed:speed;
    }else if(r->braking&&s->decel_time_ms&&r->step_nok_reason!=NOK_TIMEOUT&&r->brake_duration_ms){
        uint32_t braking_elapsed=now-r->brake_started_ms;
        if(braking_elapsed<r->brake_duration_ms)command=(int32_t)((int64_t)r->brake_initial_velocity_rpm_milli*(r->brake_duration_ms-braking_elapsed)/r->brake_duration_ms);
    }
    ModelPlant_Tick(&r->plant,command,(r->braking&&s->decel_time_ms)?0:s->accel_time_ms,1);publish(r);if(r->state!=FPGA_SIM_RUNNING)return;
    if(s->kind!=4){
        if(!r->gate_open && (s->kind==5 ? r->measured_torque_mnm<=(int32_t)s->angle_threshold_mnm : r->measured_torque_mnm>=(int32_t)s->angle_threshold_mnm)){r->gate_open=1;r->angle_gate_q=r->plant.position_q;publish(r);}
        if(!monitor_sample(r,s))return;
    }
    elapsed=now-r->step_started_ms;
    if(s->kind==1){engage_tick(r,s,now);return;}
    if(s->kind==4){if(elapsed>=s->duration_ms)complete_after_delay(r,now);return;}
    if(!r->braking){
        if(s->kind==3&&(uint32_t)r->measured_torque_mnm>=s->start_torque_mnm)r->start_torque_reached=1;
        if(r->measured_torque_mnm>=s->torque_mnm)r->torque_hit=1;
        if(r->gate_open&&r->process_angle_cdeg>=s->angle_cdeg)r->angle_hit=1;
        if(s->kind==7&&s->strategy==1){
            /* 先有载再松脱；110%回差为本参考控制器明确选定的行业实现口径。 */
            if(r->measured_torque_mnm>=(int32_t)(((uint32_t)s->torque_mnm*11U+9U)/10U))r->loosen_armed=1;
            complete=r->loosen_armed&&r->measured_torque_mnm<s->torque_mnm;
        }else switch(s->strategy){case 1:complete=r->torque_hit;break;case 2:complete=r->angle_hit;break;case 3:complete=r->torque_hit||r->angle_hit;break;case 4:complete=r->torque_hit&&r->angle_hit;break;default:fault(r,0x7009);return;}
        if(elapsed>=s->timeout_ms){r->step_nok_reason=NOK_TIMEOUT;complete=1;}
        else if(complete&&!r->start_torque_reached)r->step_nok_reason=NOK_START_TORQUE;
        if(complete)begin_braking(r,now);
    }
    if(r->braking && r->plant.velocity_rpm_milli==0)complete_after_delay(r,now);
}
void FpgaProgram_Tick(FpgaProgramRun *r,uint32_t now,uint8_t permitted)
{
    uint32_t delta=now-r->last_tick_ms;
    /* 不把暂停调试器/漏时基伪装为正常高速完成；上限与证据一起声明。 */
    if(delta>1000){if(r->state==FPGA_SIM_RUNNING)fault(r,0x700A);r->last_tick_ms=now;return;}
    while(delta--){++r->last_tick_ms;tick_one(r,r->last_tick_ms,now,permitted);}
}
#endif
