/*
 * DOCH_CiA_ObjectDictionary_Variable.c
 *
 *  Created on: 2026年10月17日
 */
/* Includes ---引用头文件----------------------------------------------------*/
#include "DOCH_CiA_Common.h"
#include "DOCH_CiA_ObjectDictionary_Variable.h"
#include "DOCH_Motor_Ctrl_Sm.h"
#include "SSC/Src/QiaoTian_XMC_ServoObjects.h"


#define ABORT_CODE_SUCCESSFUL               (0x00000000)



//64位转32位，符号位处理
int32_t limit_64_to_32(int64_t val_64)
{
    int32_t val_32 = val_64;
    if(val_64 & 0x8000000000000000)
    {
        val_32 |= 0x80000000;
    }
    else
    {
        val_32 &= 0x7FFFFFFF;
    }
    return val_32;
}


PDS_FSA kPDS_FSA;
Factor_group kFactor_group;
Profile_position_mode kProfile_position_mode;
Homing_mode kHoming_mode;
Position_control_function kPosition_control_function;
Interpolated_position_mode kInterpolated_position_mode;
Profile_velocity_mode kProfile_velocity_mode;
Profile_torque_mode kProfile_torque_mode;
CSP_CSV_CST kCSP_CSV_CST;
Optional_application kOptional_application;

uint32_t set_Controlword(uint16_t val)
{
    kPDS_FSA.Controlword = val;

    Controlword0x6040 = val;

//    ControlwordChange_PDAS_FSA();//cia402的控制字只影响PDS_FSA的状态机

    return ABORT_CODE_SUCCESSFUL;
}

uint16_t get_Controlword(void)
{
//    return kPDS_FSA.Controlword;
    return Controlword0x6040;
}

uint32_t set_Statusword(uint16_t val)
{
    //Cia402的控制字只能由PDS_FSA的状态机修改
    kPDS_FSA.Statusword = val;

    Statusword0x6041 = val;

    return ABORT_CODE_SUCCESSFUL;
}

uint16_t get_Statusword(void)
{
//    return kPDS_FSA.Statusword;
    return Statusword0x6041;
}

uint32_t set_Error_code(uint16_t val)
{
    //Cia402的错误码只能由PDS_FSA的状态机修改
    kPDS_FSA.Error_code = val;

	Error_code0x603F = val;

    return ABORT_CODE_SUCCESSFUL;
}

uint16_t get_Error_code(void)
{
    return kPDS_FSA.Error_code;
}

uint32_t set_Quick_stop_option_code(int16_t val)
{
//    set_app_Quick_stop_option_code(val);
    kPDS_FSA.Quick_stop_option_code = val;

    return ABORT_CODE_SUCCESSFUL;
}

int16_t get_Quick_stop_option_code(void)
{
//    kPDS_FSA.Quick_stop_option_code = get_app_Quick_stop_option_code();
    kPDS_FSA.Quick_stop_option_code = Quick_stop_option_code0x605A;
    return kPDS_FSA.Quick_stop_option_code;
}

uint32_t set_Modes_of_operation(int8_t val)
{
	kPDS_FSA.Modes_of_operation = val;
    kPDS_FSA.Modes_of_operation = Modes_of_operation0x6060;

    //目前支持的Cia402模式:PP,PV,PT,HM,CSP,CSV,CST,MIT
    switch(kPDS_FSA.Modes_of_operation)
    {
        case OD6060_PPM:
//            set_app_Modes_of_operation(MOTOR_CTL_SM_MODE_POSITION);
            break;
        case OD6060_PVM:
//            set_app_Modes_of_operation(MOTOR_CTL_SM_MODE_SPEED);
            break;
        case OD6060_PTM:
//            set_app_Modes_of_operation(MOTOR_CTL_SM_MODE_TORQUE);
            break;
        case OD6060_HM:
//            set_app_Modes_of_operation(MOTOR_CTL_SM_MODE_HOMING);
            break;
        case OD6060_CSP:
//            set_app_Modes_of_operation(MOTOR_CTL_SM_MODE_CSP);
            break;
        case OD6060_CSV:
//            set_app_Modes_of_operation(MOTOR_CTL_SM_MODE_CSV);
            break;
        case OD6060_CST:
//            set_app_Modes_of_operation(MOTOR_CTL_SM_MODE_CST);
            break;
        case OD6060_MIT:
//            set_app_Modes_of_operation(MOTOR_CTL_SM_MODE_MIT);
            break;
        default:
            break;
    }

    return ABORT_CODE_SUCCESSFUL;
}

