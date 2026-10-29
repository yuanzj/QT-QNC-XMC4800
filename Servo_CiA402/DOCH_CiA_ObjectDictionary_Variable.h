/*
 * DOCH_CiA_ObjectDictionary_Variable.h
 *
 *  Created on: 2026年10月17日
 */
#ifndef _DOCH_CIA_OBJECTDICTIONARY_VARIABLE_H_
#define _DOCH_CIA_OBJECTDICTIONARY_VARIABLE_H_


#ifdef __cplusplus
extern "C" {
#endif

/*-----------------------------------------------------------------------------------------
------    Includes
-----------------------------------------------------------------------------------------*/
#include <DAVE.h>




typedef struct
{
    uint16_t Controlword; //402控制字
    uint16_t Statusword; //402状态字
    uint16_t Error_code; //错误码
    int16_t  Quick_stop_option_code; //快速停止操作代码
    int8_t  Modes_of_operation;     //运行模式
    int8_t  Modes_of_operation_display; //显示运行模式
}PDS_FSA;

typedef struct
{
    uint8_t Position_encoder_resolution;
    uint32_t Position_encoder_resolution_Encoder_increments; //负载端位置反馈分辨率
    uint32_t Position_encoder_resolution_Motor_revolutions; //电机端位置反馈分辨率
    uint8_t Gear_ratio;
    uint32_t Motor_revolutions; //齿轮比分母
    uint32_t Shaft_revolutions; //齿轮比分子
    uint8_t Polarity; //运动极性
}Factor_group;

typedef struct
{
    int32_t Target_position; //位置目标值
    uint8_t Position_range_limit;
    int32_t Position_range_limit_Minimal_position_limit; //位置溢出最小值
    int32_t Position_range_limit_Maximal_position_limit; //位置溢出最大值
    uint8_t Software_position_limit;
    int32_t Software_position_limit_Minimal_position_limit; //应用位置下限
    int32_t Software_position_limit_Maximal_position_limit; //应用位置上限
    uint32_t Max_profile_velocity; //应用速度限制
    uint32_t Max_motor_speed; //电机最大转速（弃用实际不生效）
    uint32_t Profile_velocity; //轮廓速度
    uint32_t Profile_acceleration; //轮廓加速度
    uint32_t Profile_deceleration; //轮廓减速度
    uint32_t Quick_stop_deceleration; //快速停止减速度
    uint32_t Max_acceleration; //应用加速度限制
    uint32_t Max_deceleration; //应用减速度限制
}Profile_position_mode;

typedef struct
{
    int32_t Home_offset; //回零偏移
    int8_t Homing_method; //回零方法
    uint8_t Homing_speeds;
    uint32_t Homing_speeds_Speed_for_switch_search; //回零搜索开关速度
    uint32_t Homing_speeds_Speed_for_zero_search; //回零搜索零点速度
    uint32_t Homing_acceleration; //回零加速度
}Homing_mode;

typedef struct
{
    int32_t Position_demand_value; //负载端位置指令值
    int32_t Position_actual_value_inc; //负载端内部位置当前值
    int32_t Position_actual_value; //负载端位置当前值
    uint32_t Following_error_window; //位置跟随误差阈值
    uint16_t Following_error_time_out; //位置跟随误差阈值时间
    uint32_t Position_window; //位置到达检测窗口
    uint16_t Position_window_time; //位置到达检测窗口时间
    int32_t Following_error_actual_value; //负载端位置误差值
}Position_control_function;

typedef struct
{
    uint8_t Interpolation_time_period;
    uint8_t Interpolation_time_period_Ip_time_units; //插值模式时间单位
    int8_t Interpolation_time_period_Ip_time_index; //插值模式时间指数
}Interpolated_position_mode;

typedef struct
{
    int32_t Velocity_demand_value; //负载端速度指令值
    int32_t Velocity_actual_value; //负载端速度当前值
    uint16_t Velocity_window;      //速度到达检测窗口
    uint16_t Velocity_window_time; //速度到达检测窗口时间
    uint16_t Velocity_threshold;   //零速检测窗口
    uint16_t Velocity_threshold_time; //零速检测窗口时间
    int32_t Target_velocity;       //速度目标值
}Profile_velocity_mode;

typedef struct
{
    int16_t  Target_torque; //力矩目标值
    uint16_t Max_torque; //应用力矩限制相对值
    uint16_t Max_current; //应用电流限制相对值
    int16_t  Torque_demand_value; //力矩指令值
    uint32_t Motor_rated_current; //电机额定电流
    uint32_t Motor_rated_torque; //电机额定力矩/推力
    int16_t  Torque_actual_value; //力矩当前值
    int16_t  Current_actual_value; //电流当前值
    uint32_t DC_link_circuit_voltage; //母线电压当前值
    uint32_t Torque_slope; //力矩上升斜率
}Profile_torque_mode;

typedef struct
{
    int32_t Position_offset; //目标位置偏置值
    int32_t Velocity_offset; //目标速度偏置值
    int16_t Torque_offset;   //目标转矩偏置值
}CSP_CSV_CST;

typedef struct
{
    uint32_t Digital_inputs; //数字IO输入值
    uint8_t Digital_outputs;
    uint32_t Digital_outputs_Physical_outputs; //数字IO输出值
    uint32_t Digital_outputs_Bit_mask; //数字IO输出掩码开关
}Optional_application;






uint32_t set_Controlword(uint16_t val);
uint16_t get_Controlword(void);

uint32_t set_Statusword(uint16_t val);
uint16_t get_Statusword(void);

uint32_t set_Error_code(uint16_t val);
uint16_t get_Error_code(void);

uint32_t set_Quick_stop_option_code(int16_t val);
int16_t get_Quick_stop_option_code(void);

uint32_t set_Modes_of_operation(int8_t val);
int8_t get_Modes_of_operation(void);

uint32_t set_Modes_of_operation_display(int8_t val);
int8_t get_Modes_of_operation_display(void);

uint32_t set_Position_encoder_resolution(uint8_t val);
uint8_t get_Position_encoder_resolution(void);

uint32_t set_Position_encoder_resolution_Encoder_increments(uint32_t val);
uint32_t get_Position_encoder_resolution_Encoder_increments(void);

uint32_t set_Position_encoder_resolution_Motor_revolutions(uint32_t val);
uint32_t get_Position_encoder_resolution_Motor_revolutions(void);

uint32_t set_Gear_ratio(uint8_t val);
uint8_t get_Gear_ratio(void);

uint32_t set_Motor_revolutions(uint32_t val);
uint32_t get_Motor_revolutions(void);

uint32_t set_Shaft_revolutions(uint32_t val);
uint32_t get_Shaft_revolutions(void);

uint32_t set_Polarity(uint8_t val);
uint8_t get_Polarity(void);

uint32_t set_Target_position(int32_t val);
int32_t get_Target_position(void);

uint32_t set_Position_range_limit(uint8_t val);
uint8_t get_Position_range_limit(void);

uint32_t set_Position_range_limit_Minimal_position_limit(int32_t val);
int32_t get_Position_range_limit_Minimal_position_limit(void);

uint32_t set_Position_range_limit_Maximal_position_limit(int32_t val);
int32_t get_Position_range_limit_Maximal_position_limit(void);

uint32_t set_Software_position_limit(uint8_t val);
uint8_t get_Software_position_limit(void);

uint32_t set_Software_position_limit_Minimal_position_limit(int32_t val);
int32_t get_Software_position_limit_Minimal_position_limit(void);

uint32_t set_Software_position_limit_Maximal_position_limit(int32_t val);
int32_t get_Software_position_limit_Maximal_position_limit(void);

uint32_t set_Max_profile_velocity(uint32_t val);
uint32_t get_Max_profile_velocity(void);

uint32_t set_Max_motor_speed(uint32_t val);
uint32_t get_Max_motor_speed(void);

uint32_t set_Profile_velocity(uint32_t val);
uint32_t get_Profile_velocity(void);

uint32_t set_Profile_acceleration(uint32_t val);
uint32_t get_Profile_acceleration(void);

uint32_t set_Profile_deceleration(uint32_t val);
uint32_t get_Profile_deceleration(void);

uint32_t set_Quick_stop_deceleration(uint32_t val);
uint32_t get_Quick_stop_deceleration(void);

uint32_t set_Max_acceleration(uint32_t val);
uint32_t get_Max_acceleration(void);

uint32_t set_Max_deceleration(uint32_t val);
uint32_t get_Max_deceleration(void);

uint32_t set_Home_offset(int32_t val);
int32_t get_Home_offset(void);

uint32_t set_Homing_method(int8_t val);
int8_t get_Homing_method(void);

uint32_t set_Homing_speeds(uint8_t val);
uint8_t get_Homing_speeds(void);

uint32_t set_Homing_speeds_Speed_for_switch_search(uint32_t val);
uint32_t get_Homing_speeds_Speed_for_switch_search(void);

uint32_t set_Homing_speeds_Speed_for_zero_search(uint32_t val);
uint32_t get_Homing_speeds_Speed_for_zero_search(void);

uint32_t set_Homing_acceleration(uint32_t val);
uint32_t get_Homing_acceleration(void);

uint32_t set_Position_demand_value(int32_t val);
int32_t get_Position_demand_value(void);

uint32_t set_Position_actual_value_inc(int32_t val);
int32_t get_Position_actual_value_inc(void);

uint32_t set_Position_actual_value(int32_t val);
int32_t get_Position_actual_value(void);

uint32_t set_Following_error_window(uint32_t val);
uint32_t get_Following_error_window(void);

uint32_t set_Following_error_time_out(uint16_t val);
uint16_t get_Following_error_time_out(void);

uint32_t set_Position_window(uint32_t val);
uint32_t get_Position_window(void);

uint32_t set_Position_window_time(uint16_t val);
uint16_t get_Position_window_time(void);

uint32_t set_Following_error_actual_value(int32_t val);
int32_t get_Following_error_actual_value(void);

uint32_t set_Interpolation_time_period(uint8_t val);
uint8_t get_Interpolation_time_period(void);

uint32_t set_Interpolation_time_period_Ip_time_units(uint8_t val);
uint8_t get_Interpolation_time_period_Ip_time_units(void);

uint32_t set_Interpolation_time_period_Ip_time_index(int8_t val);
int8_t get_Interpolation_time_period_Ip_time_index(void);

uint32_t set_Velocity_demand_value(int32_t val);
int32_t get_Velocity_demand_value(void);

uint32_t set_Velocity_actual_value(int32_t val);
int32_t get_Velocity_actual_value(void);

uint32_t set_Velocity_window(uint16_t val);
uint16_t get_Velocity_window(void);

uint32_t set_Velocity_window_time(uint16_t val);
uint16_t get_Velocity_window_time(void);

uint32_t set_Velocity_threshold(uint16_t val);
uint16_t get_Velocity_threshold(void);

uint32_t set_Velocity_threshold_time(uint16_t val);
uint16_t get_Velocity_threshold_time(void);

uint32_t set_Target_velocity(int32_t val);
int32_t get_Target_velocity(void);

uint32_t set_Target_torque(int16_t val);
int16_t get_Target_torque(void);

uint32_t set_Max_torque(uint16_t val);
uint16_t get_Max_torque(void);

uint32_t set_Max_current(uint16_t val);
uint16_t get_Max_current(void);

uint32_t set_Torque_demand_value(int16_t val);
int16_t get_Torque_demand_value(void);

uint32_t set_Motor_rated_current(uint32_t val);
uint32_t get_Motor_rated_current(void);

uint32_t set_Motor_rated_torque(uint32_t val);
uint32_t get_Motor_rated_torque(void);

uint32_t set_Torque_actual_value(int16_t val);
int16_t get_Torque_actual_value(void);

uint32_t set_Current_actual_value(int16_t val);
int16_t get_Current_actual_value(void);

uint32_t set_DC_link_circuit_voltage(uint32_t val);
uint32_t get_DC_link_circuit_voltage(void);

uint32_t set_Torque_slope(uint32_t val);
uint32_t get_Torque_slope(void);

uint32_t set_Position_offset(int32_t val);
int32_t get_Position_offset(void);

uint32_t set_Velocity_offset(int32_t val);
int32_t get_Velocity_offset(void);

uint32_t set_Torque_offset(int16_t val);
int16_t get_Torque_offset(void);

uint32_t set_Digital_inputs(uint32_t val);
uint32_t get_Digital_inputs(void);

uint32_t set_Digital_outputs(uint8_t val);
uint8_t get_Digital_outputs(void);

uint32_t set_Digital_outputs_Physical_outputs(uint32_t val);
uint32_t get_Digital_outputs_Physical_outputs(void);

uint32_t set_Digital_outputs_Bit_mask(uint32_t val);
uint32_t get_Digital_outputs_Bit_mask(void);













#ifdef __cplusplus
}
#endif // extern "C"

#endif // end of _DOCH_CIA_OBJECTDICTIONARY_VARIABLE_H_


