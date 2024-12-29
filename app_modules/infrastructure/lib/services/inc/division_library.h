/*******************************************************************************
 *  Copyright (c) 2025 BSH Hausgeraete GmbH,
 *  Carl-Wery-Str. 34, 81739 Munich, Germany, www.bsh-group.de
 *
 *  All rights reserved. This program and the accompanying materials
 *  are protected by international copyright laws.
 *  Please contact copyright holder for licensing information.
 *
 *******************************************************************************
 *  PROJECT          TWO_IN1_CPM
 *  COMP_ABBREV      Division library
 ******************************************************************************/

#ifndef DIVISION_LIBRARY_H_
#define DIVISION_LIBRARY_H_

#ifdef __cplusplus
extern "C" {
#endif


/******************************************************************************/
/* DOCUMENTATION                                                              */
/******************************************************************************/
/** \file
 *
 *
 *  \ingroup  division_library.h
 *
 *  \brief    
 *
 */

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


/******************************************************************************/
/* PUBLIC DATA DECLARATIONS                                                   */
/******************************************************************************/


/******************************************************************************/
/* PUBLIC FUNCTION DECLARATIONS                                               */
/******************************************************************************/

int32_t Srvc_Div_S32S32_S32(int32_t s32_X, int32_t s32_Y);
int32_t Srvc_Div_U32S32_S32(uint32_t u32_X, int32_t s32_Y);
int32_t Srvc_Div_S32U32_S32(int32_t s32_X, uint32_t u32_Y);
int32_t Srvc_Div_U32U32_S32(uint32_t u32_X, uint32_t u32_Y);

uint32_t Srvc_Div_S32S32_U32(int32_t s32_X, int32_t s32_Y);
uint32_t Srvc_Div_S32U32_U32(int32_t s32_X, uint32_t u32_Y);
uint32_t Srvc_Div_U32S32_U32(uint32_t u32_X, int32_t s32_Y);
uint32_t Srvc_Div_U32U32_U32(uint32_t u32_X, uint32_t u32_Y);

int16_t Srvc_Div_S32S32_S16(int32_t s32_X, int32_t s32_Y);
int16_t Srvc_Div_U32S32_S16(uint32_t u32_X, int32_t s32_Y);
int16_t Srvc_Div_S32U32_S16(int32_t s32_X, uint32_t u32_Y);
int16_t Srvc_Div_U32U32_S16(uint32_t u32_X, uint32_t u32_Y);

uint16_t Srvc_Div_S32S32_U16(int32_t s32_X, int32_t s32_Y);
uint16_t Srvc_Div_U32S32_U16(uint32_t u32_X, int32_t s32_Y);
uint16_t Srvc_Div_S32U32_U16(int32_t s32_X, uint32_t u32_Y);
uint16_t Srvc_Div_U32U32_U16(uint32_t u32_X, uint32_t u32_Y);

int32_t Srvc_Div_S64S32_S32(int64_t s64_X, int32_t s32_Y);
uint32_t Srvc_Div_U64U32_U32(uint64_t u64_X, uint32_t u32_Y);

#ifdef __cplusplus
}
#endif

#endif  // DIVISION_LIBRARY_H_
