/*
 * DOCH_CiA_ErrorCode.h.c
 *
 *  Created on: 2026年10月09日
 */
/* Includes ---引用头文件----------------------------------------------------*/

#include "DOCH_CiA_ErrorCode.h"
#include "DOCH_CiA_ObjectDictionary_Variable.h"



// 失能自由停机
void FreeToRotate_ErrorHandle(void)
{

}


// 中断运行时，检查错误代码--更新Cia402对象字典故障码0x603F
void CiA402_ErrorCodeScan(void)
{
//    CheckErrorCode_t Check_Error_Val = (CheckErrorCode_t)app_get_check_error_val();
    CheckErrorCode_t Check_Error_Val;
    Check_Error_Val.all = 0;
    // 无错误不检查
    if (Check_Error_Val.all)
    {
    	 // 按照错误优先级顺序检查每个错误位
    	        if (Check_Error_Val.Bits.drive_overload)
    	        {
    	            set_Error_code(Load_error_error);
    	            return;
    	        }
    	        if (Check_Error_Val.Bits.drive_peak_current_overload)
    	        {
    	            set_Error_code(Driver_peak_current_overload_error);
    	            return;
    	        }
    	        if (Check_Error_Val.Bits.drive_over_current_error)
    	        {
    	            set_Error_code(Continuous_over_current_output_No_2_error);
    	            return;
    	        }
    	        if (Check_Error_Val.Bits.dc_bus_over_voltage)
    	        {
    	            set_Error_code(DC_link_over_voltage_error);
    	            return;
    	        }
    	        if (Check_Error_Val.Bits.dc_bus_under_voltage)
    	        {
    	            set_Error_code(DC_link_under_voltage_error);
    	            return;
    	        }
    	        if (Check_Error_Val.Bits.over_temperature_drive)
    	        {
    	            set_Error_code(Excess_temperature_device_error);
    	            return;
    	        }
    	        if (Check_Error_Val.Bits.under_temperature_drive)
    	        {
    	            set_Error_code(Too_low_temperature_device_error);
    	            return;
    	        }
    	        if (Check_Error_Val.Bits.over_temperature_motor)
    	        {
    	            set_Error_code(Motor_blocked_error);
    	            return;
    	        }
    	        if (Check_Error_Val.Bits.under_temperature_motor)
    	        {
    	            set_Error_code(Under_temperature_motor_error);
    	            return;
    	        }
    	        if (Check_Error_Val.Bits.over_temperature_mcu)
    	        {
    	            set_Error_code(Excess_temperature_drive_error);
    	            return;
    	        }
    	        if (Check_Error_Val.Bits.under_temperature_mcu)
    	        {
    	            set_Error_code(Too_low_temperature_drive_error);
    	            return;
    	        }
    	        if (Check_Error_Val.Bits.over_speed)
    	        {
    	            set_Error_code(Velocity_speed_controller_error);
    	            return;
    	        }
    	        if (Check_Error_Val.Bits.position_following_error)
    	        {
    	            set_Error_code(Following_error_error);
    	            return;
    	        }
    	        if (Check_Error_Val.Bits.motor_encoder_error)
    	        {
    	            set_Error_code(Incremental_sensor_1_fault_error);
    	            return;
    	        }
    	        if (Check_Error_Val.Bits.load_encoder_error)
    	        {
    	            set_Error_code(Incremental_sensor_2_fault_error);
    	            return;
    	        }
    	        if (Check_Error_Val.Bits.flash_store_error)
    	        {
    	            set_Error_code(Non_volatile_data_memory_error);
    	            return;
    	        }
    	        if (Check_Error_Val.Bits.nfault_error)
    	        {
    	            set_Error_code(Drv_nfault_error);
    	            return;
    	        }
    	        if (Check_Error_Val.Bits.drv_init_error)
    	        {
    	            set_Error_code(Drv_init_error);
    	            return;
    	        }
    	        if (Check_Error_Val.Bits.current_sample_error)
    	        {
    	            set_Error_code(Current_sample_error);
    	            return;
    	        }
    	        if (Check_Error_Val.Bits.drive_bus_voltage_error)
    	        {
    	            set_Error_code(Drive_bus_voltage_error);
    	            return;
    	        }
    	        if (Check_Error_Val.Bits.can_bus_disconnection_error)
    	        {
    	            set_Error_code(Can_bus_disconnection_error);
    	            return;
    	        }
    	        if (Check_Error_Val.Bits.external_inhibit_input_detected)
    	        {
    	            set_Error_code(External_inhibit_input_detected_error);
    	            return;
    	        }
    }
    else
    {
        set_Error_code(0);
    }
}








