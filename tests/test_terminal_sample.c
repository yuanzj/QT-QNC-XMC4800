/* 实际适配入口的终态归属：保护触发样本属于原工步，随后清步；STOP不延迟。 */
#include <assert.h>
#include <stdint.h>
#include <string.h>
#include "../FpgaSim/fpga_program.h"
#include "../Simulation/ethercat_adapter.h"
uint8_t Pset_buffer0x2030[1600];
uint32_t controller_status0x2001,status_code0x2200,status_code20x2201;
uint16_t pset_echo0x220B;
uint8_t step_echo0x220C,step_result0x220D;
int16_t Torque_actual_value0x6077;
int32_t Position_actual_value0x6064,Velocity_actual_value0x606C;
int64_t Velocity_actual_64_0x2212;
uint8_t Velocity_606C_valid0x2213;
static uint32_t now;
static uint8_t control;
uint32_t HW_GetTimer(void){return now;}
uint8_t App_JobCtrl_GetControl(void){return control;}
void App_JobCtrl_SetControl(uint8_t v){control=v;}
uint8_t App_JobCtrl_GetPsetNo(void){return 2;}
uint8_t App_Link_IsOperational(void){return 1;}
static void put(uint8_t *p,uint32_t v){for(unsigned i=0;i<4;i++)p[i]=(uint8_t)(v>>(8*i));}
static void tick(void){++now;Simulation_Tick();}
static void frame(uint32_t speed){
 uint8_t *s=Pset_buffer0x2030+3;
 memset(Pset_buffer0x2030,0,sizeof(Pset_buffer0x2030));
 Pset_buffer0x2030[0]=2;Pset_buffer0x2030[1]=3;Pset_buffer0x2030[2]=1;
 put(s,speed);put(s+12,10000);s[20]=1;s[21]=3;s[22]=1;s[23]=2;
 put(s+28,11000);put(s+32,14000);put(s+36,10000);put(s+40,1000);
 put(s+48,20000);put(s+52,100000);put(s+56,30000);put(s+60,15000);
 put(s+72,1);put(s+76,1);put(s+80,1);
}
static void start(uint16_t length){
 Simulation_Receive(length);tick();control=1;tick();assert(Simulation_IsRunning());
}
static void load(uint32_t speed){frame(speed);start(99);}
static void load_entry_fault(void){
 uint8_t *second=Pset_buffer0x2030+99;
 frame(300);Pset_buffer0x2030[2]=2;
 memcpy(second,Pset_buffer0x2030+3,96);
 second[20]=2;second[22]=2;
 put(second+24,1);put(second+32,12300);put(second+36,0);put(second+40,0);put(second+60,200);
 start(195);
}
static void load_origin_check(uint8_t direction){
 uint8_t *second=Pset_buffer0x2030+99;
 frame(300);Pset_buffer0x2030[2]=2;
 memcpy(second,Pset_buffer0x2030+3,96);
 second[20]=2;second[22]=direction;
 put(second,1800);put(second+24,1);put(second+32,30000);
 put(second+36,0);put(second+40,0);put(second+60,200);
 start(195);
}
static void test_step_origin(uint8_t direction){
 uint32_t started,transition,published;
 load_origin_check(direction);started=now;
 while(step_echo0x220C==1&&now-started<4000)tick();
 assert(step_echo0x220C==2&&Position_actual_value0x6064==0&&Velocity_actual_value0x606C==0);
 transition=now-started;
 control=3;tick();load_origin_check(direction);started=now;
 while(now-started<transition-1)tick();
 assert(step_echo0x220C==1);
 now+=3;Simulation_Tick(); /* 补跑跨步边界，入口必须对外可见。 */
 assert(step_echo0x220C==2&&Position_actual_value0x6064==0&&Velocity_actual_value0x606C==0);
 published=now;
 while(now-published<FPGA_STEP_ORIGIN_WINDOW_MS){
  tick();
  assert(step_echo0x220C==2&&Position_actual_value0x6064==0&&Velocity_actual_value0x606C==0);
 }
 tick();
 assert(step_echo0x220C==2&&((Position_actual_value0x6064>0)==(direction==1)));
 assert(Position_actual_value0x6064!=0&&Velocity_actual_value0x606C!=0);
 control=2;tick();assert(!Simulation_IsRunning()&&step_echo0x220C==0);
 control=3;tick();assert(step_echo0x220C==0&&status_code0x2200==0);
}
static void test_completion_window(void){
 uint32_t started,duration,finished;
 int16_t torque;
 int32_t position;
 load(300);started=now;
 while(Simulation_IsRunning()&&now-started<4000)tick();
 assert(!Simulation_IsRunning()&&status_code0x2200==0&&step_result0x220D==1&&step_echo0x220C==1);
 duration=now-started;torque=Torque_actual_value0x6077;position=Position_actual_value0x6064;
 assert(torque>0&&Velocity_actual_value0x606C==0);
 control=3;tick();load(300);started=now;
 while(now-started<duration-1)tick();
 assert(Simulation_IsRunning());
 now+=3;Simulation_Tick(); /* 同一次适配调用跨过实际收口，旧版已经输出卸载值。 */
 finished=started+duration;
 while(now-finished<FPGA_STEP_RESULT_WINDOW_MS){
  assert(!Simulation_IsRunning()&&status_code0x2200==0&&step_result0x220D==1);
  assert(pset_echo0x220B==0x0201&&step_echo0x220C==1);
  assert(Torque_actual_value0x6077==torque&&Position_actual_value0x6064==position&&Velocity_actual_value0x606C==0);
  tick();
 }
 assert(pset_echo0x220B==0x0200&&step_echo0x220C==0&&Torque_actual_value0x6077<torque);
 control=3;tick();load(300);
 while(Simulation_IsRunning())tick();
 assert(step_echo0x220C==1);
 control=2;tick();assert(!Simulation_IsRunning()&&step_echo0x220C==0);
 control=3;tick();assert(!Simulation_IsRunning()&&step_echo0x220C==0&&status_code0x2200==0);
}
static void test_entry_fault_echo(void){
 const uint32_t limit=now+4000;
 uint32_t fault_ms;
 load_entry_fault();
 while(Simulation_IsRunning()&&now<limit)tick();
 assert(status_code0x2200==0x7007&&step_result0x220D==0&&Torque_actual_value0x6077==414);
 assert(pset_echo0x220B==0x0202&&step_echo0x220C==2);
 fault_ms=now;
 while(now-fault_ms+1<FPGA_STEP_RESULT_WINDOW_MS){
  tick();
  assert(!Simulation_IsRunning()&&step_echo0x220C==2&&status_code0x2200==0x7007&&step_result0x220D==0);
  assert(Position_actual_value0x6064==0&&Velocity_actual_value0x606C==0);
 }
 assert(Torque_actual_value0x6077==0); /* 不重复发送触发时的扭矩快照。 */
 tick();assert(pset_echo0x220B==0x0200&&step_echo0x220C==0&&status_code0x2200==0x7007);
 control=3;tick();assert(step_echo0x220C==0&&status_code0x2200==0);
 load_entry_fault();
 while(Simulation_IsRunning()&&now<limit+4000)tick();
 assert(step_echo0x220C==2);
 control=2;tick();assert(!Simulation_IsRunning()&&step_echo0x220C==0);
 control=3;tick();assert(step_echo0x220C==0&&status_code0x2200==0);
}
int main(void){
 load(3000);while(Simulation_IsRunning()&&now<10000)tick();
 assert(status_code0x2200==0x7007&&step_result0x220D==0);
 assert(Torque_actual_value0x6077>466); /* 14Nm保护阈值；必须保留真实越限采样。 */
 assert(pset_echo0x220B==0x0201&&step_echo0x220C==1);
 tick();assert(pset_echo0x220B==0x0200&&step_echo0x220C==0);
 control=3;tick();test_completion_window();
 control=3;tick();load(300);control=2;tick();assert(!Simulation_IsRunning()&&step_echo0x220C==0);
 /* 追踪的是实际消费：同拍前被STOP覆盖的START不应冒充已运行。 */
 {
  uint32_t starts=Simulation_ControlDiagnostics.start_commands;
  uint32_t stops=Simulation_ControlDiagnostics.stop_commands;
  uint32_t running=Simulation_ControlDiagnostics.running_ticks;
  uint32_t sequence=Simulation_ControlDiagnostics.sequence;
  control=1;control=2;tick();
  assert(!Simulation_IsRunning()&&step_echo0x220C==0);
  assert(Simulation_ControlDiagnostics.start_commands==starts);
  assert(Simulation_ControlDiagnostics.stop_commands==stops+1);
  assert(Simulation_ControlDiagnostics.running_ticks==running);
  assert(Simulation_ControlDiagnostics.sequence==sequence+1);
  for(unsigned i=0;i<40;i++){control=2;tick();}
  assert(Simulation_ControlDiagnostics.magic==0x54434E51u);
  assert(Simulation_ControlDiagnostics.capacity==32);
  sequence=Simulation_ControlDiagnostics.sequence;
  for(unsigned i=0;i<32;i++){
   unsigned slot=(Simulation_ControlDiagnostics.write_index+i)%32;
   assert(Simulation_ControlDiagnostics.entries[slot].sequence==sequence-31+i);
   assert(Simulation_ControlDiagnostics.entries[slot].command==2);
   assert(Simulation_ControlDiagnostics.entries[slot].output_step==0);
  }
 }
 test_entry_fault_echo();
 test_step_origin(1);
 test_step_origin(2);
 return 0;
}
