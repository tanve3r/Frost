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
 *  COMP_ABBREV      multiplication library
 ******************************************************************************/

/******************************************************************************/
/* DOCUMENTATION                                                              */
/******************************************************************************/
/** \file          multiplication_library.c 
 *
 *  \brief
 *
 *  \details
 *
 */

/******************************************************************************/
/* INCLUDES                                                                   */
/******************************************************************************/
#include <stdbool.h>
#include "division_library.h"
#include "multiplication_library.h"

/*
 ***********************************************************************************************************************
 *
 * List of Functions
 *
 * Srvc_Mul_S32S32_U16,         Srvc_Mul_U32S32_U16,         Srvc_Mul_U32U32_U16
 * Srvc_Mul_S32S32_S16,         Srvc_Mul_U32S32_S16,         Srvc_Mul_U32U32_S16
 * Srvc_Mul_S32S32_U32,         Srvc_Mul_U32S32_U32,         Srvc_Mul_U32U32_U32
 * Srvc_Mul_S32S32_S32,         Srvc_Mul_U32S32_S32,         Srvc_Mul_U32U32_S32
 * Srvc_MulDiv_S32S32S32_S32    Srvc_MulDiv_S32S32S32_S16    Srvc_MulDiv_U32U32U32_U32
 * Srvc_MulDiv_S32S32S32_U16    Srvc_MulDiv_U32U32U32_U16    Srvc_TypeLimiter_U32_U16
 * Srvc_TypeLimiter_S32_S16     Srvc_TypeLimiter_S32_U16     Srvc_TypeLimiter_S32_U32
 * Srvc_AverageArray_S16        Srvc_Average_S32S32_S32      Srvc_AverageSliding_S16
 * Srvc_Mul_S32S32_S64          Srvc_Mul_U32U32_U64
 *
 **/

/*
 ***********************************************************************************************************************
 *
 * Multiplication
 * of two of values of 32bit length
 * with saturation to uint16_t.
 *
 ***********************************************************************************************************************
 */

/**
 ***********************************************************************************************************************
 * Srvc_Mul_S32S32_U16
 *
 * int32_t int32_t multiplication with uint16_t saturation.
 * multiply a signed 32-bit variable to a signed 32-bit variable and return the result as unsigned 16-bit.
 * The result is limited to UINT16_MAX (MINuint16_t) prevent overflows(underflows).
 *
 * \param     s32_X     Operand 1, signed 32-bit variable
 * \param     s32_Y     Operand 2, signed 32-bit variable
 * \return    uint16_t
 * \retval    (s32_X * s32_Y) saturated to uint16_t
 ***********************************************************************************************************************
 */
uint16_t Srvc_Mul_S32S32_U16(int32_t s32_X, int32_t s32_Y)
{
  int64_t s64_Tmp;

  /* interim s64_Tmp */
  s64_Tmp = ((int64_t)s32_X) * ((int64_t) s32_Y);
  s64_Tmp = ((s64_Tmp >= ((int64_t)UINT16_MAX)) ?
    ((int64_t)UINT16_MAX) : ((s64_Tmp <= 0LL) ? 0LL : s64_Tmp));

  return (uint16_t)s64_Tmp;
}

/**
 ***********************************************************************************************************************
 * Srvc_Mul_U32S32_U16
 *
 * uint32_t int32_t multiplication with uint16_t saturation.
 * multiply a unsigned 32-bit variable to a signed 32-bit variable and return the result as unsigned 16-bit.
 * The result is limited to UINT16_MAX (MINuint16_t) prevent overflows(underflows).
 *
 * \param     u32_X     Operand 1, unsigned 32-bit variable
 * \param     s32_Y     Operand 2, signed 32-bit variable
 * \return    unit16
 * \retval   (u32_X * s32_Y) saturated to uint16_t
 ***********************************************************************************************************************
 */
uint16_t Srvc_Mul_U32S32_U16(uint32_t u32_X, int32_t s32_Y)
{
  uint16_t u16_Res;
  uint64_t u64_Tmp;

  /* limitation to 0 */
  if (s32_Y <= 0) {
    u16_Res = 0;
  } else {
    /* interim s64_Tmp */
    u64_Tmp = ((uint64_t)u32_X ) * ((uint64_t)s32_Y);

    /* limitation to UINT16_MAX */
    if (u64_Tmp >= ((uint64_t) UINT16_MAX)) {
      u16_Res = UINT16_MAX;
    } else {
      /* regular expression */
      u16_Res = ((uint16_t)u64_Tmp);
    }
  }
  return u16_Res;
}

