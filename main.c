/*
 * Copyright (C) 2015 Infineon Technologies AG. All rights reserved.
 *
 * Infineon Technologies AG (Infineon) is supplying this software for use with
 * Infineon's microcontrollers.
 * This file can be freely distributed within development tools that are
 * supporting such microcontrollers.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS". NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * INFINEON SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 * OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 * ATTENTION:
 * This example demonstrates the ethercat peripheral of XMC 4800. For this purpose an
 * ethercat slave node implemented inside a library is included into this project.
 * This library is for demonstration purpose within this example only and is
 * not certified, not safe and not meant to be used in any other context than here.
 *
 */


/**
 * @file
 * @date 05 Feb, 2024
 * @version 4.0.0
 *
 * @brief XMC4800 Relax Kit EtherCat demo example
 *
 * This example initializes an ethercat slave node and makes only sense to be evaluated with a ethercat host.
 * The ethercat slave implements 8x1bit and 4x16bit on input-side and
 * 8x1bit and 4x16bit on output-side.
 *
 * Button1 (P15.13) and Button2 (P15.12) on your XMC4800 Relax EtherCAT Kit can be used to control of 2x1bit
 * master input (IN_GENERIC->IN_GEN_Bit1/2).
 *
 * On master output side 8x1bit (OUT_GENERIC->OUT_GEN_Bit1-8) are used to control the state of 8 LEDs on your
 * XMC4800 Relax EtherCAT Kit. Furthermore a 16bit integer (OUT_GENERIC->OUT_GEN_INT1) is used to dimm LED2 on
 * your base board via PWM.
 *
 * Version 1.0.0 Initial (SSC 5.11, no ECAT APP used, no distributed clocks used)<br>
 * Version 2.1.0 Added EtherCAT APP <br>
 * Version 2.2.0 Added disctributed clock support <br>
 * Version 3.0.0 Upgraded example for SSC 5.12 <br>
 * Version 3.1.0 Upgraded example with latest ECAT_SSC APP. Fixes EEPROM emulation bug <br>
 * Version 3.2.0 Upgraded example with latest ECAT_SSC APP. New feature to disable ECAT OUT-port <br>
 * Version 4.0.0 Upgraded example for SSC 5.13 <br>
 *
 */

#include <DAVE.h>               //Declarations from DAVE Code Generation (includes SFR declaration)
#include <DOCH_CiA_StateMachine.h>
#include "SSC/Src/QiaoTian_XMC_ServoObjects.h"

//#include "probe_scope_cfg.h"
//#include "probe_scope.h"

#include "ProbeScope/probe_scope_cfg.h"
#include "ProbeScope/probe_scope.h"

#define P_LED1 P1_14
#define P_LED2 P0_14
#define P_LED3 P3_14
#define P_LED4 P0_15
#define P_LED5 P1_2
#define P_LED6 P3_13
#define P_LED7 P5_3
#define P_LED8 P3_11

#define MAP2LEVEL(x) ((x==0)?XMC_GPIO_OUTPUT_LEVEL_HIGH:XMC_GPIO_OUTPUT_LEVEL_LOW)

void Init_ECAT_Adapt_LED ()
{
  /* Set mode of all LED ports to push-pull and output level to low*/
  XMC_GPIO_SetMode(P_LED1, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);
  XMC_GPIO_SetOutputHigh(P_LED1);
  XMC_GPIO_SetMode(P_LED2, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);
  XMC_GPIO_SetOutputHigh(P_LED2);
  XMC_GPIO_SetMode(P_LED3, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);
  XMC_GPIO_SetOutputHigh(P_LED3);
  XMC_GPIO_SetMode(P_LED4, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);
  XMC_GPIO_SetOutputHigh(P_LED4);
  XMC_GPIO_SetMode(P_LED5, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);
  XMC_GPIO_SetOutputHigh(P_LED5);
  XMC_GPIO_SetMode(P_LED6, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);
  XMC_GPIO_SetOutputHigh(P_LED6);
  XMC_GPIO_SetMode(P_LED7, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);
  XMC_GPIO_SetOutputHigh(P_LED7);
  XMC_GPIO_SetMode(P_LED8, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);
  XMC_GPIO_SetOutputHigh(P_LED8);
}

