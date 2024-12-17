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
 *  File Name          : Pin configuration file
 *  Description        : Code for pin configuration
 ******************************************************************************/

#ifndef PIN_CONFIG_H
#define PIN_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************/
/* INCLUDES                                                                   */
/******************************************************************************/
#include <assert.h>
#include "stdint.h"
#include "driver/gpio.h"
#include "hal/gpio_hal.h"

/******************************************************************************/
/* PUBLIC DEFINITIONS                                                         */
/******************************************************************************/

// Modbus slave address
#define CONFIG_MB_SLAVE_ADDR 3

#define BUZZER_GPIO               GPIO_NUM_5

#define DOOR_LATCH_GPIO           GPIO_NUM_21

#define DOOR_SWITCH_GPIO          GPIO_NUM_18

#define CABIN_LIGHT_GPIO          GPIO_NUM_23

#define RGB_LED_STRIP_TX_GPIO     GPIO_NUM_19

// Mod-bus pins
#define MODBUS_DE_RE_UART_RTS      GPIO_NUM_4
#define MODBUS_DI_UART_TX          GPIO_NUM_17
#define MODBUS_RO_UART_RX          GPIO_NUM_16

// Keypad pins
/* Rows */
#define KEY_ROW_1_PIN          GPIO_NUM_32
#define KEY_ROW_2_PIN          GPIO_NUM_33
#define KEY_ROW_3_PIN          GPIO_NUM_25
#define KEY_ROW_4_PIN          GPIO_NUM_26
/* Columns */
#define KEY_COL_1_PIN       GPIO_NUM_27
#define KEY_COL_2_PIN       GPIO_NUM_14
#define KEY_COL_3_PIN       GPIO_NUM_13

#define  GPIO_PIN_RESET 0
#define  GPIO_PIN_SET   1

/******************************************************************************/
/* PUBLIC TYPE DEFINITIONS                                                    */
/******************************************************************************/


/******************************************************************************/
/* PUBLIC DATA DECLARATIONS                                                   */
/******************************************************************************/


/******************************************************************************/
/* PUBLIC FUNCTION DECLARATIONS                                               */
/******************************************************************************/



#ifdef __cplusplus
}
#endif

#endif // PIN_CONFIG_H