int8_t get_Modes_of_operation(void)
{
    //目前支持的cia402模式:PP,PV,PT,HM,CSP,CSV,CST,MIT
//	switch(get_app_Modes_of_operation())
    switch(Modes_of_operation_display0x6061)
    {
        case MOTOR_CTL_SM_MODE_POSITION:
            kPDS_FSA.Modes_of_operation = OD6060_PPM;
            break;
        case MOTOR_CTL_SM_MODE_SPEED:
            kPDS_FSA.Modes_of_operation = OD6060_PVM;
            break;
        case MOTOR_CTL_SM_MODE_TORQUE:
            kPDS_FSA.Modes_of_operation = OD6060_PTM;
            break;
        case MOTOR_CTL_SM_MODE_HOMING:
            kPDS_FSA.Modes_of_operation = OD6060_HM;
            break;
        case MOTOR_CTL_SM_MODE_CSP:
            kPDS_FSA.Modes_of_operation = OD6060_CSP;
            break;
        case MOTOR_CTL_SM_MODE_CSV:
            kPDS_FSA.Modes_of_operation = OD6060_CSV;
            break;
        case MOTOR_CTL_SM_MODE_CST:
            kPDS_FSA.Modes_of_operation = OD6060_CST;
            break;
        case MOTOR_CTL_SM_MODE_MIT:
            kPDS_FSA.Modes_of_operation = OD6060_MIT;
            break;
        default:
            break;
    }

    return kPDS_FSA.Modes_of_operation;
}

uint32_t set_Modes_of_operation_display(int8_t val)
{
	kPDS_FSA.Modes_of_operation_display = val;
    kPDS_FSA.Modes_of_operation_display = Modes_of_operation_display0x6061;

    return ABORT_CODE_SUCCESSFUL;
}

int8_t get_Modes_of_operation_display(void)
{

//    switch(get_app_Modes_of_operation_display())
    switch(Modes_of_operation_display0x6061)
    {
        case MOTOR_CTL_SM_MODE_POSITION:
            kPDS_FSA.Modes_of_operation_display = OD6060_PPM;
            break;
        case MOTOR_CTL_SM_MODE_SPEED:
            kPDS_FSA.Modes_of_operation_display = OD6060_PVM;
            break;
        case MOTOR_CTL_SM_MODE_TORQUE:
            kPDS_FSA.Modes_of_operation_display = OD6060_PTM;
            break;
        case MOTOR_CTL_SM_MODE_HOMING:
            kPDS_FSA.Modes_of_operation_display = OD6060_HM;
            break;
        case MOTOR_CTL_SM_MODE_CSP:
            kPDS_FSA.Modes_of_operation_display = OD6060_CSP;
            break;
        case MOTOR_CTL_SM_MODE_CSV:
            kPDS_FSA.Modes_of_operation_display = OD6060_CSV;
            break;
        case MOTOR_CTL_SM_MODE_CST:
            kPDS_FSA.Modes_of_operation_display = OD6060_CST;
            break;
        case MOTOR_CTL_SM_MODE_MIT:
            kPDS_FSA.Modes_of_operation_display = OD6060_MIT;
            break;
        default:
            break;
    }

    return kPDS_FSA.Modes_of_operation_display;
}

uint32_t set_Position_encoder_resolution(uint8_t val)
{

    kFactor_group.Position_encoder_resolution = val;

    return ABORT_CODE_SUCCESSFUL;
}

uint8_t get_Position_encoder_resolution(void)
{

    return kFactor_group.Position_encoder_resolution;
}

uint32_t set_Position_encoder_resolution_Encoder_increments(uint32_t val)
{

    kFactor_group.Position_encoder_resolution_Encoder_increments = val;

//    set_app_Load_encoder_resolution(val);   //设置负载端编码器分辨率

    return ABORT_CODE_SUCCESSFUL;
}
uint32_t get_Position_encoder_resolution_Encoder_increments(void)
{

//    kFactor_group.Position_encoder_resolution_Encoder_increments = get_app_Load_encoder_resolution();

    return kFactor_group.Position_encoder_resolution_Encoder_increments;
}

uint32_t set_Position_encoder_resolution_Motor_revolutions(uint32_t val)
{

    kFactor_group.Position_encoder_resolution_Motor_revolutions = val;

//    set_app_Motor_encoder_resolution(val);  //设置电机端编码器分辨率

    return ABORT_CODE_SUCCESSFUL;
}

uint32_t get_Position_encoder_resolution_Motor_revolutions(void)
{

//    kFactor_group.Position_encoder_resolution_Motor_revolutions = get_app_Motor_encoder_resolution();

    return kFactor_group.Position_encoder_resolution_Motor_revolutions;
}

