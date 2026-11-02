/* 合成数据导出：输入工艺与独立夹具分别记录；不含预设测量曲线/预设成功输出。 */
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "../Simulation/native_pset.h"
static void u16(uint8_t *p,uint16_t v){p[0]=(uint8_t)v;p[1]=(uint8_t)(v>>8);}
static void u32(uint8_t *p,uint32_t v){unsigned i;for(i=0;i<4;i++)p[i]=(uint8_t)(v>>(8*i));}
int main(int argc,char **argv){
 uint8_t p[128]={122,2,1};uint8_t *s=p+3;uint16_t length=64;FpgaProgram program;FpgaProgramRun run;unsigned t,ended=0;FILE *out;
 assert(argc==3);s[0]=3;u16(s+1,61);s[3]=1;u32(s+4,11000);u32(s+8,14000);u32(s+12,10000);
 u32(s+16,1000);u32(s+20,20000);u32(s+24,800);u32(s+28,1500);u32(s+32,3000);u32(s+36,1000);u32(s+41,30000);
 s[49]=s[50]=1;u16(s+51,5000);s[55]=s[56]=2;
#if FPGA_MODEL_PROFILE == 2
 u32(s+41,100000);u32(s+24,90000);u32(s+28,120000);u32(s+32,150000);u32(s+36,100000);
#endif
 if(!strcmp(argv[1],"fast"))u32(s+41,300000);
 else if(!strcmp(argv[1],"accel"))u16(s+45,200);
 else if(!strcmp(argv[1],"angle")||!strcmp(argv[1],"or")){
  s[3]=!strcmp(argv[1],"angle")?2:3;u32(s+36,500);u32(s+12,0);u32(s+24,0);
 }else if(!strcmp(argv[1],"and")){
  s[3]=4;u32(s+36,2000);u32(s+8,30000);u32(s+28,3000);u32(s+20,29000);
 }else if(!strcmp(argv[1],"safety-torque")){s[3]=2;u32(s+20,1000);}
 else if(!strcmp(argv[1],"safety-angle"))u32(s+32,500);
 else if(!strcmp(argv[1],"window-nok")||!strcmp(argv[1],"continue")||!strcmp(argv[1],"fail-stop")){
  u32(s+24,2000);u32(s+28,3000);u32(s+36,2500);
  if(strcmp(argv[1],"window-nok")){
   uint8_t *w=p+64;p[2]=2;s[56]=!strcmp(argv[1],"continue")?1:2;length=77;w[0]=4;u16(w+1,13);u16(w+4,100);u16(w+8,1000);w[12]=2;
  }
 }else if(!strcmp(argv[1],"delay"))u16(s+53,50);
 else if(!strcmp(argv[1],"rundown")){
  memset(s,0,36);length=39;s[0]=2;u16(s+1,36);s[3]=2;u32(s+4,30000);u16(s+14,2000);s[18]=2;s[19]=1;u32(s+24,3000);u32(s+28,20000);
 }else if(!strcmp(argv[1],"release")){
  uint8_t *w=p+64;p[2]=2;length=90;w[0]=5;u16(w+1,26);u32(w+3,20000);u32(w+11,500);u32(w+15,30000);u16(w+21,2000);w[25]=2;
 }
 if(!strncmp(argv[1],"speed1000-",10)||!strcmp(argv[1],"position1000-overflow")){
  s[3]=2;u32(s+8,!strcmp(argv[1],"speed1000-hard")?14000:30000);u32(s+12,0);u32(s+16,0);u32(s+20,0);
  u32(s+24,0);u32(s+28,307199);u32(s+32,0);u32(s+36,!strcmp(argv[1],"position1000-overflow")?300000:60000);
  s[40]=!strcmp(argv[1],"speed1000-reverse");u32(s+41,1000000);u16(s+45,100);
 }
 out=fopen(argv[2],"wb");assert(out);assert(fwrite(p,1,length,out)==length);fclose(out);
 assert(NativePset_Decode(p,length,&program));FpgaProgram_Reset(&run);assert(FpgaProgram_Load(&run,&program));assert(FpgaProgram_Start(&run,0,1));
 puts("time_ms,fixture_angle_q,monitor_angle_cdeg,torque_raw,position_inc,velocity_inc_s,feedback_rpm_milli,state,step,result,all_ok,fault_code,braking,torque_hit,angle_hit");
 for(t=0;t<7000;t++){
  if(t==250&&!strcmp(argv[1],"stop"))FpgaProgram_Stop(&run);
  FpgaProgram_Tick(&run,t,1);
  printf("%u,%lld,%ld,%d,%ld,%lld,%ld,%u,%u,%u,%u,%lu,%u,%u,%u\n",t,(long long)run.plant.position_q,(long)run.measured_angle_cdeg,run.torque_raw,(long)run.position_inc,(long long)run.velocity_inc_s,(long)run.plant.velocity_rpm_milli,run.state,run.current_step,run.result,run.all_ok,(unsigned long)run.fault_code,run.braking,run.torque_hit,run.angle_hit);
  if(run.state!=FPGA_SIM_RUNNING){if(!ended)ended=t;if(t>=ended+50)break;}
 }
 assert(ended);return 0;
}
