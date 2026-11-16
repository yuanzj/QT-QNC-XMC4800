/* Regression of the four port review findings; in-memory flash, no hardware. */
#define main previous_integration_main
#include "test_c20_integration.c"
#undef main
#define put action_put
#define main previous_actions_main
#include "test_c20_identify_actions.c"
#undef main
#undef put
#ifdef QNC_UIO_PAIRED_HEADER
#include QNC_UIO_PAIRED_HEADER
#endif

#ifdef QNC_UIO_PIPELINE
void review_uio_begin(const uint8_t *,uint16_t,uint32_t);
void review_uio_feed(const uint8_t *,uint32_t);
void review_uio_finish(uint8_t,uint32_t);
static void feed_current_uio(void)
{
 uint16_t image[23]={0};APPL_InputMapping(image);
 review_uio_feed((const uint8_t *)image,clock_ms);
}
#endif

static void assert_storage_status(uint32_t expected)
{
 assert(!App_Run_IsPermitted());assert(status_code0x2200==expected);
 uint16_t image[23]={0};APPL_InputMapping(image);
 assert(get((uint8_t *)image+14)==expected);
}
static void test_latest_pair(void)
{
 uint16_t image[23]={0};APPL_InputMapping(image);
 assert(read32(0x2F00,9)==0x20261116U);
 assert(get((uint8_t *)image+42)==0x20261116U);
#ifdef QNC_UIO_PAIRED_HEADER
 uint8_t logical[44];
 assert(QEC_PAIRED_REVISION==0x060B0901U&&QEC_PAIRED_ID==read32(0x2F00,9));
 assert(qec_paired_valid((uint8_t *)image));
 assert(qec_paired_to_logical((uint8_t *)image,logical));
 assert(get(logical)==status_code0x2200);
 ((uint8_t *)image)[42]=0x09;assert(!qec_paired_valid((uint8_t *)image));
#endif
 puts("C21 pair identity and current UIO physical decoder PASS");
}
static void test_storage_reasons(void)
{
 reset();snug(10000);memset(flash,0,sizeof(flash));flash[0]=1;QEC_NvmInit(Simulation_GetRunningMilliseconds());
 tick();assert_storage_status(4);
 control=1;tick();assert(!Simulation_IsRunning());assert_storage_status(4);
 /* Loading and RESET cannot temporarily hide a persistent storage fault. */
 Simulation_Receive(99);tick();assert_storage_status(4);
 control=3;tick();assert_storage_status(4);
 memset(flash,0,sizeof(flash));QEC_NvmInit(Simulation_GetRunningMilliseconds());tick();assert(!status_code0x2200&&App_Run_IsPermitted());
}
static void test_storage_recovery(void)
{
 reset();memset(flash,0,sizeof(flash));QEC_NvmInit(Simulation_GetRunningMilliseconds());tick();assert(!status_code0x2200);
 snug(10000);qn_write_busy=true;tick();assert_storage_status(5);
 control=1;tick();assert(!Simulation_IsRunning());assert_storage_status(5);
 control=3;tick();assert_storage_status(5);
 qn_write_busy=false;tick();assert(!status_code0x2200&&App_Run_IsPermitted());
 snug(10000);start();qn_write_busy=true;tick();assert(!Simulation_IsRunning());assert_storage_status(5);
 /* Explicit RESET clears the original model's permission-loss fault; it never auto-starts. */
 qn_write_busy=false;control=3;tick();assert(!status_code0x2200&&!Simulation_IsRunning());
 status_code0x2200=0x7005;assert(App_Run_IsPermitted());assert(status_code0x2200==0x7005);
 reset();
 puts("NVM fault/busy exact status, START rejection, RESET and explicit recovery PASS");
}
static void test_last_step(void)
{
 for(unsigned action=1;action<=3;++action){
  reset();uint8_t bytes[291];packet(bytes,action==3?0x33:(uint8_t)action);
  memcpy(Pset_buffer0x2030,bytes,sizeof(bytes));Simulation_Receive(sizeof(bytes));tick();assert(!status_code0x2200);
  uint32_t nok=qn_state.nok,ok=qn_state.ok;
#ifdef QNC_UIO_PIPELINE
  review_uio_begin(bytes,sizeof(bytes),clock_ms);
#endif
  start();
#ifdef QNC_UIO_PIPELINE
  feed_current_uio();
#endif
  while(Simulation_IsRunning()){
   tick();
#ifdef QNC_UIO_PIPELINE
   feed_current_uio();
#endif
  }
  uint8_t expected=action==2?0:1;
  assert(step_echo0x220C==(action==2?1:3)&&step_result0x220D==expected);
  /* Both the visible terminal sample and the step -> 0 boundary retain last-step result. */
  while(Simulation_IsBusy()){
   tick();
#ifdef QNC_UIO_PIPELINE
   feed_current_uio();
#endif
  }
  assert(step_echo0x220C==0&&step_result0x220D==expected);
#ifdef QNC_UIO_PIPELINE
  review_uio_finish((uint8_t)action,clock_ms);
#endif
  uint16_t image[23]={0};APPL_InputMapping(image);assert(((uint8_t *)image)[37]==expected);
  assert(qn_state.nok==nok+1&&qn_state.ok==ok);
#ifdef QNC_UIO_PAIRED_HEADER
  uint8_t logical[44];assert(qec_paired_to_logical((uint8_t *)image,logical));
  assert(logical[27]==expected);
#endif
 }
 reset();snug(10000);start();finish();assert(step_result0x220D==1);
 puts("last-step OK / chain NOK: continue and jump; stop NOK and all-OK PASS");
}
static void polled_tick(unsigned *running_ms,unsigned *elapsed_ms)
{
 tick();*running_ms+=Simulation_IsRunning();++*elapsed_ms;
 unsigned before=writes;bool busy=Simulation_IsBusy()!=0;
 App_Storage_Poll(clock_ms);
 if(busy)assert(writes==before);
}
static void test_runtime_and_flash_gate(void)
{
 reset();memset(flash,0,sizeof(flash));QEC_NvmInit(Simulation_GetRunningMilliseconds());
 uint8_t wait_packet[16]={7,2,1,4,13,0,0,1,0,0,0,0xE8,3,0,0,2};
 memcpy(Pset_buffer0x2030,wait_packet,sizeof(wait_packet));Simulation_Receive(sizeof(wait_packet));tick();assert(!status_code0x2200);
 unsigned running_ms=0,elapsed_ms=0;App_Storage_Poll(clock_ms);
 for(unsigned i=0;i<1100;++i){
  control=1;polled_tick(&running_ms,&elapsed_ms);assert(Simulation_IsRunning());
  while(Simulation_IsBusy())polled_tick(&running_ms,&elapsed_ms);
 }
 assert(running_ms==1100&&elapsed_ms==24200);
 assert(qn_state.seconds==1&&qn_milliseconds==100&&qn_state.ok==1100);
 printf("runtime: running=%ums including idle window=%ums stored=%us+%ums PASS\n",running_ms,elapsed_ms,qn_state.seconds,qn_milliseconds);
 /* STOP's natural braking tail is also busy but is not active execution time. */
 reset();snug(10000);start();for(unsigned i=0;i<100;++i)tick();App_Storage_Poll(clock_ms);
 control=2;tick();assert(!Simulation_IsRunning()&&Simulation_IsBusy());App_Storage_Poll(clock_ms);
 uint32_t seconds=qn_state.seconds,remainder=qn_milliseconds;unsigned before=writes;
 while(Simulation_IsBusy()){
  tick();if(Simulation_IsBusy()){App_Storage_Poll(clock_ms);assert(writes==before);}
 }
 assert(qn_state.seconds==seconds&&qn_milliseconds==remainder);
 App_Storage_Poll(clock_ms);assert(writes>before);
 QEC_NvmInit(Simulation_GetRunningMilliseconds());assert(qn_state.seconds==seconds);
 puts("terminal window / natural braking: time excluded, flash deferred, persistence PASS");
}
int main(void)
{
 QEC_NvmInit(Simulation_GetRunningMilliseconds());Controlword0x6040=15;tick();test_latest_pair();
 test_storage_reasons();test_storage_recovery();test_last_step();test_runtime_and_flash_gate();
 return 0;
}
