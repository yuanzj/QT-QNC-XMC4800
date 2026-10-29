/*
 * DOCH_CiA_StatusWord.c
 *
 *  Created on: 2026年10月11日
 */
/* Includes ---引用头文件----------------------------------------------------*/
#include "DOCH_CiA_ErrorCode.h"
#include "DOCH_CiA_ObjectDictionary_Variable.h"
#include "DOCH_CiA_StateMachine.h"
#include "DOCH_CiA_StatusWord.h"
//#include "DOCH_DataType_define.h"



static CheckErrorCode_t CheckServoErrVal;
static CheckStatusVal_t MotionStatusVal;

static bool Check_Voltage_State(void)
{
    return true;  //获取底层电压的状态
}

static bool Check_Target_Position_Reached_State(void)
{
    //控制字非暂停，由各个应用更新目标到达状态
    if (CIA402_READ_BIT(get_Controlword(), OD6040_Halt) == 0)
    {
    	MotionStatusVal.Bits.position_target_reached = 1;
        return MotionStatusVal.Bits.position_target_reached;
    }
    return MotionStatusVal.Bits.target_reached;
}

static bool Check_Velocity_Reached_State(void)
{
    //控制字非暂停，由各个应用更新目标到达状态
    if (CIA402_READ_BIT(get_Controlword(), OD6040_Halt) == 0)
    {
        return MotionStatusVal.Bits.velocity_target_reached;
    }
    return MotionStatusVal.Bits.target_reached;
}

static bool Check_SetPoint_Acknowledge_State(void)
{
    //控制字暂停，bit12置false
    if (CIA402_READ_BIT(get_Controlword(), OD6040_Halt) == OD6040_Halt)
    {
        return false;
    }
    else if (CIA402_READ_BIT(get_Controlword(), OD6040_NewSetPoint) == OD6040_NewSetPoint)
    {
        return true;
    }
    return false;
}

static bool Check_Position_Following_Error_State(void)
{
	CheckServoErrVal.Bits.position_following_error = 0;//Following error 跟随误差---0：跟随误差在窗口内，跟踪正常

    return CheckServoErrVal.Bits.position_following_error;
}

static bool Check_Velocity_Zero_State(void)
{
    return MotionStatusVal.Bits.velocity_zero;
}

static bool Check_Homing_Attained_State(void)
{
    return MotionStatusVal.Bits.homing_attained;
}

static bool Check_Drive_Follow_Command_Value_State(void)
{

    // 非使能或暂停状态下，置false
    if (Get_CurrentState() != kOperationEnable || CIA402_READ_BIT(get_Controlword(), OD6040_Halt) == OD6040_Halt)
    {
        return false;
    }
    return true;
}

// 定义状态表,OD6060_ANY表示任何模式下均检测
static const StateTableEntry Motion_StateTable[] =
{
    {OD6060_ANY, OD6041_VoltageEnabled, Check_Voltage_State},
    {OD6060_PPM, OD6041_TargetReached,  Check_Target_Position_Reached_State},
    {OD6060_PPM, OD6041_FollowingError, Check_Position_Following_Error_State},
    {OD6060_PPM, OD6041_SetPointAcknowledge, Check_SetPoint_Acknowledge_State},
    {OD6060_PVM, OD6041_TargetReached,  Check_Velocity_Reached_State},
    {OD6060_PVM, OD6041_SpeedRunning,   Check_Velocity_Zero_State},
    {OD6060_CSP, OD6041_FollowingError, Check_Position_Following_Error_State},           //Bit13--跟随误差超限--0:No following error,1:Following error
    {OD6060_CSP, OD6041_DriveFollowCommandValue, Check_Drive_Follow_Command_Value_State},//Bit12--设定点应答--1:Target position shall be used as input to position control loop
    {OD6060_CSV, OD6041_DriveFollowCommandValue, Check_Drive_Follow_Command_Value_State},
    {OD6060_CST, OD6041_DriveFollowCommandValue, Check_Drive_Follow_Command_Value_State},
    {OD6060_HM,  OD6041_HomingAttained, Check_Homing_Attained_State}
};

//内部信号更新状态字
void UpdateStatusword(void)
{

    uint16_t statusword = get_Statusword();

    CIA402_SET_BIT(statusword, OD6041_Remote);

    const StateTableEntry *entry = Motion_StateTable;

//    MotionStatusVal = (CheckStatusVal_t)app_get_check_status_val();//测试阶段位置到达等标志位直接赋值，暂不通过控制层读取
//    CheckServoErrVal = (CheckErrorCode_t)app_get_check_error_val();

    for (uint8_t i = 0; i < CIA402_ARRAY_SIZE(Motion_StateTable); i++, entry++)
    {
        if ((entry->Op_Mode == get_Modes_of_operation()) || (entry->Op_Mode == OD6060_ANY))
        {
            if (entry->check_state())
            {
                CIA402_SET_BIT(statusword, entry->Bit_mask);
            }
            else
            {
                CIA402_CLEAR_BIT(statusword, entry->Bit_mask);
            }
        }
    }
    set_Statusword(statusword);
}

void SpecificModeStatuswordUpdate(OD6041Mask status_bit, bool state)
{
    uint16_t statusword = get_Statusword();
    if(state)
    {
        CIA402_SET_BIT(statusword, status_bit);
    }
    else
    {
        CIA402_CLEAR_BIT(statusword, status_bit);
    }
    set_Statusword(statusword);
}

bool Get_Velocity_Zero_State(void)
{
    return MotionStatusVal.Bits.velocity_zero;
}


