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

/******************************************************************************/
/* DOCUMENTATION                                                              */
/******************************************************************************/
/** \file          division_library.c 
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

/******************************************************************************/
/* PRIVATE TYPE DEFINITIONS                                                   */
/******************************************************************************/
typedef struct
{
#if ((defined (HIGH_BYTE_FIRST)) && (HIGH_BYTE_FIRST))
  uint32 h;
  uint32 l;
#else
  uint32_t l;
  uint32_t h;
#endif
} uint64s;

typedef union {
  uint64_t u64;
  uint64s u64s;
} uint64u;

/******************************************************************************/
/* PUBLIC FUNCTION DEFINITIONS                                                */
/******************************************************************************/

/*
 ***********************************************************************************************************************
 *
 * List of Functions
 *
 *                          Srvc_Div_S32S32_S32,     Srvc_Div_S32S32_S16,
 *                          Srvc_Div_U32S32_S32,     Srvc_Div_U32S32_S16,
 *                          Srvc_Div_S32U32_S32,     Srvc_Div_S32U32_S16,
 *                          Srvc_Div_U32U32_S32,     Srvc_Div_U32U32_S16,
 *                          Srvc_Div_S32S32_U32,     Srvc_Div_S32S32_U16,
 *                          Srvc_Div_U32S32_U32,     Srvc_Div_U32S32_U16,
 *                          Srvc_Div_S32U32_U32,     Srvc_Div_S32U32_U16,
 *                          Srvc_Div_U32U32_U32,     Srvc_Div_U32U32_U16,
 *                          Srvc_Div_S64S32_S32,     Srvc_Div_U64U32_U32
 *
 ***********************************************************************************************************************
 */


/*
 ***********************************************************************************************************************
 *
 *
 *
 * ARITHMETIC DIVISION with 32 Bit return value.
 *
 *
 *
 ***********************************************************************************************************************
 */

/**
 ***********************************************************************************************************************
 * Srvc_Div_U64U32_U32
 *
 * \brief uint64_t uint32_t division with uint32_t saturation and check on divide by zero.
 *
 * Divide an unsigned 64-bit variable by a unsigned 32-bit variable and return the result as unsigned 32-bit varaible.
 * The result is limited to UINT32_MAX (MINuint32_t) to prevent overflow (underflow).
* Note, this function is used in all other 64bit divisor variants.
 *
 * \param      X_u64                          Operand1, unsigned 64-bit variable
 * \param      u32_Y                          Operand2, unsigned 32-bit variable
 * \return     (s64_X / u32_Y)                Result,  unsigned 32-bit variable
 *
 ***********************************************************************************************************************
 */
uint32_t Srvc_Div_U64U32_U32(uint64_t X_u64, uint32_t u32_Y)
{
  uint64u tmp_u64s;
  uint64_t u64_Res = 0;
  uint32_t u32_Tmp;
  uint8_t i = 0;

  /* create union */
  tmp_u64s.u64 = X_u64;


  /* avoid zero divisor  */
  if (u32_Y == 0ul) {
    if (X_u64 == 0) {
      /* 0/0 =1 */
      u64_Res = 1;
    } else {
      /* limitation of result in case of a zero divisor */
      u64_Res = UINT32_MAX;
    }
  } else if (u32_Y > (uint32_t)0X7FFFFFFF) {
    /* calculate the interim result */
    u32_Tmp = tmp_u64s.u64s.h;
    u64_Res = ((uint64_t) u32_Tmp);

    /* calculate the rest */
    tmp_u64s.u64 -= ((uint64_t) u32_Tmp) * ((uint64_t) u32_Y);

    /* as long as the high Bytes are filled */
    while (tmp_u64s.u64s.h > 0) {
      /* calculate the interim result */
      u32_Tmp = tmp_u64s.u64s.h;
      u64_Res += ((uint64_t) u32_Tmp);

      /* calculate the rest */
      tmp_u64s.u64 -= ((uint64_t) u32_Tmp) * ((uint64_t) u32_Y);
    }
    u32_Tmp = tmp_u64s.u64s.l / u32_Y;
    u64_Res += ((uint64_t) u32_Tmp);

    /* limitation  */
    u64_Res = ( (u64_Res > ((uint64_t)UINT32_MAX)) ? ((uint64_t)UINT32_MAX) : u64_Res );
  } else {
    /* divide the high bytes */
    u32_Tmp = tmp_u64s.u64s.h / u32_Y;

    /* calculate the interim result */
    u64_Res = u64_Res + u32_Tmp;

    /* calculate the rest */
    tmp_u64s.u64s.h -= u32_Tmp * u32_Y;

    if (u64_Res < ((uint64_t)UINT32_MAX) ) {
      while (i < 32) {
        /* go just one bit to the right */
        u64_Res <<= 1;
        tmp_u64s.u64 <<= 1;

        /* modulo */
        u32_Tmp = tmp_u64s.u64s.h / u32_Y;

        /*  oddment  */
        tmp_u64s.u64s.h -= u32_Tmp * u32_Y;

        /* new interim result */
        u64_Res = u64_Res + ((uint64_t)u32_Tmp);

        /* limit your further efforts in case of maximum value */
        if (u64_Res >= ((uint64_t)UINT32_MAX) ) {
          i = 32;
        }
        i++;
      }
    }
    /* limitation  */
    u64_Res = ( (u64_Res > ((uint64_t)UINT32_MAX)) ? ((uint64_t)UINT32_MAX) : u64_Res );
  }

  return (uint32_t) u64_Res;
}