void Init_Relax_Button ()
{
  /* INITIALIZE BUTTON1 ON PORT 5.13 FOR INPUT */
  /* Set mode to input tristate */
  XMC_GPIO_SetMode(P15_13, XMC_GPIO_MODE_INPUT_TRISTATE);
  /* Enable digital input. Only needed because P15.13 is an analog port */
  XMC_GPIO_EnableDigitalInput(P15_13);

  /* INITIALIZE BUTTON2 ON PORT 5.12 FOR INPUT */
  /* Set mode to input tristate */
  XMC_GPIO_SetMode(P15_12, XMC_GPIO_MODE_INPUT_TRISTATE);
  /* Enable digital input. Only needed because P15.12 is an analog port */
  XMC_GPIO_EnableDigitalInput(P15_12);
}

void process_app(TOBJ7000 *OUT_GENERIC, TOBJ6000 *IN_GENERIC)
{
  /* OUTPUT PROCESSING */
  /* Check bitfield set by master OUT_GEN_Bit1..8 and set LEDs accordingly */
//  XMC_GPIO_SetOutputLevel(P_LED1, MAP2LEVEL(OUT_GENERIC->OUT_GEN_Bit1));
  XMC_GPIO_SetOutputLevel(P_LED2, MAP2LEVEL(OUT_GENERIC->OUT_GEN_Bit2));
  XMC_GPIO_SetOutputLevel(P_LED3, MAP2LEVEL(OUT_GENERIC->OUT_GEN_Bit3));
  XMC_GPIO_SetOutputLevel(P_LED4, MAP2LEVEL(OUT_GENERIC->OUT_GEN_Bit4));
  XMC_GPIO_SetOutputLevel(P_LED5, MAP2LEVEL(OUT_GENERIC->OUT_GEN_Bit5));
  XMC_GPIO_SetOutputLevel(P_LED6, MAP2LEVEL(OUT_GENERIC->OUT_GEN_Bit6));
  XMC_GPIO_SetOutputLevel(P_LED7, MAP2LEVEL(OUT_GENERIC->OUT_GEN_Bit7));
  XMC_GPIO_SetOutputLevel(P_LED8, MAP2LEVEL(OUT_GENERIC->OUT_GEN_Bit8));

  /* Check integer set by Master OUT_GEN_INT1 and set duty cycle of PWM driving LED 2 accordingly */
  PWM_CCU8_SetDutyCycleSymmetric(&PWM_CCU8_0, XMC_CCU8_SLICE_COMPARE_CHANNEL_1,
		  6000+((uint32_t)4000*(uint32_t)OUT_GENERIC->OUT_GEN_INT1)/65535);

  /* INPUT PROCESSING */
  /*Check Button 1 and set IN_GEN_Bit1 which is sent to master accordingly*/
  if (XMC_GPIO_GetInput(P15_13))
    IN_GENERIC->IN_GEN_Bit1 = 1;
  else
    IN_GENERIC->IN_GEN_Bit1 = 0;

  /*Check Button 2 and set IN_GEN_Bit2 which is sent to master accordingly*/
  if (XMC_GPIO_GetInput(P15_12))
    IN_GENERIC->IN_GEN_Bit2 = 1;
  else
    IN_GENERIC->IN_GEN_Bit2 = 0;
}

/* Timer frequency (Hz) */
#define TICKS_PER_SECOND (1000)

int main(void)
{
  DAVE_STATUS_t status;
  uint32_t timer=0;
  status = DAVE_Init();                     /* Initialization of DAVE APPs  */

  Init_ECAT_Adapt_LED ();                   /* Initialize the ports which drive LEDs on EtherCat shield*/
  Init_Relax_Button();                      /* Initialize buttons on XMC4800 */

  PWM_CCU8_Start(&PWM_CCU8_0);

  /*Create basic mapping*/
//  APPL_GenerateMapping(&nPdInputSize,&nPdOutputSize);
  bRunApplication = TRUE;

  //Debug Micrium uc/probe Scope
  ProbeScope_Init(40000);
  SysTick_Config(SystemCoreClock/40000);
  /* Initialize Micrium uc/probe Scope */
//  ProbeScope_Init(SystemCoreClock / TICKS_PER_SECOND);
//  /* Initialize timer and set the SysTick priority */
//  SysTick_Config(SystemCoreClock / TICKS_PER_SECOND);

  if(status == DAVE_STATUS_FAILURE)
  {
    /* Placeholder for error handler code. The while loop below can be replaced with an user error handler. */
    XMC_DEBUG("DAVE APPs initialization failed\n");
    while(1U)
    {
    }
  }

  /* Placeholder for user application code. The while loop below can be replaced with user application code. */
  while(1U)
  {
    MainLoop();
  }
}

