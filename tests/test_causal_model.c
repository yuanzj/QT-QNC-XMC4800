/* 独立夹具/字面预期验证，不以模型产生的结果重新生成预期。 */
#ifdef NDEBUG
#error Assertions must execute
#endif
#include <assert.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "../Simulation/native_pset.h"
#if FPGA_SIM_SCENARIO != 9
#error Build with scenario 9
#endif
static void u16(uint8_t *p,uint16_t v){p[0]=(uint8_t)v;p[1]=(uint8_t)(v>>8);}
static void u32(uint8_t *p,uint32_t v){unsigned i;for(i=0;i<4;i++)p[i]=(uint8_t)(v>>(8*i));}
static void frame(uint8_t p[64]){
 uint8_t *s=p+3;memset(p,0,64);p[0]=122;p[1]=2;p[2]=1;s[0]=3;u16(s+1,61);s[3]=1;
 u32(s+4,11000);u32(s+8,14000);u32(s+12,10000);u32(s+16,1000);u32(s+20,20000);
 u32(s+24,800);u32(s+28,1500);u32(s+32,3000);u32(s+36,1000);u32(s+41,30000);
 s[49]=s[50]=1;u16(s+51,5000);s[55]=s[56]=2;
}
static FpgaProgram decode(const uint8_t *p,uint16_t n){FpgaProgram program;assert(NativePset_Decode(p,n,&program));return program;}
static void start(FpgaProgramRun *r,const FpgaProgram *p){FpgaProgram_Reset(r);assert(FpgaProgram_Load(r,p));assert(FpgaProgram_Start(r,0,1));}
static unsigned finish(FpgaProgramRun *r,unsigned limit){unsigned t;for(t=1;t<=limit;t++){FpgaProgram_Tick(r,t,1);if(r->state!=FPGA_SIM_RUNNING)return t;}return 0;}
#if FPGA_MODEL_PROFILE == 1
static void test_failure_jump(void)
{
 uint8_t packet[3+3*96]={9,3,3};
 FpgaProgram program;
 FpgaProgramRun run;
 unsigned n,t;
 uint8_t visited=0;
 for(n=0;n<3;n++){
  uint8_t *step=packet+3+n*96;
  u32(step,300);u32(step+12,5000);
  step[20]=(uint8_t)(n+1);step[21]=3;step[22]=1;step[23]=2;
  u32(step+28,11000);u32(step+32,30000);u32(step+40,1000);
  u32(step+48,20000);u32(step+52,100000);u32(step+56,30000);
  u32(step+60,15000);u32(step+76,1);u32(step+80,1);
 }
 packet[3+23]=0x33;
 u32(packet+3+44,2000); /* 独立接头在目标扭矩时低于20°判定窗。 */
 assert(NativePset_Decode(packet,sizeof(packet),&program));
 start(&run,&program);
 for(t=1;t<5000&&run.state==FPGA_SIM_RUNNING;t++){
  visited|=(uint8_t)(1u<<(run.current_step-1u));
  FpgaProgram_Tick(&run,t,1);
 }
 assert(visited==0x05 && run.state==FPGA_SIM_DONE && !run.result && !run.all_ok);
 u32(packet+3+44,0);
 assert(NativePset_Decode(packet,sizeof(packet),&program));
 start(&run,&program);
 visited=0;
 for(t=1;t<5000&&run.state==FPGA_SIM_RUNNING;t++){
  visited|=(uint8_t)(1u<<(run.current_step-1u));
  FpgaProgram_Tick(&run,t,1);
 }
 assert(visited==0x07 && run.state==FPGA_SIM_DONE && run.result && run.all_ok);
 packet[3+23]=0x13;
 assert(!NativePset_Decode(packet,sizeof(packet),&program));
 packet[3+23]=0x43;
 assert(!NativePset_Decode(packet,sizeof(packet),&program));
 packet[3+23]=0x33;
 packet[3+2*96+23]=0x13;
 assert(!NativePset_Decode(packet,sizeof(packet),&program));
 packet[3+23]=2;
 u32(packet+3+2*96+44,2000);
 assert(NativePset_Decode(packet,sizeof(packet),&program));
 start(&run,&program);
 assert(finish(&run,9000)>0 && run.state==FPGA_SIM_FAULT);
 assert(run.fault_code==FPGA_SIM_INVALID_FAILURE_JUMP && !run.result);
}
#endif
int main(void){
 uint8_t bytes[64],other[64];FpgaProgram p,q;FpgaProgramRun a,b;unsigned t;
 frame(bytes);p=decode(bytes,64);assert(p.steps[0].speed_rpm_milli==30000&&p.steps[0].strategy==1);
 memcpy(other,bytes,64);other[6]=4;assert(NativePset_Decode(other,64,&q)&&q.steps[0].strategy==4);
 other[6]=1;other[60]=1;assert(!NativePset_Decode(other,64,&q)); /* auto adjust未实现明确拒绝 */
 memcpy(other,bytes,64);other[3]=1;assert(!NativePset_Decode(other,64,&q)); /* 未实现认帽不假OK */
#if FPGA_MODEL_PROFILE == 1
 test_failure_jump();
 start(&a,&p);t=finish(&a,5000);assert(t==2076&&a.state==FPGA_SIM_DONE&&a.result==1);
 assert(a.torque_raw==414&&a.position_inc==7927234&&a.velocity_inc_s==0); /* 独立1ms积分字面预期 */
 printf("hard-normal ticks=%u raw_torque=%d position=%ld\n",t,a.torque_raw,(long)a.position_inc);
 q=p;q.steps[0].speed_rpm_milli=100000;start(&b,&q);t=finish(&b,5000);
 assert(t<2076&&b.state==FPGA_SIM_FAULT&&b.fault_code==0x7007&&b.velocity_inc_s>0); /* 不把制动速度假置0 */
 q=p;q.steps[0].speed_rpm_milli=100000;q.steps[0].accel_time_ms=200;start(&b,&q);FpgaProgram_Tick(&b,100,1);
 assert(b.plant.velocity_rpm_milli==50000&&b.plant.position_q==1515*MODEL_ANGLE_Q);
 q=p;q.steps[0].speed_rpm_milli=100000;start(&a,&q);FpgaProgram_Tick(&a,100,1);assert(a.plant.position_q==6000*MODEL_ANGLE_Q);
 q=p;q.steps[0].speed_rpm_milli=100000;q.steps[0].torque_mnm=12000;start(&b,&q);FpgaProgram_Tick(&b,100,1);
 assert(a.plant.position_q==b.plant.position_q&&a.torque_raw==b.torque_raw); /* 改目标不改同指令下的接头反馈 */
 q=p;q.steps[0].strategy=2;q.steps[0].safe_torque_mnm=1000;start(&b,&q);assert(finish(&b,5000)==2005&&b.fault_code==0x7005);
 q=p;q.steps[0].safe_torque_mnm=1000;start(&b,&q);assert(finish(&b,5000)==2076&&b.result); /* 扭矩策略下安全扭矩不是图中活动保护 */
 q=p;q.steps[0].safe_angle_cdeg=500;start(&b,&q);assert(finish(&b,5000)==2033&&b.fault_code==0x7006);
 q=p;q.steps[0].strategy=3;q.steps[0].angle_cdeg=500;q.steps[0].min_torque_mnm=0;q.steps[0].min_angle_cdeg=0;
 start(&b,&q);t=finish(&b,5000);assert(t<2076&&b.result&&b.angle_hit&&!b.torque_hit&&b.measured_torque_mnm<11000);
 q=p;q.steps[0].strategy=4;q.steps[0].angle_cdeg=2000;q.steps[0].max_angle_cdeg=3000;q.steps[0].max_torque_mnm=30000;q.steps[0].safe_torque_mnm=29000;
 start(&b,&q);assert(finish(&b,5000)>2076&&b.result&&b.angle_hit&&b.torque_hit&&b.measured_angle_cdeg>=2000);
 q=p;q.steps[0].strategy=2;q.steps[0].angle_cdeg=500;start(&b,&q);assert(finish(&b,5000)<2076&&b.state==FPGA_SIM_DONE&&!b.result&&b.last_nok_reason==1);
 start(&b,&p);FpgaProgram_Tick(&b,100,1);FpgaProgram_Stop(&b);assert(b.velocity_inc_s>0&&b.state==FPGA_SIM_STOPPED);FpgaProgram_Tick(&b,120,1);assert(!b.velocity_inc_s&&!b.result);
 start(&b,&p);FpgaProgram_Tick(&b,100,1);FpgaProgram_Tick(&b,101,0);assert(b.state==FPGA_SIM_FAULT&&b.fault_code==0x7004&&b.velocity_inc_s>0);
 q=p;q.count=2;q.steps[0].angle_cdeg=2500;q.steps[0].min_angle_cdeg=2000;q.steps[0].max_angle_cdeg=3000;q.steps[0].failure_action=1;
 memset(&q.steps[1],0,sizeof(q.steps[1]));q.steps[1].kind=4;q.steps[1].duration_ms=100;q.steps[1].timeout_ms=1000;q.steps[1].failure_action=2;
 start(&b,&q);FpgaProgram_Tick(&b,1000,1);FpgaProgram_Tick(&b,2000,1);FpgaProgram_Tick(&b,2076,1);assert(b.pending_next&&!b.result&&b.current_step==1);FpgaProgram_Tick(&b,2096,1);assert(b.current_step==2);FpgaProgram_Tick(&b,2196,1);assert(b.state==FPGA_SIM_DONE&&!b.result&&!b.all_ok);
 q.steps[0].failure_action=2;start(&b,&q);assert(finish(&b,3000)==2076&&b.current_step==0&&!b.result);
 {
  uint8_t data[39]={123,2,1,2,36,0};uint8_t *st=data+3;
  st[3]=2;u32(st+4,30000);u16(st+14,2000);st[18]=2;st[19]=1;u32(st+24,3000);u32(st+28,20000);
  q=decode(data,sizeof(data));start(&b,&q);assert(finish(&b,1000)==182&&b.result&&b.measured_angle_cdeg==3132);
  st[3]=1;assert(!NativePset_Decode(data,sizeof(data),&q)); /* 缺安全角度不假装可验扭矩下旋 */
 }
 {
  uint8_t data[90];uint8_t *st=data+64;frame(data);data[2]=2;memset(st,0,26);st[0]=5;u16(st+1,26);
  u32(st+3,20000);u32(st+11,500);u32(st+15,30000);u16(st+21,2000);st[25]=2;
  q=decode(data,sizeof(data));start(&b,&q);t=finish(&b,5000);
  assert(t==2139+FPGA_STEP_ORIGIN_WINDOW_MS&&b.result&&b.position_inc==-4404019&&b.measured_angle_cdeg==630&&b.torque_raw<0);
 }
 q=p;q.steps[0].post_delay_ms=50;start(&b,&q);assert(finish(&b,5000)==2126&&b.result);
 start(&b,&p);FpgaProgram_Tick(&b,2001,1);assert(b.state==FPGA_SIM_FAULT&&b.fault_code==0x700A);
 start(&b,&p);FpgaProgram_Tick(&b,100,1);assert(b.plant.velocity_rpm_milli==30000);
 b.plant.valid=0;FpgaProgram_Tick(&b,101,1);
 assert(b.state==FPGA_SIM_FAULT&&b.fault_code==0x700B&&!b.result);
 assert(b.plant.velocity_rpm_milli==28000&&b.velocity_inc_s>0);
 FpgaProgram_Tick(&b,115,1);assert(b.plant.velocity_rpm_milli==0&&b.velocity_inc_s==0);
 assert(!FpgaProgram_Load(&b,&p));
 b.plant.valid=1;FpgaProgram_Stop(&b);
 assert(b.state==FPGA_SIM_FAULT&&!FpgaProgram_Load(&b,&p)&&!FpgaProgram_Start(&b,116,1));
 FpgaProgram_Reset(&b);assert(FpgaProgram_Load(&b,&p)&&FpgaProgram_Start(&b,0,1));
 assert(finish(&b,5000)==2076&&b.result);
#elif FPGA_MODEL_PROFILE == 2
 p.steps[0].speed_rpm_milli=100000;
 p.steps[0].min_angle_cdeg=90000;p.steps[0].max_angle_cdeg=120000;p.steps[0].safe_angle_cdeg=150000;
 start(&a,&p);t=finish(&a,5000);assert(t>2000&&t<3000&&a.result&&a.measured_angle_cdeg>=90000&&a.measured_angle_cdeg<=120000);printf("soft-normal ticks=%u angle=%ld\n",t,(long)a.measured_angle_cdeg);
#elif FPGA_MODEL_PROFILE == 3
 start(&a,&p);t=finish(&a,6000);assert(t>=5000&&t<5100&&!a.result&&a.last_nok_reason==3&&a.measured_angle_cdeg==0&&a.torque_raw<33);printf("free-run timeout ticks=%u\n",t);
#else
 start(&a,&p);t=finish(&a,1000);assert(t>0&&t<100&&!a.result&&a.state==FPGA_SIM_FAULT&&a.fault_code==0x7007);printf("jam protection ticks=%u\n",t);
#endif
 (void)other;(void)q;(void)b;puts("causal profile PASS");return 0;
}
