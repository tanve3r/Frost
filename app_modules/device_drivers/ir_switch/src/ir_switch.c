/*******************************************************************************
 *  Copyright (c) 2024 Bangalore,
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

/******************************************************************************/
/* PRIVATE DEFINITIONS                                                        */
/******************************************************************************/

/******************************************************************************/
/* PRIVATE TYPE DEFINITIONS                                                   */
/******************************************************************************/

/******************************************************************************/
/* PRIVATE FUNCTION DECLARATIONS AND PRIVATE MACRO FUNCTION DEFINITIONS       */
/******************************************************************************/

/******************************************************************************/
/* EXTERN VARIABLE DEFINTIONS                                                 */
/******************************************************************************/

/******************************************************************************/
/* PRIVATE DATA DEFINTIONS                                                    */
/******************************************************************************/


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
}

/**
 * @brief IR switch status
 *
 */
IRSwitch_State GetIRswitchStatus(void)
{
  return((IRSwitch_State)gpio_get_level(IR_SWITCH_GPIO));
}

/******************************************************************************/
/* PRIVATE FUNCTION DEFINITIONS                                               */
/******************************************************************************/

