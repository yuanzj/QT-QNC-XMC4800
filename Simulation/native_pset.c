/* 字节布局依据冻结UIO的ethercat_xmc_protocol.c；模型不执行真实FPGA算法。 */
#include "native_pset.h"
#include <limits.h>
#include <string.h>

static uint16_t u16(const uint8_t *p) { return (uint16_t)(p[0] | ((uint16_t)p[1] << 8)); }
static uint32_t u32(const uint8_t *p) { return p[0] | ((uint32_t)p[1] << 8) | ((uint32_t)p[2] << 16) | ((uint32_t)p[3] << 24); }

uint8_t NativePset_Decode(const uint8_t *p, uint16_t length, FpgaProgram *program)
{
    FpgaProgram candidate;
    uint16_t cursor = 3;
    uint8_t i;
    if (!p || !program || length < 4 || p[0] == 0 || p[0] == 255 || p[1] != 2 ||
        p[2] == 0 || p[2] > FPGA_PROGRAM_MAX_STEPS) return 0;
    memset(&candidate, 0, sizeof(candidate));
    candidate.pset_no = p[0];
    candidate.count = p[2];
    for (i = 0; i < candidate.count; ++i) {
        const uint8_t *s = p + cursor;
        FpgaProgramStep *step = &candidate.steps[i];
        uint16_t size;
        int16_t traw;
        int32_t pos;
        if ((uint32_t)cursor + 3 > length) return 0;
        size = u16(s + 1);
        if ((uint32_t)cursor + size > length) return 0;
        step->kind = s[0];
        step->duration_ms = 1000; /* 运动类统一1s线性试验波形，不冒称实际速度环。 */
        step->failure_action = 2;
        step->angle_reset = 1;
        switch (s[0]) {
        case 1:
            if (size != 22 || s[20] > 1 || u32(s + 3) > INT32_MAX || u32(s + 15) > INT32_MAX) return 0;
            step->torque_mnm = (int32_t)u32(s + 3);
            step->angle_cdeg = (int32_t)u32(s + 15);
            step->direction = s[20];
            break;
        case 2:
            if (size != 36 || s[3] < 1 || s[3] > 2 || s[19] > 1 || s[18] < 1 || s[18] > 2 ||
                u32(s + 10) > INT32_MAX || u32(s + 24) > INT32_MAX) return 0;
            step->torque_mnm = (int32_t)u32(s + 10);
            step->angle_cdeg = (int32_t)u32(s + 24);
            step->angle_reset = s[19];
            step->timeout_ms = u16(s + 14);
            step->duration_ms += u16(s + 16);
            step->failure_action = s[18];
            break;
        case 3:
            if (size != 61 || s[3] < 1 || s[3] > 3 || s[40] > 1 || s[49] > 1 ||
                s[55] < 1 || s[55] > 2 || s[56] < 1 || s[56] > 2 ||
                u32(s + 4) > INT32_MAX || u32(s + 8) > INT32_MAX || u32(s + 12) > INT32_MAX ||
                u32(s + 24) > INT32_MAX || u32(s + 28) > INT32_MAX || u32(s + 36) > INT32_MAX) return 0;
            step->torque_mnm = (int32_t)u32(s + 4);
            step->min_torque_mnm = (int32_t)u32(s + 12);
            step->max_torque_mnm = (int32_t)u32(s + 8);
            step->min_angle_cdeg = (int32_t)u32(s + 24);
            step->max_angle_cdeg = (int32_t)u32(s + 28);
            step->angle_cdeg = (int32_t)u32(s + 36);
            if (step->min_torque_mnm > step->max_torque_mnm || step->min_angle_cdeg > step->max_angle_cdeg) return 0;
            step->direction = s[40];
            step->angle_reset = s[49];
            step->timeout_ms = u16(s + 51);
            step->duration_ms += u16(s + 53);
            step->failure_action = s[56];
            break;
        case 4:
            if (size != 13 || s[3] != 0 || s[6] != 0 || s[7] != 0 || u16(s + 4) == 0 ||
                u16(s + 4) > 5000 || u16(s + 8) < u16(s + 4) || s[12] < 1 || s[12] > 2) return 0;
            step->duration_ms = (uint32_t)u16(s + 4) + u16(s + 10);
            step->angle_reset = 0;
            step->timeout_ms = u16(s + 8);
            step->failure_action = s[12];
            break;
        case 5:
            if (size != 26 || s[25] < 1 || s[25] > 2 || u32(s + 11) > INT32_MAX) return 0;
            step->angle_cdeg = (int32_t)u32(s + 11);
            step->direction = 1;
            step->timeout_ms = u16(s + 21);
            step->duration_ms += u16(s + 23);
            step->failure_action = s[25];
            break;
        case 6:
            if (size != 5) return 0;
            step->duration_ms = 20; /* 只产生逻辑完成反馈，不操作实际DO。 */
            step->angle_reset = 0;
            break;
        default: return 0;
        }
        if (!FpgaProgram_Convert(step->torque_mnm, step->angle_cdeg, &traw, &pos)) return 0;
        cursor = (uint16_t)(cursor + size);
    }
    if (cursor != length) return 0;
    *program = candidate;
    return 1;
}
