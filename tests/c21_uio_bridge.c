/* Compile upstream production events/publisher/job with its existing host stubs.
 * All upstream sources are read only; wrappers expose only the regression boundary. */
#define main upstream_pipeline_main
#include "test_ethercat_job_pipeline.c"
#undef main
#include "ethercat/ethercat_qiaotian_paired.h"
#include "c21_uio_decode.inc"

void review_uio_begin(const uint8_t *pset,uint16_t length,uint32_t ms)
{
 reset();assert(length<=sizeof(g_pset));memcpy(g_pset,pset,length);g_pset_length=length;
 uio_hmi_cycle_events_on_start(pset[0],pset[2],1U,0U,0,ms,0U);
}
void review_uio_feed(const uint8_t physical[46],uint32_t ms)
{
 ethercat_xmc_inputs_t inputs;
 assert(qec_paired_to_logical(physical,inputs.raw));
 review_decode_tx(&inputs,&sample);
 memcpy(raw,inputs.raw,sizeof(raw));
 tick=ms;clock_us=(uint64_t)ms*1000U;
 feed_at(ms);uio_hmi_cycle_events_feed(&sample,ms);
}
void review_uio_finish(uint8_t action,uint32_t ms)
{
 /* Passing last-step OK must still produce chain NOK after an earlier NOK. */
 uio_hmi_cycle_events_finish(action!=2U,0U,ms);
 unsigned count=action==1U?3U:action==2U?1U:2U;
 assert(last_result.result==2U&&last_result.executed_steps==count);
 assert(g_hmi_cycle_dbg.step_count_rec==count);
 for(unsigned i=0;i<count;++i){
  const uio_hmi_step_trace_t *s=(const uio_hmi_step_trace_t *)&g_hmi_cycle_dbg.steps[i];
  assert(s->used&&s->step_seq==i+1U);
  assert(s->step_no==(action==3U&&i==1U?3U:i+1U));
  assert(s->step_result==(i==0U?2U:1U));
  assert(s->step_type==(i==0U?1U:3U));
 }
 assert(uio_hmi_cycle_events_failed_step());
 puts("latest UIO real event producer: step sequence, actual metadata, last result and chain NOK PASS");
}
