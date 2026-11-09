/* 减速参数从真实96B字节进入控制；独立接头不改，正常斜坡不旁路保护/超时/停止。 */
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "../Simulation/native_pset.h"
static void put(uint8_t *p,uint32_t v){for(unsigned i=0;i<4;i++)p[i]=(uint8_t)(v>>(8*i));}
static FpgaProgram decode(unsigned ms,unsigned angle,unsigned reverse)
{
 uint8_t b[99]={0},*s=b+3;FpgaProgram p;b[0]=9;b[1]=3;b[2]=1;
 put(s,300);put(s+8,ms);put(s+12,10000);s[20]=1;s[21]=3;s[22]=(uint8_t)(reverse?2:1);s[23]=2;
 put(s+24,angle?1:0);put(s+28,2000);put(s+32,30000);put(s+40,angle?0:1000);put(s+48,20000);put(s+52,100000);put(s+56,30000);put(s+60,angle?3000:15000);put(s+72,1);put(s+76,1);put(s+80,1);
 assert(NativePset_Decode(b,sizeof(b),&p));return p;
}
static void start(FpgaProgramRun *r,const FpgaProgram *p){FpgaProgram_Reset(r);assert(FpgaProgram_Load(r,p));assert(FpgaProgram_Start(r,0,1));}
static unsigned brake(FpgaProgramRun *r){for(unsigned t=1;t<10000;t++){FpgaProgram_Tick(r,t,1);if(r->braking)return t;assert(r->state==FPGA_SIM_RUNNING);}assert(0);return 0;}
static unsigned finish(FpgaProgramRun *r){unsigned t=r->last_tick_ms;while(r->state==FPGA_SIM_RUNNING&&t<12000)FpgaProgram_Tick(r,++t,1);assert(t<12000);return t;}
static void check_ramp(unsigned ms,unsigned reverse)
{
 FpgaProgram p=decode(ms,1,reverse);FpgaProgramRun r;start(&r,&p);unsigned at=brake(&r),end=finish(&r);
 assert(r.state==FPGA_SIM_DONE&&r.result&&r.velocity_inc_s==0);assert(end-at==(ms<15?15:ms));assert(r.measured_angle_cdeg>=3000);
 printf("angle dir=%u decel=%u stopped_after=%u ms\n",reverse,ms,end-at);
}
int main(void)
{
 FpgaProgram p,q;FpgaProgramRun r,a;unsigned t,at,end;
 for(unsigned direction=0;direction<2;direction++){check_ramp(1,direction);check_ramp(100,direction);check_ramp(200,direction);}
 p=decode(100,1,0);q=decode(200,1,0);start(&r,&p);start(&a,&q);
 for(t=1;t<160;t++){FpgaProgram_Tick(&r,t,1);FpgaProgram_Tick(&a,t,1);assert(!r.braking&&!a.braking);assert(r.plant.position_q==a.plant.position_q&&r.plant.torque_mnm==a.plant.torque_mnm);}
 /* 0路径沿用15ms夹具自然制动，不能被新的参数接入改写。 */
 p=decode(0,1,0);start(&r,&p);at=brake(&r);end=finish(&r);assert(end-at==15&&r.result);
 /* 运动中STOP/撤联锁不等已配置的一秒慢斜坡。 */
 p=decode(1000,1,1);start(&r,&p);at=brake(&r);FpgaProgram_Tick(&r,at+10,1);FpgaProgram_Stop(&r);t=r.last_tick_ms;
 while(r.velocity_inc_s&&t<at+40)FpgaProgram_Tick(&r,++t,1);assert(r.state==FPGA_SIM_STOPPED&&!r.result&&!r.velocity_inc_s&&t<=at+25);
 start(&r,&p);at=brake(&r);FpgaProgram_Tick(&r,at+1,0);assert(r.state==FPGA_SIM_FAULT&&r.fault_code==0x7004);t=r.last_tick_ms;
 while(r.velocity_inc_s&&t<at+30)FpgaProgram_Tick(&r,++t,1);assert(!r.velocity_inc_s&&t<=at+15);
#if FPGA_MODEL_PROFILE == 1
 p=decode(0,0,0);start(&r,&p);finish(&r);assert(r.result);int32_t zero=r.peak_torque_mnm;
 p=decode(100,0,0);start(&r,&p);finish(&r);assert(r.result&&r.peak_torque_mnm>zero);int32_t hundred=r.peak_torque_mnm;
 p=decode(200,0,0);start(&r,&p);finish(&r);assert(r.result&&r.peak_torque_mnm>hundred);
 p=decode(400,0,0);p.steps[0].max_torque_mnm=20000;start(&r,&p);finish(&r);assert(r.state==FPGA_SIM_FAULT&&r.fault_code==0x7007&&!r.result);
 p=decode(1000,0,0);p.steps[0].timeout_ms=2080;start(&r,&p);end=finish(&r);assert(r.state==FPGA_SIM_DONE&&!r.result&&r.last_nok_reason==3&&end<2120);
#endif
 /* 超过60000ms显式拒绝并保持调用方旧程序。 */
 {uint8_t b[99]={0};b[0]=9;b[1]=3;b[2]=1;put(b+3,300);put(b+11,60001);put(b+15,10000);b[23]=1;b[24]=3;b[25]=1;b[26]=2;q=p;assert(!NativePset_Decode(b,sizeof(b),&p));assert(!memcmp(&p,&q,sizeof(p)));}
 puts("deceleration PASS");return 0;
}
