/* 真实96B下旋扭矩模式：按独立反馈触发停止；保护/超时不因模式切换失效。 */
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "../Simulation/native_pset.h"
static void put(uint8_t *p,uint32_t v){for(unsigned i=0;i<4;i++)p[i]=(uint8_t)(v>>(8*i));}
static void rundown(uint8_t *s,unsigned seq)
{
 put(s,300);put(s+12,5000);s[20]=(uint8_t)seq;s[21]=2;s[22]=1;s[23]=2;
 put(s+28,6000);put(s+32,1000);put(s+36,2000);put(s+40,20000);put(s+44,100000);put(s+48,1);put(s+52,1);
}
#if FPGA_MODEL_PROFILE == 1
static void snug(uint8_t *s)
{
 put(s,300);put(s+12,5000);s[20]=2;s[21]=3;s[22]=1;s[23]=2;
 put(s+28,11000);put(s+32,14000);put(s+36,10000);put(s+40,1000);put(s+48,20000);put(s+52,100000);put(s+56,20000);put(s+60,1000);put(s+76,1);put(s+80,1);
}
#endif
static FpgaProgram decode(const uint8_t *b,unsigned count)
{FpgaProgram p;assert(NativePset_Decode(b,(uint16_t)(3+96*count),&p));return p;}
static void start(FpgaProgramRun *r,const FpgaProgram *p)
{FpgaProgram_Reset(r);assert(FpgaProgram_Load(r,p));assert(FpgaProgram_Start(r,0,1));}
static unsigned finish(FpgaProgramRun *r)
{unsigned t=r->last_tick_ms;while(r->state==FPGA_SIM_RUNNING&&t<8000)FpgaProgram_Tick(r,++t,1);assert(t<8000);return t;}
#if FPGA_MODEL_PROFILE == 1
static void test_auto_adjust(void)
{
 uint8_t b[99]={9,3,1};
 uint8_t *step=b+3;
 FpgaProgramRun r;
 unsigned t;
 rundown(step,1);
 put(step+36,8000);
 put(step+56,1);put(step+60,10);put(step+64,50);put(step+68,1000);
 FpgaProgram p=decode(b,1);
 start(&r,&p);
 for(t=1;t<3000&&r.measured_torque_mnm<1500;t++)FpgaProgram_Tick(&r,t,1);
 assert(r.measured_torque_mnm>=1500&&r.plant.velocity_rpm_milli==30000&&!r.braking);
 FpgaProgram_Tick(&r,t,1);
 assert(r.plant.velocity_rpm_milli==FPGA_MODEL_MAX_RPM_MILLI/100);
 finish(&r);
 assert(r.result&&r.peak_torque_mnm>=8000);
 put(step+68,500);
 p=decode(b,1);
 start(&r,&p);
 for(t=1;t<5000&&r.measured_torque_mnm<=4200;t++)FpgaProgram_Tick(&r,t,1);
 assert(r.measured_torque_mnm>4200&&!r.braking);
 FpgaProgram_Tick(&r,t,1);
 assert(r.plant.velocity_rpm_milli>0&&r.plant.velocity_rpm_milli<(int32_t)(FPGA_MODEL_MAX_RPM_MILLI/100));
 finish(&r);
 assert(r.result&&r.peak_torque_mnm>=8000);
}
#endif
int main(void)
{
 uint8_t b[195]={9,3,1},bad[195];FpgaProgram p,q;FpgaProgramRun r,a;unsigned t;
 rundown(b+3,1);p=decode(b,1);assert(p.steps[0].kind==2&&p.steps[0].strategy==1&&p.steps[0].torque_mnm==2000);
 memcpy(bad,b,sizeof(b));put(bad+27,2);q=p;assert(!NativePset_Decode(bad,99,&q)&&!memcmp(&p,&q,sizeof(p)));
 memcpy(bad,b,sizeof(b));put(bad+39,0);assert(!NativePset_Decode(bad,99,&q));
 memcpy(bad,b,sizeof(b));put(bad+47,307200);assert(!NativePset_Decode(bad,99,&q));
 /* 在目标停止之前，改目标不得改变接头；两种模式均保持旧角度分支可用。 */
 start(&r,&p);q=p;q.steps[0].torque_mnm=4000;start(&a,&q);
 for(t=1;t<=1000;t++){FpgaProgram_Tick(&r,t,1);FpgaProgram_Tick(&a,t,1);assert(!r.braking&&!a.braking);assert(r.plant.position_q==a.plant.position_q&&r.plant.torque_mnm==a.plant.torque_mnm);}
#if FPGA_MODEL_PROFILE == 1
 test_auto_adjust();
 finish(&r);assert(r.state==FPGA_SIM_DONE&&r.result&&r.peak_torque_mnm>=2000&&r.velocity_inc_s==0);
 printf("torque target2 final=%ld angle=%ld\n",(long)r.peak_torque_mnm,(long)r.measured_angle_cdeg);
 q=p;q.steps[0].safe_angle_cdeg=50;start(&r,&q);finish(&r);assert(r.state==FPGA_SIM_FAULT&&r.fault_code==0x7006&&!r.result);
 /* 下旋的两个安全值都是全程上限，不仅监测另一种模式的安全值。 */
 q=p;q.steps[0].safe_torque_mnm=3000;start(&r,&q);finish(&r);assert(r.state==FPGA_SIM_FAULT&&r.fault_code==0x7005&&!r.result);
 q=p;q.steps[0].speed_rpm_milli=300000;start(&r,&q);finish(&r);assert(r.state==FPGA_SIM_FAULT&&r.fault_code==0x7005&&!r.result);
 q=p;q.steps[0].strategy=2;q.steps[0].angle_threshold_mnm=0;q.steps[0].safe_angle_cdeg=6100;start(&r,&q);finish(&r);assert(r.state==FPGA_SIM_FAULT&&r.fault_code==0x7006&&!r.result);
 /* 同一接头连续经历扭矩下旋再拧紧，步间不换成新试件。 */
 b[2]=2;snug(b+99);q=decode(b,2);start(&r,&q);unsigned entered=0;
 for(t=1;t<8000&&r.state==FPGA_SIM_RUNNING;t++){FpgaProgram_Tick(&r,t,1);if(r.current_step==2&&!entered){entered=1;assert(r.plant.position_q>36000*MODEL_ANGLE_Q);}}
 assert(entered&&r.state==FPGA_SIM_DONE&&r.result);b[2]=1;
#else
 finish(&r);assert(r.state==FPGA_SIM_DONE&&!r.result&&r.last_nok_reason==3); /* 空转达不到扭矩，不伪造成功 */
#endif
 q=p;q.steps[0].timeout_ms=100;start(&r,&q);assert(finish(&r)>=100&&r.state==FPGA_SIM_DONE&&!r.result&&r.last_nok_reason==3);
 q=p;q.steps[0].strategy=2;q.steps[0].angle_threshold_mnm=0;start(&r,&q);finish(&r);assert(r.result&&r.measured_angle_cdeg>=6000);
 q=p;q.steps[0].decel_time_ms=1000;start(&r,&q);FpgaProgram_Tick(&r,100,1);FpgaProgram_Stop(&r);t=r.last_tick_ms;while(r.velocity_inc_s&&t<130)FpgaProgram_Tick(&r,++t,1);assert(r.state==FPGA_SIM_STOPPED&&!r.result&&!r.velocity_inc_s);
 puts("rundown torque PASS");return 0;
}
