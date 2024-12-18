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
 *  File Name          : buzzer
 *  Description        : Code for buzzer
 ******************************************************************************/


/******************************************************************************/
/* INCLUDES                                                                   */
/******************************************************************************/

#include <stdio.h>
#include "esp_log.h"
#include "driver/gpio.h"
#include "buzzer.h"
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
 * @brief buzzer initialization function
 *
 */
void Buzzer_Init(void)
{
	gpio_reset_pin(BUZZER_GPIO);
    /* Set the GPIO as a push/pull output */
    gpio_set_direction(BUZZER_GPIO, GPIO_MODE_OUTPUT);
    
}

/**
 * @brief buzzer state
 */
void SetBuzzer(Buzzer_State e_buzzer_state)
{
  gpio_set_level(BUZZER_GPIO, e_buzzer_state);
}

/******************************************************************************/
/* PRIVATE FUNCTION DEFINITIONS                                               */
/******************************************************************************/

