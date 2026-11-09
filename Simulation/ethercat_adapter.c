/* 现有专家PSET到独立逻辑工具模型的适配；保留真实SDO/PDO，不操作实际FPGA或电机。 */
#include "ethercat_adapter.h"
#include "native_pset.h"
#include <limits.h>
#if FPGA_TEST_POSITION_VECTOR
#include "position_test_vector.h"
#endif
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
#if FPGA_SIM_SCENARIO == 9
static uint32_t entry_fault_published_ms;
static uint8_t completed_step;
#endif
volatile SimulationControlDiagnostics Simulation_ControlDiagnostics = {
    .magic = 0x54434E51u, .version = 1u, .capacity = SIMULATION_CONTROL_TRACE_CAPACITY
};
#if FPGA_TEST_SDO_COMMIT_TRACE
volatile SimulationSdoCommitDiagnostics Simulation_SdoCommitDiagnostics = {
    .magic = 0x53434E51u, .version = 1u
};
#endif

/* 只观察已经完成的模型拍；不写任何对象字典或模型状态。 */
static void trace_control(uint32_t now, uint8_t command, uint32_t state_before, uint8_t permitted)
{
    volatile SimulationControlDiagnostics *d = &Simulation_ControlDiagnostics;
    volatile SimulationControlTraceEntry *entry;
    uint32_t sequence;
    if (simulator.state == FPGA_SIM_RUNNING) ++d->running_ticks;
    if (command == 0) return;
    if (command == 1) ++d->start_commands;
    if (command == 2) ++d->stop_commands;
    if (command == 3) ++d->reset_commands;
    sequence = d->sequence + 1u;
    entry = &d->entries[d->write_index];
    entry->sequence = sequence;
    entry->epoch_ms = now;
    entry->command = command;
    entry->permitted = permitted;
    entry->valid_task = valid_task;
    entry->pset_no = simulator.program.pset_no;
    entry->state_before = state_before;
    entry->state_after = simulator.state;
    entry->output_step = step_echo0x220C;
    entry->result = simulator.result;
    entry->torque_raw = simulator.torque_raw;
    entry->position_inc = simulator.position_inc;
    d->write_index = (d->write_index + 1u) % SIMULATION_CONTROL_TRACE_CAPACITY;
    d->sequence = sequence;
}

void Simulation_Receive(uint16_t length)
{
#if FPGA_TEST_SDO_COMMIT_TRACE
    volatile SimulationSdoCommitDiagnostics *d = &Simulation_SdoCommitDiagnostics;
    uint8_t pset_no = length ? Pset_buffer0x2030[0] : 0;
    ++d->notifications;
    ++d->received_by_pset[pset_no];
    d->last_pset_no = pset_no;
    d->last_length = length;
    d->last_mode = length > 1 ? Pset_buffer0x2030[1] : 0;
    ++d->sequence;
#endif
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
#if FPGA_TEST_SDO_COMMIT_TRACE
    ++Simulation_SdoCommitDiagnostics.load_attempts;
    Simulation_SdoCommitDiagnostics.last_tick_ms = last_ms;
#endif
    if (!NativePset_Decode(Pset_buffer0x2030, pending_length, &decoded_program) ||
        !FpgaProgram_Load(&simulator, &decoded_program)) {
        status_code0x2200 = 1;
#if FPGA_TEST_SDO_COMMIT_TRACE
        ++Simulation_SdoCommitDiagnostics.load_failures;
        ++Simulation_SdoCommitDiagnostics.sequence;
#endif
        return;
    }
    valid_task = 1;
    status_code0x2200 = 0;
#if FPGA_TEST_SDO_COMMIT_TRACE
    ++Simulation_SdoCommitDiagnostics.load_successes;
    ++Simulation_SdoCommitDiagnostics.loaded_by_pset[decoded_program.pset_no];
    ++Simulation_SdoCommitDiagnostics.sequence;
#endif
}

static void reset_task(void)
{
#if FPGA_SIM_SCENARIO == 9
    if (!simulator.plant.valid ||
        (simulator.fault_code == FPGA_SIM_TOOL_UNAVAILABLE && simulator.plant.velocity_rpm_milli != 0)) {
        return;
    }
#endif
    FpgaProgram_Reset(&simulator);
    valid_task = 0;
    status_code0x2200 = 0;
}

