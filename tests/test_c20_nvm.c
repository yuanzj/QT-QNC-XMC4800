/* 日志真实实现：换区、校准/计数恢复及逐字节掉电截断。 */
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <setjmp.h>
#define QN_HOST_TEST 1
static uint8_t flash[32768],saved[32768];
static int fail_after=-1;
static unsigned writes,erases;
static jmp_buf powercut;
static const uint8_t *qn_memory(uint32_t address)
{assert(address>=0x0C004000U && address<0x0C00C000U);return flash+(address-0x0C004000U);}
static bool qn_program(uint32_t address,const uint32_t *page)
{
    assert(address>=0x0C004000U && address+256U<=0x0C00C000U && address%256U==0U);++writes;
    uint8_t *out=flash+(address-0x0C004000U);const uint8_t *in=(const uint8_t *)page;
    for(unsigned i=0;i<256U;++i){if(fail_after==0)longjmp(powercut,1);if(fail_after>0)--fail_after;assert((out[i]|in[i])==in[i]);out[i]|=in[i];}
    return true;
}
static bool qn_erase(uint32_t address)
{
    assert(address==0x0C004000U || address==0x0C008000U);++erases;
    if(fail_after==0)longjmp(powercut,1);
    memset(flash+(address-0x0C004000U),0U,16384U);return true;
}
#include "../SSC/Src/qiaotian_nvm.inc"
int main(void)
{
    memset(flash,0,sizeof(flash));QEC_NvmInit(0U);assert(!qn_fault && !qn_ready && qn_state.cal[0].k==1000U);
    assert(QEC_NvmCommit(0U));assert(qn_ready);
    qn_state.cal[1]=(qn_cal_t){.k=1023,.b=-7,.limit=123,.epoch_ms=1794450000123ULL,.pset=254,.valid=1};
    assert(QEC_NvmCommit(1U));
    for(unsigned i=0;i<150U;++i){QEC_NvmCycle(i%3U!=0U,254U);QEC_NvmPoll(0U,false);}
    QEC_NvmInit(0U);assert(!qn_fault && !qn_bad_pages && qn_state.ok==100U && qn_state.nok==50U);
    assert(qn_state.cal[0].count==150U && qn_state.cal[1].count==150U && qn_state.cal[1].b==-7 && qn_state.cal[1].epoch_ms==1794450000123ULL);
    assert(erases>=3U);memcpy(saved,flash,sizeof(flash));
    /* 一页任意写入前缀掉电：只能恢复旧或完整新状态。 */
    for(unsigned cut=0;cut<=256U;++cut){
        memcpy(flash,saved,sizeof(flash));QEC_NvmInit(0U);qn_state.cal[0].k=1100U;
        fail_after=(int)cut;
        if(!setjmp(powercut))(void)QEC_NvmCommit(0U);
        fail_after=-1;QEC_NvmInit(0U);assert(!qn_fault);
        assert(qn_state.cal[0].k==(cut==256U?1100U:1000U));assert(qn_state.ok==100U);
    }
    /* 换区所有页前缀掉电，旧区保持完整，直到新区区头原子提交。 */
    memcpy(flash,saved,sizeof(flash));QEC_NvmInit(0U);
    while(qn_next<64U)assert(QEC_NvmCommit(0U));memcpy(saved,flash,sizeof(flash));
    for(unsigned cut=0;cut<=3U*256U;++cut){
        memcpy(flash,saved,sizeof(flash));QEC_NvmInit(0U);qn_state.cal[0].k=1200U;fail_after=(int)cut;
        if(!setjmp(powercut))(void)QEC_NvmCommit(0U);
        fail_after=-1;QEC_NvmInit(0U);assert(!qn_fault);
        assert(qn_state.cal[0].k==(cut==3U*256U?1200U:1000U));assert(qn_state.cal[1].b==-7);
    }

    memset(flash,0,sizeof(flash));flash[0]=255U;QEC_NvmInit(0U);assert(qn_fault && !QEC_NvmCommit(0U));
    memcpy(flash,saved,sizeof(flash));QEC_NvmInit(0U);flash[qn_bank*16384U+256U+13U]^=1U;QEC_NvmInit(0U);assert(qn_fault);
    printf("QEC NVM: cycles/restart/257 append cuts/769 compaction cuts/unknown occupancy/corruption PASS (%u writes)\n",writes);
    return 0;
}