/**
 ***********************************************************************************************************************
 * Srvc_Div_S32S32_S32
 *
 * \brief int32_t int32_t division with int32_t saturation and check on divide by zero.
 *
 * Divide a signed 32-bit variable by a signed 32-bit variable and return the result as signed 32-bit.
 * The result is limited to INT32_MAX (INT32_MIN) prevent overflows(underflows).
 *
 * \param      s32_X                      Operand1, signed   32-bit variable
 * \param      s32_Y                      Operand2, signed   32-bit variable
 * \return     (s32_X / s32_Y)            Result,    signed   32-bit
 ***********************************************************************************************************************
 */
int32_t Srvc_Div_S32S32_S32(int32_t s32_X, int32_t s32_Y)
{
  int32_t s32_Res;

  /* divide by zero */
  if (s32_Y == 0) {
    /* limitation */
    s32_Res = ( (s32_X >= 0) ? (INT32_MAX) : (INT32_MIN));
  } else {
    /* special case */
    if ( (s32_Y == -1) && (s32_X == INT32_MIN) ) {
      s32_Res = INT32_MAX;
    } else {
      /* regular */
      s32_Res = (s32_X / s32_Y);
    }
  }
  return s32_Res;
}

/**
 ***********************************************************************************************************************
 * Srvc_Div_U32S32_S32
 *
 * \brief uint32_t int32_t division with int32_t saturation and check on divide by zero.
 *
 * Divide a unsigned 32-bit variable by a signed 32-bit variable and return the result as signed 32-bit.
 * The result is limited to INT32_MAX (INT32_MIN) prevent overflows(underflows).
 *
 * \param      u32_X                      Operand1, unsigned 32-bit variable
 * \param      s32_Y                      Operand2, signed   32-bit variable
 * \return     (u32_X / s32_Y)            Result,    signed   32-bit
 ***********************************************************************************************************************
 */
int32_t Srvc_Div_U32S32_S32(uint32_t u32_X, int32_t s32_Y)
{
  int32_t s32_Res;

  /* neutal element */
  if (s32_Y == 1) {
    /* regular */
    if (u32_X <= ((uint32_t) INT32_MAX) ) {
      s32_Res = ((int32_t) u32_X);
    } else {
      /* limitation */
      s32_Res = INT32_MAX;
    }
  } else if (s32_Y == 0) {
    /* divide by zero */
    /* limitation */
    s32_Res = INT32_MAX;
  } else {
    /* regular */
    if (u32_X <= ((uint32_t) INT32_MAX) ) {
      s32_Res = ( ((int32_t) u32_X) / s32_Y);
    } else if (s32_Y > 0) {
      /* regular - positive */
      s32_Res = ((int32_t) ( u32_X / ((uint32_t) s32_Y)) );
    } else {  /* regular - negative */
      /* special case */
      if (s32_Y == INT32_MIN) {
        s32_Res = (-((int32_t)  ( u32_X / (((uint32_t) INT32_MAX) + 1) )  ));
      } else if ( (u32_X == UINT32_MAX) && (s32_Y == -1) ) {
        s32_Res = INT32_MIN;
      } else {
        /* regular */
        s32_Res = ((int32_t) ( u32_X / ((uint32_t) (-s32_Y))) );
      }
    }
  }
  return s32_Res;
}

