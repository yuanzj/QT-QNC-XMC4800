/* Returned flash errors and execution accounting independent of main-loop phase. */
#define main previous_integration_main
#include "test_c20_integration.c"
#undef main

static uint32_t runtime_ms(void){return qn_state.seconds*1000U+qn_milliseconds;}
static void fresh(void)
{
 reset();fail_program_on=fail_erase_on=program_fail_bytes=erase_fail_bytes=0;
 memset(flash,0,sizeof(flash));writes=erases=0;Controlword0x6040=15;
 QEC_NvmInit(Simulation_GetRunningMilliseconds());tick();assert(!status_code0x2200);
}
static void wait_task(unsigned duration)
{
 const uint8_t packet[16]={7,2,1,4,13,0,0,0,0,0,0,0xB8,0x0B,0,0,2};
 memcpy(Pset_buffer0x2030,packet,sizeof(packet));
 Pset_buffer0x2030[7]=(uint8_t)duration;Pset_buffer0x2030[8]=(uint8_t)(duration>>8);
 Simulation_Receive(sizeof(packet));tick();assert(!status_code0x2200);
}
static void assert_latched(void)
{
 tick();assert(QEC_NvmRunStatus()==4U&&status_code0x2200==4U&&!qn_write_busy&&qn_dirty);
 assert(!App_Run_IsPermitted());
 uint16_t image[23]={0};APPL_InputMapping(image);assert(get((uint8_t *)image+14)==4U);
 unsigned old_writes=writes,old_erases=erases;uint8_t medium[32768];memcpy(medium,flash,sizeof(medium));
 fail_program_on=fail_erase_on=0;
 for(unsigned i=0;i<5;++i){
  App_Storage_Poll(clock_ms);assert(!QEC_NvmCommit(0U));tick();
 }
 assert(writes==old_writes&&erases==old_erases&&!memcmp(medium,flash,sizeof(medium)));
 control=3;tick();assert(status_code0x2200==4U);
 /* Valid download, ordinary RESET and START must not clear the hardware error. */
 snug(10000);control=1;tick();assert(!Simulation_IsRunning()&&status_code0x2200==4U);
 assert(!App_Run_IsPermitted());
}
static void test_returned_flash_failures(void)
{
 /* Existing journal: append, compaction erase, copied snapshot and final header. */
 for(unsigned kind=0;kind<4;++kind)for(unsigned partial=0;partial<2;++partial){
  fresh();assert(QEC_NvmCommit(0U));unsigned active=qn_bank;
  uint8_t previous[16384];memcpy(previous,flash+active*16384U,sizeof(previous));
  if(kind)qn_next=64U;
  if(kind==1U){fail_erase_on=erases+1U;erase_fail_bytes=partial?128U:0U;}
  else {fail_program_on=writes+(kind==3U?2U:1U);program_fail_bytes=partial?128U:0U;}
  QEC_NvmCycle(1U,7U);App_Storage_Poll(clock_ms);
  assert_latched();
  if(kind)assert(!memcmp(previous,flash+active*16384U,sizeof(previous)));
  /* A simulated restart reloads the old committed state without erasing evidence. */
  unsigned before=writes;QEC_NvmInit(Simulation_GetRunningMilliseconds());
  assert(!QEC_NvmRunStatus()&&qn_state.ok==0U&&writes==before);
 }
 /* Empty medium: first erase, first snapshot and first header failures. */
 for(unsigned kind=0;kind<3;++kind){
  fresh();if(!kind)fail_erase_on=1U;else fail_program_on=kind;
  QEC_NvmCycle(1U,7U);App_Storage_Poll(clock_ms);assert_latched();
 }
 /* Explicit calibration commit must preserve its last durable value on error. */
 fresh();assert(QEC_NvmCommit(0U));
 assert(!write_value(0x2F10,1,1794820000123ULL,8));
 assert(!write_value(0x2310,3,1100,4));fail_program_on=writes+1U;
 assert(write_value(0x2310,6,1,1)==ABORTIDX_IN_THIS_STATE_DATA_CANNOT_BE_READ_OR_STORED);
 assert(qn_state.cal[0].k==1000U);assert_latched();
 puts("flash returned failures: append/erase/compaction snapshot/header/first commit/calibration, partial writes, fault4/START gate/no retry PASS");
}
static void poll(void){App_Storage_Poll(clock_ms);}
static void test_poll_phases(void)
{
 const unsigned periods[]={1,3,7,22,31,0};
 for(unsigned phase=0;phase<sizeof(periods)/sizeof(periods[0]);++phase){
  fresh();wait_task(1);poll();uint32_t base=Simulation_GetRunningMilliseconds(),executed=0;
  for(unsigned cycle=0;cycle<1100;++cycle){
   start();uint32_t begun=clock_ms;
   if(periods[phase]&&clock_ms%periods[phase]==0U)poll();
   while(Simulation_IsRunning()){
    tick();if(periods[phase]&&clock_ms%periods[phase]==0U)poll();
   }
   executed+=clock_ms-begun;
   while(Simulation_IsBusy()){
    unsigned before=writes;tick();
    if(periods[phase]&&clock_ms%periods[phase]==0U){bool busy=Simulation_IsBusy();poll();if(busy)assert(writes==before);}
   }
   if(!periods[phase])poll(); /* Poll only after each entire cycle, never while running. */
  }
  poll();assert(executed==1100U&&Simulation_GetRunningMilliseconds()-base==executed);
  assert(runtime_ms()==executed&&qn_state.ok==1100U);
  printf("main poll period=%ums (0=end only): executed=%u recorded=%u PASS\n",periods[phase],executed,runtime_ms());
  uint32_t counter=Simulation_GetRunningMilliseconds();reset();poll();assert(runtime_ms()==executed);
  assert(Simulation_GetRunningMilliseconds()==counter);
  QEC_NvmInit(counter);assert(qn_state.seconds==1U);poll();assert(qn_state.seconds==1U&&qn_milliseconds==0U);
 }
}
static void test_idle_delays_and_boundaries(void)
{
 fresh();wait_task(100);poll();uint32_t before=Simulation_GetRunningMilliseconds();
 for(unsigned i=0;i<37;++i)tick();start();poll();
 assert(runtime_ms()==0U&&Simulation_GetRunningMilliseconds()==before);
 for(unsigned i=0;i<23;++i)tick();poll();assert(runtime_ms()==23U);
 finish();poll();assert(runtime_ms()==100U);
 /* Miss an entire two-second run in the main loop; ISR accounting still captures it. */
 fresh();wait_task(2000);start();finish();poll();assert(runtime_ms()==2000U);
 /* Catch-up after a completed short step must not include its terminal idle interval. */
 fresh();wait_task(1);start();clock_ms+=50U;Simulation_Tick();poll();assert(runtime_ms()==1U);
 /* Unsigned wall-clock wrap does not reset or inflate the execution counter. */
 fresh();clock_ms=UINT32_MAX-20U;Simulation_Tick();wait_task(100);start();finish();poll();assert(runtime_ms()==100U);
 /* A model clock fault (>1000ms) must not invent elapsed execution. */
 fresh();wait_task(2000);start();clock_ms+=1001U;Simulation_Tick();poll();assert(!Simulation_IsRunning()&&runtime_ms()==0U);
 /* Storage snapshot subtraction supports wrapping and saturates public seconds. */
 fresh();QEC_NvmInit(UINT32_MAX-3U);QEC_NvmPoll(5U,true);assert(runtime_ms()==9U);
 qn_state.seconds=UINT32_MAX-1U;QEC_NvmPoll(3005U,true);assert(qn_state.seconds==UINT32_MAX);
 puts("runtime: idle-to-start, >1s no main poll, catch-up, hardware timer/counter wrap and saturation PASS");
}
/* Identical PSET bytes and final sample time; only ISR call cadence changes. */
static void load_fault_timing_task(unsigned kind)
{
 snug(10000);uint8_t *s=Pset_buffer0x2030+3;
 if(!kind){
  put(s+24+4,25U);put(s+24+8,50U);put(s+24+12,0U);
 }else{
  put(s,1U);put(s+24+4,30000U);put(s+24+8,30000U);
  put(s+24+12,0U);put(s+24+16,0U);put(s+24+24,1U);
 }
 Simulation_Receive(99);tick();assert(!status_code0x2200);
}
static void test_fault_catchup_consistency(void)
{
 for(unsigned kind=0;kind<2;++kind){
  uint32_t expected_fault_ms=0,reference_code=0;
  uint8_t same_packet[1600];
  const unsigned cadence[]={1U,7U,50U,1000U};
  for(unsigned mode=0;mode<4;++mode){
   fresh();load_fault_timing_task(kind);
   if(!mode)memcpy(same_packet,Pset_buffer0x2030,sizeof(same_packet));
   else assert(!memcmp(same_packet,Pset_buffer0x2030,sizeof(same_packet)));
   QEC_NvmInit(Simulation_GetRunningMilliseconds());start();uint32_t begun=clock_ms;
   uint32_t base=Simulation_GetRunningMilliseconds();
   if(!mode){
    while(Simulation_IsRunning())tick();
    expected_fault_ms=clock_ms-begun;reference_code=status_code0x2200;
    assert(reference_code==(kind?0x7008U:0x7007U)&&expected_fault_ms<=50U);
    while(clock_ms-begun<1000U)tick();
   }else{
    /* Same final wall-clock sample for all modes, including post-fault braking. */
    while(clock_ms-begun<1000U){
     uint32_t remaining=1000U-(clock_ms-begun);
     clock_ms+=remaining<cadence[mode]?remaining:cadence[mode];Simulation_Tick();
    }
   }
   assert(!Simulation_IsRunning()&&status_code0x2200==reference_code);
   assert(Simulation_GetRunningMilliseconds()-base==expected_fault_ms);
   poll();assert(runtime_ms()==expected_fault_ms&&qn_state.nok==1U);
   uint32_t counted=Simulation_GetRunningMilliseconds();
   for(unsigned i=0;i<20;++i){tick();poll();}
   assert(Simulation_GetRunningMilliseconds()==counted&&runtime_ms()==expected_fault_ms);
   printf("same PSET fault=0x%x ISR cadence=%ums: counted=%u reference=%u PASS\n",reference_code,cadence[mode],runtime_ms(),expected_fault_ms);
  }
 }
}

static void test_abort_tails(void)
{
 for(unsigned command=2;command<=4;++command){
  fresh();snug(10000);poll();start();uint32_t begun=clock_ms;
  for(unsigned i=0;i<100;++i)tick();
  if(command==4U)link_operational=0;else control=(uint8_t)command;
  tick();assert(!Simulation_IsRunning());uint32_t expected=clock_ms-begun;
  poll();assert(runtime_ms()==expected);unsigned before=writes;
  while(Simulation_IsBusy()){
   tick();if(Simulation_IsBusy()){poll();assert(writes==before);assert(runtime_ms()==expected);}
  }
  poll();assert(runtime_ms()==expected&&qn_state.nok==1U);
  link_operational=1;
 }
 puts("STOP/RESET/link-loss: execution counted once, natural brake and result windows excluded PASS");
}
int main(void)
{
 QEC_NvmInit(Simulation_GetRunningMilliseconds());Controlword0x6040=15;tick();
 test_returned_flash_failures();test_poll_phases();test_idle_delays_and_boundaries();test_abort_tails();test_fault_catchup_consistency();
 return 0;
}
