/*
 * DOCH_MotorCtrl_DataParam.h
 *
 *  Created on: 2026年10月06日
 */
#ifndef _DOCH_MOTORCTRL_DATAPARAM_H_
#define _DOCH_MOTORCTRL_DATAPARAM_H_


#ifdef __cplusplus
extern "C" {
#endif



/*-----------------------------------------------------------------------------------------
------    Includes
-----------------------------------------------------------------------------------------*/
#include <DAVE.h>




typedef struct
{
    uint16_t Controlword; //控制字
    uint8_t Halt_running_cmd; //运行中暂停控制命令
    bool Start_Upedge_state;  // Bit4-New Set Position
}AppControlWord;



typedef struct
{
    int64_t Position_demand_value; //负载端位置指令值
    int64_t Position_actual_value_inc; //负载端内部位置当前值
    int64_t Position_actual_value; //负载端位置当前值
    int64_t Following_error_actual_value; //负载端位置误差值
    float Velocity_demand_value; //负载端速度指令值
    float Velocity_actual_value; //负载端速度当前值
    float Torque_demand_value; //力矩指令值
    float Torque_actual_value; //力矩当前值
    float Current_actual_value; //电流当前值
    float D_current_actual_value; //d轴电流当前值
    float U_current_actual_value; //U相当前电流
    float V_current_actual_value; //V相当前电流
    float W_current_actual_value; //W相当前电流
    int64_t Motor_position_demand_value; //电机端位置指令值
    int64_t Motor_position_actual_value; //电机端位置当前值
    int64_t Motor_following_error_actual_value; //电机端位置误差值
    float Motor_velocity_demand_value; //电机端速度指令值
    float Motor_velocity_actual_value; //电机端速度当前值
    uint16_t U_adc_mid_val; //U相电流校准值
    uint16_t V_adc_mid_val; //V相电流校准值
    uint16_t W_adc_mid_val; //W相电流校准值
    float Current_loop_time; //电流环耗时
    float Position_loop_time; //位置环耗时
    float Current_loop_cycle; //电流环周期
    float Position_loop_cycle; //位置环周期
    float Interp_period; //插值时间周期
    uint8_t Emergency_brake_requested; //紧急制动请求值
    uint8_t Target_update_state; //目标值更新状态
    int8_t Homing_step; //回零步骤
    uint8_t Encoder_zero_crossing_state; //编码器过零点状态
    int8_t Homing_state; //回零状态
}AppMotionInfo;





void set_app_Controlword(uint16_t val);
void set_app_Halt_running_cmd(uint8_t val);
uint8_t get_app_Emergency_brake_requested(void);
void set_app_start_upedge_state(bool state);




#ifdef __cplusplus
}
#endif // extern "C"

#endif // end of _DOCH_MOTORCTRL_DATAPARAM_H_


