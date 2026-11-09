/* 实际适配入口的冷启动回归：未下发工艺时健康空闲，非法启动拒绝，清错后仍不自行运行。 */
#include <assert.h>
#include <stdint.h>
#include "../Simulation/ethercat_adapter.h"
#include "../Simulation/model_config.h"
uint8_t Pset_buffer0x2030[1528];
uint32_t controller_status0x2001, status_code0x2200, status_code20x2201;
uint16_t pset_echo0x220B;
uint8_t step_echo0x220C, step_result0x220D;
int16_t Torque_actual_value0x6077;
int32_t Position_actual_value0x6064, Velocity_actual_value0x606C;
#if FPGA_SIM_INT64
int64_t Velocity_actual_64_0x2212;
uint8_t Velocity_606C_valid0x2213;
#endif
static uint32_t clock_ms;
static uint8_t command;
uint32_t HW_GetTimer(void) { return clock_ms; }
uint8_t App_JobCtrl_GetControl(void) { return command; }
void App_JobCtrl_SetControl(uint8_t value) { command = value; }
uint8_t App_JobCtrl_GetPsetNo(void) { return 7; }
uint8_t App_Link_IsOperational(void) { return 1; }
int main(void)
{
    for (clock_ms = 1; clock_ms <= 2000; ++clock_ms) {
        Simulation_Tick();
        assert(status_code0x2200 == 0 && !Simulation_IsRunning());
        assert(Torque_actual_value0x6077 == 0 && Velocity_actual_value0x606C == 0);
        assert(pset_echo0x220B == 0 && step_echo0x220C == 0 && step_result0x220D == 0);
    }
    command = 1; Simulation_Tick();
    assert(status_code0x2200 != 0 && !Simulation_IsRunning());
    ++clock_ms; command = 3; Simulation_Tick();
    assert(status_code0x2200 == 0 && !Simulation_IsRunning());
    ++clock_ms; Simulation_Tick();
    assert(status_code0x2200 == 0 && !Simulation_IsRunning());
    return 0;
}
