################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Servo_CiA402/subdir.mk
-include SSC/Src/subdir.mk
-include ProbeScope/subdir.mk
-include Motor_Control/subdir.mk
-include Motion_Control/subdir.mk
-include Libraries/XMCLib/src/subdir.mk
-include Libraries/Newlib/subdir.mk
-include Dave/Generated/TIMER/subdir.mk
-include Dave/Generated/PWM_CCU8/subdir.mk
-include Dave/Generated/INTERRUPT/subdir.mk
-include Dave/Generated/GLOBAL_CCU8/subdir.mk
-include Dave/Generated/GLOBAL_CCU4/subdir.mk
-include Dave/Generated/E_EEPROM_XMC4/subdir.mk
-include Dave/Generated/EVENT_GENERATOR/subdir.mk
-include Dave/Generated/EVENT_DETECTOR/subdir.mk
-include Dave/Generated/ECAT_SSC/subdir.mk
-include Dave/Generated/CPU_CTRL_XMC4/subdir.mk
-include Dave/Generated/CLOCK_XMC4/subdir.mk
-include Dave/Generated/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
DOCH_ECAT_XMC48_Servo_Probe_20261018.hex \

SECONDARY_LIST += \
DOCH_ECAT_XMC48_Servo_Probe_20261018.lst \

SECONDARY_SIZE += \
DOCH_ECAT_XMC48_Servo_Probe_20261018.siz \


LIST_FILES = $(addsuffix .o.lst, $(basename $(OBJS))) 
MAP_FILE = "DOCH_ECAT_XMC48_Servo_Probe_20261018.map"

TOOLCHAIN_ROOT=C:/Infineon/Tools/DAVE IDE/4.5.0.202105191637/eclipse/ARM-GCC-49
PROJECT_LOC=D:/AAA-Å¡½ô/03.MXC4800/DOCH_ECAT_XMC48_Servo_Probe_20261018

# All Target
all: DOCH_ECAT_XMC48_Servo_Probe_20261018.elf secondary-outputs

# Tool invocations
DOCH_ECAT_XMC48_Servo_Probe_20261018.elf: $(OBJS) ../linker_script.ld $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: ARM-GCC C Linker'
	$(file >objects.rsp,$(OBJS))
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-gcc" -T"../linker_script.ld" -nostartfiles -Xlinker --gc-sections -specs=nano.specs -specs=nosys.specs -Wl,-Map,$(MAP_FILE) -mfloat-abi=softfp -mfpu=fpv4-sp-d16 -mcpu=cortex-m4 -mthumb -o "DOCH_ECAT_XMC48_Servo_Probe_20261018.elf" "@objects.rsp" $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo.
DOCH_ECAT_XMC48_Servo_Probe_20261018.hex: DOCH_ECAT_XMC48_Servo_Probe_20261018.elf
	@echo 'Invoking: ARM-GCC Create Flash Image'
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-objcopy" -O ihex "DOCH_ECAT_XMC48_Servo_Probe_20261018.elf" "DOCH_ECAT_XMC48_Servo_Probe_20261018.hex"
	@echo 'Finished building: $@'
	@echo.
DOCH_ECAT_XMC48_Servo_Probe_20261018.lst: DOCH_ECAT_XMC48_Servo_Probe_20261018.elf
	@echo 'Invoking: ARM-GCC Create Listing'
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-objdump" -h -S "DOCH_ECAT_XMC48_Servo_Probe_20261018.elf" > "DOCH_ECAT_XMC48_Servo_Probe_20261018.lst"
	@echo 'Finished building: $@'
	@echo.
DOCH_ECAT_XMC48_Servo_Probe_20261018.siz: DOCH_ECAT_XMC48_Servo_Probe_20261018.elf
	@echo 'Invoking: ARM-GCC Print Size'
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-size" --format=berkeley "DOCH_ECAT_XMC48_Servo_Probe_20261018.elf"
	@echo 'Finished building: $@'
	@echo.