uint32_t set_Gear_ratio(uint8_t val)
{
    kFactor_group.Gear_ratio = val;

    return ABORT_CODE_SUCCESSFUL;
}

uint8_t get_Gear_ratio(void)
{
    return kFactor_group.Gear_ratio;
}

uint32_t set_Motor_revolutions(uint32_t val)
{

    kFactor_group.Motor_revolutions = val;

    //电子齿轮比分母
//    set_app_Reduction_ratio_den(val);

    return ABORT_CODE_SUCCESSFUL;
}

uint32_t get_Motor_revolutions(void)
{
//    kFactor_group.Motor_revolutions = get_app_Reduction_ratio_den();
    return kFactor_group.Motor_revolutions;
}

uint32_t set_Shaft_revolutions(uint32_t val)
{

    kFactor_group.Shaft_revolutions = val;
    //电子齿轮比分子
//    set_app_Reduction_ratio_num(val);

    return ABORT_CODE_SUCCESSFUL;
}

uint32_t get_Shaft_revolutions(void)
{

//    kFactor_group.Shaft_revolutions = get_app_Reduction_ratio_num();

    return kFactor_group.Shaft_revolutions;
}

uint32_t set_Polarity(uint8_t val)
{

    kFactor_group.Polarity = val;

//    set_app_Polarity(val);

    return ABORT_CODE_SUCCESSFUL;
}

uint8_t get_Polarity(void)
{

//    kFactor_group.Polarity = get_app_Polarity();

    return kFactor_group.Polarity;
}

uint32_t set_Target_position(int32_t val)
{
    kProfile_position_mode.Target_position = val;

//    set_app_Target_position(val);

    return ABORT_CODE_SUCCESSFUL;
}
int32_t get_Target_position(void)
{

//    kProfile_position_mode.Target_position = get_app_Target_position();

    return kProfile_position_mode.Target_position;
}

uint32_t set_Position_range_limit(uint8_t val)
{

    kProfile_position_mode.Position_range_limit = val;

    return ABORT_CODE_SUCCESSFUL;
}

uint8_t get_Position_range_limit(void)
{

    return kProfile_position_mode.Position_range_limit;
}

uint32_t set_Position_range_limit_Minimal_position_limit(int32_t val)
{

    kProfile_position_mode.Position_range_limit_Minimal_position_limit = val;

//    set_app_Position_range_limit_Minimal_position_limit(val);

    return ABORT_CODE_SUCCESSFUL;
}

int32_t get_Position_range_limit_Minimal_position_limit(void)
{

//    kProfile_position_mode.Position_range_limit_Minimal_position_limit = limit_64_to_32(get_app_Position_range_limit_Minimal_position_limit());

    return kProfile_position_mode.Position_range_limit_Minimal_position_limit;
}

uint32_t set_Position_range_limit_Maximal_position_limit(int32_t val)
{

    kProfile_position_mode.Position_range_limit_Maximal_position_limit = val;

//    set_app_Position_range_limit_Maximal_position_limit(val);

    return ABORT_CODE_SUCCESSFUL;
}

int32_t get_Position_range_limit_Maximal_position_limit(void)
{

//    kProfile_position_mode.Position_range_limit_Maximal_position_limit = limit_64_to_32(get_app_Position_range_limit_Maximal_position_limit());

    return kProfile_position_mode.Position_range_limit_Maximal_position_limit;
}

uint32_t set_Software_position_limit(uint8_t val)
{

    kProfile_position_mode.Software_position_limit = val;

    return ABORT_CODE_SUCCESSFUL;
}
uint8_t get_Software_position_limit(void)
{

    return kProfile_position_mode.Software_position_limit;
}

uint32_t set_Software_position_limit_Minimal_position_limit(int32_t val)
{

    kProfile_position_mode.Software_position_limit_Minimal_position_limit = val;

//    set_app_Software_position_limit_Minimal_position_limit(val);

    return ABORT_CODE_SUCCESSFUL;
}

int32_t get_Software_position_limit_Minimal_position_limit(void)
{

//    kProfile_position_mode.Software_position_limit_Minimal_position_limit = limit_64_to_32(get_app_Software_position_limit_Minimal_position_limit());

    return kProfile_position_mode.Software_position_limit_Minimal_position_limit;
}

uint32_t set_Software_position_limit_Maximal_position_limit(int32_t val)
{

    kProfile_position_mode.Software_position_limit_Maximal_position_limit = val;

//    set_app_Software_position_limit_Maximal_position_limit(val);

    return ABORT_CODE_SUCCESSFUL;
}

