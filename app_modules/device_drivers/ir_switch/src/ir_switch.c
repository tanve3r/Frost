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
 *  File Name          : ir_switch
 *  Description        : Code for door_switch
 ******************************************************************************/


/******************************************************************************/
/* INCLUDES                                                                   */
/******************************************************************************/

#include <stdio.h>
#include "esp_log.h"
#include "driver/gpio.h"
#include "ir_switch.h"
#include "pin_config.h"
#include "extended_services.h"

/******************************************************************************/
/* PRIVATE DEFINITIONS                                                        */
/******************************************************************************/

/******************************************************************************/
/* PRIVATE TYPE DEFINITIONS                                                   */
/******************************************************************************/

/******************************************************************************/
/* PRIVATE FUNCTION DECLARATIONS AND PRIVATE MACRO FUNCTION DEFINITIONS       */
/******************************************************************************/
//const static char *TAG = "IR_SW";
/******************************************************************************/
/* EXTERN VARIABLE DEFINTIONS                                                 */
/******************************************************************************/

/******************************************************************************/
/* PRIVATE DATA DEFINTIONS                                                    */
/******************************************************************************/
static Srvc_DebounceParam_t st_Ir_tmdeb_ms;
static Srvc_DebounceState_t st_Ir_stateDeb = {0,0};

/******************************************************************************/
/* PUBLIC FUNCTION DEFINITIONS                                                */
/******************************************************************************/

/**
 * @brief Door_Switch initialization function
 *
 */
void IR_Switch_Init(void)
{
  gpio_reset_pin(IR_SWITCH_GPIO);
  gpio_set_direction(IR_SWITCH_GPIO, GPIO_MODE_INPUT);
  gpio_set_pull_mode(IR_SWITCH_GPIO,GPIO_PULLDOWN_ONLY);
  
  st_Ir_tmdeb_ms.TimeHighLow = 200;
  st_Ir_tmdeb_ms.TimeLowHigh = 10;
}

/**
 * @brief IR switch status
 *
 */
uint8_t GetIRswitchStatus(void)
{
	IRSwitch_State IrSwitchStatus = (gpio_get_level(IR_SWITCH_GPIO) == 1) ? DOOR_SWITCH_RESET:DOOR_SWITCH_SET;
	uint8_t debval = Srvc_Debounce((bool)IrSwitchStatus, 
	                     &st_Ir_stateDeb,
	                     &st_Ir_tmdeb_ms,
	                     10);
	                     
//	ESP_LOGI(TAG, "IR:%d IRD:%d\n", IrSwitchStatus,debval);                     
	return(debval);
}

/******************************************************************************/
/* PRIVATE FUNCTION DEFINITIONS                                               */
/******************************************************************************/

