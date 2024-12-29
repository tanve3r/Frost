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
 *  COMP_ABBREV      Extended services library
 ******************************************************************************/

#ifndef EXTENDED_SERVICES_H_
#define EXTENDED_SERVICES_H_

#ifdef __cplusplus
extern "C" {
#endif


/******************************************************************************/
/* DOCUMENTATION                                                              */
/******************************************************************************/
/** \file
 *
 *
 *  \ingroup  extended_services.h
 *
 *  \brief    
 *
 */

/******************************************************************************/
/* LINT OPTIONS                                                               */
/******************************************************************************/
/* All deactivated lint errors/warnings are tested and there are no problem.  */
/*lint -save    
*/

/*Note 9045: complete definition of 'xx' is unnecessary in this translation unit [MISRA 2012 Directive 4.8, advisory] */
/*lint -e9045*/

/******************************************************************************/
/* INCLUDES                                                                   */
/******************************************************************************/
#include <assert.h>
#include <stdbool.h>
#include "stdint.h"

/******************************************************************************/
/* PUBLIC DEFINITIONS                                                         */
/******************************************************************************/

/******************************************************************************/
/* PUBLIC TYPE DEFINITIONS                                                    */
/******************************************************************************/

/** 32-bit SW-timer struct */
typedef struct
{
  uint32_t tiStrd;        /* stored timer-value */
} Srvc_SWTmrU32_t;

/**
Srvc_DebounceParam_t: Parameter struct for Debounce.
Contains the times for Low and High transition.
*/
typedef struct
{
  int16_t TimeHighLow;  /**< Time for a High to Low transition in ms  */
  int16_t TimeLowHigh;  /**< Time for a Low to High transition in ms  */
} Srvc_DebounceParam_t;

/**
Srvc_DebounceState_t: State struct for Debounce.
Saves the internal state and the software timers that are needed for debouncing.
*/
typedef struct
{
  bool XOld;      /**< Old input value from last call  */
  int32_t Timer;  /**< Timer for internal state  */
} Srvc_DebounceState_t;

/*****************************
* Type Def for Maps
******************************/
/** MapS16 - type for signed integer 16Bit map.              */
typedef const int16_t Srvc_MapS16_t[];
/** SearchRes_t - type for search results.                   */
typedef int32_t Srvc_SearchRes_t;
/** ValS16 - type for signed integer 16Bit value array       */
typedef const int16_t Srvc_ValS16_t[];
/** DistribS16 - type for signed integer 16Bit distribution  */
typedef const int16_t Srvc_DistribS16_t[];
/** CurveS16 - type for signed integer 16Bit curve           */
typedef  const int16_t Srvc_CurveS16_t[];
/** sint32 - type for signed integer 32Bit                   */
typedef int32_t sint32;
/** CurveS32 - type for signed integer 32Bit curve           */
typedef sint32 Srvc_CurveS32_t[];

/******************************************************************************/
/* PUBLIC DATA DECLARATIONS                                                   */
/******************************************************************************/


/******************************************************************************/
/* PUBLIC FUNCTION DECLARATIONS                                               */
/******************************************************************************/
extern uint8_t Srvc_CalcCRC (const uint8_t pu8_Buff[], const uint16_t u16_Lgth);
uint16_t Srvc_calc_2sComplementcrc(const uint8_t* buffer, const uint8_t size );
extern bool Srvc_Debounce(bool X, Srvc_DebounceState_t * State, const Srvc_DebounceParam_t * Param, int32_t Dt_Time);

extern void Srvc_StartSWTmrU32(Srvc_SWTmrU32_t * tmrPtr);
extern uint32_t Srvc_DiffSWTmrU32(const Srvc_SWTmrU32_t * tmrPtr);
extern bool Srvc_TestSWTmrU32(const Srvc_SWTmrU32_t * tmrPtr);
extern void Srvc_StopSWTmrU32(Srvc_SWTmrU32_t * tmrPtr);

int16_t Srvc_IpoCurveS16(int32_t s32_X, Srvc_CurveS16_t s16_Cur);
extern int32_t Srvc_LimitS32(int32_t s32_X, int32_t s32_Min, int32_t s32_Max);
extern uint32_t Srvc_LimitU32(uint32_t u32_X, uint32_t u32_Min, uint32_t u32_Max);

extern int16_t Srvc_IpoMapS16S16(int32_t X_s32, int32_t Y_s32, Srvc_MapS16_t MapVal);
extern int32_t Srvc_DistrSearchS16(int32_t X, int32_t Num, Srvc_DistribS16_t Distr);
extern int16_t Srvc_IpoGroupMapS16(Srvc_SearchRes_t XSearchRes, Srvc_SearchRes_t YSearchRes, int32_t Num, Srvc_ValS16_t MapVal);

extern uint32_t Srvc_ulGetCurrentTime( void );
extern uint32_t service_tConvertMStoTicks(uint32_t const ul_time_ms);
extern uint32_t service_tConvertTickstoMS(uint32_t const ul_ticks);
//extern uint32_t Srvc_RampUpDown(uint32_t u32_command_vel,bool b_Rampmode, bool b_ResetRamp);

extern int32_t Srvc_Abs_S32_S32 (int32_t s32_X);

sint32 Srvc_IpoCurveS32(sint32 s32_X, Srvc_CurveS32_t s32_Cur);

#ifdef __cplusplus
}
#endif

#endif  // EXTENDED_SERVICES_H_
