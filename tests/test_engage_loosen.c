/* HMI实际模式3输入验证认帽/有载松脱；接头仍为固定夹具，目标不进入反馈模型。 */
#ifdef NDEBUG
#error Assertions must execute
#endif
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "../Simulation/native_pset.h"
static void put(uint8_t *p,uint32_t v){unsigned i;for(i=0;i<4;i++)p[i]=(uint8_t)(v>>(8*i));}
static uint8_t *common(uint8_t *p,unsigned index,uint8_t type,uint8_t direction)
{
 uint8_t *s=p+3+96*index;put(s,300);put(s+12,type==1?0:5000);s[20]=(uint8_t)(index+1);s[21]=type;s[22]=direction;s[23]=type==1?0:2;return s;
}
static void snug(uint8_t *p,unsigned index)
{
 uint8_t *s=common(p,index,3,1);uint32_t v[15]={0,11000,14000,10000,1000,0,20000,30000,20000,1000,0,0,0,1,1};unsigned i;
 for(i=0;i<15;i++)put(s+24+4*i,v[i]);
}
static void engage(uint8_t *p,uint8_t direction,uint32_t angle,uint32_t count)
{
 uint8_t *s=common(p,0,1,direction);put(s,100);put(s+4,100);put(s+24,1500);put(s+28,angle);put(s+32,100);put(s+36,count);
}
static void loosen(uint8_t *p,unsigned index,uint8_t strategy)
{
 uint8_t *s=common(p,index,5,2);uint32_t v[10]={strategy,2000,30000,0,5000,30000,2000,0,0,10000};unsigned i;
 for(i=0;i<10;i++)put(s+24+4*i,v[i]);
}
static FpgaProgram program(const uint8_t *p,unsigned size)
{FpgaProgram q;assert(NativePset_Decode(p,(uint16_t)size,&q));return q;}
static void start(FpgaProgramRun *r,const FpgaProgram *p)
{FpgaProgram_Reset(r);assert(FpgaProgram_Load(r,p));assert(FpgaProgram_Start(r,0,1));}
static unsigned finish(FpgaProgramRun *r,unsigned until)
{unsigned t;for(t=1;t<=until;t++){FpgaProgram_Tick(r,t,1);if(r->state!=FPGA_SIM_RUNNING)return t;}return 0;}
int main(void)
{
 uint8_t raw[291]={9,3,2},bad[291];FpgaProgram p,q;FpgaProgramRun r,a;unsigned t;uint8_t negative=0,positive=0,second=0,unloaded=0,loaded=0;
 engage(raw,1,40000,1);snug(raw,1);p=program(raw,195);assert(p.steps[0].kind==1);
 memcpy(bad,raw,195);put(bad+3+36,0);assert(!NativePset_Decode(bad,195,&q));
 memcpy(bad,raw,195);put(bad+3+36,16);assert(!NativePset_Decode(bad,195,&q));
 memcpy(bad,raw,195);bad[3+22]=5;assert(!NativePset_Decode(bad,195,&q));
 memcpy(bad,raw,195);put(bad+3+40,1);assert(!NativePset_Decode(bad,195,&q)); /* 保留槽不静默忽略 */
#if FPGA_MODEL_PROFILE == 1
 start(&r,&p);assert(finish(&r,12000)>6000&&r.result&&r.state==FPGA_SIM_DONE);
 printf("engage+snug: final raw torque=%d\n",r.torque_raw);
 engage(raw,3,3000,3);p=program(raw,195);start(&r,&p);
 for(t=1;t<10000&&r.state==FPGA_SIM_RUNNING;t++){FpgaProgram_Tick(&r,t,1);assert(r.current_step<=1);if(r.velocity_inc_s<0)negative=1;if(r.velocity_inc_s>0)positive=1;}
 assert(negative&&positive&&r.state==FPGA_SIM_DONE&&!r.result&&r.last_nok_reason==5&&r.measured_torque_mnm<1500);printf("engage-exhausted ticks=%u\n",t);
 start(&r,&p);for(t=1;t<2000;t++){FpgaProgram_Tick(&r,t,1);if(r.search_waiting)break;}assert(r.search_waiting&&r.search_attempt==1);
 FpgaProgram_Stop(&r);FpgaProgram_Tick(&r,t+200,1);assert(r.state==FPGA_SIM_STOPPED&&r.search_attempt==1&&!r.result);
 engage(raw,1,40000,1);put(raw+3,3000);p=program(raw,195);start(&r,&p);assert(finish(&r,2000)&&r.state==FPGA_SIM_FAULT&&r.fault_code==0x7007); /* 两种速度宽度都合法的300rpm仍应真实越限 */
 engage(raw,1,40000,1);p=program(raw,195);start(&r,&p);FpgaProgram_Tick(&r,100,1);FpgaProgram_Tick(&r,101,0);assert(r.state==FPGA_SIM_FAULT&&r.fault_code==0x7004);
 memset(raw,0,sizeof(raw));raw[0]=10;raw[1]=3;raw[2]=3;snug(raw,0);loosen(raw,1,0);snug(raw,2);p=program(raw,291);assert(p.steps[1].kind==7);start(&r,&p);
 for(t=1;t<12000&&r.state==FPGA_SIM_RUNNING;t++){
  FpgaProgram_Tick(&r,t,1);
  if(r.current_step==2){second=1;if(r.measured_torque_mnm>=2200)loaded=1;if(r.velocity_inc_s<0)negative=1;if(r.pending_next){assert(loaded&&r.measured_torque_mnm<2000&&r.velocity_inc_s==0);unloaded=1;}}
 }
 assert(second&&negative&&loaded&&unloaded&&r.state==FPGA_SIM_DONE&&r.result);printf("loaded-torque-loosen+retighten ticks=%u\n",t);
 memcpy(bad,raw,291);put(bad+3+96+24,2);assert(!NativePset_Decode(bad,291,&q));
 memcpy(bad,raw,291);put(bad+3+96+64,1);assert(!NativePset_Decode(bad,291,&q)); /* 第11槽保留 */
 loosen(raw,1,1);p=program(raw,291);start(&r,&p);assert(finish(&r,12000)>2000&&r.result);
 /* 相同控制输出下，仅改目标不能改变接头反馈。 */
 p.steps[1].strategy=1;p.steps[1].torque_mnm=2000;q=p;q.steps[1].torque_mnm=4000;start(&r,&p);start(&a,&q);
 for(t=1;t<=2110;t++){FpgaProgram_Tick(&r,t,1);FpgaProgram_Tick(&a,t,1);assert(r.plant.position_q==a.plant.position_q&&r.plant.torque_mnm==a.plant.torque_mnm);}
#endif
#if FPGA_MODEL_PROFILE == 3
 start(&r,&p); /* 此处p仍是合法认帽+拧紧；空转永不建立认帽载荷。 */
 assert(finish(&r,12000)&&r.state==FPGA_SIM_DONE&&!r.result&&r.last_nok_reason==5);
#endif
 /* 未建立过载荷时低扭矩不得直接判“已松脱”；失败后不执行后续拧紧。 */
 memset(raw,0,sizeof(raw));raw[0]=11;raw[1]=3;raw[2]=2;loosen(raw,0,0);put(raw+3+12,200);snug(raw,1);p=program(raw,195);start(&r,&p);t=finish(&r,1000);assert(t>=200&&t<250&&!r.result&&r.last_nok_reason==3&&r.state==FPGA_SIM_DONE);
 (void)a;(void)q;(void)negative;(void)positive;(void)second;(void)unloaded;(void)loaded;puts("engage/loosen model PASS");return 0;
}
