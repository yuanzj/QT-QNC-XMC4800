/*
 * DOCH_Motor_Ctrl_Sm.h
 *
 *  Created on: 2026年10月06日
 */
#ifndef _DOCH_MOTOR_CTRL_SM_H_
#define _DOCH_MOTOR_CTRL_SM_H_


#ifdef __cplusplus
extern "C" {
#endif




#define MOTOR_CTL_SM_PI (3.14159265358979323846f)     // PI
#define MOTOR_CTL_SM_TWO_PI (6.28318530717958647692f) // 2PI
#define MOTOR_CTL_SM_RPM_2_RAD_S (0.104719755119660f) //  RPM 转 角速度 rad/s
#define MOTOR_CTL_SM_RAD_S_2_RPM (9.549296585513721f) // 角速度 rad/s 转 RPM
#define MOTOR_CTL_SM_120_DEG_RAD (2.094395102393195f) // 120° 对应 弧度






#define MOTOR_CTL_SM_NONE_ERROR (0)             // 0：无错误
#define MOTOR_CTL_SM_UNDER_VOLTAGE_ERROR (1)    // 1：欠压保护错误
#define MOTOR_CTL_SM_OVER_VOLTAGE_ERROR (2)     // 2：过压保护错误
#define MOTOR_CTL_SM_OVER_SPEED_ERROR (3)       // 3：过速保护错误
#define MOTOR_CTL_SM_UNDER_TEMP_ERROR (4)       // 4：低温保护错误
#define MOTOR_CTL_SM_OVER_TEMP_ERROR (5)        // 5：高温保护错误
#define MOTOR_CTL_SM_POS_FELLOW_ERROR (6)       // 6：位置跟随误差过大保护错误
#define MOTOR_CTL_SM_OVER_CURRENT_MAX_ERROR (7) // 7：过流保护
#define MOTOR_CTL_SM_NFAULT_ERROR (8)           // 8：nFault 底层相关故障错误




#define MOTOR_CTL_SM_MODE_IDLE (0)                           // 0：空闲模式
#define MOTOR_CTL_SM_MODE_TORQUE (1)                         // 1：力矩模式
#define MOTOR_CTL_SM_MODE_SPEED (2)                          // 2：速度模式
#define MOTOR_CTL_SM_MODE_POSITION (3)                       // 3：位置模式
#define MOTOR_CTL_SM_MODE_RECIPROCAL_MOTION (4)              // 4：往复运动模式
#define MOTOR_CTL_SM_MODE_REFERENCE_SIGNAL (5)               // 5：参考信号
#define MOTOR_CTL_SM_MODE_MIT (6)                            // 6：MIT模式
#define MOTOR_CTL_SM_MODE_HOMING (7)                         // 7：回零模式
#define MOTOR_CTL_SM_MODE_CSP (8)                            // 8：同步位置模式
#define MOTOR_CTL_SM_MODE_CSV (9)                            // 9：同步速度模式
#define MOTOR_CTL_SM_MODE_CST (10)                           // 10：同步时间模式
#define MOTOR_CTL_SM_MODE_VOLTAGE (127)                      // 127：电压直接控制模式



#define MOTOR_CTL_SM_STATE_ERROR   (-1) // -1：错误状态
#define MOTOR_CTL_SM_STATE_DISABLE ( 0) // 0：失能电机状态
#define MOTOR_CTL_SM_STATE_ENABLE  ( 1) // 1：使能电机状态


#define MOTOR_CTL_SM_MOTOR_DISABLE         (0)  // 0：失能电机
#define MOTOR_CTL_SM_MOTOR_ENABLE          (1)  // 1：使能电机   0->1 上升沿使能电机
#define MOTOR_CTL_SM_MOTOR_EMERGENCY_BRAKE (2)  // 2：紧急停车
#define MOTOR_CTL_SM_MOTOR_CLEAR_ERROR     (3)  // 3：清除错误  0->3 上升沿清除错误




#define IDENTIFICATION_MODE_STATE_ERROR            (-1) // -1：辨识错误
#define IDENTIFICATION_MODE_STATE_IDLE             ( 0) // 0：空闲状态
#define IDENTIFICATION_MODE_STATE_SEARCH           ( 1) // 1：搜索阶段
#define IDENTIFICATION_MODE_STATE_STABLE_INCENTIVE ( 2) // 2：稳定激励状态
#define IDENTIFICATION_MODE_STATE_FINISH           ( 3) // 3：辨识完成状态

#define REFERENCE_SIGNAL_TARGET_D_CURRENT   (0)   // d轴电流
#define REFERENCE_SIGNAL_TARGET_Q_CURRENT   (1)   // q轴电流
#define REFERENCE_SIGNAL_TARGET_SPEED       (2)   // 速度
#define REFERENCE_SIGNAL_TARGET_POSITION    (3)   // 位置
#define REFERENCE_SIGNAL_VF_MODE            (254) // VF模式
#define REFERENCE_SIGNAL_IF_MODE            (255) // IF模式





#define POS_SPEED_CTL_MODE_SPEED    (0.0f)  //纯速度控制模式
#define POS_SPEED_CTL_MODE_POSITION (1.0f)  //位置控制模式



#define TQ_FC_COM_MIN_SPEED_RAD_S   (1.0f)  //转矩脉动、摩擦辨识的转速 rad/s












#ifdef __cplusplus
}
#endif // extern "C"

#endif // end of _DOCH_MOTOR_CTRL_SM_H_
