/* 确定性工具反馈模型：执行次数、启停、联锁和失败处理可验证，控制算法仍待真实FPGA。 */
#include "fpga_program.h"
#include <limits.h>
#include <string.h>

uint8_t FpgaProgram_Convert(int32_t torque_mnm, int32_t angle_cdeg, int16_t *torque, int32_t *position)
{
    int64_t t = (int64_t)torque_mnm * 1000 / FPGA_MODEL_FULL_SCALE_MNM;
    int64_t a = (int64_t)angle_cdeg * FPGA_MODEL_ENCODER * FPGA_MODEL_GEAR / 36000;
    if (t < INT16_MIN || t > INT16_MAX || a < INT32_MIN || a > INT32_MAX) return 0;
    *torque = (int16_t)t;
    *position = (int32_t)a;
    return 1;
}

void FpgaProgram_Reset(FpgaProgramRun *run)
{
    memset(run, 0, sizeof(*run));
    run->state = FPGA_SIM_IDLE;
}

uint8_t FpgaProgram_Load(FpgaProgramRun *run, const FpgaProgram *program)
{
    if (run->state == FPGA_SIM_RUNNING || program->count == 0 ||
        program->count > FPGA_PROGRAM_MAX_STEPS || program->pset_no == 0) return 0;
    FpgaProgram_Reset(run);
    run->program = *program;
    run->state = FPGA_SIM_READY;
    return 1;
}

static void begin_step(FpgaProgramRun *run, uint32_t now_ms)
{
    const FpgaProgramStep *step = &run->program.steps[run->current_step - 1];
    run->step_started_ms = now_ms;
    /* native 0x220D是最近完成工步结果：切换新工步时保留，供UIO边沿收口。 */
    run->pending_next = 0;
    run->step_origin_inc = step->angle_reset ? 0 : run->position_inc;
    run->position_inc = run->step_origin_inc;
    run->torque_raw = 0;
}

uint8_t FpgaProgram_Start(FpgaProgramRun *run, uint32_t now_ms, uint8_t permitted)
{
    if (!permitted || run->program.count == 0 ||
        (run->state != FPGA_SIM_READY && run->state != FPGA_SIM_DONE && run->state != FPGA_SIM_STOPPED)) return 0;
    run->state = FPGA_SIM_RUNNING;
    run->current_step = 1;
    run->result = 0;
    run->all_ok = 1;
    run->fault_code = 0;
    run->position_inc = 0;
    begin_step(run, now_ms);
    return 1;
}

void FpgaProgram_Stop(FpgaProgramRun *run)
{
    run->state = FPGA_SIM_STOPPED;
    run->current_step = 0;
    run->result = 0;
    run->pending_next = 0;
    run->velocity_inc_s = 0;
}

static void fault(FpgaProgramRun *run, uint32_t code)
{
    run->state = FPGA_SIM_FAULT;
    run->fault_code = code;
    run->result = 0;
    run->current_step = 0;
    run->velocity_inc_s = 0;
}

#if FPGA_SIM_SCENARIO == 5
/* C类原始PDO位置输入：不做有符号溢出运算，不改变参数、故障或启停判定。
 * 单步拧紧在300ms从一侧边界跳到另一侧；多步在工步边界切换符号。
 * 非拧紧步置0用于跨步归零对照，速度置0避免把跳变当物理运动。 */
static void inject_position_vector(FpgaProgramRun *run, const FpgaProgramStep *step, uint32_t elapsed)
{
    int32_t position = 2147483000L;
    if (step->kind != 3) position = 0;
    else {
        if (step->direction == 1) position = -position;
        if (run->program.count == 1 && elapsed >= 300) position = -position;
    }
    run->position_inc = position;
    run->velocity_inc_s = 0;
}
#endif

void FpgaProgram_Tick(FpgaProgramRun *run, uint32_t now_ms, uint8_t permitted)
{
    const FpgaProgramStep *step;
    uint32_t elapsed, duration;
    int32_t torque_mnm, angle_cdeg, position;
    int16_t torque;
    uint8_t ok = 1;
    int64_t final_position;
    if (run->state != FPGA_SIM_RUNNING) return;
    if (!permitted) { fault(run, 3); return; }
    if (run->pending_next) {
        if ((uint32_t)(now_ms - run->finished_ms) < 20) return;
        ++run->current_step;
        begin_step(run, now_ms);
    }
    step = &run->program.steps[run->current_step - 1];
    elapsed = now_ms - run->step_started_ms;
    duration = step->duration_ms;
    torque_mnm = step->torque_mnm;
    angle_cdeg = step->angle_cdeg;
    if (step->kind == 3) {
        if ((FPGA_SIM_SCENARIO == 1 && step->max_torque_mnm > INT32_MAX - 1000) ||
            (FPGA_SIM_SCENARIO == 2 && step->max_angle_cdeg > INT32_MAX - 100)) {
            fault(run, 0x7002); return;
        }
        if (FPGA_SIM_SCENARIO == 1) torque_mnm = step->max_torque_mnm + 1000;
        if (FPGA_SIM_SCENARIO == 2) angle_cdeg = step->max_angle_cdeg + 100;
        if (FPGA_SIM_SCENARIO == 3 && step->timeout_ms) duration = step->timeout_ms + 1;
        if (FPGA_SIM_SCENARIO == 4 && elapsed >= 100) { fault(run, 0x7001); return; }
#if FPGA_SIM_SCENARIO == 6
        /* C类对照：先在活动工步保持故障20ms，再以与场景4相同的失败边沿收口。
         * 只改变测试故障的出现时刻，不把UIO漏码通过延迟默认模型来掩盖。 */
        if (elapsed >= 100) {
            run->fault_code = 0x7001;
            if (elapsed >= 120) { fault(run, 0x7001); return; }
        }
#endif
        ok = torque_mnm >= step->min_torque_mnm && torque_mnm <= step->max_torque_mnm &&
             angle_cdeg >= step->min_angle_cdeg && angle_cdeg <= step->max_angle_cdeg;
    }
    if (step->direction == 1) { torque_mnm = -torque_mnm; angle_cdeg = -angle_cdeg; }
    if (!FpgaProgram_Convert(torque_mnm, angle_cdeg, &torque, &position)) {
        fault(run, 0x7002); return;
    }
    final_position = (int64_t)run->step_origin_inc + position;
    if (final_position < INT32_MIN || final_position > INT32_MAX || duration == 0) {
        fault(run, 0x7002); return;
    }
    if (step->timeout_ms && elapsed >= step->timeout_ms && duration > step->timeout_ms) {
        ok = 0;
        duration = step->timeout_ms;
    }
    {
        uint32_t progress = elapsed < duration ? elapsed : duration;
        int64_t velocity = (int64_t)position * 1000 / duration;
        if (velocity < INT32_MIN || velocity > INT32_MAX) { fault(run, 0x7002); return; }
        run->torque_raw = (int16_t)((int64_t)torque * progress / duration);
        run->position_inc = (int32_t)((int64_t)run->step_origin_inc + (int64_t)position * progress / duration);
        run->velocity_inc_s = elapsed < duration ? (int32_t)velocity : 0;
    }
#if FPGA_SIM_SCENARIO == 5
    inject_position_vector(run, step, elapsed);
#endif
    if (elapsed < duration) return;
    run->result = ok;
    if (!ok) run->all_ok = 0;
    if ((!ok && step->failure_action == 2) || run->current_step == run->program.count) {
        run->state = FPGA_SIM_DONE;
        run->current_step = 0;
        run->result = run->all_ok;
    } else {
        run->pending_next = 1;
        run->finished_ms = now_ms;
    }
}