# Other Targets
clean:
	-$(RM) $(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE)$(ARM_GCC_FOR_XMC_LINKER_OUTPUT_TYPE_OUTPUTS)$(S_DEPS)$(S_UPPER_DEPS)$(C_DEPS)
	-$(RM) Dave/Generated/CLOCK_XMC4/clock_xmc4.o Dave/Generated/CLOCK_XMC4/clock_xmc4_conf.o Dave/Generated/CPU_CTRL_XMC4/cpu_ctrl_xmc4.o Dave/Generated/CPU_CTRL_XMC4/cpu_ctrl_xmc4_conf.o Dave/Generated/DAVE.o Dave/Generated/ECAT_SSC/ecat_ssc.o Dave/Generated/ECAT_SSC/ecat_ssc_conf.o Dave/Generated/ECAT_SSC/xmc_eschw.o Dave/Generated/EVENT_DETECTOR/event_detector.o Dave/Generated/EVENT_DETECTOR/event_detector_conf.o Dave/Generated/EVENT_GENERATOR/event_generator.o Dave/Generated/EVENT_GENERATOR/event_generator_conf.o Dave/Generated/E_EEPROM_XMC4/e_eeprom_xmc4.o Dave/Generated/E_EEPROM_XMC4/e_eeprom_xmc4_conf.o Dave/Generated/GLOBAL_CCU4/global_ccu4.o Dave/Generated/GLOBAL_CCU4/global_ccu4_conf.o Dave/Generated/GLOBAL_CCU8/global_ccu8.o Dave/Generated/GLOBAL_CCU8/global_ccu8_conf.o Dave/Generated/INTERRUPT/interrupt.o Dave/Generated/INTERRUPT/interrupt_conf.o Dave/Generated/PWM_CCU8/pwm_ccu8.o Dave/Generated/PWM_CCU8/pwm_ccu8_conf.o Dave/Generated/TIMER/timer.o Dave/Generated/TIMER/timer_conf.o Libraries/Newlib/syscalls.o Libraries/XMCLib/src/xmc4_eru.o Libraries/XMCLib/src/xmc4_flash.o Libraries/XMCLib/src/xmc4_gpio.o Libraries/XMCLib/src/xmc4_rtc.o Libraries/XMCLib/src/xmc4_scu.o Libraries/XMCLib/src/xmc_can.o Libraries/XMCLib/src/xmc_ccu4.o Libraries/XMCLib/src/xmc_ccu8.o Libraries/XMCLib/src/xmc_common.o Libraries/XMCLib/src/xmc_dac.o Libraries/XMCLib/src/xmc_dma.o Libraries/XMCLib/src/xmc_dsd.o Libraries/XMCLib/src/xmc_ebu.o Libraries/XMCLib/src/xmc_ecat.o Libraries/XMCLib/src/xmc_eru.o Libraries/XMCLib/src/xmc_eth_mac.o Libraries/XMCLib/src/xmc_eth_phy_dp83848.o Libraries/XMCLib/src/xmc_eth_phy_ksz8031rnl.o Libraries/XMCLib/src/xmc_eth_phy_ksz8081rnb.o Libraries/XMCLib/src/xmc_fce.o Libraries/XMCLib/src/xmc_gpio.o Libraries/XMCLib/src/xmc_hrpwm.o Libraries/XMCLib/src/xmc_i2c.o Libraries/XMCLib/src/xmc_i2s.o Libraries/XMCLib/src/xmc_ledts.o Libraries/XMCLib/src/xmc_posif.o Libraries/XMCLib/src/xmc_rtc.o 
	-$(RM) Libraries/XMCLib/src/xmc_sdmmc.o Libraries/XMCLib/src/xmc_spi.o Libraries/XMCLib/src/xmc_uart.o Libraries/XMCLib/src/xmc_usbd.o Libraries/XMCLib/src/xmc_usbh.o Libraries/XMCLib/src/xmc_usic.o Libraries/XMCLib/src/xmc_vadc.o Libraries/XMCLib/src/xmc_wdt.o Motion_Control/DOCH_cyclic_sync_position.o Motor_Control/DOCH_MotorCtrl_DataParam.o Motor_Control/DOCH_Motor_Ctrl_Sm.o Motor_Control/DOCH_PosLoopCtrl.o Motor_Control/DOCH_PositionCommand.o ProbeScope/probe_scope.o SSC/Src/QiaoTian_XMC_Servo.o SSC/Src/coeappl.o SSC/Src/ecatappl.o SSC/Src/ecatcoe.o SSC/Src/ecatslv.o SSC/Src/mailbox.o SSC/Src/objdef.o SSC/Src/sdoserv.o Servo_CiA402/DOCH_CiA_ErrorCode.o Servo_CiA402/DOCH_CiA_ObjectDictionary_Variable.o Servo_CiA402/DOCH_CiA_StateMachine.o Servo_CiA402/DOCH_CiA_StatusWord.o Startup/startup_XMC4800.o Startup/system_XMC4800.o main.o  DOCH_ECAT_XMC48_Servo_Probe_20261018.elf $(LIST_FILES) $(MAP_FILE) objects.rsp
	-@echo.
secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
