/* EtherCAT对象字典到逻辑FPGA模拟模块的接入点，非物理SPI协议。 */
#ifndef SIMULATION_ETHERCAT_ADAPTER_H
#define SIMULATION_ETHERCAT_ADAPTER_H
#include <stdint.h>
#include "model_config.h"
/* 只读调试追踪，不进PDO/SDO，也不参与接头反馈、控制或质量判定。
 * 记录模型实际消费的命令，不把UIO的TCP受理等同于模型开始执行。 */
#define SIMULATION_CONTROL_TRACE_CAPACITY 32u
typedef struct {
    /* epoch_ms沿用MCU的HW_GetTimer单调毫秒，不是日历时间。 */
    uint32_t sequence, epoch_ms, command, permitted, valid_task, pset_no;
    uint32_t state_before, state_after, output_step, result;
    /* 模型内部反馈；显式位置故障向量只改发布值，不覆盖此处取证原值。 */
    int32_t torque_raw, position_inc;
} SimulationControlTraceEntry;
typedef struct {
    uint32_t magic, version, capacity, sequence, write_index;
    uint32_t running_ticks, start_commands, stop_commands, reset_commands;
    SimulationControlTraceEntry entries[SIMULATION_CONTROL_TRACE_CAPACITY];
} SimulationControlDiagnostics;
/* 空闲时读取RAM，前后比较sequence，变化时重读；sequence在整条追踪写完后发布。 */
extern volatile SimulationControlDiagnostics Simulation_ControlDiagnostics;
#if FPGA_TEST_SDO_COMMIT_TRACE
/* 仅观察SSC完整0x2030写提交回调及下一拍解析/加载；不统计邮箱分片。
 * 回调已在SSC提交后调用，诊断不参与准入；读取时须停核并保留复位边界证据。 */
typedef struct {
    uint32_t magic, version, sequence;
    uint32_t notifications, load_attempts, load_successes, load_failures;
    uint32_t last_pset_no, last_length, last_mode, last_tick_ms;
    uint32_t received_by_pset[256], loaded_by_pset[256];
} SimulationSdoCommitDiagnostics;
extern volatile SimulationSdoCommitDiagnostics Simulation_SdoCommitDiagnostics;
#endif
void Simulation_Tick(void);
void Simulation_Receive(uint16_t length);
uint8_t Simulation_IsRunning(void);
#if FPGA_C20_PROFILE
/* Monotonic modulo-2^32 execution milliseconds, independent of main-loop polls. */
uint32_t Simulation_GetRunningMilliseconds(void);
#endif
/* Includes the original plant's braking tail; maintenance must wait for zero speed. */
uint8_t Simulation_IsBusy(void);
uint32_t Simulation_Crc32(const uint8_t *bytes, uint16_t length);
#endif
