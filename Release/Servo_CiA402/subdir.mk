################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Servo_CiA402/DOCH_CiA_ErrorCode.c \
../Servo_CiA402/DOCH_CiA_ObjectDictionary_Variable.c \
../Servo_CiA402/DOCH_CiA_StateMachine.c \
../Servo_CiA402/DOCH_CiA_StatusWord.c 

OBJS += \
./Servo_CiA402/DOCH_CiA_ErrorCode.o \
./Servo_CiA402/DOCH_CiA_ObjectDictionary_Variable.o \
./Servo_CiA402/DOCH_CiA_StateMachine.o \
./Servo_CiA402/DOCH_CiA_StatusWord.o 

C_DEPS += \
./Servo_CiA402/DOCH_CiA_ErrorCode.d \
./Servo_CiA402/DOCH_CiA_ObjectDictionary_Variable.d \
./Servo_CiA402/DOCH_CiA_StateMachine.d \
./Servo_CiA402/DOCH_CiA_StatusWord.d 


# Each subdirectory must supply rules for building sources it contributes
Servo_CiA402/%.o: ../Servo_CiA402/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM-GCC C Compiler'
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-gcc" -MMD -MT "$@" -DXMC4800_F144x2048 -I"$(PROJECT_LOC)/Libraries/XMCLib/inc" -I"${workspace_loc:/DOCH_ECAT_XMC48_Servo_Probe_20261018/Servo_CiA402" -I"$(PROJECT_LOC)/Libraries/CMSIS/Include" -I"$(PROJECT_LOC)/Libraries/CMSIS/Infineon/XMC4800_series/Include" -I"$(PROJECT_LOC)" -I"$(PROJECT_LOC)/Dave/Generated" -I"$(PROJECT_LOC)/Libraries" -Os -ffunction-sections -fdata-sections -Wall -std=gnu99 -mfloat-abi=softfp -Wa,-adhlns="$@.lst" -pipe -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d) $@" -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mthumb -o "$@" "$<" 
	@echo 'Finished building: $<'
	@echo.