/**
 ***********************************************************************************************************************
 * Srvc_Div_S32U32_S32
 *
 * \brief int32_t uint32_t division with int32_t saturation and check on divide by zero.
 *
 * Divide a signed 32-bit variable by a unsigned 32-bit variable and return the result as signed 32-bit.
 * The result is limited to INT32_MAX (INT32_MIN) prevent overflows(underflows).
 *
 * \param      s32_X                      Operand1, signed   32-bit variable
 * \param      u32_Y                      Operand2, unsigned 32-bit variable
 * \return     (s32_X / u32_Y)            Result,    signed   32-bit
 ***********************************************************************************************************************
 */
int32_t Srvc_Div_S32U32_S32(int32_t s32_X, uint32_t u32_Y)
{
  int32_t s32_Res;

  if (u32_Y > INT32_MAX) {
    /* special case */
    if ((s32_X == INT32_MIN) && (u32_Y == ((uint32_t) INT32_MAX + 1))) {
      s32_Res = -1;
    } else {
      /* denominator too big */
      s32_Res = 0;
    }
  } else {
    /* divide by zero */
    if (u32_Y == 0) {
      /* limitation */
      s32_Res = (s32_X < 0) ? (INT32_MIN) : (INT32_MAX);
    } else {
      /* regular */
      s32_Res = s32_X / ((int32_t) u32_Y);
    }
  }
  return s32_Res;
}

/**
 ***********************************************************************************************************************
 * Srvc_Div_U32U32_S32
 *
 * \brief int32_t uint32_t division with int32_t saturation and check on divide by zero.
 *
 * Divide a unsigned 32-bit variable by a unsigned 32-bit variable and return the result as signed 32-bit.
 * The result is limited to INT32_MAX (INT32_MIN) prevent overflows(underflows).
 *
 * \param      u32_X                      Operand1, unsigned 32-bit variable
 * \param      u32_Y                      Operand2, unsigned 32-bit variable
 * \return     (u32_X / u32_Y)            Result,    signed   32-bit
 ***********************************************************************************************************************
 */
int32_t Srvc_Div_U32U32_S32(uint32_t u32_X, uint32_t u32_Y)
{
  int32_t s32_Res;
  uint32_t u32_Res;

  /* divide by zero */
  if (u32_Y == 0) {
    /* limitation */
    s32_Res = INT32_MAX;
  } else {
    /* regular */
    u32_Res = (u32_X / u32_Y);

    /* limitation */
    s32_Res = ( u32_Res > ((uint32_t) INT32_MAX) ) ? (INT32_MAX) : ((int32_t) u32_Res);
  }
  return s32_Res;
}

/**
 ***********************************************************************************************************************
 * Srvc_Div_S32S32_U32
 *
 * \brief int32_t int32_t division with uint32_t saturation and check on divide by zero.
 *
 * Divide a signed 32-bit variable by a signed 32-bit variable and return the result as unsigned 32-bit.
 * The result is limited to UINT32_MAX (MINuint32_t) prevent overflows(underflows).
 *
 * \param      s32_X                      Operand1, signed   32-bit variable
 * \param      s32_Y                      Operand2, signed   32-bit variable
 * \return     (s32_X / s32_Y)            Result,    unsigned 32-bit
 ***********************************************************************************************************************
 */
uint32_t Srvc_Div_S32S32_U32(int32_t s32_X, int32_t s32_Y)
{
  uint32_t u32_Res;
  int32_t s32_Res;

  /* divide by zero */
  if (s32_Y == 0) {
    /* limitation */
    u32_Res = ( (s32_X >= 0) ? (UINT32_MAX) : (0));
  } else if ( (s32_Y == -1) && (s32_X == INT32_MIN) ) {
    /* special case */
    u32_Res = ( ((uint32_t) INT32_MAX) + 1 );
  } else {
    /* regular */
    s32_Res = (s32_X / s32_Y);

    /* limitation */
    u32_Res = (s32_Res < 0) ? (0) : ((uint32_t) s32_Res);
  }
  return u32_Res;
}

