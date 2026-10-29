################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ProbeScope/probe_scope.c 

OBJS += \
./ProbeScope/probe_scope.o 

C_DEPS += \
./ProbeScope/probe_scope.d 


# Each subdirectory must supply rules for building sources it contributes
ProbeScope/%.o: ../ProbeScope/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM-GCC C Compiler'
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-gcc" -MMD -MT "$@" -DXMC4800_F144x2048 -I"$(PROJECT_LOC)/Libraries/XMCLib/inc" -I"${workspace_loc:/DOCH_ECAT_XMC48_Servo_Probe_20261018/Servo_CiA402" -I"$(PROJECT_LOC)/Libraries/CMSIS/Include" -I"$(PROJECT_LOC)/Libraries/CMSIS/Infineon/XMC4800_series/Include" -I"$(PROJECT_LOC)" -I"$(PROJECT_LOC)/Dave/Generated" -I"$(PROJECT_LOC)/Libraries" -Os -ffunction-sections -fdata-sections -Wall -std=gnu99 -mfloat-abi=softfp -Wa,-adhlns="$@.lst" -pipe -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d) $@" -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mthumb -o "$@" "$<" 
	@echo 'Finished building: $<'
	@echo.

