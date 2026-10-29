/*
 * DOCH_CiA_StatusWord.h
 *
 *  Created on: 2026年10月11日
 */
#ifndef _DOCH_CIA_STATUSWORD_H_
#define _DOCH_CIA_STATUSWORD_H_


#ifdef __cplusplus
extern "C" {
#endif




/*-----------------------------------------------------------------------------------------
------    Includes
-----------------------------------------------------------------------------------------*/
#include <DOCH_CiA_Common.h>



typedef enum
{
    OD6041_StateMark           = 0x006F,  //状态相关掩码
    OD6041_Start               = 0x006F,  /* Default value */
    OD6041_NotReadyToSwitchOn  = 0x0000,
    OD6041_SwitchedOnDisable   = 0x0040,
    OD6041_ReadyToSwitchOn     = 0x0021,
    OD6041_SwitchedOn          = 0x0023,
    OD6041_OperationEnable     = 0x0027,
    OD6041_QuickStopActive     = 0x0007, //修正该值
    OD6041_FaultReactionActive = 0x000F,
    OD6041_Fault               = 0x0008,
    OD6041_StateSwitch         = 0x0100,
    OD6041_VoltageEnabled      = 0x0010,
    OD6041_Warning             = 0x0080,
    OD6041_Remote              = 0x0200,
    OD6041_TargetReached       = 0x0400,//Bit10
    OD6041_InternalLimitActive = 0x0800,

    /// 表示具体模式下 运行状态
    OD6041_OperationModeMark   = 0x3000,  //模式操作掩码--Bit12,Bit13
    OD6041_SetPointAcknowledge = 0x1000,  //Bit12
    OD6041_FollowingError      = 0x2000,  //Bit13
    OD6041_SpeedRunning        = 0x1000,
    OD6041_MaxSlippageError    = 0x2000,
    OD6041_HomingAttained      = 0x1000, //Bit12
    OD6041_HomingError         = 0x2000,
    OD6041_IpModeActive        = 0x1000,
    OD6041_DriveFollowCommandValue = 0x1000, //Bit12 CSP、PP、CSV、CST

    //系统辨识掩码 kOd6041_IDENT_ERROR
    OD6041_IdentStateMark      = 0xC000,   //Bit15,Bit16
    //辨识空闲状态
    OD6041_IdentIdle = 0,
    //辨识成功
    OD6041_IdentSuccess = 1,
    //辨识运行中
    OD6041_IdentRunning = 2,
    //辨识错误 具体原因查询错误代码
    OD6041_IdentError = 3,
}OD6041Mask;

typedef struct
{
    int8_t Op_Mode;        // 运行模式
    uint16_t Bit_mask;         // 对应的位掩码
    bool (*check_state)(void); // 检查状态的函数指针
} StateTableEntry;


typedef union
{
    uint32_t all;
    struct
    {
        uint32_t target_reached : 1;                // 目标到达
        uint32_t velocity_zero : 1;                 // 零速到达
        uint32_t homing_attained : 1;               // 回零完成
        uint32_t position_target_reached : 1;       // 位置到达
        uint32_t velocity_target_reached : 1;       // 速度到达
        uint32_t target_torque_reached : 1;         // 力矩到达
        uint32_t motor_enable_state : 1;            // 电机使能状态
        uint32_t encoder_zero_crossing_state : 1;   // 编码器过零点状态

        uint32_t reserved : 24;
    } Bits; // 位字段
} CheckStatusVal_t;




void UpdateStatusword(void);

//允许特殊情况下,在其它应用代码更新状态字
void SpecificModeStatuswordUpdate(OD6041Mask status_bit, bool state);

bool Get_Velocity_Zero_State(void);











#ifdef __cplusplus
}
#endif // extern "C"

#endif // end of _DOCH_CIA_STATUSWORD_H_

