/* 测试输入：编码器计数偏置/反向及跨步复位；不作物理角度或质量判定证据。
 * 0关闭，1正向回绕，2反向回绕，3跨步大跳变对照。默认构建不引用此函数。
 * 使用UINT32模运算并显式解释补码，避免有符号溢出与超范围强制转换。 */
#ifndef SIMULATION_POSITION_TEST_VECTOR_H
#define SIMULATION_POSITION_TEST_VECTOR_H
#include <stdint.h>
#include <limits.h>
#include "model_config.h"
static inline int32_t Simulation_PositionTestVector(int32_t native_position, uint8_t step)
{
    uint32_t bits = (uint32_t)native_position;
    if (step == 0 || FPGA_TEST_POSITION_VECTOR == 0) return native_position;
    if (FPGA_TEST_POSITION_VECTOR == 1)
        bits += (uint32_t)INT32_MAX - 262144u;
    else if (FPGA_TEST_POSITION_VECTOR == 2)
        bits = (uint32_t)INT32_MIN + 262144u - bits;
    else
        bits += (step & 1u) ? (uint32_t)INT32_MAX - 536870912u : (uint32_t)INT32_MIN + 536870912u;
    return bits <= (uint32_t)INT32_MAX ? (int32_t)bits : -1 - (int32_t)(UINT32_MAX - bits);
}
#endif