/**
 ***********************************************************************************************************************
 * Srvc_Mul_U32U32_U16
 *
 * uint32_t uint32_t multiplication with uint16_t saturation.
 * multiply a unsigned 32-bit variable to a unsigned 32-bit variable and return the result as unsigned 16-bit.
 * The result is limited to UINT16_MAX (MINuint16_t) prevent overflows(underflows).
 *
 * \param     u32_X     Operand 1, unsigned 32-bit variable
 * \param     u32_Y     Operand 2, unsigned 32-bit variable
 * \return    unit16
 * \retval   (u32_X * u32_Y) saturated to uint16_t
 ***********************************************************************************************************************
 */
uint16_t Srvc_Mul_U32U32_U16(uint32_t u32_X, uint32_t u32_Y)
{
  uint16_t u16_Res;
  uint64_t u64_Tmp;

  /* interim u64_Tmp */
  u64_Tmp = ((uint64_t)u32_X) * ((uint64_t)u32_Y);

  /* limitation to UINT16_MAX */
  if (u64_Tmp >= ((uint64_t)UINT16_MAX)) {
    u16_Res = UINT16_MAX;
  } else {
    /* regular expression */
    u16_Res = ((uint16_t)u64_Tmp);
  }
  return u16_Res;
}

/**
 ***********************************************************************************************************************
 *
 * Multiplication
 * of two of values of 32bit length
 * with saturation to int16_t.
 *
 ***********************************************************************************************************************
 */

/**
 ***********************************************************************************************************************
 * Srvc_Mul_S32S32_S16
 *
 * int32_t int32_t multiplication with int16_t saturation.
 * multiply a signed 32-bit variable to a signed 32-bit variable and return the result as signed 16-bit.
 * The result is limited to UINT16_MAX (INT16_MIN) prevent overflows(underflows).
 *
 * \param     s32_X     Operand 1, signed 32-bit variable
 * \param     s32_Y     Operand 2, signed 32-bit variable
 * \return    int16_t
 * \retval    (s32_X * s32_Y) saturated to int16_t
 ***********************************************************************************************************************
 */
int16_t Srvc_Mul_S32S32_S16(int32_t s32_X, int32_t s32_Y)
{
  int64_t s64_Res;

  /* interim s64_Res */
  s64_Res = ((int64_t)s32_X) * ((int64_t) s32_Y);
  s64_Res = ((s64_Res >= ((int64_t)UINT16_MAX)) ? ((int64_t)UINT16_MAX) :
    ((s64_Res <= ((int64_t)INT16_MIN)) ? ((int64_t)INT16_MIN) :
    s64_Res));
  return (int16_t)s64_Res;
}

/**
 ***********************************************************************************************************************
 * Srvc_Mul_U32S32_S16
 *
 * uint32_t int32_t multiplication with int16_t saturation.
 * multiply a unsigned 32-bit variable to a signed 32-bit variable and return the result as signed 16-bit.
 * The result is limited to UINT16_MAX (INT16_MIN) prevent overflows(underflows).
 *
 * \param     u32_X     Operand 1, unsigned 32-bit variable
 * \param     s32_Y     Operand 2, signed 32-bit variable
 * \return    int16_t
 * \retval   (u32_X * s32_Y) saturated to int16_t
 ***********************************************************************************************************************
 */
int16_t Srvc_Mul_U32S32_S16(uint32_t u32_X, int32_t s32_Y)
{
  int16_t s16_Res;
  int64_t s64_Tmp;

  /* interim s64_Tmp */
  s64_Tmp = ((int64_t)u32_X) * ((int64_t)s32_Y);

  /* limitation to UINT16_MAX */
  if (s64_Tmp >= INT16_MAX) {
    s16_Res = INT16_MAX;
  } else if (s64_Tmp <= INT16_MIN) {
    /* handle underflow */
    s16_Res = INT16_MIN;
  } else {
    s16_Res = ((int16_t)s64_Tmp);
  }
  return s16_Res;
}