int32_t get_Software_position_limit_Maximal_position_limit(void)
{

//    kProfile_position_mode.Software_position_limit_Maximal_position_limit = limit_64_to_32(get_app_Software_position_limit_Maximal_position_limit());

    return kProfile_position_mode.Software_position_limit_Maximal_position_limit;
}

uint32_t set_Max_profile_velocity(uint32_t val)
{

    kProfile_position_mode.Max_profile_velocity = val;

    // P/s转RPM
//    set_app_Max_profile_velocity((float)val * get_app_Load_pps_2_rpm());

    return ABORT_CODE_SUCCESSFUL;
}
uint32_t get_Max_profile_velocity(void)
{

//    kProfile_position_mode.Max_profile_velocity = get_app_Max_profile_velocity() * get_app_Load_rpm_2_pps();

    return kProfile_position_mode.Max_profile_velocity;
}

uint32_t set_Max_motor_speed(uint32_t val)
{

    kProfile_position_mode.Max_motor_speed = val;

//    set_app_Max_motor_speed((float)val);

    return ABORT_CODE_SUCCESSFUL;
}
uint32_t get_Max_motor_speed(void)
{

//    kProfile_position_mode.Max_motor_speed = get_app_Max_motor_speed();

    return kProfile_position_mode.Max_motor_speed;
}

uint32_t set_Profile_velocity(uint32_t val)
{

    kProfile_position_mode.Profile_velocity = val;

    // P/s转RPM
//    set_app_Profile_velocity((float)val * get_app_Load_pps_2_rpm());

    return ABORT_CODE_SUCCESSFUL;
}
uint32_t get_Profile_velocity(void)
{

//    kProfile_position_mode.Profile_velocity = get_app_Profile_velocity() * get_app_Load_rpm_2_pps();

    return kProfile_position_mode.Profile_velocity;
}

uint32_t set_Profile_acceleration(uint32_t val)
{

    kProfile_position_mode.Profile_acceleration = val;

    // P/s/s转RPM/s
//    set_app_Profile_acceleration((float)val * get_app_Load_pps_2_rpm());

    return ABORT_CODE_SUCCESSFUL;
}
uint32_t get_Profile_acceleration(void)
{

//    kProfile_position_mode.Profile_acceleration = get_app_Profile_acceleration() * get_app_Load_rpm_2_pps();

    return kProfile_position_mode.Profile_acceleration;
}

uint32_t set_Profile_deceleration(uint32_t val)
{

    kProfile_position_mode.Profile_deceleration = val;

    // P/s/s转RPM/s
//    set_app_Profile_deceleration((float)val * get_app_Load_pps_2_rpm());

    return ABORT_CODE_SUCCESSFUL;
}
uint32_t get_Profile_deceleration(void)
{

//    kProfile_position_mode.Profile_deceleration = get_app_Profile_deceleration() * get_app_Load_rpm_2_pps();

    return kProfile_position_mode.Profile_deceleration;
}

uint32_t set_Quick_stop_deceleration(uint32_t val)
{

    kProfile_position_mode.Quick_stop_deceleration = val;

    // P/s/s转RPM/s
//    set_app_Quick_stop_deceleration((float)val * get_app_Load_pps_2_rpm());

    return ABORT_CODE_SUCCESSFUL;
}
uint32_t get_Quick_stop_deceleration(void)
{

//    kProfile_position_mode.Quick_stop_deceleration = get_app_Quick_stop_deceleration() * get_app_Load_rpm_2_pps();

    return kProfile_position_mode.Quick_stop_deceleration;
}

uint32_t set_Max_acceleration(uint32_t val)
{

    kProfile_position_mode.Max_acceleration = val;

    // P/s/s转RPM/s
//    set_app_Max_acceleration((float)val * get_app_Load_pps_2_rpm());

    return ABORT_CODE_SUCCESSFUL;
}

uint32_t get_Max_acceleration(void)
{

//    kProfile_position_mode.Max_acceleration = get_app_Max_acceleration() * get_app_Load_rpm_2_pps();

    return kProfile_position_mode.Max_acceleration;
}

uint32_t set_Max_deceleration(uint32_t val)
{

    kProfile_position_mode.Max_deceleration = val;

    // P/s/s转RPM/s
//    set_app_Max_deceleration((float)val * get_app_Load_pps_2_rpm());

    return ABORT_CODE_SUCCESSFUL;
}

uint32_t get_Max_deceleration(void)
{

//    kProfile_position_mode.Max_deceleration = get_app_Max_deceleration() * get_app_Load_rpm_2_pps();

    return kProfile_position_mode.Max_deceleration;
}

