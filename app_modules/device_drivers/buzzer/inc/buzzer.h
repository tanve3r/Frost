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
 *  File Name          : buzzer
 *  Description        : Code for buzzer
 ******************************************************************************/

#ifndef BUZZER_H
#define BUZZER_H

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
 * @brief buzzer state
 */
typedef enum Buzzer_State
{
  BUZZER_RESET = 0,
  BUZZER_SET
}Buzzer_State;

/******************************************************************************/
/* PUBLIC DATA DECLARATIONS                                                   */
/******************************************************************************/


/******************************************************************************/
/* PUBLIC FUNCTION DECLARATIONS                                               */
/******************************************************************************/
void Buzzer_Init(void);
void SetBuzzer(Buzzer_State e_buzzer_state);


#ifdef __cplusplus
}
#endif

#endif // BUZZER_H
