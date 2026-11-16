/* Actual C20 SDO/PDO callbacks plus original independent model, no board access. */
#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <limits.h>
#include "../Simulation/ethercat_adapter.h"
#include "../Simulation/c20_profile.h"
#include "../FpgaSim/fpga_program.h"
#include "c20_abort_codes.h"
typedef uint8_t UINT8;
typedef uint16_t UINT16;
typedef uint32_t UINT32;
#define MBXMEM
#define QN_HOST_TEST 1
static uint8_t flash[32768];
static unsigned writes,erases;
/* Return failures independently of the separate power-cut/CRC media tests. */
static unsigned fail_program_on,fail_erase_on,program_fail_bytes,erase_fail_bytes;
static const uint8_t *qn_memory(uint32_t address)
{ assert(address>=0x0C004000U && address<0x0C00C000U);return flash+(address-0x0C004000U); }
static bool qn_program(uint32_t address,const uint32_t *page)
{
 assert(address>=0x0C004000U && address+256U<=0x0C00C000U && address%256U==0U);++writes;
 bool fail=fail_program_on==writes;
 memcpy(flash+(address-0x0C004000U),page,fail?program_fail_bytes:256U);return !fail;
}
static bool qn_erase(uint32_t address)
{
 assert(address==0x0C004000U || address==0x0C008000U);++erases;
 bool fail=fail_erase_on==erases;
 memset(flash+(address-0x0C004000U),0,fail?erase_fail_bytes:16384U);return !fail;
}
uint8_t Pset_buffer0x2030[1600];
uint32_t controller_status0x2001,status_code0x2200,status_code20x2201;
uint16_t pset_echo0x220B,Statusword0x6041,Error_code0x603F,Controlword0x6040;
uint8_t step_echo0x220C,step_result0x220D;
int16_t Torque_actual_value0x6077;
int32_t Position_actual_value0x6064,Velocity_actual_value0x606C,current_sample0x2208;
int64_t Velocity_actual_64_0x2212;
uint8_t Velocity_606C_valid0x2213;
static struct {char tool_sn[16];uint32_t max_torque;} Tool_Spec0x2000={"QIAOTIAN-TW-0001",30000};
static uint32_t clock_ms,irq_state;
static uint8_t irq_tick_pending;
static void tick(void);
static uint8_t control,selected=7,link_operational=1;
uint32_t HW_GetTimer(void){return clock_ms;}
uint8_t App_JobCtrl_GetControl(void){return control;}
void App_JobCtrl_SetControl(uint8_t v){control=v;}
uint8_t App_JobCtrl_GetPsetNo(void){return selected;}
uint8_t App_Link_IsOperational(void){return link_operational;}
uint8_t Pset_IsRunning(void){return Simulation_IsBusy();}
static uint32_t __get_PRIMASK(void){return irq_state;}
static void __disable_irq(void){irq_state=1;}
static void __set_PRIMASK(uint32_t v)
{
 irq_state=v;
 if(!v&&irq_tick_pending){irq_tick_pending=0;tick();}
}
#include "../SSC/Src/qiaotian_protocol.inc"
/* Extracted unchanged from the production SSC implementation by the test runner. */
#include "c20_ethercat_functions.inc"
static void put(uint8_t *p,uint32_t v){for(unsigned i=0;i<4;++i)p[i]=(uint8_t)(v>>(8*i));}
static uint32_t get(const uint8_t *p){return (uint32_t)p[0]|(uint32_t)p[1]<<8|(uint32_t)p[2]<<16|(uint32_t)p[3]<<24;}
static void tick(void){++clock_ms;Simulation_Tick();}
static uint32_t read32(uint16_t index,uint8_t sub)
{uint16_t data[4]={0};assert(!ECAT_Read_QEC_Callback(index,sub,4,data,0));return get((uint8_t *)data);}
static uint8_t write_value(uint16_t index,uint8_t sub,uint64_t v,unsigned bytes)
{uint16_t data[4]={0};for(unsigned i=0;i<bytes;++i)((uint8_t *)data)[i]=(uint8_t)(v>>(8*i));return ECAT_Write_QEC_Callback(index,sub,bytes,data,0);}
static void reset(void){control=3;tick();for(unsigned i=0;i<100;++i)tick();}
static void snug(uint32_t timeout)
{
 uint8_t *s=Pset_buffer0x2030+3;memset(Pset_buffer0x2030,0,sizeof(Pset_buffer0x2030));
 Pset_buffer0x2030[0]=7;Pset_buffer0x2030[1]=3;Pset_buffer0x2030[2]=1;
 put(s,300);put(s+12,timeout);s[20]=1;s[21]=3;s[22]=1;s[23]=2;
 uint32_t v[15]={0,11000,14000,10000,1000,0,20000,100000,30000,15000,0,0,0,1,1};
 for(unsigned i=0;i<15;++i)put(s+24+4*i,v[i]);Simulation_Receive(99);tick();assert(status_code0x2200==QEC_NvmRunStatus());
}
static void identify(uint32_t timeout,uint32_t attempts)
{
 uint8_t *s=Pset_buffer0x2030+3;memset(Pset_buffer0x2030,0,sizeof(Pset_buffer0x2030));
 Pset_buffer0x2030[0]=7;Pset_buffer0x2030[1]=3;Pset_buffer0x2030[2]=1;
 put(s,300);put(s+12,timeout);s[20]=1;s[21]=1;s[22]=1;s[23]=2;
 put(s+24,1000);put(s+28,500);put(s+32,200);put(s+36,attempts);
 Simulation_Receive(99);tick();assert(status_code0x2200==QEC_NvmRunStatus());
}
static void start(void){control=1;tick();assert(Simulation_IsRunning());}
static void finish(void)
{for(unsigned i=0;i<15000&&Simulation_IsBusy();++i)tick();assert(!Simulation_IsBusy());}
static void test_pdo_and_records(void)
{
 struct {uint16_t data[23];uint8_t guard[16];} image;memset(&image,0xA5,sizeof(image));
 Position_actual_value0x6064=209715200;Velocity_actual_64_0x2212=-4194304000LL;
 Torque_actual_value0x6077=400;Statusword0x6041=0x237;pset_echo0x220B=0x0703;
 step_echo0x220C=3;step_result0x220D=1;current_sample0x2208=-42;
 APPL_InputMapping(image.data);uint8_t *p=(uint8_t *)image.data;
 assert(p[0]==0x37&&p[1]==2);assert(get(p+4)==30000);assert((int32_t)get(p+8)==-10000);
 assert(p[12]==0x90&&p[13]==1);assert(get(p+22)==209715200);
 assert(qec_get(p+26,8)==(uint64_t)-4194304000LL);assert(p[34]==3&&p[35]==7&&p[36]==3&&p[37]==1);
 assert((int32_t)get(p+38)==-42&&get(p+42)==0x20261116U);
 for(unsigned i=0;i<sizeof(image.guard);++i)assert(image.guard[i]==0xA5);
 uint16_t output[9]={0};uint8_t *o=(uint8_t *)output;
 o[0]=15;put(o+2,12345);put(o+6,100);o[10]=9;o[12]=8;put(o+13,2);
 APPL_OutputMapping(output);assert(Controlword0x6040==15&&controller_status0x2001==2);
 assert(qec_target_position==12345&&qec_target_velocity==100&&qec_target_torque==9);
 assert(Position_actual_value0x6064==209715200&&!Simulation_IsRunning());
 controller_status0x2001=0;
 assert(read32(0x2300,4)==30000&&read32(0x2300,6)==10000&&read32(0x2300,7)==300000);
 assert(write_value(0x2400,1,10001,4)==ABORTIDX_VALUE_EXCEEDED);
 assert(!write_value(0x2400,1,10000,4));assert(read32(0x2400,1)==10000);
 uint16_t data[16]={0};assert(ECAT_Read_QEC_Callback(0x2500,1,4,data,0)==ABORTIDX_SUBINDEX_NOT_EXISTING);
 assert(ECAT_Read_QEC_Callback(0x2300,4,2,data,0)==ABORTIDX_PARAM_LENGTH_ERROR);
 assert(ECAT_Read_QEC_Callback(0x2300,4,4,data,1)==ABORTIDX_UNSUPPORTED_ACCESS);
}
static void test_calibration(void)
{
 assert(write_value(0x2310,6,1,1)==ABORTIDX_VALUE_EXCEEDED);
 assert(!write_value(0x2F10,1,1794820000123ULL,8));
 assert(!write_value(0x2310,3,1100,4));assert(!write_value(0x2310,4,(uint32_t)-100,4));
 assert(!write_value(0x2310,6,1,1));assert(qn_state.cal[0].k==1100&&qn_state.cal[0].b==-100);
 unsigned before=writes;assert(!write_value(0x2310,6,1,1));assert(writes==before);
 assert(!write_value(0x2310,3,1200,4));assert(write_value(0x2310,6,1,1)==ABORTIDX_VALUE_EXCEEDED);
 assert(qn_state.cal[0].k==1100);assert(!write_value(0x2310,1,1,1));assert(!write_value(0x2310,2,7,2));
 assert(!write_value(0x2310,3,1000,4));assert(!write_value(0x2310,4,0,4));assert(!write_value(0x2310,6,1,1));
 QEC_NvmInit(Simulation_GetRunningMilliseconds());assert(qn_state.cal[0].k==1100&&qn_state.cal[1].valid&&qn_state.cal[1].pset==7);
 /* Per-PSET identity calibration overrides tool scope for its published values. */
 pset_echo0x220B=0x0700;Torque_actual_value0x6077=400;assert(qec_torque()==400);
 pset_echo0x220B=0x0800;assert(qec_torque()==437);
 pset_echo0x220B=0;
}
static void test_lifecycle(void)
{
 reset();snug(10000);
 /* A START already accepted into the mailbox takes priority over maintenance. */
 control=1;irq_tick_pending=1;
 assert(write_value(0x2400,1,6000,4)==ABORTIDX_IN_THIS_STATE_DATA_CANNOT_BE_READ_OR_STORED);
 assert(Simulation_IsRunning()&&!status_code0x2200);
 /* Storage polling during an active cycle must not revoke its run permission. */
 irq_tick_pending=1;App_Storage_Poll(clock_ms);assert(Simulation_IsRunning()&&!status_code0x2200);
 assert(ECAT_Write_QEC_Callback(0x2400,1,4,(UINT16 *)Pset_buffer0x2030,0)==ABORTIDX_IN_THIS_STATE_DATA_CANNOT_BE_READ_OR_STORED);
 finish();assert(step_result0x220D==1&&qn_state.ok==1&&qn_state.nok==0&&qn_state.cal[1].count==1);
 for(unsigned i=0;i<50;++i)tick();assert(qn_state.ok==1);
 App_Storage_Poll(clock_ms);QEC_NvmInit(Simulation_GetRunningMilliseconds());assert(qn_state.ok==1);
 reset();snug(10000);control=1;irq_tick_pending=1;unsigned before_start=writes;
 App_Storage_Poll(clock_ms);assert(Simulation_IsRunning()&&!status_code0x2200&&writes==before_start);
 for(unsigned i=0;i<200;++i)tick();
 control=2;tick();assert(!Simulation_IsRunning()&&Simulation_IsBusy()&&qn_state.nok==1);
 unsigned before=writes;App_Storage_Poll(clock_ms);assert(writes==before);
 assert(ECAT_Write_QEC_Callback(0x2310,6,1,(UINT16 *)Pset_buffer0x2030,0)==ABORTIDX_IN_THIS_STATE_DATA_CANNOT_BE_READ_OR_STORED);
 finish();App_Storage_Poll(clock_ms);assert(writes>before);
 reset();snug(10000);start();for(unsigned i=0;i<200;++i)tick();control=3;tick();
 assert(qn_state.nok==2&&qn_state.cal[1].count==3);
 snug(10000);start();link_operational=0;tick();finish();link_operational=1;assert(qn_state.nok==3);
 reset();identify(100,3);start();uint32_t begun=clock_ms;finish();assert(clock_ms-begun<200&&!step_result0x220D&&qn_state.nok==4);
 /* Unloaded fixed joint exhausts exactly N searches, rather than C20's N+1 success. */
 reset();identify(0,3);start();finish();assert(!step_result0x220D&&qn_state.nok==5);
 assert(Simulation_ControlDiagnostics.entries[(Simulation_ControlDiagnostics.write_index+31U)%32U].valid_task);
 App_Storage_Poll(clock_ms);QEC_NvmInit(Simulation_GetRunningMilliseconds());assert(qn_state.ok==1&&qn_state.nok==5&&qn_state.cal[1].count==6);
 /* Occupied, invalid storage fails closed; no loop or statistic is fabricated. */
 memset(flash,0,sizeof(flash));flash[0]=1;QEC_NvmInit(Simulation_GetRunningMilliseconds());assert(!App_Run_IsPermitted());
 reset();snug(10000);control=1;tick();assert(!Simulation_IsRunning()&&status_code0x2200);
 memset(flash,0,sizeof(flash));QEC_NvmInit(Simulation_GetRunningMilliseconds());assert(App_Run_IsPermitted());
 Controlword0x6040=0;assert(!App_Run_IsPermitted());Controlword0x6040=15;
 qn_write_busy=true;assert(!App_Run_IsPermitted());qn_write_busy=false;
 qec_maintenance_busy=true;assert(!App_Run_IsPermitted());unsigned before_maintenance=writes;
 assert(write_value(0x2310,6,1,1)==ABORTIDX_IN_THIS_STATE_DATA_CANNOT_BE_READ_OR_STORED);
 App_Storage_Poll(clock_ms);assert(qec_maintenance_busy&&writes==before_maintenance);qec_maintenance_busy=false;
}
static void test_sixteen_steps(void)
{
 reset();snug(10000);uint8_t *first=Pset_buffer0x2030+3;
 uint32_t v[15]={1,0,30000,0,0,0,10000,0,30000,1,0,0,0,1,1};
 for(unsigned j=0;j<15;++j)put(first+24+4*j,v[j]);
 Pset_buffer0x2030[2]=16;
 for(unsigned i=1;i<16;++i){memcpy(first+96*i,first,96);first[96*i+20]=(uint8_t)(i+1);}
 Simulation_Receive(1539);tick();assert(!status_code0x2200);start();uint16_t visited=0;
 for(unsigned t=0;t<15000&&Simulation_IsBusy();++t){
  tick();if(step_echo0x220C)visited|=(uint16_t)(1U<<(step_echo0x220C-1));
  uint16_t image[23]={0};APPL_InputMapping(image);uint8_t *p=(uint8_t *)image;
  assert(get(p+22)==(uint32_t)Position_actual_value0x6064);
  assert(qec_get(p+26,8)==(uint64_t)Velocity_actual_64_0x2212);
 }
 assert(visited==UINT16_MAX&&step_result0x220D&&qn_state.ok==1&&qn_state.nok==0);
}
int main(void)
{
 QEC_NvmInit(Simulation_GetRunningMilliseconds());tick();test_pdo_and_records();test_calibration();test_lifecycle();test_sixteen_steps();
 puts("C20 interface + independent model: PDO/records/calibration/NVM/normal/STOP/RESET/link/identify PASS");return 0;
}
