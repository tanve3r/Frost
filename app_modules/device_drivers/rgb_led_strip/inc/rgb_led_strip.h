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
 *  File Name          : rgb_led_strip
 *  Description        : Code for rgb_led_strip
 ******************************************************************************/

#ifndef RGB_LED_STRIP_H
#define RGB_LED_STRIP_H

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************/
/* INCLUDES                                                                   */
/******************************************************************************/
#include <assert.h>
#include "stdint.h"

/******************************************************************************/
/* PUBLIC DEFINITIONS                                                         */
/******************************************************************************/


/******************************************************************************/
/* PUBLIC TYPE DEFINITIONS                                                    */
/******************************************************************************/
/*
 * @brief door latch state
 */
typedef enum LED_STRIP_COLOR
{
  LED_COLOR_OFF = 0,
  LED_COLOR_RED,
  LED_COLOR_GREEN,
  LED_COLOR_BLUE,
  LED_COLOR_YELLOW,
  LED_COLOR_CYAN,
  LED_COLOR_MAGENTA,
  LED_COLOR_ORANGE,
  LED_COLOR_YELLOW_GREEN,
  LED_COLOR_CYAN_GREEN,
  LED_COLOR_CYAN_BLUE,
  LED_COLOR_BLUE_MAGENTA,
  LED_COLOR_RED_MAGENTA,
  LED_COLOR_WHITE,

  LED_MAX_COLORS
}LED_STRIP_COLOR;

/******************************************************************************/
/* PUBLIC DATA DECLARATIONS                                                   */
/******************************************************************************/


/******************************************************************************/
/* PUBLIC FUNCTION DECLARATIONS                                               */
/******************************************************************************/
void rgb_ledStrip_Init (void);
void rgb_SetLedStrip (LED_STRIP_COLOR e_Color);

#ifdef __cplusplus
}
#endif

#endif // RGB_LED_STRIP_H
