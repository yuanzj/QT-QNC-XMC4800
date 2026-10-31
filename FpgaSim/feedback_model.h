/* 独立合成接头：不接收目标扭矩/目标角度/判定窗口，不预设OK/NOK。 */
#ifndef FEEDBACK_MODEL_H
#define FEEDBACK_MODEL_H
#include <stdint.h>
#include "../Simulation/model_config.h"
#define MODEL_ANGLE_Q 1000000LL /* 每0.01度的子刻度；积分保留余数。 */
typedef struct {
    int32_t seat_angle_cdeg, drag_mnm, stiffness_mnm_per_deg, capacity_mnm;
    int32_t brake_rpm_milli_per_ms;
    uint8_t free_run, jam;
} ModelPlantConfig;
typedef struct {
    ModelPlantConfig config;
    int64_t position_q;
    int32_t velocity_rpm_milli, torque_mnm;
    uint8_t valid;
    int8_t last_direction;
} ModelPlantState;
/* 配置来自独立固定夹具，绝不随PSET目标调整。1硬/2软/3空转/4卡滞。 */
void ModelPlant_Init(ModelPlantState *plant, uint8_t profile);
/* 一次严格1ms；command为控制器输出，active=0时独立制动/卸载。 */
void ModelPlant_Tick(ModelPlantState *plant, int32_t command_rpm_milli, uint16_t accel_ms, uint8_t active);
#endif