uint32_t set_Home_offset(int32_t val)
{

    kHoming_mode.Home_offset = val;

//    set_app_Home_offset(val);

    return ABORT_CODE_SUCCESSFUL;
}

int32_t get_Home_offset(void)
{

//    kHoming_mode.Home_offset = get_app_Home_offset();

    return kHoming_mode.Home_offset;
}

uint32_t set_Homing_method(int8_t val)
{
    kHoming_mode.Homing_method = val;

//    set_app_Homing_method(val);

    return ABORT_CODE_SUCCESSFUL;
}

int8_t get_Homing_method(void)
{

//    kHoming_mode.Homing_method = get_app_Homing_method();

    return kHoming_mode.Homing_method;
}

uint32_t set_Homing_speeds(uint8_t val)
{

    kHoming_mode.Homing_speeds = val;

    return ABORT_CODE_SUCCESSFUL;
}

uint8_t get_Homing_speeds(void)
{

    return kHoming_mode.Homing_speeds;
}

uint32_t set_Homing_speeds_Speed_for_switch_search(uint32_t val)
{

    kHoming_mode.Homing_speeds_Speed_for_switch_search = val;

    // P/s转RPM
//    set_app_Homing_speed_search_for_switch((float)val * get_app_Load_pps_2_rpm());

    return ABORT_CODE_SUCCESSFUL;
}

uint32_t get_Homing_speeds_Speed_for_switch_search(void)
{

    // RPM转P/s
//    kHoming_mode.Homing_speeds_Speed_for_switch_search = get_app_Homing_speed_search_for_switch() * get_app_Load_rpm_2_pps();

    return kHoming_mode.Homing_speeds_Speed_for_switch_search;
}

uint32_t set_Homing_speeds_Speed_for_zero_search(uint32_t val)
{

    kHoming_mode.Homing_speeds_Speed_for_zero_search = val;

    // P/s转RPM
//    set_app_Homing_speed_search_for_zero((float)val * get_app_Load_pps_2_rpm());

    return ABORT_CODE_SUCCESSFUL;
}

uint32_t get_Homing_speeds_Speed_for_zero_search(void)
{
    // RPM转P/s
//    kHoming_mode.Homing_speeds_Speed_for_zero_search = get_app_Homing_speed_search_for_zero() * get_app_Load_rpm_2_pps();

    return kHoming_mode.Homing_speeds_Speed_for_zero_search;
}

uint32_t set_Homing_acceleration(uint32_t val)
{

    kHoming_mode.Homing_acceleration = val;

    // P/s/s转RPM/s
//    set_app_Homing_acceleration((float)val * get_app_Load_pps_2_rpm());

    return ABORT_CODE_SUCCESSFUL;
}

uint32_t get_Homing_acceleration(void)
{
    // RPM/s/s转P/s/s
//    kHoming_mode.Homing_acceleration = get_app_Homing_acceleration() * get_app_Load_rpm_2_pps();

    return kHoming_mode.Homing_acceleration;
}

uint32_t set_Position_demand_value(int32_t val)
{

    kPosition_control_function.Position_demand_value = val;

    return ABORT_CODE_SUCCESSFUL;
}

int32_t get_Position_demand_value(void)
{

//    kPosition_control_function.Position_demand_value = get_app_Position_demand_value();

    return kPosition_control_function.Position_demand_value;
}

uint32_t set_Position_actual_value_inc(int32_t val)
{

    kPosition_control_function.Position_actual_value_inc = val;

    return ABORT_CODE_SUCCESSFUL;
}

int32_t get_Position_actual_value_inc(void)
{

//    kPosition_control_function.Position_actual_value_inc = get_app_Position_actual_value_inc();

    return kPosition_control_function.Position_actual_value_inc;
}

uint32_t set_Position_actual_value(int32_t val)
{

    kPosition_control_function.Position_actual_value = val;

    return ABORT_CODE_SUCCESSFUL;
}

int32_t get_Position_actual_value(void)
{

//    kPosition_control_function.Position_actual_value = get_app_Position_actual_value();

    return kPosition_control_function.Position_actual_value;
}

uint32_t set_Following_error_window(uint32_t val)
{

//    set_app_Following_error_window(val);

    kPosition_control_function.Following_error_window = val;

    return ABORT_CODE_SUCCESSFUL;
}

uint32_t get_Following_error_window(void)
{

//    kPosition_control_function.Following_error_window = get_app_Following_error_window();

    return kPosition_control_function.Following_error_window;
}

