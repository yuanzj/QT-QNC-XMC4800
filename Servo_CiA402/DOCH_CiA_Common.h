/*
 * DOCH_CiA_Common.h
 *
 *  Created on: 2026年10月09日
 */
#ifndef _DOCH_CIA_COMMON_H_
#define _DOCH_CIA_COMMON_H_


#ifdef __cplusplus
extern "C" {
#endif



/*-----------------------------------------------------------------------------------------
------    Includes
-----------------------------------------------------------------------------------------*/
#include <DAVE.h>



// 总线运行模式
#define OD6060_ANY      (-2)          //任何模式(仅用于状态字检测,无实际意义)
#define OD6060_NULL     (-1)          //无效模式
#define OD6060_NO_MODE  (0)           //空模式
#define OD6060_PPM      (1)           //轮廓位置
#define OD6060_VLM      (2)          //用作速度模式
#define OD6060_PVM      (3)           //轮廓速度  相当于位置速度模式
#define OD6060_PTM      (4)           //轮廓力矩
#define OD6060_RESERVED (5)           //保留的模式
#define OD6060_HM       (6)           //回零模式（非总线运行模式）
#define OD6060_IPM      (7)           //插值模式
#define OD6060_CSP      (8)           //周期同步位置
#define OD6060_CSV      (9)           //周期同步速度
#define OD6060_CST      (10)          //周期同步力矩
#define OD6060_MIT      (11)          //MIT模式



typedef enum
{
    EMERGENCY_BRAKE_MODE_DISABLED = 0,           // Disable emergency stop
    EMERGENCY_BRAKE_MODE_SLOW_DOWN_RAMP,         // Slow down the ramp
    EMERGENCY_BRAKE_MODE_QUICK_STOP_RAMP,        // Quick stop the ramp
    EMERGENCY_BRAKE_MODE_CURRENT_LIMIT,          // Limit the current
    EMERGENCY_BRAKE_MODE_VOLTAGE_LIMIT,          // Limit the voltage
    EMERGENCY_BRAKE_MODE_SLOW_DOWN_RAMP_ENABLE,  // Enable after slow down ramp
    EMERGENCY_BRAKE_MODE_QUICK_STOP_RAMP_ENABLE, // Enable after quick stop ramp
    EMERGENCY_BRAKE_MODE_CURRENT_LIMIT_ENABLE,   // Enable after current limit
    EMERGENCY_BRAKE_MODE_VOLTAGE_LIMIT_ENABLE,   // Enable after voltage limit
} APP_Emergency_Brake_Mode;




#define CIA402_SET_BIT(x, y)     (x) |= (y)          //将x的y位设置为1，示例：CIA402_SET_BIT(x, 0x10)将x的第4位置为1
#define CIA402_CLEAR_BIT(x, y)   (x) &= ~(y)         //将x的y位置置为0，示例：CIA402_CLEAR_BIT(x, 0x80)将x的第7位置为0
#define CIA402_READ_BIT(x, y)    ((x) & (y))
#define CIA402_ABS(x)            (((x) > 0) ? (x) : -(x))

#define CIA402_ARRAY_SIZE(array) (sizeof(array) / sizeof((array)[0]))
#define CIA402_PI                (3.14159265358979323846f)









#ifdef __cplusplus
}
#endif // extern "C"

#endif // end of _DOCH_CIA_COMMON_H_
