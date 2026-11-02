/* 现有专家PSET到独立逻辑工具模型的适配；保留真实SDO/PDO，不操作实际FPGA或电机。 */
#include "ethercat_adapter.h"
#include "native_pset.h"
#include <limits.h>
#if FPGA_SIM_INT64
extern int64_t Velocity_actual_64_0x2212;
extern uint8_t Velocity_606C_valid0x2213;
#endif

extern uint32_t HW_GetTimer(void);
extern uint8_t Pset_buffer0x2030[];
extern uint8_t App_JobCtrl_GetControl(void);
extern void App_JobCtrl_SetControl(uint8_t value);
extern uint8_t App_JobCtrl_GetPsetNo(void);
extern uint8_t App_Link_IsOperational(void);
extern uint32_t controller_status0x2001;
extern uint32_t status_code0x2200;
extern uint32_t status_code20x2201;
extern uint16_t pset_echo0x220B;
extern uint8_t step_echo0x220C;
extern uint8_t step_result0x220D;
extern int16_t Torque_actual_value0x6077;
extern int32_t Position_actual_value0x6064;
extern int32_t Velocity_actual_value0x606C;

static FpgaProgramRun simulator;
static FpgaProgram decoded_program;
static volatile uint16_t pending_length;
static volatile uint8_t received;
static uint8_t valid_task;
static uint8_t clock_started;
static uint32_t last_ms;

void Simulation_Receive(uint16_t length)
{
    pending_length = length;
    received = 1;
}

uint8_t Simulation_IsRunning(void)
{
    return simulator.state == FPGA_SIM_RUNNING;
}

uint32_t Simulation_Crc32(const uint8_t *bytes, uint16_t length)
{
    uint32_t crc = 0xFFFFFFFFu;
    uint16_t i;
    for (i = 0; i < length; ++i) {
        uint8_t bit;
        crc ^= bytes[i];
        for (bit = 0; bit < 8; ++bit)
            crc = (crc >> 1) ^ ((crc & 1u) ? 0xEDB88320u : 0u);
    }
    return crc ^ 0xFFFFFFFFu;
}

static void load_task(void)
{
    valid_task = 0;
    if (!NativePset_Decode(Pset_buffer0x2030, pending_length, &decoded_program) ||
        !FpgaProgram_Load(&simulator, &decoded_program)) {
        status_code0x2200 = 1;
        return;
    }
    valid_task = 1;
    status_code0x2200 = 0;
}

void Simulation_Tick(void)
{
    uint32_t now = HW_GetTimer();
    uint8_t command;
    uint8_t permitted;
    if (clock_started && now == last_ms) return;
    clock_started = 1;
    last_ms = now;
    if (received) {
        received = 0;
        load_task();
    }
    permitted = App_Link_IsOperational() && ((controller_status0x2001 & 3u) == 0);
    command = App_JobCtrl_GetControl();
    if (command) App_JobCtrl_SetControl(0);
    if (command == 3) {
        FpgaProgram_Reset(&simulator);
        valid_task = 0;
        status_code0x2200 = 0;
    } else if (command == 2) {
        FpgaProgram_Stop(&simulator);
    } else if (command == 1) {
        if (!valid_task || simulator.program.count == 0 || App_JobCtrl_GetPsetNo() != simulator.program.pset_no ||
            !FpgaProgram_Start(&simulator, now, permitted)) status_code0x2200 = 1;
        else status_code0x2200 = 0;
    } else if (command != 0) {
        status_code0x2200 = 1;
    }
    FpgaProgram_Tick(&simulator, now, permitted);
    if (simulator.state == FPGA_SIM_FAULT) status_code0x2200 = simulator.fault_code;
#if FPGA_SIM_SCENARIO == 6
    /* 仅提前故障测试镜像在活动步输出测试码；默认镜像及同拍场景不改变时序。 */
    if (simulator.state == FPGA_SIM_RUNNING && simulator.fault_code != 0)
        status_code0x2200 = simulator.fault_code;
#endif
    status_code20x2201 = 0;
    if (simulator.state == FPGA_SIM_RUNNING) {
        pset_echo0x220B = (uint16_t)(((uint16_t)simulator.program.pset_no << 8) | simulator.current_step);
        step_echo0x220C = simulator.current_step;
    } else {
        uint8_t finished = simulator.state == FPGA_SIM_DONE ||
                           simulator.state == FPGA_SIM_STOPPED || simulator.state == FPGA_SIM_FAULT;
        pset_echo0x220B = finished ? (uint16_t)((uint16_t)simulator.program.pset_no << 8) : 0;
        step_echo0x220C = 0;
    }
    step_result0x220D = simulator.result;
    Torque_actual_value0x6077 = simulator.torque_raw;
    Position_actual_value0x6064 = simulator.position_inc;
#if FPGA_SIM_INT64
    Velocity_actual_64_0x2212 = simulator.velocity_inc_s;
    Velocity_606C_valid0x2213 = simulator.velocity_inc_s >= INT32_MIN && simulator.velocity_inc_s <= INT32_MAX;
    /* 标准606C仍为INT32。超范围不截断/钳位；SDO回调拒读，PDO使用2212。 */
    if (Velocity_606C_valid0x2213) Velocity_actual_value0x606C = (int32_t)simulator.velocity_inc_s;
#else
    Velocity_actual_value0x606C = simulator.velocity_inc_s;
#endif
}
