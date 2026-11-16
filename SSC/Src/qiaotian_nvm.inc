/* SPDX-License-Identifier: BSD-3-Clause */
/* 每页只写一次；CRC整页提交；换区先完整复制状态、最后提交区头。 */
#include "qiaotian_nvm.h"
#include <string.h>
#ifndef QN_HOST_TEST
#include "xmc_flash.h"
static const uint8_t *qn_memory(uint32_t address){return (const uint8_t *)(uintptr_t)address;}
static bool qn_program(uint32_t address,const uint32_t *data)
{
    if(address<0x0C004000U || address>=0x0C00C000U || address%256U)return false;
    uint32_t irq=__get_PRIMASK();__disable_irq();
    XMC_FLASH_ProgramPage((uint32_t *)(uintptr_t)address,data);
    uint32_t error=XMC_FLASH_GetStatus()&
        (XMC_FLASH_STATUS_OPERATION_ERROR|XMC_FLASH_STATUS_COMMAND_SEQUENCE_ERROR|
         XMC_FLASH_STATUS_PROTECTION_ERROR|XMC_FLASH_STATUS_DOUBLE_BIT_ERROR|XMC_FLASH_STATUS_VERIFY_ERROR);
    __set_PRIMASK(irq);
    return !error && memcmp(qn_memory(address),data,256U)==0;
}
static bool qn_erase(uint32_t address)
{
    if(address!=0x0C004000U && address!=0x0C008000U)return false;
    uint32_t irq=__get_PRIMASK();__disable_irq();XMC_FLASH_EraseSector((uint32_t *)(uintptr_t)address);
    uint32_t error=XMC_FLASH_GetStatus()&
        (XMC_FLASH_STATUS_OPERATION_ERROR|XMC_FLASH_STATUS_COMMAND_SEQUENCE_ERROR|
         XMC_FLASH_STATUS_PROTECTION_ERROR|XMC_FLASH_STATUS_VERIFY_ERROR);
    __set_PRIMASK(irq);
    if(error)return false;
    for(unsigned i=0;i<16384U;++i)if(qn_memory(address)[i]!=0U)return false;
    return true;
}
#endif
qn_state_t qn_state;
volatile bool qn_write_busy;
static uint32_t qn_generation;
static unsigned qn_bank,qn_next;
static bool qn_ready,qn_dirty;
/* Main-loop flash failures are observed by the model ISR. */
static volatile bool qn_fault;
static uint32_t qn_bad_pages;
static unsigned qn_dirty_scope;
static uint32_t qn_running_ms,qn_milliseconds;
static uint32_t qn_rd(const uint8_t *p){return (uint32_t)p[0]|(uint32_t)p[1]<<8|(uint32_t)p[2]<<16|(uint32_t)p[3]<<24;}
static void qn_put(uint8_t *p,uint32_t v){for(unsigned i=0;i<4U;++i)p[i]=(uint8_t)(v>>(i*8U));}
static uint32_t qn_crc(const uint8_t *p,unsigned n)
{
    uint32_t c=UINT32_MAX;
    for(unsigned i=0;i<n;++i){c^=p[i];for(unsigned b=0;b<8U;++b)c=(c>>1)^((0U-(c&1U))&0xEDB88320U);}
    return ~c;
}
static uint32_t qn_base(unsigned bank){return 0x0C004000U+bank*16384U;}
static bool qn_valid(const uint8_t *p,uint32_t magic)
{return qn_rd(p)==magic && qn_crc(p,252U)==qn_rd(p+252U);}
static void qn_save_cal(uint8_t *p,const qn_cal_t *c)
{
    qn_put(p,c->k);qn_put(p+4,c->limit);qn_put(p+8,c->count);qn_put(p+12,(uint32_t)c->b);
    qn_put(p+16,(uint32_t)c->epoch_ms);qn_put(p+20,(uint32_t)(c->epoch_ms>>32));
    qn_put(p+24,(uint32_t)c->pset|((uint32_t)c->valid<<16));
}
static void qn_load_cal(qn_cal_t *c,const uint8_t *p)
{
    c->k=qn_rd(p);c->limit=qn_rd(p+4);c->count=qn_rd(p+8);uint32_t v=qn_rd(p+12);
    c->b=v<=INT32_MAX?(int32_t)v:-1-(int32_t)(UINT32_MAX-v);
    c->epoch_ms=(uint64_t)qn_rd(p+16)|((uint64_t)qn_rd(p+20)<<32);
    c->pset=(uint16_t)qn_rd(p+24);c->valid=(uint8_t)(qn_rd(p+24)>>16);
}
static bool qn_page(unsigned bank,unsigned slot,unsigned scope)
{
    uint32_t page[64];uint8_t *p=(uint8_t *)page;memset(p,0,sizeof(page));
    qn_put(p,0x51454344U);qn_put(p+4,qn_generation);qn_put(p+8,scope);
    qn_save_cal(p+12,&qn_state.cal[0]);qn_save_cal(p+40,&qn_state.cal[scope]);
    qn_put(p+68,qn_state.ok);qn_put(p+72,qn_state.nok);qn_put(p+76,qn_state.seconds);qn_put(p+80,qn_state.period);
    qn_put(p+84,(uint32_t)qn_state.last_cal_epoch_ms);qn_put(p+88,(uint32_t)(qn_state.last_cal_epoch_ms>>32));
    qn_put(p+252,qn_crc(p,252U));return qn_program(qn_base(bank)+slot*256U,page);
}
static bool qn_compact(void)
{
    unsigned target=qn_ready ? 1U-qn_bank : 0U;
    if(qn_generation==UINT32_MAX || !qn_erase(qn_base(target)))return false;
    ++qn_generation;unsigned slot=1U;
    for(unsigned i=0;i<QN_SCOPE_CAPACITY;++i)if(qn_state.cal[i].valid)
        if(!qn_page(target,slot++,i)){--qn_generation;return false;}
    uint32_t page[64];memset(page,0,sizeof(page));uint8_t *p=(uint8_t *)page;
    qn_put(p,0x51454348U);qn_put(p+4,qn_generation);qn_put(p+8,slot-1U);qn_put(p+252,qn_crc(p,252U));
    if(!qn_program(qn_base(target),page)){--qn_generation;return false;}
    qn_bank=target;qn_next=slot;qn_ready=true;return true;
}
void QEC_NvmInit(uint32_t running_ms)
{
    memset(&qn_state,0,sizeof(qn_state));qn_state.cal[0].k=1000U;qn_state.cal[0].limit=500000U;
    qn_state.cal[0].valid=1U;qn_state.period=500000U;qn_ready=false;qn_generation=0U;qn_next=1U;qn_bank=0U;
    qn_fault=false;qn_bad_pages=0U;
    qn_dirty=false;qn_dirty_scope=0U;qn_running_ms=running_ms;qn_milliseconds=0U;qn_write_busy=false;
    for(unsigned b=0;b<2U;++b){const uint8_t *p=qn_memory(qn_base(b));
        if(qn_valid(p,0x51454348U) && qn_rd(p+4)>qn_generation){qn_generation=qn_rd(p+4);qn_bank=b;qn_ready=true;}}
    if(!qn_ready){
        /* 保留现场并阻止写入。 */
        for(unsigned b=0;b<2U;++b)for(unsigned j=0;j<16384U;++j)
            if(qn_memory(qn_base(b))[j]!=0U)qn_fault=true;
        return;
    }
    for(unsigned slot=1U;slot<64U;++slot){const uint8_t *p=qn_memory(qn_base(qn_bank)+slot*256U);
        bool erased=true;for(unsigned j=0;j<256U;++j)if(p[j]!=0U){erased=false;break;}
        if(!erased)qn_next=slot+1U;
        if(!qn_valid(p,0x51454344U) || qn_rd(p+4)!=qn_generation || qn_rd(p+8)>=QN_SCOPE_CAPACITY){
            if(!erased)++qn_bad_pages;
            /* 区头承诺完整复制的前缀出现缺页时。 */
            if(slot<=qn_rd(qn_memory(qn_base(qn_bank))+8U))qn_fault=true;
            continue;
        }
        unsigned scope=qn_rd(p+8);qn_load_cal(&qn_state.cal[0],p+12);qn_load_cal(&qn_state.cal[scope],p+40);
        qn_state.ok=qn_rd(p+68);qn_state.nok=qn_rd(p+72);qn_state.seconds=qn_rd(p+76);qn_state.period=qn_rd(p+80);
        qn_state.last_cal_epoch_ms=(uint64_t)qn_rd(p+84)|((uint64_t)qn_rd(p+88)<<32);
    }
}
uint32_t QEC_NvmRunStatus(void)
{
    return qn_fault ? QEC_STATUS_NVM_FAULT : qn_write_busy ? QEC_STATUS_NVM_BUSY : 0U;
}
bool QEC_NvmCommit(unsigned scope)
{
    if(qn_fault || scope>=QN_SCOPE_CAPACITY || !qn_state.cal[scope].valid)return false;
    qn_write_busy=true;
    bool ok;
    if(!qn_ready || qn_next>=64U)ok=qn_compact();
    else {unsigned slot=qn_next++;ok=qn_page(qn_bank,slot,scope);}
    if(ok)qn_dirty=false;
    else {
        /* A returned flash error is terminal for this session: retain pending data
         * and the medium, and never silently retry/allow a new cycle after it. */
        qn_dirty=true;
        qn_fault=true;
    }
    qn_write_busy=false;return ok;
}
void QEC_NvmCycle(uint8_t ok,uint8_t pset)
{
    uint32_t *count=ok ? &qn_state.ok : &qn_state.nok;if(*count<UINT32_MAX)++*count;
    if(qn_state.cal[0].count<UINT32_MAX)++qn_state.cal[0].count;
    qn_dirty_scope=0U;
    for(unsigned i=1;i<QN_SCOPE_CAPACITY;++i)if(qn_state.cal[i].valid && qn_state.cal[i].pset==pset){
        if(qn_state.cal[i].count<UINT32_MAX)++qn_state.cal[i].count;
        qn_dirty_scope=i;break;}
    qn_dirty=true;
}
void QEC_NvmPoll(uint32_t running_ms,bool busy)
{
    /* Unsigned subtraction also handles the execution counter wrapping.  The
     * adapter accumulates every execution tick, including cycles between polls. */
    uint32_t elapsed=running_ms-qn_running_ms;qn_running_ms=running_ms;
    uint64_t total=(uint64_t)qn_milliseconds+elapsed;
    uint32_t seconds=(uint32_t)(total/1000U);
    qn_milliseconds=(uint32_t)(total%1000U);
    if(seconds){
        qn_state.seconds=seconds>UINT32_MAX-qn_state.seconds ? UINT32_MAX : qn_state.seconds+seconds;
        qn_dirty=true;
    }
    if(qn_dirty && !busy && !qn_fault)(void)QEC_NvmCommit(qn_dirty_scope);
}