/**
 ***********************************************************************************************************************
 * Srvc_Mul_U32U32_S16
 *
 * uint32_t uint32_t multiplication with uint16_t saturation.
 * multiply a unsigned 32-bit variable to a unsigned 32-bit variable and return the result as signed 16-bit.
 * The result is limited to UINT16_MAX (INT16_MIN) prevent overflows(underflows).
 *
 * \param     u32_X     Operand 1, unsigned 32-bit variable
 * \param     u32_Y     Operand 1, unsigned 32-bit variable
 * \return    int16_t
 * \retval   (u32_X * u32_Y) saturated to int16_t
 ***********************************************************************************************************************
 */
int16_t Srvc_Mul_U32U32_S16(uint32_t u32_X, uint32_t u32_Y)
{
  int16_t s16_Res;
  uint64_t u64_Tmp;

  /* interim u64_Tmp */
  u64_Tmp = ((uint64_t)u32_X) * ((uint64_t)u32_Y);

  /* limitation to UINT16_MAX */
  if (u64_Tmp >= ((uint64_t)INT16_MAX)) {
    s16_Res = INT16_MAX;
  } else {
    /* regular expression */
    s16_Res = ((int16_t)u64_Tmp );
  }
  return s16_Res;
}

/**
 ***********************************************************************************************************************
 *
 * Multiplication
 * of two of values of 32bit length
 * with saturation to uint32_t.
 *
 ***********************************************************************************************************************
 */

/**
 ***********************************************************************************************************************
 * Srvc_Mul_S32S32_U32
 *
 * int32_t int32_t multiplication with uint32_t saturation.
 * multiply a signed 32-bit variable to a signed 32-bit variable and return the result as unsigned 32-bit.
 * The result is limited to UINT32_MAX (MINuint32_t) prevent overflows(underflows).
 *
 * \param     s32_X     Operand 1, signed 32-bit variable
 * \param     s32_Y     Operand 2, signed 32-bit variable
 * \return    uint32_t
 * \retval    (s32_X * s32_Y) saturated to uint32_t
 ***********************************************************************************************************************
 */
uint32_t Srvc_Mul_S32S32_U32(int32_t s32_X, int32_t s32_Y)
{
  uint32_t u32_Res;
  int64_t s64_Tmp;

  /* interim s64_Tmp */
  s64_Tmp = ((int64_t)s32_X) * ((int64_t)s32_Y);

  /* limitation to UINT32_MAX */
  if (s64_Tmp >= ((int64_t)UINT32_MAX)) {
    u32_Res = UINT32_MAX;
  } else if (s64_Tmp <= 0L) {
    /* limitation to 0 */
    u32_Res = 0L;
  } else {
    /* regular expresion */
    u32_Res = ((uint32_t)s64_Tmp);
  }

  return u32_Res;
}

/**
 ***********************************************************************************************************************
 * Srvc_Mul_U32S32_U32
 *
 * uint32_t int32_t multiplication with uint32_t saturation.
 * multiply a unsigned 32-bit variable to a signed 32-bit variable and return the result as unsigned 32-bit.
 * The result is limited to UINT32_MAX (MINuint32_t) prevent overflows(underflows).
 *
 * \param     u32_X     Operand 1, unsigned 32-bit variable
 * \param     s32_Y     Operand 2, signed 32-bit variable
 * \return    uint32_t
 * \retval   (u32_X * s32_Y) saturated to uint32_t
 ***********************************************************************************************************************
 */
uint32_t Srvc_Mul_U32S32_U32(uint32_t u32_X, int32_t s32_Y)
{
  uint32_t u32_Res;
  uint64_t u64_Tmp;

  /* limitation to 0*/
  if (s32_Y <= 0) {
    u32_Res = 0;
  } else {
    /* interim u64_Tmp */
    u64_Tmp = ((uint64_t)u32_X) * ((uint64_t)s32_Y);

    /* limitation to MAYXuint32_t */
    if (u64_Tmp >= ((uint64_t)UINT32_MAX)) {
      u32_Res = UINT32_MAX;
    } else {
      /* regular expresion */
      u32_Res = ((uint32_t)u64_Tmp);
    }
  }
  return u32_Res;
}

