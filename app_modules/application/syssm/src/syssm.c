/*******************************************************************************
 *  Copyright (c) 2025 Bangalore,
 *
 *  All rights reserved. This program and the accompanying materials
 *  are protected by international copyright laws.
 *  Please contact copyright holder for licensing information.
 *
 *
 *  @author Tanveer
 *
 *******************************************************************************
 *  PROJECT              FROST
 *  File Name          : syssm
 *  Description        : Code for system state machine applications
 ******************************************************************************/


/******************************************************************************/
/* INCLUDES                                                                   */
/******************************************************************************/

#include "stdbool.h"
#include <stdio.h>
#include "esp_log.h"
#include "buzzer.h"
#include "ir_switch.h"
#include "sdkconfig.h"
#include "syssm.h"
#include "rgb_led_strip.h"
#include "ldr_sensor.h"
#include "flash_nvs.h"

//#define TESTMODE_ENABLE

/******************************************************************************/
/* PRIVATE DEFINITIONS                                                        */
/******************************************************************************/
typedef enum sysSM_States
{
	INIT = 0,
	IDLE,
	BOTTLE_PRESENT,
	REMINDER_DRINK,
	REMINDER_CLEAN,
	STANDBY
}sysSM_States;


/******************************************************************************/
/* PRIVATE TYPE DEFINITIONS                                                   */
/******************************************************************************/

const static char *TAG = "sysSM";
#ifndef TESTMODE_ENABLE
static sysSM_States CurrentState = INIT;
#endif
/******************************************************************************/
/* PRIVATE FUNCTION DECLARATIONS AND PRIVATE MACRO FUNCTION DEFINITIONS       */
/******************************************************************************/


/******************************************************************************/
/* EXTERN VARIABLE DEFINTIONS                                                 */
/******************************************************************************/

/******************************************************************************/
/* PRIVATE DATA DEFINTIONS                                                    */
/******************************************************************************/
static FlashData frostdata = {0,0};

/******************************************************************************/
/* PUBLIC FUNCTION DEFINITIONS                                                */
/******************************************************************************/
/**
 * @brief system state machine initialization function
 *
 */
void SysSm_Init(void)
{
  ESP_LOGI(TAG, "Hello from System \n");
}

#ifdef TESTMODE_ENABLE
/**
 * @brief system state machine process
 *
 */
void SysSm_Process (void)
{ 
  static bool statussetflag = false;
  static bool statusresetflag = false;
	static LED_STRIP_COLOR color = LED_COLOR_OFF;
	IRSwitch_State status = GetIRswitchStatus();
//	ESP_LOGI(TAG, "IR:%d LDR:%d\n", status, Get_LDR_Data());
	
	if(status)
	{
		SetBuzzer(BUZZER_SET);
		if(statussetflag == false)
		{
			color ++;
			if(color >= LED_MAX_COLORS)
			{
				color = LED_COLOR_OFF;
			}
			ESP_LOGI(TAG, "1IR:%d LDR:%d\n", status, Get_LDR_Data());
			
			rgb_setLed(LED_1, color);
			rgb_setLed(LED_2, color);
			rgb_setLed(LED_3, color);
		}
         statussetflag =  true;
         statusresetflag = false;
	}
	else{

		SetBuzzer(BUZZER_RESET);
		
		if(statusresetflag == false)
		{
			ESP_LOGI(TAG, "2IR:%d LDR:%d\n", status, Get_LDR_Data());
			rgb_setLed(LED_1, color);
			rgb_setLed(LED_2, color);
			rgb_setLed(LED_3, color);
		}
         statusresetflag =  true;
		 statussetflag = false;
	}
	
}

#else
/**
 * @brief system state machine process
 *
 */
void SysSm_Process (void)
{ 
	switch(CurrentState)
	{
		case INIT:
		{
			FlashReadParameters(&frostdata);
			frostdata.Drink_Timer_ms ++;
			frostdata.PlaceTimer_ms++;
			CurrentState = IDLE;
		}
		break;
		case IDLE:
		{
			FlashWriteParameters(&frostdata);
			CurrentState = BOTTLE_PRESENT;
		}
		break;
		case BOTTLE_PRESENT:
		{
			
		}
		break;
		case REMINDER_DRINK:
		{
			
		}
		break;
		case REMINDER_CLEAN:
		{
			
		}
		break;
		case STANDBY:
		{
			
		}
		break;
		default:
		break;
		
	}
}
#endif
