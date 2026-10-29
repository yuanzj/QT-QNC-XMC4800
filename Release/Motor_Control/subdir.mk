################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Motor_Control/DOCH_MotorCtrl_DataParam.c \
../Motor_Control/DOCH_Motor_Ctrl_Sm.c \
../Motor_Control/DOCH_PosLoopCtrl.c \
../Motor_Control/DOCH_PositionCommand.c 

OBJS += \
./Motor_Control/DOCH_MotorCtrl_DataParam.o \
./Motor_Control/DOCH_Motor_Ctrl_Sm.o \
./Motor_Control/DOCH_PosLoopCtrl.o \
./Motor_Control/DOCH_PositionCommand.o 

C_DEPS += \
./Motor_Control/DOCH_MotorCtrl_DataParam.d \
./Motor_Control/DOCH_Motor_Ctrl_Sm.d \
./Motor_Control/DOCH_PosLoopCtrl.d \
./Motor_Control/DOCH_PositionCommand.d 


# Each subdirectory must supply rules for building sources it contributes
Motor_Control/%.o: ../Motor_Control/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM-GCC C Compiler'
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-gcc" -MMD -MT "$@" -DXMC4800_F144x2048 -I"$(PROJECT_LOC)/Libraries/XMCLib/inc" -I"${workspace_loc:/DOCH_ECAT_XMC48_Servo_Probe_20261018/Servo_CiA402" -I"$(PROJECT_LOC)/Libraries/CMSIS/Include" -I"$(PROJECT_LOC)/Libraries/CMSIS/Infineon/XMC4800_series/Include" -I"$(PROJECT_LOC)" -I"$(PROJECT_LOC)/Dave/Generated" -I"$(PROJECT_LOC)/Libraries" -Os -ffunction-sections -fdata-sections -Wall -std=gnu99 -mfloat-abi=softfp -Wa,-adhlns="$@.lst" -pipe -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d) $@" -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mthumb -o "$@" "$<" 
	@echo 'Finished building: $<'
	@echo.