/**
 ***********************************************************************************************************************
 * Srvc_Mul_U32U32_U32
 *
 * uint32_t uint32_t multiplication with uint32_t saturation.
 * multiply a unsigned 32-bit variable to a unsigned 32-bit variable and return the result as unsigned 32-bit.
 * The result is limited to UINT32_MAX (MINuint32_t) prevent overflows(underflows).
 *
 * \param     u32_X     Operand 1, unsigned 32-bit variable
 * \param     u32_Y     Operand 2, unsigned 32-bit variable
 * \return    uint32_t
 * \retval   (u32_X * u32_Y) saturated to uint32_t
 ***********************************************************************************************************************
 */
uint32_t Srvc_Mul_U32U32_U32(uint32_t u32_X, uint32_t u32_Y)
{
  uint32_t u32_Res;
  uint64_t u64_Tmp;

  /* interim u64_Tmp */
  u64_Tmp = ((uint64_t)u32_X) * ((uint64_t)u32_Y);

  /* limitation to UINT32_MAX */
  if (u64_Tmp >= ((uint64_t)UINT32_MAX)) {
    u32_Res = UINT32_MAX;
  } else {
    /* regular expression */
    u32_Res = ((uint32_t) u64_Tmp);
  }
  return u32_Res;
}

/*
 ***********************************************************************************************************************
 *
 * Multiplication
 * of two of values of 32bit length
 * with saturation to int32_t.
 *
 ***********************************************************************************************************************
 */

/**
 ***********************************************************************************************************************
 * Srvc_Mul_S32S32_S32
 *
 * int32_t int32_t multiplication with int32_t saturation.
 * multiply a signed 32-bit variable to a signed 32-bit variable and return the result as signed 32-bit.
 * The result is limited to INT32_MAX (INT32_MIN) prevent overflows(underflows).
 *
 * \param     s32_X     Operand 1, signed 32-bit variable
 * \param     s32_Y     Operand 2, signed 32-bit variable
 * \return    int32_t
 * \retval   (s32_X * s32_Y) saturated to int32_t
 ***********************************************************************************************************************
 */
int32_t Srvc_Mul_S32S32_S32(int32_t s32_X, int32_t s32_Y)
{
  int64_t s64_Tmp;
  bool b_Tmp, b_Tmp1;

  /*  interim s64_Tmp */
  s64_Tmp = ((int64_t)s32_X) * ((int64_t)s32_Y);
  b_Tmp = (s64_Tmp >= (int64_t)INT32_MAX);
  b_Tmp1 = s64_Tmp <= ((int32_t)INT32_MIN);
  /* limitation */
  s64_Tmp = ((b_Tmp ) ? ((int64_t)INT32_MAX ) :
    ((b_Tmp1) ? (INT32_MIN) : s64_Tmp) );

  return (int32_t)s64_Tmp;
}

/**
 ***********************************************************************************************************************
 * Srvc_Mul_U32S32_S32
 *
 * uint32_t int32_t multiplication with int32_t saturation.
 * multiply a unsigned 32-bit variable to a signed 32-bit variable and return the result as signed 32-bit.
 * The result is limited to INT32_MAX (INT32_MIN) prevent overflows(underflows).
 *
 * \param     u32_X     Operand 1, unsigned 32-bit variable
 * \param     s32_Y     Operand 2, signed 32-bit variable
 * \return    int32_t
 * \retval   (s32_X * u32_Y) saturated to int32_t
 ***********************************************************************************************************************
 */
int32_t Srvc_Mul_U32S32_S32(uint32_t u32_X, int32_t s32_Y)
{
  int32_t s32_Res;
  int64_t s64_Tmp;

  /* interim _tmp_s64 */
  s64_Tmp = ((int64_t)u32_X) * ((int64_t)s32_Y);

  /* limitation to MAint32 */
  if (s64_Tmp >= ((int64_t)INT32_MAX)) {
    s32_Res = INT32_MAX;
  } else if (s64_Tmp <= ((int32_t)INT32_MIN)) {
    /* limitation to INT32_MIN */
    s32_Res = INT32_MIN;
  } else {
    /* regular expression */
    s32_Res = ((int32_t) s64_Tmp);
  }
  return s32_Res;
}