uint32_t set_Following_error_time_out(uint16_t val)
{

    kPosition_control_function.Following_error_time_out = val;

//    set_app_Following_error_time_out((float)val * 0.001f);

    return ABORT_CODE_SUCCESSFUL;
}

uint16_t get_Following_error_time_out(void)
{

//    kPosition_control_function.Following_error_time_out = get_app_Following_error_time_out() * 1000;

    return kPosition_control_function.Following_error_time_out;
}

uint32_t set_Position_window(uint32_t val)
{

//    set_app_Position_window(val);

    kPosition_control_function.Position_window = val;

    return ABORT_CODE_SUCCESSFUL;
}

uint32_t get_Position_window(void)
{

//    kPosition_control_function.Position_window = get_app_Position_window();

    return kPosition_control_function.Position_window;
}

uint32_t set_Position_window_time(uint16_t val)
{

//    set_app_Position_window_time((float)val * 0.001f);

    kPosition_control_function.Position_window_time = val;

    return ABORT_CODE_SUCCESSFUL;
}

uint16_t get_Position_window_time(void)
{

//    kPosition_control_function.Position_window_time = get_app_Position_window_time() * 1000;

    return kPosition_control_function.Position_window_time;
}

uint32_t set_Following_error_actual_value(int32_t val)
{

    kPosition_control_function.Following_error_actual_value = val;

    return ABORT_CODE_SUCCESSFUL;
}

int32_t get_Following_error_actual_value(void)
{

//    kPosition_control_function.Following_error_actual_value = get_app_Following_error_actual_value();

    return kPosition_control_function.Following_error_actual_value;
}

uint32_t set_Interpolation_time_period(uint8_t val)
{

    kInterpolated_position_mode.Interpolation_time_period = val;

    return ABORT_CODE_SUCCESSFUL;
}

uint8_t get_Interpolation_time_period(void)
{

    return kInterpolated_position_mode.Interpolation_time_period;
}

uint32_t set_Interpolation_time_period_Ip_time_units(uint8_t val)
{

    kInterpolated_position_mode.Interpolation_time_period_Ip_time_units = val;

//    set_app_Interp_time_value(val);

    return ABORT_CODE_SUCCESSFUL;
}

uint8_t get_Interpolation_time_period_Ip_time_units(void)
{

    return kInterpolated_position_mode.Interpolation_time_period_Ip_time_units;
}

uint32_t set_Interpolation_time_period_Ip_time_index(int8_t val)
{

    kInterpolated_position_mode.Interpolation_time_period_Ip_time_index = val;

//    set_app_Interp_time_index(val);

    return ABORT_CODE_SUCCESSFUL;
}

int8_t get_Interpolation_time_period_Ip_time_index(void)
{
    return kInterpolated_position_mode.Interpolation_time_period_Ip_time_index;
}

uint32_t set_Velocity_demand_value(int32_t val)
{

    kProfile_velocity_mode.Velocity_demand_value = val;

    return ABORT_CODE_SUCCESSFUL;
}

int32_t get_Velocity_demand_value(void)
{
    // RPM 转 P/s
//    kProfile_velocity_mode.Velocity_demand_value = get_app_Velocity_demand_value() * get_app_Load_rpm_2_pps();

    return kProfile_velocity_mode.Velocity_demand_value;
}

uint32_t set_Velocity_actual_value(int32_t val)
{

    kProfile_velocity_mode.Velocity_actual_value = val;

    return ABORT_CODE_SUCCESSFUL;
}
int32_t get_Velocity_actual_value(void)
{
    // P/s 转 RPM
//    kProfile_velocity_mode.Velocity_actual_value = get_app_Velocity_actual_value() * get_app_Load_rpm_2_pps();

    return kProfile_velocity_mode.Velocity_actual_value;
}

uint32_t set_Velocity_window(uint16_t val)
{
    // P/s转RPM
//    set_app_Velocity_window((float)val * get_app_Load_pps_2_rpm());

    kProfile_velocity_mode.Velocity_window = val;

    return ABORT_CODE_SUCCESSFUL;
}

uint16_t get_Velocity_window(void)
{

//    kProfile_velocity_mode.Velocity_window = get_app_Velocity_window() * get_app_Load_rpm_2_pps();

    return kProfile_velocity_mode.Velocity_window;
}

uint32_t set_Velocity_window_time(uint16_t val)
{

//    set_app_Velocity_window_time((float)val * 0.001f);

    kProfile_velocity_mode.Velocity_window_time = val;

    return ABORT_CODE_SUCCESSFUL;
}

uint16_t get_Velocity_window_time(void)
{

//    kProfile_velocity_mode.Velocity_window_time = get_app_Velocity_window_time() * 1000;

    return kProfile_velocity_mode.Velocity_window_time;
}

