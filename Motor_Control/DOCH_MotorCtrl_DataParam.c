/*
 * DOCH_MotorCtrl_DataParam.c
 *
 *  Created on: 2026年10月06日
 */
/* Includes ---引用头文件----------------------------------------------------*/
#include "DOCH_MotorCtrl_DataParam.h"
#include "DOCH_Motor_Ctrl_Sm.h"


uint16_t ECAT_Servo_On = 0;


AppControlWord kAppControlWord;
AppMotionInfo  kAppMotionInfo;

void set_app_Controlword(uint16_t val)
{
	switch(val)
	{
		case MOTOR_CTL_SM_MOTOR_DISABLE:
			ECAT_Servo_On = 0;
			break;
		case MOTOR_CTL_SM_MOTOR_ENABLE:
			ECAT_Servo_On = 1;
			break;
		case MOTOR_CTL_SM_MOTOR_EMERGENCY_BRAKE:// 强制进入紧急停车（QuickStop）状态

			break;
		case MOTOR_CTL_SM_MOTOR_CLEAR_ERROR://清除应用层错误

			break;
		default:

			break;
	}

}



void set_app_Halt_running_cmd(uint8_t val)
{

    kAppControlWord.Halt_running_cmd = val;

}


uint8_t get_app_Emergency_brake_requested(void)
{
    return kAppMotionInfo.Emergency_brake_requested;
}


void set_app_start_upedge_state(bool state)
{
	kAppControlWord.Start_Upedge_state = state;
}