/**
 ***********************************************************************************************************************
 * Srvc_Mul_U32U32_S32
 *
 * uint32_t uint32_t multiplication with int32_t saturation.
 * multiply a unsigned 32-bit variable to a unsigned 32-bit variable and return the result as signed 32-bit.
 * The result is limited to INT32_MAX (INT32_MIN) prevent overflows(underflows).
 *
 * \param     u32_X     Operand 1, unsigned 32-bit variable
 * \param     u32_Y     Operand 1, unsigned 32-bit variable
 * \return    int32_t
 * \retval    (u32_X * u32_Y) saturated to int32_t
 ***********************************************************************************************************************
 */
int32_t Srvc_Mul_U32U32_S32(uint32_t u32_X, uint32_t u32_Y)
{
  int32_t s32_Res;
  uint64_t u64_Tmp;

  /* interim u64_Tmp */
  u64_Tmp = ((uint64_t)u32_X) * ((uint64_t)u32_Y);

  /* limitation to INT32_MAX */
  if (u64_Tmp >= ((uint64_t) INT32_MAX)) {
    s32_Res = INT32_MAX;
  } else {
    /* regular expression */
    s32_Res = ((int32_t)u64_Tmp);
  }
  return s32_Res;
}

/*
 ***********************************************************************************************************************
 *
 *
 *
 * MUL DIV FUNCTIONS
 *
 *
 *
 ***********************************************************************************************************************
 */

/*
 ***********************************************************************************************************************
 *
 * Multiplication of two 32 bit variables and
 * Division by an other 32 bit variable
 * with saturation to int16_t
 *
 ***********************************************************************************************************************
 */

/**
 ***********************************************************************************************************************
 * Srvc_AverageArray_S16
 *
 * \brief Average calculation of u8_N values provided by array. Protection against overflow is done by algorithm.
 *
 * \param      *Array_pcs16    pointer to the int16_t-array, within the values X[u_Index] to average
 * \param      u8_N           length of the array
 * \return   int16_t
 * \retval   sum(X[u_Index]) / u8_N
 ***********************************************************************************************************************
 */
int16_t Srvc_AverageArray_S16(const int16_t * Array_pcs16, uint8_t u8_N)
{
  int32_t s32_Res;
  uint8_t u_Index;

  s32_Res = Array_pcs16[0];

  if (u8_N > 1) {
    for (u_Index = 1U; u_Index < ((uint8_t)(u8_N)); u_Index++) {
      s32_Res += (*(++Array_pcs16));
    }
    s32_Res /= ((int32_t)(u8_N));
  }

  return (int16_t)s32_Res;
}

/**
 ***********************************************************************************************************************
 *
 * Srvc_Average_S32S32_S32
 *
 * \brief The function calculates the average of two int32_t operands. Algorithm protects overflow.
 *
 * \param     s32_X     first operand
 * \param     s32_Y     second operand
 * \return  int32_t
 * \retval  (s32_X + s32_Y) / 2
 ***********************************************************************************************************************
 */
int32_t Srvc_Average_S32S32_S32(int32_t s32_X, int32_t s32_Y)
{
  int32_t s32_Res;

  s32_Res = (int32_t)(((int64_t)s32_X + (int64_t)s32_Y) / 2l);
  return s32_Res;
}

/*
 ***********************************************************************************************************************
 * Srvc_AverageArray_S32
 *
 * \brief Average calculation of u8_N values provided by array. Protection against overflow is done by algorithm.
 *
 * \param         *Array_pcs32    pointer to the int32_t, within the values X[u_Index] to average
 * \param         u8_N           length of the array
 * \return   int32_t
 * \retval   sum(X[u_Index]) / u8_N
 ***********************************************************************************************************************
 */
/*int32_t Srvc_AverageArray_S32 (const int32_t *Array_pcs32, uint8_t u8_N)
{
    int64_t s64_Tmp;
    uint   u_Index;

    s64_Tmp = Array_pcs32[0];

    if(u8_N > 1)
    {
        for(u_Index = 1U; u_Index <((uint)( u8_N)) ; u_Index++)
        {
            s64_Tmp += (*(++Array_pcs32));
        }
        s64_Tmp = (int64_t)Srvc_Div_S64S32_S32(s64_Tmp, (int32_t)u8_N);
    }

    return ((int32_t)s64_Tmp);
}*/