void Simulation_Tick(void)
{
    uint32_t now = HW_GetTimer();
    uint8_t command;
    uint8_t permitted;
    uint32_t state_before;
#if FPGA_SIM_SCENARIO == 9
    uint8_t terminal_step;
#endif
    /* 冷启动先建立有效的独立反馈模型；与清错复位走同一初始化，不能靠下发工艺消除上电假故障。 */
    if (!clock_started) FpgaProgram_Reset(&simulator);
    if (clock_started && now == last_ms) return;
    clock_started = 1;
    last_ms = now;
    if (received) {
        received = 0;
        load_task();
    }
    permitted = App_Link_IsOperational() && ((controller_status0x2001 & 3u) == 0);
    command = App_JobCtrl_GetControl();
    state_before = simulator.state;
    if (command) App_JobCtrl_SetControl(0);
    if (command == 3) {
        reset_task();
    } else if (command == 2) {
        FpgaProgram_Stop(&simulator);
    } else if (command == 1) {
        if (!valid_task || simulator.program.count == 0 || App_JobCtrl_GetPsetNo() != simulator.program.pset_no ||
            !FpgaProgram_Start(&simulator, now, permitted)) status_code0x2200 = 1;
        else status_code0x2200 = 0;
    } else if (command != 0) {
        status_code0x2200 = 1;
    }
#if FPGA_SIM_SCENARIO == 9
    terminal_step = simulator.state == FPGA_SIM_RUNNING ? simulator.current_step : 0;
#endif
    FpgaProgram_Tick(&simulator, now, permitted);
    if (simulator.state == FPGA_SIM_FAULT) status_code0x2200 = simulator.fault_code;
#if FPGA_SIM_SCENARIO == 9
    if (simulator.state == FPGA_SIM_DONE) {
        if (terminal_step != 0) completed_step = terminal_step;
        terminal_step = (uint32_t)(now - simulator.finished_ms) < FPGA_STEP_RESULT_WINDOW_MS
                        ? completed_step : 0;
    } else {
        completed_step = 0;
    }
    if (simulator.state == FPGA_SIM_FAULT && simulator.entry_fault_step != 0) {
        if (state_before != FPGA_SIM_FAULT) entry_fault_published_ms = now;
        /* 入口保护可早于主站下一次采样。保留真实故障所属的工步，其他反馈继续更新。 */
        if ((uint32_t)(now - entry_fault_published_ms) < FPGA_STEP_RESULT_WINDOW_MS)
            terminal_step = simulator.entry_fault_step;
    }
#endif
#if FPGA_SIM_SCENARIO == 6
    /* 仅提前故障测试镜像在活动步输出测试码；默认镜像及同拍场景不改变时序。 */
    if (simulator.state == FPGA_SIM_RUNNING && simulator.fault_code != 0)
        status_code0x2200 = simulator.fault_code;
#endif
    status_code20x2201 = 0;
    if (simulator.state == FPGA_SIM_RUNNING) {
        pset_echo0x220B = (uint16_t)(((uint16_t)simulator.program.pset_no << 8) | simulator.current_step);
        step_echo0x220C = simulator.current_step;
#if FPGA_SIM_SCENARIO == 9
    } else if (terminal_step != 0 &&
               (simulator.state == FPGA_SIM_DONE || simulator.state == FPGA_SIM_FAULT)) {
        /* 完成窗口内保留原工步。故障沿用触发拍或入口保护窗口，制动反馈继续更新。 */
        pset_echo0x220B = (uint16_t)(((uint16_t)simulator.program.pset_no << 8) | terminal_step);
        step_echo0x220C = terminal_step;
#endif
    } else {
        uint8_t finished = simulator.state == FPGA_SIM_DONE ||
                           simulator.state == FPGA_SIM_STOPPED || simulator.state == FPGA_SIM_FAULT;
        pset_echo0x220B = finished ? (uint16_t)((uint16_t)simulator.program.pset_no << 8) : 0;
        step_echo0x220C = 0;
    }
    step_result0x220D = simulator.result;
    Torque_actual_value0x6077 = simulator.torque_raw;
    Position_actual_value0x6064 = simulator.position_inc;
#if FPGA_TEST_POSITION_VECTOR
    Position_actual_value0x6064 = Simulation_PositionTestVector(simulator.position_inc, step_echo0x220C);
#endif
#if FPGA_SIM_INT64
    Velocity_actual_64_0x2212 = simulator.velocity_inc_s;
    Velocity_606C_valid0x2213 = simulator.velocity_inc_s >= INT32_MIN && simulator.velocity_inc_s <= INT32_MAX;
    /* 标准606C仍为INT32。超范围不截断/钳位；SDO回调拒读，PDO使用2212。 */
    if (Velocity_606C_valid0x2213) Velocity_actual_value0x606C = (int32_t)simulator.velocity_inc_s;
#else
    Velocity_actual_value0x606C = simulator.velocity_inc_s;
#endif
    trace_control(now, command, state_before, permitted);
}