/**
 ***********************************************************************************************************************
 * Srvc_Div_S32U32_U32
 *
 * \brief int32_t uint32_t division with uint32_t saturation and check on divide by zero.
 *
 * Divide a signed 32-bit variable by a unsigned 32-bit variable and return the result as unsigned 32-bit.
 * The result is limited to UINT32_MAX (MINuint32_t) prevent overflows(underflows).
 *
 * \param      s32_X                      Operand1, signed   32-bit variable
 * \param      u32_Y                      Operand2, unsigned 32-bit variable
 * \return     (s32_X / u32_Y)            Result,    unsigned 32-bit
 **********************************************************************************************************************
 */
uint32_t Srvc_Div_S32U32_U32(int32_t s32_X, uint32_t u32_Y)
{
  uint32_t u32_Res;

  /* divide by zero */
  if (s32_X < 0) {
    /* limitation */
    u32_Res = 0;
  } else {
    /* limitation */
    u32_Res = (u32_Y == 0) ? (UINT32_MAX) : ( ((uint32_t) s32_X) / u32_Y );
  }
  return u32_Res;
}

/**
 ***********************************************************************************************************************
 * Srvc_Div_U32S32_U32
 *
 * \brief uint32_t int32_t division with uint32_t saturation and check on divide by zero.
 *
 * Divide a unsigned 32-bit variable by a signed 32-bit variable and return the result as unsigned 32-bit.
 * The result is limited to UINT32_MAX (MINuint32_t) prevent overflows(underflows).
 *
 * \param      u32_X                      Operand1, unsigned 32-bit variable
 * \param      s32_Y                      Operand2, signed   32-bit variable
 * \return     (u32_X / s32_Y)            Result,    unsigned 32-bit
 ***********************************************************************************************************************
 */
uint32_t Srvc_Div_U32S32_U32(uint32_t u32_X, int32_t s32_Y)
{
  uint32_t u32_Res;

  /* divide by zero */
  if (s32_Y < 0) {
    /* limitation */
    u32_Res = 0;
  } else {
    /* limitation */
    u32_Res = (s32_Y == 0) ? (UINT32_MAX) : ( u32_X / ((uint32_t) s32_Y) );
  }
  return u32_Res;
}

/**
 ***********************************************************************************************************************
 * Srvc_Div_U32U32_U32
 *
 * \brief uint32_t uint32_t division with uint32_t saturation and check on divide by zero.
 *
 * Divide a unsigned 32-bit variable by a unsigned 32-bit variable and return the result as unsigned 32-bit.
 * The result is limited to UINT32_MAX (MINuint32_t) prevent overflows(underflows).
 *
 * \param      u32_X                      Operand1, unsigned 32-bit variable
 * \param      u32_Y                      Operand2, unsigned 32-bit variable
 * \return     (u32_X / u32_Y)            Result,    unsigned 32-bit
 ***********************************************************************************************************************
 */
uint32_t Srvc_Div_U32U32_U32(uint32_t u32_X, uint32_t u32_Y)
{
  uint32_t u32_Res;

  /* divide by zero */
  if (u32_Y == 0) {
    /* limitation */
    u32_Res = UINT32_MAX;
  } else {
    /* regular */
    u32_Res = (u32_X / u32_Y);
  }
  return u32_Res;
}

/*
 ***********************************************************************************************************************
 *
 *
 *
 * ARITHMETIC DIVISION with 16 Bit return value.
 *
 *
 *
 ***********************************************************************************************************************
 */

/**
 ***********************************************************************************************************************
 * Srvc_Div_S32S32_S16
 *
 * \brief int32_t int32_t division with int16_t saturation and check on divide by zero.
 *
 * Divide a signed 32-bit variable by a signed 32-bit variable and return the result as signed 16-bit.
 * The result is limited to INT16_MAX (INT16_MIN) prevent overflows(underflows).
 *
 * \param      s32_X                      Operand1, signed   32-bit variable
 * \param      s32_Y                      Operand2, signed   32-bit variable
 * \return     (s32_X / s32_Y)            Result,    signed   16-bit
 ***********************************************************************************************************************
 */