/**

 * @brief SYNC0IRQHandler() - EtherCAT Interrupt Routine for SYNC0
 *
 * <b>Details of function</b><br>
 * This routine is handling the SYNC0 Interrupts and need to call the SSC Stack
 */
void SYNC0IRQHandler (void)
{
	Sync0_Isr();
}

/**

 * @brief SYNC1IRQHandler() - EtherCAT Interrupt Routine for SYNC1
 *
 * <b>Details of function</b><br>
 * This routine is handling the SYNC1 Interrupts and need to call the SSC Stack
 */
void SYNC1IRQHandler (void)
{
	Sync1_Isr();
}

/**

 * @brief ENABLE_ESC_INT_USER() - Enabling of user specific EtherCAT Interrupt Routines
 *
 * <b>Details of function</b><br>
 * This routine is called from ECAT_APP on request of SSC stack once interrupts (sync1/sync0) need to be enabled
 */
void ENABLE_ESC_INT_USER()
{
	INTERRUPT_Enable(&INT_SYNC0);
	INTERRUPT_Enable(&INT_SYNC1);
}

/**

 * @brief DISABLE_ESC_INT_USER() - Disabling of user specific EtherCAT Interrupt Routines
 *
 * <b>Details of function</b><br>
 * This routine is called from ECAT_APP on request of SSC stack once interrupts (sync1/sync0) need to be disabled
 */
void DISABLE_ESC_INT_USER()
{
	INTERRUPT_Disable(&INT_SYNC0);
	INTERRUPT_Disable(&INT_SYNC1);
}





#define TIMEOUT 1000


extern uint16_t ECAT_Servo_On;


uint16_t PassNumber = 0;
uint16_t TimeOut = TIMEOUT;
uint16_t Tick_1ms;
uint16_t Tick_1s;
void IRQHandler_PosCtrl_125us(void)
{
	XMC_CCU8_SLICE_ClearEvent(PWM_CCU8_0.ccu8_slice_ptr, XMC_CCU8_SLICE_IRQ_ID_PERIOD_MATCH|XMC_CCU8_SLICE_IRQ_ID_ONE_MATCH);// Clears interrupt flag

    switch(PassNumber)
	{
	    case 0:
	    	StateMachine_CiA402_Run();
			PassNumber = 1;
		break;

		case 1:

			PassNumber = 2;
		break;

		case 2:

			PassNumber = 3;
		break;

		case 3:
			if(ECAT_Servo_On)
			{
				TimeOut--;
				if(TimeOut == 0)
				{
					TimeOut = TIMEOUT;
					XMC_GPIO_ToggleOutput(P_LED1);
					XMC_GPIO_ToggleOutput(P_LED2);
					XMC_GPIO_ToggleOutput(P_LED3);
					XMC_GPIO_ToggleOutput(P_LED4);
				}
			}
			else
			{
				XMC_GPIO_SetOutputLow(P_LED1);
				XMC_GPIO_SetOutputLow(P_LED2);
				XMC_GPIO_SetOutputLow(P_LED3);
				XMC_GPIO_SetOutputLow(P_LED4);
				TimeOut = TIMEOUT;
			}

			PassNumber = 0;
		break;
	}
    /* FPGA_SIM: feedback is owned by the isolated simulator, not direct target echo. */
    /* Position_actual_value0x6064 = Target_position0x607A; */
    Modes_of_operation_display0x6061 = Modes_of_operation0x6060;

    Cur_Loop_IdKp0x2302 = Cur_Loop_IqKp0x2300;
    Cur_Loop_IdKi0x2303 = Cur_Loop_IqKi0x2301;

    Quick_stop_Test0x205A = Quick_stop_option_code0x605A;
    ShutdownOption_Test0x205B = ShutdownOptionCode0x605B;
}

//Debug Micrium uc/probe Scope
void SysTick_Handler(void)
{
    /* Take a sample of the active oscilloscope channels */
    ProbeScope_Sampling();
}

