/* 完整SDO提交诊断的实际适配回归：重复、拒绝与零长度均可观察；开关不改变任何PDO输出。 */
#ifdef NDEBUG
#error Compile with assertions enabled
#endif
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include "../Simulation/ethercat_adapter.h"
uint8_t Pset_buffer0x2030[1600];
uint32_t controller_status0x2001, status_code0x2200, status_code20x2201;
uint16_t pset_echo0x220B;
uint8_t step_echo0x220C, step_result0x220D;
int16_t Torque_actual_value0x6077;
int32_t Position_actual_value0x6064, Velocity_actual_value0x606C;
int64_t Velocity_actual_64_0x2212;
uint8_t Velocity_606C_valid0x2213;
static uint32_t now;
static uint8_t command;
uint32_t HW_GetTimer(void) { return now; }
uint8_t App_JobCtrl_GetControl(void) { return command; }
void App_JobCtrl_SetControl(uint8_t v) { command = v; }
uint8_t App_JobCtrl_GetPsetNo(void) { return 2; }
uint8_t App_Link_IsOperational(void) { return 1; }
static void put(uint8_t *p, uint32_t v) { for (unsigned i = 0; i < 4; ++i) p[i] = (uint8_t)(v >> (8*i)); }
int main(void)
{
    uint8_t *s = Pset_buffer0x2030 + 3;
    Pset_buffer0x2030[0] = 2; Pset_buffer0x2030[1] = 3; Pset_buffer0x2030[2] = 2;
    put(s, 300); put(s+12, 10000); s[20]=1; s[21]=3; s[22]=1; s[23]=2;
    put(s+28,11000); put(s+32,14000); put(s+36,10000); put(s+40,1000);
    put(s+48,20000); put(s+52,100000); put(s+56,30000); put(s+60,15000);
    put(s+72,1); put(s+76,1); put(s+80,1);
    memcpy(s+96,s,96);
    s[96+20]=2;
    Simulation_Receive(195); Simulation_Tick();
    now=1; Simulation_Receive(195); Simulation_Tick();
    Pset_buffer0x2030[1]=0; now=2; Simulation_Receive(195); Simulation_Tick();
    now=3; Simulation_Receive(0); Simulation_Tick();
    Pset_buffer0x2030[0]=255; Pset_buffer0x2030[1]=3;
    now=4; Simulation_Receive(195); Simulation_Tick();
    Pset_buffer0x2030[0]=2; now=5; Simulation_Receive(195); Simulation_Tick();
#if FPGA_TEST_SDO_COMMIT_TRACE
    assert(sizeof(SimulationSdoCommitDiagnostics)==2092);
    assert(Simulation_SdoCommitDiagnostics.magic==0x53434E51u);
    assert(Simulation_SdoCommitDiagnostics.version==1);
    assert(Simulation_SdoCommitDiagnostics.sequence==12);
    assert(Simulation_SdoCommitDiagnostics.notifications==6);
    assert(Simulation_SdoCommitDiagnostics.load_attempts==6);
    assert(Simulation_SdoCommitDiagnostics.load_successes==3);
    assert(Simulation_SdoCommitDiagnostics.load_failures==3);
    assert(Simulation_SdoCommitDiagnostics.received_by_pset[2]==4);
    assert(Simulation_SdoCommitDiagnostics.received_by_pset[0]==1);
    assert(Simulation_SdoCommitDiagnostics.received_by_pset[255]==1);
    assert(Simulation_SdoCommitDiagnostics.loaded_by_pset[2]==3);
    assert(Simulation_SdoCommitDiagnostics.loaded_by_pset[255]==0);
    assert(Simulation_SdoCommitDiagnostics.last_pset_no==2);
    assert(Simulation_SdoCommitDiagnostics.last_length==195);
    assert(Simulation_SdoCommitDiagnostics.last_mode==3);
    assert(Simulation_SdoCommitDiagnostics.last_tick_ms==5);
#endif
    command=1;
    for (now=6; now<6006; ++now) {
        Simulation_Tick();
        printf("%u,%u,%u,%u,%" PRIu32 ",%d,%" PRId64 ",%" PRId32 "\n",
               now,step_echo0x220C,pset_echo0x220B,step_result0x220D,status_code0x2200,
               Torque_actual_value0x6077,Velocity_actual_64_0x2212,Position_actual_value0x6064);
    }
    assert(!Simulation_IsRunning() && status_code0x2200==0 && step_result0x220D==1);
    assert(Simulation_ControlDiagnostics.start_commands==1);
    return 0;
}