int16_t Srvc_Div_S32S32_S16(int32_t s32_X, int32_t s32_Y)
{
  int32_t s32_Res;

  /* divide by zero */
  if (s32_Y == 0) {
    /* limitation */
    s32_Res = ( (s32_X >= 0) ? (INT16_MAX) : (INT16_MIN));
  } else {
    /* special case */
    if ( (s32_Y == -1) && (s32_X == INT32_MIN) ) {
      s32_Res = INT16_MAX;
    } else {
      /* regular */
      s32_Res = (s32_X / s32_Y);

      /* limitation */
      s32_Res = (s32_Res > INT16_MAX) ? (INT16_MAX) : (s32_Res);
      s32_Res = (s32_Res < INT16_MIN) ? (INT16_MIN) : (s32_Res);
    }
  }
  return (int16_t) s32_Res;
}

/**
 ***********************************************************************************************************************
 * Srvc_Div_U32S32_S16
 *
 * \brief uint32_t int32_t division with int16_t saturation and check on divide by zero.
 *
 * Divide a unsigned 32-bit variable by a signed 32-bit variable and return the result as signed 16-bit.
 * The result is limited to INT16_MAX (INT16_MIN) prevent overflows(underflows).
 *
 * \param      u32_X                      Operand1, unsigned 32-bit variable
 * \param      s32_Y                      Operand2, signed   32-bit variable
 * \return     (u32_X / s32_Y)            Result,    signed   16-bit
 ***********************************************************************************************************************
 */
int16_t Srvc_Div_U32S32_S16(uint32_t u32_X, int32_t s32_Y)
{
  int32_t s32_Res;

  /* neutal element */
  if (s32_Y == 1) {
    /* regular */
    if (u32_X <= ((uint32_t) INT32_MAX) ) {
      s32_Res = ((int32_t) u32_X);
    } else {
      /* limitation */
      s32_Res = INT32_MAX;
    }
  } else if (s32_Y == 0) {
    /* divide by zero */
    /* limitation */
    s32_Res = INT32_MAX;
  } else {
    /* regular */
    if (u32_X <= ((uint32_t) INT32_MAX) ) {
      s32_Res = ( ((int32_t) u32_X) / s32_Y);
    } else if (s32_Y > 0) {
      /* regular - positive */
      s32_Res = ((int32_t) ( u32_X / ((uint32_t) s32_Y)) );
    } else {
      /* regular - negative */
      /* special case */
      if (s32_Y == INT32_MIN) {
        s32_Res = (-((int32_t)  ( u32_X / (((uint32_t) INT32_MAX) + 1) )  ));
      } else if ( (u32_X == UINT32_MAX) && (s32_Y == -1) ) {
        /* special case */
        s32_Res = INT32_MIN;
      } else {
        /* regular */
        s32_Res = ((int32_t) ( u32_X / ((uint32_t) (-s32_Y))) );
      }
    }
  }

  /* limitation */
  s32_Res = (s32_Res > INT16_MAX) ? (INT16_MAX) : (s32_Res);
  s32_Res = (s32_Res < INT16_MIN) ? (INT16_MIN) : (s32_Res);

  return (int16_t) s32_Res;
}

/**
 ***********************************************************************************************************************
 * Srvc_Div_S32U32_S16
 *
 * \brief int32_t uint32_t division with int16_t saturation and check on divide by zero.
 *
 * Divide a signed 32-bit variable by a unsigned 32-bit variable and return the result as signed 16-bit.
 * The result is limited to INT16_MAX (INT16_MIN) prevent overflows(underflows).
 *
 * \param      s32_X                      Operand1, signed   32-bit variable
 * \param      u32_Y                      Operand2, unsigned 32-bit variable
 * \return     (s32_X / u32_Y)            Result,    signed   16-bit
 ***********************************************************************************************************************
 */
int16_t Srvc_Div_S32U32_S16(int32_t s32_X, uint32_t u32_Y)
{
  int32_t s32_Res;

  if (u32_Y > INT32_MAX) {
    /* special case */
    if ((s32_X == INT32_MIN) && (u32_Y == ((uint32_t) INT32_MAX + 1))) {
      s32_Res = -1;
    } else {
      /* denominator too big */
      s32_Res = 0;
    }
  } else {
    /* divide by zero */
    if (u32_Y == 0) {
      /* limitation */
      s32_Res = (s32_X < 0) ? (INT16_MIN) : (INT16_MAX);
    } else {
      /* regular */
      s32_Res = s32_X / ((int32_t) u32_Y);

      /* limitation */
      s32_Res = (s32_Res > INT16_MAX) ? (INT16_MAX) : (s32_Res);
      s32_Res = (s32_Res < INT16_MIN) ? (INT16_MIN) : (s32_Res);
    }
  }
  return (int16_t) s32_Res;
}