uint32_t set_Velocity_threshold(uint16_t val)
{
    // P/s转RPM
//    set_app_Velocity_threshold((float)val * get_app_Load_pps_2_rpm());

    kProfile_velocity_mode.Velocity_threshold = val;

    return ABORT_CODE_SUCCESSFUL;
}

uint16_t get_Velocity_threshold(void)
{

//    kProfile_velocity_mode.Velocity_threshold = get_app_Velocity_threshold() * get_app_Load_rpm_2_pps();

    return kProfile_velocity_mode.Velocity_threshold;
}

uint32_t set_Velocity_threshold_time(uint16_t val)
{

//    set_app_Velocity_threshold_time((float)val * 0.001f);

    kProfile_velocity_mode.Velocity_threshold_time = val;

    return ABORT_CODE_SUCCESSFUL;
}
uint16_t get_Velocity_threshold_time(void)
{

//    kProfile_velocity_mode.Velocity_threshold_time = get_app_Velocity_threshold_time() * 1000;

    return kProfile_velocity_mode.Velocity_threshold_time;
}

uint32_t set_Target_velocity(int32_t val)
{

    kProfile_velocity_mode.Target_velocity = val;
    // P/s 转 RPM
//    set_app_Target_velocity((float)val * get_app_Load_pps_2_rpm());

    return ABORT_CODE_SUCCESSFUL;
}

int32_t get_Target_velocity(void)
{
    // RPM 转 P/s
//    kProfile_velocity_mode.Target_velocity = get_app_Target_velocity() * get_app_Load_rpm_2_pps();

    return kProfile_velocity_mode.Target_velocity;
}

uint32_t set_Target_torque(int16_t val)
{
    kProfile_torque_mode.Target_torque = val;
    // 额定电流千分比转实际电流
//    set_app_Target_torque((float)val * get_app_Motor_rated_current() * MATH_ARMS2APEAK * 0.001f);

    return ABORT_CODE_SUCCESSFUL;
}

int16_t get_Target_torque(void)
{
//    kProfile_torque_mode.Target_torque = get_app_Target_torque()*1000/(get_app_Motor_rated_current()*MATH_ARMS2APEAK);

    return kProfile_torque_mode.Target_torque;
}

uint32_t set_Max_torque(uint16_t val)
{
    kProfile_torque_mode.Max_torque = val;
    // 额定电流千分比转实际电流
//    set_app_Max_current((float)val * get_app_Motor_rated_current() * MATH_ARMS2APEAK * 0.001f);

    return ABORT_CODE_SUCCESSFUL;
}
uint16_t get_Max_torque(void)
{

//    kProfile_torque_mode.Max_torque = get_app_Max_current() * 1000 / (get_app_Motor_rated_current() * MATH_ARMS2APEAK);

    return kProfile_torque_mode.Max_torque;
}

uint32_t set_Max_current(uint16_t val)
{
    kProfile_torque_mode.Max_current = val;

//    set_app_Max_current((float)val * get_app_Motor_rated_current() * MATH_ARMS2APEAK * 0.001f);

    return ABORT_CODE_SUCCESSFUL;
}

uint16_t get_Max_current(void)
{

//    kProfile_torque_mode.Max_current = get_app_Max_current() * 1000 / (get_app_Motor_rated_current() * MATH_ARMS2APEAK);

    return kProfile_torque_mode.Max_current;
}

uint32_t set_Torque_demand_value(int16_t val)
{

    kProfile_torque_mode.Torque_demand_value = val;

    return ABORT_CODE_SUCCESSFUL;
}

int16_t get_Torque_demand_value(void)
{

//    kProfile_torque_mode.Torque_demand_value = get_app_Torque_demand_value() * 1000 / (get_app_Motor_rated_current() * MATH_ARMS2APEAK);

    return kProfile_torque_mode.Torque_demand_value;
}

uint32_t set_Motor_rated_current(uint32_t val)
{

    kProfile_torque_mode.Motor_rated_current = val;

//    set_app_Motor_rated_current((float)val * 0.001f);

    return ABORT_CODE_SUCCESSFUL;
}

uint32_t get_Motor_rated_current(void)
{

//    kProfile_torque_mode.Motor_rated_current = get_app_Motor_rated_current() * 1000;

    return kProfile_torque_mode.Motor_rated_current;
}

uint32_t set_Motor_rated_torque(uint32_t val)
{

    kProfile_torque_mode.Motor_rated_torque = val;

    // mNm 转 Nm
//    set_app_Motor_rated_torque((float)val * 0.001f);

    return ABORT_CODE_SUCCESSFUL;
}

