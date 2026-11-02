/* 独立逻辑工具模型：确定性斜坡反馈与工步时序，无SPI、寄存器或电机调用。
 * 仅用于B/C类测试替代；不代表真实FPGA控制算法或物理量精度。 */
#ifndef FPGA_PROGRAM_H
#define FPGA_PROGRAM_H
#include <stdint.h>
#include "fpga_sim.h"

#define FPGA_PROGRAM_MAX_STEPS 16
/* 模拟规格与Windows测试配置一致，仅作为人工模型，不是实物工具档案。 */
#define FPGA_MODEL_ENCODER 8388608LL
#define FPGA_MODEL_GEAR 30LL
#define FPGA_MODEL_FULL_SCALE_MNM 30000LL
/* 0~8为旧C类测试向量；9为独立负载反馈的功能参考模型。 */
#include "../Simulation/model_config.h"
#if FPGA_SIM_SCENARIO == 9
#include "feedback_model.h"
#endif

typedef struct {
    uint8_t kind, direction, failure_action, angle_reset;
    uint32_t duration_ms, timeout_ms;
    int32_t torque_mnm, angle_cdeg;
    int32_t min_torque_mnm, max_torque_mnm, min_angle_cdeg, max_angle_cdeg;
#if FPGA_SIM_SCENARIO == 9
    uint32_t speed_rpm_milli, safe_torque_mnm, safe_angle_cdeg, angle_threshold_mnm;
    uint16_t accel_time_ms, post_delay_ms;
    uint8_t strategy, torque_value_mode, angle_value_mode, torque_reset;
#endif
} FpgaProgramStep;

typedef struct {
    uint8_t pset_no, count;
    FpgaProgramStep steps[FPGA_PROGRAM_MAX_STEPS];
} FpgaProgram;

typedef struct {
    FpgaSimState state;
    FpgaProgram program;
    uint32_t step_started_ms, finished_ms, fault_code;
    uint8_t current_step, result, all_ok, pending_next;
    int16_t torque_raw;
#if FPGA_SIM_INT64
    int32_t position_inc, step_origin_inc;
    int64_t velocity_inc_s;
#else
    int32_t position_inc, velocity_inc_s, step_origin_inc;
#endif
#if FPGA_SIM_SCENARIO == 9
    ModelPlantState plant;
    int64_t angle_gate_q;
    int32_t peak_torque_mnm, peak_angle_cdeg, measured_torque_mnm, measured_angle_cdeg;
    uint32_t last_tick_ms, brake_started_ms, delay_started_ms;
    uint8_t gate_open, braking, completing, torque_hit, angle_hit, step_nok_reason, last_nok_reason;
#endif
} FpgaProgramRun;

void FpgaProgram_Reset(FpgaProgramRun *run);
/* 运行中拒绝替换，失败保持已加载程序。 */
uint8_t FpgaProgram_Load(FpgaProgramRun *run, const FpgaProgram *program);
uint8_t FpgaProgram_Start(FpgaProgramRun *run, uint32_t now_ms, uint8_t permitted);
void FpgaProgram_Stop(FpgaProgramRun *run);
/* 1ms单调时基；联锁优先于同拍成功，步间保留20ms可观察的完成结果。 */
void FpgaProgram_Tick(FpgaProgramRun *run, uint32_t now_ms, uint8_t permitted);
/* 明确拒绝模型原始量越界，不截断或静默饱和。 */
uint8_t FpgaProgram_Convert(int32_t torque_mnm, int32_t angle_cdeg, int16_t *torque, int32_t *position);
#endif
