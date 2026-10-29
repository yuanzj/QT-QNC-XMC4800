/* 只接受单个时间等待工步。通信适配参考C15，模拟模型位于独立FpgaSim目录。 */
#include "ethercat_adapter.h"
#include "../FpgaSim/fpga_sim.h"

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

static FpgaSim simulator;
static volatile uint16_t pending_length;
static volatile uint8_t received;
static uint8_t pset_no;
static uint8_t valid_task;
static uint8_t clock_started;
static uint32_t last_ms;

static uint16_t read_u16(const uint8_t *p)
{
    return (uint16_t)((uint16_t)p[0] | ((uint16_t)p[1] << 8));
}

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
    const uint8_t *p = Pset_buffer0x2030;
    uint16_t duration;
    uint16_t maximum;
    valid_task = 0;
    pset_no = 0;
    FpgaSim_Reset(&simulator);
    status_code0x2200 = 1; /* 测试固件参数不支持，不能冒充已执行。 */
    if (pending_length != 16 || p[0] == 0 || p[1] != 2 || p[2] != 1 ||
        p[3] != 4 || read_u16(p + 4) != 13 || p[6] != 0 ||
        p[9] != 0 || p[10] != 0 || p[13] != 0 || p[14] != 0 || p[15] != 2) return;
    duration = read_u16(p + 7);
    maximum = read_u16(p + 11);
    if (maximum < duration || !FpgaSim_LoadWait(&simulator, duration)) return;
    pset_no = p[0];
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
        FpgaSim_Reset(&simulator);
        valid_task = 0;
        pset_no = 0;
        status_code0x2200 = 0;
    } else if (command == 2) {
        FpgaSim_Stop(&simulator);
    } else if (command == 1) {
        if (!valid_task || App_JobCtrl_GetPsetNo() != pset_no ||
            !FpgaSim_Start(&simulator, now, permitted)) status_code0x2200 = 1;
    } else if (command != 0) {
        status_code0x2200 = 1;
    }
    FpgaSim_Tick(&simulator, now, permitted);
    if (simulator.state == FPGA_SIM_FAULT) status_code0x2200 = 3;
    status_code20x2201 = 0;
    if (simulator.state == FPGA_SIM_RUNNING) {
        pset_echo0x220B = (uint16_t)(((uint16_t)pset_no << 8) | 1u);
        step_echo0x220C = 1;
    } else {
        uint8_t finished = simulator.state == FPGA_SIM_DONE ||
                           simulator.state == FPGA_SIM_STOPPED || simulator.state == FPGA_SIM_FAULT;
        pset_echo0x220B = finished ? (uint16_t)((uint16_t)pset_no << 8) : 0;
        step_echo0x220C = 0;
    }
    step_result0x220D = simulator.result;
}
