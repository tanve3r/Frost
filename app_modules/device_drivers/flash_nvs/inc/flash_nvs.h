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
 *  File Name          : flash_nvs
 *  Description        : Code for flash
 ******************************************************************************/

#ifndef FLASH_NVS_H
#define FLASH_NVS_H

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
typedef struct FlashData
{
	int32_t Drink_Timer_ms;
	int32_t PlaceTimer_ms;
}FlashData;
/******************************************************************************/
/* PUBLIC DATA DECLARATIONS                                                   */
/******************************************************************************/


/******************************************************************************/
/* PUBLIC FUNCTION DECLARATIONS                                               */
/******************************************************************************/
void Flash_Init(void);
void FlashWriteParameters(FlashData* data);
void FlashReadParameters(FlashData* data);


#ifdef __cplusplus
}
#endif

#endif // FLASH_NVS_H
