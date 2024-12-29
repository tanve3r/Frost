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

#ifndef IR_SWITCH_H
#define IR_SWITCH_H

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
 * @brief IR latch state
 */
typedef enum IRSwitch_State
{
  DOOR_SWITCH_RESET = 0,
  DOOR_SWITCH_SET
}IRSwitch_State;

/******************************************************************************/
/* PUBLIC DATA DECLARATIONS                                                   */
/******************************************************************************/


/******************************************************************************/
/* PUBLIC FUNCTION DECLARATIONS                                               */
/******************************************************************************/
void IR_Switch_Init(void);
uint8_t GetIRswitchStatus(void);


#ifdef __cplusplus
}
#endif

#endif // IR_SWITCH_H
