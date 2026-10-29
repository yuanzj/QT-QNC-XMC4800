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
/* 0正常，1扭矩NOK，2角度NOK，3超时，4未知故障；在构建清单中标记场景。 */
#ifndef FPGA_SIM_SCENARIO
#define FPGA_SIM_SCENARIO 0
#endif

typedef struct {
    uint8_t kind, direction, failure_action, angle_reset;
    uint32_t duration_ms, timeout_ms;
    int32_t torque_mnm, angle_cdeg;
    int32_t min_torque_mnm, max_torque_mnm, min_angle_cdeg, max_angle_cdeg;
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
    int32_t position_inc, velocity_inc_s, step_origin_inc;
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