/**
 *********************************************************************************************************************
 *
 *  Srvc_AverageSliding_S16
 *
 * \brief The function calculates the new average of listed values, after a swap of one defined value.
 *
 *   Srvc_AvrgsldngS16_t x;
 *  int16_t a[32] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 *                   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, Avgd_Val ;
 *   x.ps16_Beg = &a[0];
 *   x.ps16_End = &a[31];
 *   x.ps16_Act = &a[0];
 *   x.u8_N = 32;
 *   x.s32_Sum = 0;
 *   s16_Inp = current value;
 *   Pointer increment will be done by the fumction itself
 *   Avgd_Val = Srvc_AverageSliding_S16 (&x,s16_Inp);
 * \param       *Struct_cpst            pointer to an Array of int16_t operands X[u_Index]
 * \param       s16_Inp                 value of a defined operand to swap
 * \param       s32_SampleCount
 * \param       s32_MaxSampleCount
 * \return  int16_t
 * \retval  sum(X[u_Index])/n           average of the listed int16_t operands past swap
 ***********************************************************************************************************************
 */
int16_t Srvc_AverageSliding_S16(
  Srvc_AvrgsldngS16_t * const Struct_cpst, int16_t s16_Inp,
  int32_t s32_SampleCount, int32_t s32_MaxSampleCount)
{
  int32_t s32_Tmp;
  int16_t s16_MovAvgVal = 0;

  /* calculate the new sum */
  Struct_cpst->s32_Sum =
    ((Struct_cpst->s32_Sum - ((int32_t) (*(Struct_cpst->ps16_Act)))) + ((int32_t) (s16_Inp)));

  /* swap the actual value (act) against the new one (Inp) */
  *Struct_cpst->ps16_Act = s16_Inp;

  /* compare references */
  if (Struct_cpst->ps16_Act == Struct_cpst->ps16_End) {
    /* close the  memory loop */
    Struct_cpst->ps16_Act = Struct_cpst->ps16_Beg;
  } else {
    /* actualize actual reference */
    (Struct_cpst->ps16_Act)++;
  }

  s32_Tmp = (Struct_cpst->s32_Sum / ((int32_t)(Struct_cpst->u8_N)));

  /** check if the samples reached the maximum sample value*/
  if (s32_SampleCount >= s32_MaxSampleCount) {
    /** return the averaged filtered value */
    s16_MovAvgVal = (int16_t)s32_Tmp;
  } else {
    /** return instantenous value*/
    s16_MovAvgVal = s16_Inp;
  }
  return (int16_t)(s16_MovAvgVal);
}

/*
 ***********************************************************************************************************************
 *
 * Srvc_AverageSliding_S32
 *
 * \brief The function calculates the new average of listed values, after a swap of one defined value. *     .
 *
 *
 * \param           Struct_cpst      pointer to an Array of int16_t operands
 * \param           Inp_s32          value of a defined operand to swap
 * \return
 * \retval  sum(X[u_Index])/n,                                 average of the listed int32_t operands past swap
 ***********************************************************************************************************************
*/
// int32_t Srvc_AverageSliding_S32 (Srvc_AvrgsldngS32_t *const Struct_cpst, int32_t Inp_s32)
//{
//
//     /* calculate the new sum */
//     Struct_cpst->s64_Sum = ((Struct_cpst->s64_Sum - ((int64_t) (*(Struct_cpst->act_ps32))))
//                                                         + ((int64_t) (Inp_s32)));
//
//     /* swap the actual value (act) against the new one (Inp) */
//     *Struct_cpst->act_ps32    = Inp_s32;
//
//     /* compare references */
//     if( Struct_cpst->act_ps32 == Struct_cpst->ps32_End )
//     {
//         /* close the  memory loop */
//         Struct_cpst->act_ps32 = Struct_cpst->ps32_Beg;
//     }
//     else
//     {
//         /* actualize actual reference */
//         (Struct_cpst->ps32_Act)++;
//     }
//
//     return (Srvc_Div_S64S32_S32(Struct_cpst->s64_Sum, (int32_t)Struct_cpst->u8_N));
//
//}

/**
 ***********************************************************************************************************************
 * Srvc_Mul_S32S32_S64
 *
 * int32_t int32_t multiplication with int64_t result.
 * multiply a signed 32-bit variable to a signed 32-bit variable and return the result as signed 64-bit.
 *
 *
 * \param     s32_X         Operand 1, signed 32-bit variable
 * \param     s32_Y         Operand 2, signed 32-bit variable
 * \return   (s32_X * s32_Y) saturated to int64_t
 ***********************************************************************************************************************
 */
