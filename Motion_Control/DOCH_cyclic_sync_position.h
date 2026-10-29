/*
 * DOCH_cyclic_sync_position.h
 *
 * S2/M2 simulated EtherCAT slave（客户协议 v2）—— 1 ms 模拟模型 + Pset/工步引擎接口。
 * 由 SSC 的 APPL_Application()（总线周期/1 ms 定时器驱动）调用。
 */

#ifndef _DOCH_CYCLIC_SYNC_POSITION_H_
#define _DOCH_CYCLIC_SYNC_POSITION_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* 每 1 ms 调用一次；内部用 HW_GetTimer() 做 1 ms 门控，可被更快的调用频率安全重入。
   M2 起内部还会调度 Pset 解析/工步引擎。 */
void SimulatedSlave_Tick(void);

/* 0x2030:00 SDO 写回调收到整串 Pset 后调用（仅打标记，解析在下一个 1 ms tick）。 */
void Pset_OnBufferReceived(uint16_t len);
/* 下载准入必须与实际复制置于同一中断临界区。 */
uint8_t Pset_IsRunning(void);

/* C12 §5.4: CRC-32/ISO-HDLC（poly 0xEDB88320、init/xorout 0xFFFFFFFF，与主站 uio_hmi_crc32 一致）。 */
uint32_t Pset_Crc32_Calc(const uint8_t * p, uint16_t len);

#ifdef __cplusplus
}
#endif

#endif /* _DOCH_CYCLIC_SYNC_POSITION_H_ */