/**
 ***********************************************************************************************************************
 * Srvc_Div_U32U32_S16
 *
 * \brief int32_t uint32_t division with int16_t saturation and check on divide by zero.
 *
 * Divide a unsigned 32-bit variable by a unsigned 32-bit variable and return the result as signed 16-bit.
 * The result is limited to INT16_MAX (INT16_MIN) prevent overflows(underflows).
 *
 * \param      u32_X                      Operand1, unsigned 32-bit variable
 * \param      u32_Y                      Operand2, unsigned 32-bit variable
 * \return     (u32_X / u32_Y)            Result,    signed   16-bit
 ***********************************************************************************************************************
 */
int16_t Srvc_Div_U32U32_S16(uint32_t u32_X, uint32_t u32_Y)
{
  int32_t s32_Res;
  uint32_t u32_Res;

  /* divide by zero */
  if (u32_Y == 0) {
    /* limitation */
    s32_Res = INT16_MAX;
  } else {
    /* regular */
    u32_Res = (u32_X / u32_Y);

    /* limitation */
    s32_Res = ( u32_Res > ((uint32_t) INT16_MAX) ) ? (INT16_MAX) : ((int32_t) u32_Res);
  }
  return (int16_t) s32_Res;
}

/**
 ***********************************************************************************************************************
 * Srvc_Div_S32S32_U16
 *
 * \brief int32_t int32_t division with uint16_t saturation and check on divide by zero.
 *
 * Divide a signed 32-bit variable by a signed 32-bit variable and return the result as unsigned 16-bit.
 * The result is limited to UINT16_MAX (MINuint16_t) prevent overflows(underflows).
 *
 * \param      s32_X                      Operand1, signed   32-bit variable
 * \param      s32_Y                      Operand2, signed   32-bit variable
 * \return     (s32_X / s32_Y)            Result,    unsigned 16-bit
 ***********************************************************************************************************************
 */
uint16_t Srvc_Div_S32S32_U16(int32_t s32_X, int32_t s32_Y)
{
  uint32_t u32_Res;
  int32_t s32_Res;

  /* divide by zero */
  if (s32_Y == 0) {
    /* limitation */
    u32_Res = ( (s32_X >= 0) ? ((uint32_t) UINT16_MAX) : ((uint32_t) 0));
  } else if ( (s32_Y == -1) && (s32_X == INT32_MIN) ) {
    /* special case */
    u32_Res = ((uint32_t) UINT16_MAX);
  } else {
    /* regular */
    s32_Res = (s32_X / s32_Y);

    /* limitation */
    u32_Res = ( s32_Res < ((int32_t) 0) ) ? ((uint32_t) 0) : ((uint32_t) s32_Res);
    u32_Res = ( s32_Res > ((int32_t) UINT16_MAX) ) ? ((uint32_t) UINT16_MAX) : (u32_Res);
  }
  return (uint16_t) u32_Res;
}

/**
 ***********************************************************************************************************************
 * Srvc_Div_U32S32_U16
 *
 * \brief uint32_t int32_t division with uint16_t saturation and check on divide by zero.
 *
 * Divide a unsigned 32-bit variable by a signed 32-bit variable and return the result as unsigned 16-bit.
 * The result is limited to UINT16_MAX (MINuint16_t) prevent overflows(underflows).
 *
 * \param      u32_X                      Operand1, unsigned 32-bit variable
 * \param      s32_Y                      Operand2, signed   32-bit variable
 * \return     (u32_X / s32_Y)            Result,    unsigned 16-bit
 ***********************************************************************************************************************
 */
uint16_t Srvc_Div_U32S32_U16(uint32_t u32_X, int32_t s32_Y)
{
  uint32_t u32_Res;

  /* divide by zero */
  if (s32_Y < 0) {
    /* limitation */
    u32_Res = 0;
  } else {
    /* limitation */
    u32_Res = (s32_Y == 0) ? (UINT16_MAX) : ( u32_X / ((uint32_t) s32_Y) );
    u32_Res = ( u32_Res > ((uint32_t) UINT16_MAX) ) ? ((uint32_t) UINT16_MAX) : (u32_Res);
  }
  return (uint16_t) u32_Res;
}