int64_t Srvc_Mul_S32S32_S64(int32_t s32_X, int32_t s32_Y)
{
  return (int64_t)s32_X * s32_Y;
}

/**
 ***********************************************************************************************************************
 * Srvc_Mul_U32U32_U64
 *
 * uint32_t uint32_t multiplication with uint64_t result.
 * multiply a signed 32-bit variable to a signed 32-bit variable and return the result as unsigned 64-bit.
 *
 * \param     u32_X         Operand 1, unsigned 32-bit variable
 * \param     u32_Y         Operand 1, unsigned 32-bit variable
 * \return   (u32_X * u32_Y) saturated to uint64_t
 ***********************************************************************************************************************
 */
uint64_t Srvc_Mul_U32U32_U64(uint32_t u32_X, uint32_t u32_Y)
{
  return (uint64_t)u32_X * u32_Y;
}

/*
 **********************************************************************************************************************
 *
 * Limiter function
 *
 **********************************************************************************************************************
 */


/**
 **********************************************************************************************************************
 * Srvc_TypeLimiter_S32_S16
 *
 * \brief Limitation of a int32_t value to int16_t.
 *
 * The input variable is limited thus the return value is between INT16_MIN and UINT16_MAX.
 *
 * \param      s32_X   Value to be limited
 * \return   int16_t          The value of s32_X limited to int16_t range
 **********************************************************************************************************************
 */
int16_t Srvc_TypeLimiter_S32_S16(int32_t s32_X)
{
  return (int16_t) ( (s32_X <= (int32_t) INT16_MIN) ? (INT16_MIN) : (
           (s32_X >= (int32_t) UINT16_MAX) ? (UINT16_MAX) : (s32_X)
  ) );
}

/**
 **********************************************************************************************************************
 * Srvc_TypeLimiter_S32_U16
 *
 * \brief Limitation of a int32_t value to uint16_t.
 *
 * The input variable is limited thus the return value is between MINuint16_t and UINT16_MAX.
 *
 * \param     s32_X   Value to be limited
 * \return   uint16_t         The value of s32_X limited to uint16_t range
 **********************************************************************************************************************
 */
uint16_t Srvc_TypeLimiter_S32_U16(int32_t s32_X)
{
  return (uint16_t) ( (s32_X <= (int32_t) 0) ? (0) : (
           (s32_X >= (int32_t) UINT16_MAX) ? (UINT16_MAX) : (s32_X)
  ) );
}

/**
 **********************************************************************************************************************
 * Srvc_TypeLimiter_S32_U32
 *
 * \brief Limitation of a int32_t value to uint32_t.
 *
 * The input variable is limited thus the return value is not smaller than MINuint32_t.
 *
 * \param      s32_X   Value to be limited
 * \return   uint32_t          The limited value of s32_X
 **********************************************************************************************************************
 */
uint32_t Srvc_TypeLimiter_S32_U32(int32_t s32_X)
{
  return (uint32_t)( (s32_X <= (int32_t) 0) ? (0) : ((uint32_t)s32_X));
}

/**
 **********************************************************************************************************************
 * Srvc_TypeLimiter_U32_U16
 *
 * \brief Limitation of a uint32_t value to uint16_t.
 *
 * The input variable is limited thus the return value is not greater than UINT16_MAX.
 *
 * \param      u32_X   Value to be limited
 * \return   uint16_t          The value of u32_X limited to uint16_t range
 **********************************************************************************************************************
 */
uint16_t Srvc_TypeLimiter_U32_U16(uint32_t u32_X)
{
  return (uint16_t)( (u32_X >= (uint32_t) UINT16_MAX) ? (UINT16_MAX) : (u32_X));
}

/*
 ***********************************************************************************************************************
 *
 *
 *
 * ARITHMETIC COUPLED MULTIPLICATION AND DIVISION with 32 Bit and 16 BIT return value.
 *
 *
 *
 ***********************************************************************************************************************
 */