uint32_t get_Motor_rated_torque(void)
{

//    kProfile_torque_mode.Motor_rated_torque = get_app_Motor_rated_torque() * 1000;

    return kProfile_torque_mode.Motor_rated_torque;
}

uint32_t set_Torque_actual_value(int16_t val)
{
    kProfile_torque_mode.Torque_actual_value = val;

    return ABORT_CODE_SUCCESSFUL;
}

int16_t get_Torque_actual_value(void)
{
    // 实际力矩转为额定力矩千分比
//    kProfile_torque_mode.Torque_actual_value = get_app_Current_actual_value() * 1000 / (get_app_Motor_rated_current() * MATH_ARMS2APEAK);

    return kProfile_torque_mode.Torque_actual_value;
}

uint32_t set_Current_actual_value(int16_t val)
{

    kProfile_torque_mode.Current_actual_value = val;

    return ABORT_CODE_SUCCESSFUL;
}

int16_t get_Current_actual_value(void)
{

//    kProfile_torque_mode.Current_actual_value = get_app_Current_actual_value() * 1000 / (get_app_Motor_rated_current() * MATH_ARMS2APEAK);

    return kProfile_torque_mode.Current_actual_value;
}

uint32_t set_DC_link_circuit_voltage(uint32_t val)
{

    kProfile_torque_mode.DC_link_circuit_voltage = val;

    return ABORT_CODE_SUCCESSFUL;
}

uint32_t get_DC_link_circuit_voltage(void)
{

//    kProfile_torque_mode.DC_link_circuit_voltage = get_app_DC_link_circuit_voltage() * 1000;

    return kProfile_torque_mode.DC_link_circuit_voltage;
}

uint32_t set_Torque_slope(uint32_t val)
{
    kProfile_torque_mode.Torque_slope = val;
    // 千分比转电流
//    set_app_Torque_slope((float)val * get_app_Motor_rated_current() * MATH_ARMS2APEAK * 0.001f);

    return ABORT_CODE_SUCCESSFUL;
}

uint32_t get_Torque_slope(void)
{

//    kProfile_torque_mode.Torque_slope = get_app_Torque_slope() * 1000 / (get_app_Motor_rated_current() * MATH_ARMS2APEAK);

    return kProfile_torque_mode.Torque_slope;
}

uint32_t set_Position_offset(int32_t val)
{
    kCSP_CSV_CST.Position_offset = val;

    return ABORT_CODE_SUCCESSFUL;
}

int32_t get_Position_offset(void)
{
    return kCSP_CSV_CST.Position_offset;
}

uint32_t set_Velocity_offset(int32_t val)
{

    kCSP_CSV_CST.Velocity_offset = val;

    return ABORT_CODE_SUCCESSFUL;
}

int32_t get_Velocity_offset(void)
{
    return kCSP_CSV_CST.Velocity_offset;
}

uint32_t set_Torque_offset(int16_t val)
{

    kCSP_CSV_CST.Torque_offset = val;

    return ABORT_CODE_SUCCESSFUL;
}

int16_t get_Torque_offset(void)
{

    return kCSP_CSV_CST.Torque_offset;
}

uint32_t set_Digital_inputs(uint32_t val)
{
    kOptional_application.Digital_inputs = val;

    return ABORT_CODE_SUCCESSFUL;
}

uint32_t get_Digital_inputs(void)
{
//    kOptional_application.Digital_inputs = get_app_Digital_io_inputs_status();

    return kOptional_application.Digital_inputs;
}

uint32_t set_Digital_outputs(uint8_t val)
{
    kOptional_application.Digital_outputs = val;

    return ABORT_CODE_SUCCESSFUL;
}

uint8_t get_Digital_outputs(void)
{
    return kOptional_application.Digital_outputs;
}

uint32_t set_Digital_outputs_Physical_outputs(uint32_t val)
{
    kOptional_application.Digital_outputs_Physical_outputs = val;

//    set_app_Digital_io_outputs_phys(val);

    return ABORT_CODE_SUCCESSFUL;
}

uint32_t get_Digital_outputs_Physical_outputs(void)
{
    return kOptional_application.Digital_outputs_Physical_outputs;
}

uint32_t set_Digital_outputs_Bit_mask(uint32_t val)
{
    kOptional_application.Digital_outputs_Bit_mask = val;

//    set_app_Digital_io_outputs_mask(val);

    return ABORT_CODE_SUCCESSFUL;
}

uint32_t get_Digital_outputs_Bit_mask(void)
{
    return kOptional_application.Digital_outputs_Bit_mask;
}






