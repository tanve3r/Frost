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
 *  File Name          : syssm
 *  Description        : Code for system state machine applications
 ******************************************************************************/


/******************************************************************************/
/* INCLUDES                                                                   */
/******************************************************************************/

#include <stdio.h>
#include "esp_log.h"
#include "buzzer.h"
#include "sdkconfig.h"
#include "syssm.h"
#include "rgb_led_strip.h"

/******************************************************************************/
/* PRIVATE DEFINITIONS                                                        */
/******************************************************************************/



/******************************************************************************/
/* PRIVATE TYPE DEFINITIONS                                                   */
/******************************************************************************/

const static char *TAG = "Frost";

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
 * @brief system state machine initialization function
 *
 */
void SysSm_Init(void)
{
  ESP_LOGI(TAG, "Hello from System \n");
}

/**
 * @brief system state machine process
 *
 */
void SysSm_Process (void)
{

  
    //ESP_LOGI(TAG, "Door switch status is = %d\n", door_switch_val);

 // SetBuzzer(door_switch_val);

}