/**
 ***********************************************************************************************************************
 * Srvc_MulDiv_S32S32S32_S32
 *
 * \brief Multiplies two int32_t variables, divides the interim value by a third one and limits the result to a int16_t
 *
 * \param     s32_X         Operand 1, signed 32-bit variable
 * \param     s32_Y         Operand 2, signed 32-bit variable
 * \param     s32_Z         Operand 3, signed 32-bit variable
 * \return   int32_t
 * \retval   ((u32_X * u32_Y) / u32_Z )saturated to int32_t
 *
 ***********************************************************************************************************************
 */
int32_t Srvc_MulDiv_S32S32S32_S32(int32_t s32_X, int32_t s32_Y, int32_t s32_Z)
{
  return Srvc_Div_S64S32_S32(Srvc_Mul_S32S32_S64(s32_X, s32_Y), s32_Z);
}

/**
 ***********************************************************************************************************************
 * Srvc_MulDiv_S32S32S32_S16
 *
 * \brief Multiplies two int32_t variables, divides the interim value by a third one and limits the result to a int16_t
 *
 * \param     s32_X         Operand 1, signed 32-bit variable
 * \param     s32_Y         Operand 2, signed 32-bit variable
 * \param     s32_Z         Operand 3, signed 32-bit variable
 * \return   int16_t
 * \retval   ((u32_X * u32_Y) / u32_Z )saturated to int16_t
 *
 ***********************************************************************************************************************
 */
int16_t Srvc_MulDiv_S32S32S32_S16(int32_t s32_X, int32_t s32_Y, int32_t s32_Z)
{
  return Srvc_TypeLimiter_S32_S16(Srvc_MulDiv_S32S32S32_S32(s32_X, s32_Y, s32_Z));
}

/**
 ***********************************************************************************************************************
 * Srvc_MulDiv_U32U32U32_U32
 *
 * \brief Multiplies two uint32_t variables, divides the interim value by a third one and limits the result to a uint32_t
 *
 * \param     u32_X         Operand 1, unsigned 32-bit variable
 * \param     u32_Y         Operand 2, unsigned 32-bit variable
 * \param     u32_Z         Operand 3, unsigned 32-bit variable
 * \return   uint32_t
 * \retval   ((u32_X * u32_Y) / u32_Z )saturated to uint32_t
 *
 ***********************************************************************************************************************
 */
uint32_t Srvc_MulDiv_U32U32U32_U32(uint32_t u32_X, uint32_t u32_Y, uint32_t u32_Z)
{
  return Srvc_Div_U64U32_U32(Srvc_Mul_U32U32_U64(u32_X, u32_Y), u32_Z);
}

/**
 ***********************************************************************************************************************
 * Srvc_MulDiv_S32S32S32_U16
 *
 * \brief Multiplies two int32_t variables, divides the interim value by a third one and limits the result to a int16_t
 *
 * \param     s32_X         Operand 1, signed 32-bit variable
 * \param     s32_Y         Operand 2, signed 32-bit variable
 * \param     s32_Z         Operand 3, signed 32-bit variable
 * \return   uint16_t
 * \retval   ((u32_X * u32_Y)  /  u32_Z ) saturated to uint16_t
 *
 ***********************************************************************************************************************
 */
uint16_t Srvc_MulDiv_S32S32S32_U16(int32_t s32_X, int32_t s32_Y, int32_t s32_Z)
{
  return Srvc_TypeLimiter_S32_U16(Srvc_MulDiv_S32S32S32_S32(s32_X, s32_Y, s32_Z));
}

/**
 ***********************************************************************************************************************
 * Srvc_MulDiv_U32U32U32_U16
 *
 * \brief Multiplies two uint32_t variables, dividesthe interim value by a third one and limits the result to an uint16_t
 *
 * \param     u32_X         Operand 1, unsigned 32-bit variable
 * \param     u32_Y         Operand 2, unsigned 32-bit variable
 * \param     u32_Z         Operand 3, unsigned 32-bit variable
 * \return   uint16_t
 * \retval   ((u32_X * u32_Y)  /  u32_Z )saturated to uint16_t
 *
 ***********************************************************************************************************************
 */
uint16_t Srvc_MulDiv_U32U32U32_U16(uint32_t u32_X, uint32_t u32_Y, uint32_t u32_Z)
{
  return Srvc_TypeLimiter_U32_U16(Srvc_MulDiv_U32U32U32_U32(u32_X, u32_Y, u32_Z));
}
