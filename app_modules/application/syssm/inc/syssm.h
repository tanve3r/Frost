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

#ifndef SYSSM_H
#define SYSSM_H

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
typedef enum SYSSM_BLE_DATA
{
	BLE_DRINK_TIMER = 0,
	BLE_PLACE_TIMER,
	BLE_CLEAN_TIMER
}SYSSM_BLE_DATA;

/******************************************************************************/
/* PUBLIC DATA DECLARATIONS                                                   */
/******************************************************************************/


/******************************************************************************/
/* PUBLIC FUNCTION DECLARATIONS                                               */
/******************************************************************************/
void SysSm_Init (void);
void SysSm_Process (void);
void SysSm_Update_Flash(SYSSM_BLE_DATA dataId, int32_t data);

#ifdef __cplusplus
}
#endif

#endif // SYSSM_H
