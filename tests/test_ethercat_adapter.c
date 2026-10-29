/* 对象字典接入测试：无总线替身反馈、只驱动实际适配入口与可控毫秒时钟。 */
#ifdef NDEBUG
#error Compile tests with -UNDEBUG
#endif
#include <assert.h>
#include <stdint.h>
#include <string.h>
#include "../Simulation/ethercat_adapter.h"

uint8_t Pset_buffer0x2030[1528];
uint32_t controller_status0x2001, status_code0x2200, status_code20x2201;
uint16_t pset_echo0x220B;
uint8_t step_echo0x220C, step_result0x220D;
int16_t Torque_actual_value0x6077;
int32_t Position_actual_value0x6064, Velocity_actual_value0x606C;
static uint32_t clock_ms;
static uint8_t control, selected=7;
uint32_t HW_GetTimer(void) { return clock_ms; }
uint8_t App_JobCtrl_GetControl(void) { return control; }
void App_JobCtrl_SetControl(uint8_t value) { control=value; }
uint8_t App_JobCtrl_GetPsetNo(void) { return selected; }
uint8_t App_Link_IsOperational(void) { return 1; }
static void tick(uint32_t now) { clock_ms=now;Simulation_Tick(); }
int main(void)
{
    const uint8_t valid[16]={7,2,1,4,13,0,0,0xE8,3,0,0,0xD0,7,0,0,2};
    memcpy(Pset_buffer0x2030,valid,sizeof(valid));Simulation_Receive(16);tick(0);
    control=1;tick(1);assert(Simulation_IsRunning());
    tick(1001);assert(!Simulation_IsRunning() && step_result0x220D==1);
    Pset_buffer0x2030[1]=3;Simulation_Receive(16);tick(1002);
    assert(status_code0x2200==1);
    control=1;tick(1003);
    assert(!Simulation_IsRunning()); /* 不能把失败新请求当成旧已加载程序执行。 */
    memcpy(Pset_buffer0x2030,valid,sizeof(valid));Simulation_Receive(16);tick(2000);
    control=1;tick(2001);assert(Simulation_IsRunning());
    control=2;tick(3001);assert(!Simulation_IsRunning() && step_result0x220D==0 && step_echo0x220C==0);
    assert(pset_echo0x220B==0x0700);
    control=3;tick(3002);control=1;tick(3003);assert(!Simulation_IsRunning());
    assert(Simulation_Crc32(Pset_buffer0x2030,16)==0x8f908a63);
    return 0;
}
