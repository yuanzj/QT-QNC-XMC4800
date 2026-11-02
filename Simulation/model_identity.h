/* 厂商型号快照0x2214:00，固定24B小端；不是实际工具铭牌/正式码表。 */
#ifndef SIMULATION_MODEL_IDENTITY_H
#define SIMULATION_MODEL_IDENTITY_H
#include "model_config.h"
#define SIMULATION_MODEL_IDENTITY_BYTES 24
/* 0..15名称；16..19码表版本U32；20型号代码；21有效位；22来源；23保留。
 * 有效位bit0名称、bit1代码、bit2码表；来源0未知/1铭牌直读/2正式码表/3模拟。 */
#if FPGA_MODEL_IDENTITY_VALID
#define SIMULATION_MODEL_IDENTITY_INITIALIZER {'S','I','M','-','Q','N','C','3','0',0,0,0,0,0,0,0, 0,0,0,0, 0,1,3,0}
#else
#define SIMULATION_MODEL_IDENTITY_INITIALIZER {0}
#endif
#endif
