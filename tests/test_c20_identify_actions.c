/* New identify header preserves the original load and declared failure actions. */
#include <assert.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "../Simulation/native_pset.h"
static void put(uint8_t *p,uint32_t v){for(unsigned i=0;i<4;++i)p[i]=(uint8_t)(v>>(8*i));}
static void packet(uint8_t bytes[291],uint8_t action)
{
 memset(bytes,0,291);bytes[0]=7;bytes[1]=3;bytes[2]=3;
 for(unsigned i=0;i<3;++i){
  uint8_t *s=bytes+3+96*i;put(s,300);put(s+12,5000);s[20]=(uint8_t)(i+1);s[21]=3;s[22]=1;s[23]=2;
  uint32_t v[15]={1,0,30000,0,0,0,10000,0,30000,1,0,0,0,1,1};
  for(unsigned j=0;j<15;++j)put(s+24+4*j,v[j]);
 }
 uint8_t *s=bytes+3;memset(s,0,96);put(s,300);put(s+12,100);s[20]=1;s[21]=1;s[22]=1;s[23]=action;
 put(s+24,1000);put(s+28,500);put(s+32,200);put(s+36,3);
}
int main(void)
{
 uint8_t bytes[291];FpgaProgram p;FpgaProgramRun r;
 for(unsigned action=1;action<=3;++action){
  packet(bytes,action==3?0x33:(uint8_t)action);assert(NativePset_Decode(bytes,291,&p));
  assert(p.steps[0].timeout_ms==100&&p.steps[0].engage_repeat_count==3&&p.steps[0].failure_action==action);
  FpgaProgram_Reset(&r);assert(FpgaProgram_Load(&r,&p));assert(FpgaProgram_Start(&r,0,1));
  uint8_t visited=0;
  for(unsigned t=1;t<10000&&r.state==FPGA_SIM_RUNNING;++t){
   if(r.current_step)visited|=(uint8_t)(1U<<(r.current_step-1));FpgaProgram_Tick(&r,t,1);
  }
  assert(r.state==FPGA_SIM_DONE&&!r.result);
  assert(visited==(action==1?7:action==2?1:5));
 }
 puts("identify advanced timeout and continue/stop/jump preserve independent load PASS");return 0;
}
