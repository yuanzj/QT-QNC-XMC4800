/* Compare the new executor with the SHA-locked pre-observation executor. */
#define main previous_identify_actions_main
#include "test_c20_identify_actions.c"
#undef main
#define FpgaProgram_Reset Reference_Reset
#define FpgaProgram_Load Reference_Load
#define FpgaProgram_Start Reference_Start
#define FpgaProgram_Stop Reference_Stop
#define FpgaProgram_Tick Reference_Tick
#include "pre_observation_executor.inc"
#undef FpgaProgram_Reset
#undef FpgaProgram_Load
#undef FpgaProgram_Start
#undef FpgaProgram_Stop
#undef FpgaProgram_Tick

static void check_same(const FpgaProgramRun *actual,const FpgaProgramRun *reference)
{
 FpgaProgramRun a=*actual,b=*reference;
 a.observed_running_ms=b.observed_running_ms=0;
 assert(!memcmp(&a,&b,sizeof(a)));
 assert(actual->observed_running_ms<=1000U);
}
int main(void)
{
 const unsigned strides[]={1,7,50,1000,1001};
 for(unsigned action=1;action<=3;++action)for(unsigned mode=0;mode<5;++mode){
  uint8_t bytes[291];packet(bytes,action==3?0x33:(uint8_t)action);
  FpgaProgram p;assert(NativePset_Decode(bytes,sizeof(bytes),&p));
  FpgaProgramRun a,b;FpgaProgram_Reset(&a);Reference_Reset(&b);check_same(&a,&b);
  assert(FpgaProgram_Load(&a,&p)==Reference_Load(&b,&p));check_same(&a,&b);
  uint32_t now=UINT32_MAX-40U;
  assert(FpgaProgram_Start(&a,now,1)==Reference_Start(&b,now,1));check_same(&a,&b);
  for(unsigned call=0;call<300;++call){
   now+=strides[mode];FpgaProgram_Tick(&a,now,1);Reference_Tick(&b,now,1);check_same(&a,&b);
  }
  FpgaProgram_Stop(&a);Reference_Stop(&b);check_same(&a,&b);
  now++;FpgaProgram_Tick(&a,now,0);Reference_Tick(&b,now,0);check_same(&a,&b);
  FpgaProgram_Reset(&a);Reference_Reset(&b);check_same(&a,&b);
 }
 /* Autonomous torque/angle faults, tool invalidation and permission revocation. */
 for(unsigned kind=0;kind<4;++kind){
  uint8_t bytes[291];packet(bytes,1);bytes[2]=1;
  uint8_t *s=bytes+3;s[21]=3;s[23]=2;
  memset(s+24,0,72);put(s+24,1);put(s+24+8,kind?30000:50);put(s+24+24,kind==1?1:10000);
  put(s+24+32,30000);put(s+24+36,1000);put(s+24+52,1);put(s+24+56,1);
  FpgaProgram p;assert(NativePset_Decode(bytes,99,&p));
  FpgaProgramRun a,b;FpgaProgram_Reset(&a);Reference_Reset(&b);
  assert(FpgaProgram_Load(&a,&p)&&Reference_Load(&b,&p));
  assert(FpgaProgram_Start(&a,0,1)&&Reference_Start(&b,0,1));
  if(kind==2)a.plant.valid=b.plant.valid=0;
  for(unsigned now=50;now<=1000;now+=50){
   FpgaProgram_Tick(&a,now,kind!=3);Reference_Tick(&b,now,kind!=3);check_same(&a,&b);
  }
 }
 printf("observer-only change: all original model state/feedback/quality fields match SHA-locked reference, profile=%u PASS\n",FPGA_MODEL_PROFILE);
 return 0;
}
