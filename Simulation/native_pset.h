/* 现有UIO原生专家PSET解码；仅做隔离模拟输入转换，不定义新的生产协议。 */
#ifndef NATIVE_PSET_H
#define NATIVE_PSET_H
#include "../FpgaSim/fpga_program.h"
/* type4是原生WAIT、type5是原生卸荷，不能冒充HMI的卸荷4／拧松5。 */
uint8_t NativePset_Decode(const uint8_t *bytes, uint16_t length, FpgaProgram *program);
#endif