/**
 ***********************************************************************************************************************
 * Srvc_Div_S32U32_U16
 *
 * \brief int32_t uint32_t division with uint16_t saturation and check on divide by zero.
 *
 * Divide a signed 32-bit variable by a unsigned 32-bit variable and return the result as unsigned 16-bit.
 * The result is limited to UINT16_MAX (MINuint16_t) prevent overflows(underflows).
 *
 * \param      s32_X                      Operand1, signed   32-bit variable
 * \param      u32_Y                      Operand2, unsigned 32-bit variable
 * \return     (s32_X / u32_Y)            Result,    unsigned 16-bit
 ***********************************************************************************************************************
 */
uint16_t Srvc_Div_S32U32_U16(int32_t s32_X, uint32_t u32_Y)
{
  uint32_t u32_Res;

  /* divide by zero */
  if (s32_X < 0) {
    /* limitation */
    u32_Res = 0;
  } else {
    /* limitation */
    u32_Res = (u32_Y == 0) ? (UINT16_MAX) : ( ((uint32_t) s32_X) / u32_Y );
    u32_Res = ( u32_Res > ((uint32_t) UINT16_MAX) ) ? ((uint32_t) UINT16_MAX) : (u32_Res);
  }
  return (uint16_t) u32_Res;
}

/**
 ***********************************************************************************************************************
 * Srvc_Div_U32U32_U16
 *
 * \brief uint32_t uint32_t division with uint16_t saturation and check on divide by zero.
 *
 * Divide a unsigned 32-bit variable by a unsigned 32-bit variable and return the result as unsigned 16-bit.
 * The result is limited to UINT16_MAX (MINuint16_t) prevent overflows(underflows).
 *
 * \param      u32_X                      Operand1, unsigned 32-bit variable
 * \param      u32_Y                      Operand2, unsigned 32-bit variable
 * \return     (u32_X / u32_Y)            Result,    unsigned 16-bit
 ***********************************************************************************************************************
 */
uint16_t Srvc_Div_U32U32_U16(uint32_t u32_X, uint32_t u32_Y)
{
  uint32_t u32_Res;

  /* divide by zero */
  if (u32_Y == 0) {
    /* limitation */
    u32_Res = UINT16_MAX;
  } else {
    /* regular */
    u32_Res = (u32_X / u32_Y);

    /* limitation */
    u32_Res = ( u32_Res > ((uint32_t) UINT16_MAX) ) ? ((uint32_t) UINT16_MAX) : (u32_Res);
  }
  return (uint16_t) u32_Res;
}

/**
 ***********************************************************************************************************************
 * Srvc_Div_S64S32_S32
 *
 * \brief uint64_t uint32_t division with int32_t saturation and check on divide by zero.
 *
 * Divide a signed 64-bit variable by a signed 32-bit variable and return the result as signed 32-bit.
 * The result is limited to INT32_MAX (INT32_MIN) prevent overflows(underflows).
 *
 * \param      s64_X                      Operand1, unsigned 32-bit variable
 * \param      s32_Y                      Operand2, unsigned 32-bit variable
 * \return     (s64_X / s32_Y)            Result,    unsigned 16-bit
 ***********************************************************************************************************************
 */
int32_t Srvc_Div_S64S32_S32(int64_t s64_X, int32_t s32_Y)
{
  int64_t s64_Res;
/******************************************************************************
*   To overcome the compiler limitation it type conversion (int32_t) is done
*   DONT REMOVE THE TYPE CONVERSION
*
******************************************************************************/
  if (s32_Y == 0) {
    /* limitation */
    s64_Res = ( (s64_X >= 0) ? ((int32_t)INT32_MAX) : ((int32_t)INT32_MIN));
  } else {
    s64_Res = (s64_X / s32_Y);
  }
  s64_Res =
    ( (s64_Res >=
    ( (int32_t)INT32_MAX) ) ? ((int32_t)INT32_MAX) : ( (s64_Res <=
    (int32_t)INT32_MIN) ? ((int32_t)INT32_MIN) : s64_Res) );
  return (int32_t)s64_Res;
}
