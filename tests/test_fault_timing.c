/* 相同故障、两种边沿时序：验证真实适配字段，默认模型不应输出测试故障。 */
#ifdef NDEBUG
#error Compile tests with -UNDEBUG
#endif
#include <assert.h>
#include <stdint.h>
#include <string.h>
#include "../Simulation/ethercat_adapter.h"
#include "../FpgaSim/fpga_program.h"

uint8_t Pset_buffer0x2030[1528];
uint32_t controller_status0x2001, status_code0x2200, status_code20x2201;
uint16_t pset_echo0x220B;
uint8_t step_echo0x220C, step_result0x220D;
int16_t Torque_actual_value0x6077;
int32_t Position_actual_value0x6064, Velocity_actual_value0x606C;
static uint32_t clock_ms;
static uint8_t control;
uint32_t HW_GetTimer(void) { return clock_ms; }
uint8_t App_JobCtrl_GetControl(void) { return control; }
void App_JobCtrl_SetControl(uint8_t value) { control=value; }
uint8_t App_JobCtrl_GetPsetNo(void) { return 101; }
uint8_t App_Link_IsOperational(void) { return 1; }
static void put32(uint8_t *p,uint32_t n)
{ p[0]=(uint8_t)n;p[1]=(uint8_t)(n>>8);p[2]=(uint8_t)(n>>16);p[3]=(uint8_t)(n>>24); }
static void tick(uint32_t now) { clock_ms=now;Simulation_Tick(); }
int main(void)
{
    uint8_t *s=Pset_buffer0x2030+3;
    Pset_buffer0x2030[0]=101;Pset_buffer0x2030[1]=2;Pset_buffer0x2030[2]=1;
    s[0]=3;s[1]=61;s[3]=1;put32(s+4,11000);put32(s+8,12000);put32(s+12,10000);
    put32(s+24,1000);put32(s+28,1400);put32(s+36,1200);put32(s+41,100000);
    s[49]=s[50]=1;s[51]=0xD0;s[52]=7;s[55]=s[56]=2;
    Simulation_Receive(64);tick(0);control=1;tick(1);
    assert(Simulation_IsRunning() && pset_echo0x220B==0x6501);
    tick(100);assert(Simulation_IsRunning() && status_code0x2200==0);
    tick(101);
#if FPGA_SIM_SCENARIO == 4
    assert(!Simulation_IsRunning() && pset_echo0x220B==0x6500 && !step_result0x220D);
    assert(status_code0x2200==0x7001);
#elif FPGA_SIM_SCENARIO == 6
    assert(Simulation_IsRunning() && pset_echo0x220B==0x6501 && status_code0x2200==0x7001);
    tick(120);assert(Simulation_IsRunning() && pset_echo0x220B==0x6501 && status_code0x2200==0x7001);
    tick(121);assert(!Simulation_IsRunning() && pset_echo0x220B==0x6500 && !step_result0x220D);
    assert(status_code0x2200==0x7001);
#else
    assert(Simulation_IsRunning() && pset_echo0x220B==0x6501 && status_code0x2200==0);
    tick(1001);assert(!Simulation_IsRunning() && step_result0x220D==1 && status_code0x2200==0);
#endif
    control=3;tick(2000);assert(status_code0x2200==0 && step_echo0x220C==0);
    return 0;
}
