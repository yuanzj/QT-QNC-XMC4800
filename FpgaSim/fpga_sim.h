/* 最小FPGA逻辑模拟：只接收等待任务，不依赖EtherCAT、SPI、寄存器或电机。 */
#ifndef FPGA_SIM_H
#define FPGA_SIM_H
#include <stdint.h>

typedef enum { FPGA_SIM_IDLE, FPGA_SIM_READY, FPGA_SIM_RUNNING,
               FPGA_SIM_DONE, FPGA_SIM_STOPPED, FPGA_SIM_FAULT } FpgaSimState;
typedef struct {
    FpgaSimState state;
    uint32_t started_ms;
    uint16_t duration_ms;
    uint8_t result;
} FpgaSim;

/* 清除任务和结果；调用者负责保留通信层的最后接收摘要。 */
void FpgaSim_Reset(FpgaSim *sim);
/* 仅支持1..5000ms的等待，运行中拒绝替换，失败不修改当前任务。 */
uint8_t FpgaSim_LoadWait(FpgaSim *sim, uint16_t duration_ms);
/* 必须有有效任务、总线OP且控制器无报警/初始化联锁。 */
uint8_t FpgaSim_Start(FpgaSim *sim, uint32_t now_ms, uint8_t permitted);
/* 停止优先于计时完成，停止后结果为失败。 */
void FpgaSim_Stop(FpgaSim *sim);
/* 单调毫秒时基；失去许可先中止，不会在同一拍报告成功。 */
void FpgaSim_Tick(FpgaSim *sim, uint32_t now_ms, uint8_t permitted);
#endif
