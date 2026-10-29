/*
 * DOCH_CiA_StateMachine.h
 * CiA Draft Standard Proposal 402,Drives and motion control device profile, Part 2: Operation modes and application data
 *  Created on: 2026年10月18日
 */
#ifndef _DOCH_CIA_STATEMACHINE_H_
#define _DOCH_CIA_STATEMACHINE_H_


#ifdef __cplusplus
extern "C" {
#endif




/*-----------------------------------------------------------------------------------------
------    Includes
-----------------------------------------------------------------------------------------*/
#include <DOCH_CiA_Common.h>






typedef enum
{
    kStart = 0,
    kNotReadyToSwitchOn,
    kSwitchOnDisable,
    kReadyToSwitchOn,
    kSwitchOn,
    kOperationEnable,
    kQuickStopActive,
    kFaultReactionActive,
    kFault,
    kAnyState
}Cia402State;


//Chapter 8, Table 27 - Command Coding
typedef enum
{
    OD6040_StandardMark = 143,

    OD6040_ShutdownMark = 135,
    OD6040_Shutdown = 6,                   //Transitions 2,6,8

    OD6040_SwitchOn = 7,                   //Transitions 3

    OD6040_SwitchOn_EnableOperation = 15,  //Transitions 3,4（note:Automatic transition to Enable operation state after executing SWITCHED ON state functionality）

    OD6040_DisableVoltageMark = 130,
    OD6040_DisableVoltage = 0,             //Transitions 7,9,10,12

    OD6040_QuickStopMark = 134,
    OD6040_QuickStop = 2,                  //Transitions 7,10,11

    OD6040_DisableOperation = 7,           //Transitions 5

    OD6040_EnableOperation = 15,           //Transitions 4，16

    OD6040_FaultReset = 128,               //Transitions 15

    OD6040_Halt = 256,                 //Bit 8   暂停使能位
    OD6040_NewSetPoint = 16,           //Bit 4
    OD6040_HomingOperationStart = 16,  //Bit 4
    OD6040_EnableInterpolation = 16,   //Bit 4
    OD6040_ChangeSetImmediately = 32,  //Bit 5
    OD6040_Relative = 64,              //使能相对位置  //Bit 6
}CiA_OD6040;


typedef bool (*EventFunction)(void);
typedef void (*ActionFunction)(void);

typedef struct
{
    Cia402State CurrentState;
    Cia402State NextState;
    bool Auto_transition;   //自动转换标志，true表示自动转换，false表示控制字跳转
    EventFunction event;
    ActionFunction action;
}FSATransition;

void PDS_FSA_Run(void);
void ControlwordChange_PDAS_FSA(void);
Cia402State Get_CurrentState(void);

extern void StateMachine_CiA402_Run(void);






#ifdef __cplusplus
}
#endif // extern "C"

#endif // end of _DOCH_CIA_STATEMACHINE_H_
