/* 通过真实原生解码/独立接头/适配器验证速度，不以目标生成测量预期。 */
#ifdef NDEBUG
#error Assertions must execute
#endif
#include <assert.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "../Simulation/native_pset.h"
#include "../Simulation/ethercat_adapter.h"
uint8_t Pset_buffer0x2030[1528];
uint32_t controller_status0x2001, status_code0x2200, status_code20x2201;
uint16_t pset_echo0x220B;
uint8_t step_echo0x220C,step_result0x220D,Velocity_606C_valid0x2213=1;
int16_t Torque_actual_value0x6077;
int32_t Position_actual_value0x6064,Velocity_actual_value0x606C;
int64_t Velocity_actual_64_0x2212;
static uint32_t clock_ms;
static uint8_t control,permitted=1;
uint32_t HW_GetTimer(void){return clock_ms;}
uint8_t App_JobCtrl_GetControl(void){return control;}
void App_JobCtrl_SetControl(uint8_t v){control=v;}
uint8_t App_JobCtrl_GetPsetNo(void){return 122;}
uint8_t App_Link_IsOperational(void){return permitted;}
static void tick(uint32_t n){clock_ms=n;Simulation_Tick();}
static void u16(uint8_t *p,uint16_t v){p[0]=(uint8_t)v;p[1]=(uint8_t)(v>>8);}
static void u32(uint8_t *p,uint32_t v){unsigned i;for(i=0;i<4;i++)p[i]=(uint8_t)(v>>(8*i));}
static void frame(uint8_t p[64],uint32_t speed){
 uint8_t *s=p+3;memset(p,0,64);p[0]=122;p[1]=2;p[2]=1;s[0]=3;u16(s+1,61);s[3]=2;
 u32(s+4,11000);u32(s+8,30000);u32(s+28,300000);u32(s+36,60000);
 u32(s+41,speed);u16(s+45,100);s[49]=s[50]=1;u16(s+51,5000);s[55]=s[56]=2;
}
static void start(FpgaProgramRun *r,const FpgaProgram *p){FpgaProgram_Reset(r);assert(FpgaProgram_Load(r,p));assert(FpgaProgram_Start(r,0,1));}
int main(void){
 uint8_t bytes[64];FpgaProgram p;FpgaProgramRun run;unsigned i;
 const uint32_t speeds[]={1,500000,512000,512001,1000000,1000001,0,0xFFFFFFFFU};
 for(i=0;i<sizeof(speeds)/sizeof(speeds[0]);i++){
  frame(bytes,speeds[i]);assert(NativePset_Decode(bytes,64,&p)==(speeds[i]>0&&speeds[i]<=FPGA_MODEL_MAX_RPM_MILLI));
 }
 /* 下旋、卸荷的速度准入也同步；不是只改拧紧分支。 */
 for(i=0;i<2;i++){
  uint8_t data[39]={122,2,1},*s=data+3;unsigned size=i?26:36;
  s[0]=i?5:2;u16(s+1,(uint16_t)size);
  if(i){u32(s+3,20000);u32(s+11,500);u16(s+21,2000);s[25]=2;}
  else{s[3]=2;u16(s+14,2000);s[18]=2;s[19]=1;u32(s+24,60000);u32(s+28,20000);}
  u32(s+(i?15:4),FPGA_MODEL_MAX_RPM_MILLI);assert(NativePset_Decode(data,(uint16_t)(size+3),&p));
  u32(s+(i?15:4),FPGA_MODEL_MAX_RPM_MILLI+1);assert(!NativePset_Decode(data,(uint16_t)(size+3),&p));
 }
#if FPGA_SIM_INT64 && FPGA_MODEL_PROFILE == 3
 /* 有界空转角度工步：100ms加速，600°触发制动，不作为真实拧紧成功。 */
 for(i=0;i<2;i++){
  unsigned t;int64_t sign=i?-1:1;
  frame(bytes,1000000);bytes[43]=(uint8_t)i;assert(NativePset_Decode(bytes,64,&p));start(&run,&p);
  FpgaProgram_Tick(&run,100,1);assert(run.state==FPGA_SIM_RUNNING);
  assert(run.plant.velocity_rpm_milli==sign*1000000&&run.velocity_inc_s==sign*4194304000LL);
  for(t=101;t<1000&&run.state==FPGA_SIM_RUNNING;t++)FpgaProgram_Tick(&run,t,1);
  assert(run.state==FPGA_SIM_DONE&&run.result&&run.velocity_inc_s==0);
  assert(run.measured_angle_cdeg>200000&&run.measured_angle_cdeg<220000);
  printf("1000rpm direction=%u terminal_ms=%u measured_cdeg=%ld raw_position=%ld\n",i,t-1,(long)run.measured_angle_cdeg,(long)run.position_inc);
 }
 /* STOP和联锁仍带真实合成制动尾巴，不把反馈速度直接清零。 */
 frame(bytes,1000000);assert(NativePset_Decode(bytes,64,&p));start(&run,&p);FpgaProgram_Tick(&run,100,1);FpgaProgram_Stop(&run);
 FpgaProgram_Tick(&run,101,1);assert(run.state==FPGA_SIM_STOPPED&&run.velocity_inc_s==4185915392LL&&!run.result);
 FpgaProgram_Tick(&run,600,1);assert(run.velocity_inc_s==0&&!run.result);
 start(&run,&p);FpgaProgram_Tick(&run,100,1);FpgaProgram_Tick(&run,101,0);
 assert(run.state==FPGA_SIM_FAULT&&run.fault_code==0x7004&&run.velocity_inc_s==4185915392LL&&!run.result);
 /* 长程即使目标合法，也必须保留制动造成的INT32位置越界故障。 */
 p.steps[0].angle_cdeg=300000;p.steps[0].max_angle_cdeg=307199;start(&run,&p);
 for(i=1;i<2000&&run.state==FPGA_SIM_RUNNING;i++)FpgaProgram_Tick(&run,i,1);
 assert(run.state==FPGA_SIM_FAULT&&run.fault_code==0x7002&&!run.result);
 printf("position overflow protection at %u ms, no successful completion\n",i-1);
 assert(run.velocity_inc_s>0);FpgaProgram_Tick(&run,i+600,1);
 assert(run.state==FPGA_SIM_FAULT&&run.fault_code==0x7002&&run.velocity_inc_s==0&&!run.result);
 /* 走实际SDO接收适配入口，确认全64位到达OD，标准606C有效标志随范围变化。 */
 frame(Pset_buffer0x2030,1000000);Simulation_Receive(64);tick(0);control=1;tick(1);tick(51);
 assert(Velocity_actual_64_0x2212==2097152000LL&&Velocity_606C_valid0x2213&&Velocity_actual_value0x606C==2097152000);
 tick(101);assert(Velocity_actual_64_0x2212==4194304000LL&&!Velocity_606C_valid0x2213);
 assert(Velocity_actual_value0x606C==2097152000); /* 最后有效值不可经SDO冒充当前值，见真实回调测试。 */
 control=2;tick(102);assert(Velocity_actual_64_0x2212==4185915392LL&&!Velocity_606C_valid0x2213&&!step_result0x220D);
 tick(602);assert(Velocity_actual_64_0x2212==0&&Velocity_606C_valid0x2213&&Velocity_actual_value0x606C==0);
 control=3;tick(603);frame(Pset_buffer0x2030,1000000);Pset_buffer0x2030[43]=1;Simulation_Receive(64);tick(604);control=1;tick(605);tick(705);
 assert(Velocity_actual_64_0x2212==-4194304000LL&&!Velocity_606C_valid0x2213);
 control=2;tick(706);tick(1206);assert(Velocity_606C_valid0x2213&&Velocity_actual_value0x606C==0);
#elif FPGA_SIM_INT64 && FPGA_MODEL_PROFILE == 1
 frame(bytes,1000000);u32(bytes+3+8,14000);assert(NativePset_Decode(bytes,64,&p));start(&run,&p);
 for(i=1;i<1000&&run.state==FPGA_SIM_RUNNING;i++)FpgaProgram_Tick(&run,i,1);
 assert(run.state==FPGA_SIM_FAULT&&run.fault_code==0x7007&&!run.result);
 printf("hard-joint 1000rpm overtorque correctly NOK at %u ms\n",i-1);
#else
 /* 旧模式不能解码1000，运行时即使被直接注入过速，也不得32位回绕。 */
 frame(bytes,500000);assert(NativePset_Decode(bytes,64,&p));p.steps[0].speed_rpm_milli=1000000;start(&run,&p);FpgaProgram_Tick(&run,100,1);
 assert(run.state==FPGA_SIM_FAULT&&run.fault_code==0x7002&&!run.result);
#endif
 (void)run;(void)p;(void)tick;puts("velocity boundaries PASS");return 0;
}
