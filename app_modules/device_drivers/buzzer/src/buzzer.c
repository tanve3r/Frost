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
#include "hal/gpio_hal.h"
#include "buzzer.h"
#include "pin_config.h"

/******************************************************************************/
/* PRIVATE DEFINITIONS                                                        */
/******************************************************************************/
#define GPIO_OUTPUT_PIN_SEL  ((1ULL<<BUZZER_GPIO) | (1ULL<<BUZZER_GPIO))

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
	//zero-initialize the config structure.
    gpio_config_t io_conf = {};
    //disable interrupt
    io_conf.intr_type = GPIO_INTR_DISABLE;
    //set as output mode
    io_conf.mode = GPIO_MODE_OUTPUT;
    //bit mask of the pins that you want to set,e.g.GPIO18/19
    io_conf.pin_bit_mask = GPIO_OUTPUT_PIN_SEL;
    //disable pull-down mode
    io_conf.pull_down_en = 0;
    //disable pull-up mode
    io_conf.pull_up_en = 0;
    //configure GPIO with the given settings
    gpio_config(&io_conf);
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

