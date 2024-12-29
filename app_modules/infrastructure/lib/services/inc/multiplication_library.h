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
 *  COMP_ABBREV      Multiplication library
 ******************************************************************************/

#ifndef MULTIPLICATION_LIBRARY_H_
#define MULTIPLICATION_LIBRARY_H_

#ifdef __cplusplus
extern "C" {
#endif


/******************************************************************************/
/* DOCUMENTATION                                                              */
/******************************************************************************/
/** \file
 *
 *
 *  \ingroup  multiplication_library.h
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

#define Srvc_MulDiv32(M1, M2, D)             Srvc_MulDiv_S32S32S32_S32((M1), (M2), (D))

// TODO: remove once finalyse what is the exact value
#define TX_TIMER_TICKS_PER_SECOND         1

/******************************************************************************/
/* PUBLIC TYPE DEFINITIONS                                                    */
/******************************************************************************/

typedef struct
{
  int32_t s32_Sum;       // Sum value stored
  uint8_t u8_N;           // no of average to be considered
  int16_t * ps16_Beg;     // starting address of array
  int16_t * ps16_End;     // end address of array
  int16_t * ps16_Act;     // actual position of array. Initialize with starting address of array.
} Srvc_AvrgsldngS16_t;


/* specialised struct, used in Srvc_AveragSliding_S32*/
typedef struct
{
  int64_t s64_Sum;
  uint8_t u8_N;
  int32_t * ps32_Beg;
  int32_t * ps32_End;
  int32_t * ps32_Act;
} Srvc_AvrgsldngS32_t;

/******************************************************************************/
/* PUBLIC DATA DECLARATIONS                                                   */
/******************************************************************************/


/******************************************************************************/
/* PUBLIC FUNCTION DECLARATIONS                                               */
/******************************************************************************/

uint16_t Srvc_Mul_S32S32_U16(int32_t s32_X, int32_t s32_Y);
uint16_t Srvc_Mul_U32S32_U16(uint32_t u32_X, int32_t s32_Y);
uint16_t Srvc_Mul_U32U32_U16(uint32_t u32_X, uint32_t u32_Y);

int16_t Srvc_Mul_S32S32_S16(int32_t s32_X, int32_t s32_Y);
int16_t Srvc_Mul_U32S32_S16(uint32_t u32_X, int32_t s32_Y);
int16_t Srvc_Mul_U32U32_S16(uint32_t u32_X, uint32_t u32_Y);

uint32_t Srvc_Mul_S32S32_U32(int32_t s32_X, int32_t s32_Y);
uint32_t Srvc_Mul_U32S32_U32(uint32_t u32_X, int32_t s32_Y);
uint32_t Srvc_Mul_U32U32_U32(uint32_t u32_X, uint32_t u32_Y);

int32_t Srvc_Mul_S32S32_S32(int32_t s32_X, int32_t s32_Y);
int32_t Srvc_Mul_U32S32_S32(uint32_t u32_X, int32_t s32_Y);
int32_t Srvc_Mul_U32U32_S32(uint32_t u32_X, uint32_t u32_Y);

int16_t Srvc_MulDiv_S32S32S32_S16(int32_t s32_X, int32_t s32_Y, int32_t s32_Z);
int32_t Srvc_MulDiv_S32S32S32_S32(int32_t s32_X, int32_t s32_Y, int32_t s32_Z);
uint16_t Srvc_MulDiv_U32U32U32_U16(uint32_t u32_X, uint32_t u32_Y, uint32_t u32_Z);
uint16_t Srvc_MulDiv_S32S32S32_U16(int32_t s32_X, int32_t s32_Y, int32_t s32_Z);
uint32_t Srvc_MulDiv_U32U32U32_U32(uint32_t u32_X, uint32_t u32_Y, uint32_t u32_Z);
int32_t Srvc_Average_S32S32_S32(int32_t s32_X, int32_t s32_Y);


int16_t Srvc_AverageArray_S16(const int16_t * Array_pcs16, uint8_t u8_N);

// int16_t Srvc_AverageSliding_S16 (Srvc_AvrgsldngS16_t *const Struct_cpst, int16_t s16_Inp);
int16_t Srvc_AverageSliding_S16(  Srvc_AvrgsldngS16_t * const Struct_cpst, int16_t s16_Inp, int32_t s32_SampleCount, int32_t s32_MaxSampleCount);

/********************************************************
*   Accessed by other functions
********************************************************/
int16_t Srvc_TypeLimiter_S32_S16(int32_t s32_X);
uint16_t Srvc_TypeLimiter_S32_U16(int32_t s32_X);
uint32_t Srvc_TypeLimiter_S32_U32(int32_t s32_X);
uint16_t Srvc_TypeLimiter_U32_U16(uint32_t u32_X);

uint16_t Srvc_Div_S32S32_U16(int32_t s32_X, int32_t s32_Y);
int64_t Srvc_Mul_S32S32_S64(int32_t s32_X, int32_t s32_Y);
uint64_t Srvc_Mul_U32U32_U64(uint32_t u32_X, uint32_t u32_Y);

#ifdef __cplusplus
}
#endif

#endif  // MULTIPLICATION_LIBRARY_H_
