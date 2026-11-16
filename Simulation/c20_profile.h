/* C20 interface bridge: original model publishes encoder inc and INT64 inc/s. */
#ifndef SIMULATION_C20_PROFILE_H
#define SIMULATION_C20_PROFILE_H
#include <stdint.h>
#include "model_config.h"
#if FPGA_C20_PROFILE
#define QEC_SIM_PAIRED_ID UINT32_C(0x20261116)
#define XMC_SIM_GEAR_RATIO 30U
#define XMC_SIM_ENCODER_RESOLUTION 8388608U
#define XMC_SIM_MAX_OUTPUT_DECI_RPM 10000U
#define XMC_SIM_MAX_OUTPUT_RPM_MILLI 1000000U
#define XMC_SIM_MAX_MOTOR_DECI_RPM 300000U
extern int64_t Velocity_actual_64_0x2212;
#define SimulatedSlave_Velocity64 Velocity_actual_64_0x2212
/* Accessed only by the model tick; storage polling stays in the main loop. */
uint8_t App_Run_IsPermitted(void);
/* Pending controls have priority over starting an idle flash transaction. */
uint8_t App_JobCtrl_GetControl(void);
/* Main-loop storage owner; reserves the same gate as SDO maintenance. */
void App_Storage_Poll(uint32_t now);
#endif
#endif
