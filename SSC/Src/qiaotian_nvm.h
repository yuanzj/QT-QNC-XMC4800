/* SPDX-License-Identifier: BSD-3-Clause */
/* 有界校准档案和统计；双区日志只使用预留16KiB扇区1/2。 */
#ifndef QIAOTIAN_NVM_H
#define QIAOTIAN_NVM_H
#include <stdint.h>
#include <stdbool.h>
#define QN_SCOPE_CAPACITY 17U
#define QEC_STATUS_NVM_FAULT 4U
#define QEC_STATUS_NVM_BUSY 5U
typedef struct {
    uint32_t k,limit,count;
    int32_t b;
    uint64_t epoch_ms;
    uint16_t pset;
    uint8_t valid;
} qn_cal_t;
typedef struct {
    qn_cal_t cal[QN_SCOPE_CAPACITY];
    uint32_t ok,nok,seconds,period;
    uint64_t last_cal_epoch_ms;
} qn_state_t;
extern qn_state_t qn_state;
extern volatile bool qn_write_busy;
/* Baseline is the adapter's accumulated execution time, not wall-clock uptime. */
void QEC_NvmInit(uint32_t running_ms);
uint32_t QEC_NvmRunStatus(void);
static inline bool QEC_RunPermitted(uint16_t control, uint32_t *status)
{
    uint32_t reason = QEC_NvmRunStatus();
    if (*status == 0U || *status == QEC_STATUS_NVM_FAULT || *status == QEC_STATUS_NVM_BUSY)
        *status = reason;
    return reason == 0U && (control & 0x018FU) == 0x000FU;
}
bool QEC_NvmCommit(unsigned scope);
void QEC_NvmCycle(uint8_t ok,uint8_t pset);
/* Collect an execution-time snapshot; busy blocks flash but never changes time. */
void QEC_NvmPoll(uint32_t running_ms,bool busy);
#endif
