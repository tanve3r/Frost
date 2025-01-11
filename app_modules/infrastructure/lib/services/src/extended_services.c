/*******************************************************************************
 *  Copyright (c) 2023 BSH Hausgeraete GmbH,
 *  Carl-Wery-Str. 34, 81739 Munich, Germany, www.bsh-group.de
 *
 *  All rights reserved. This program and the accompanying materials
 *  are protected by international copyright laws.
 *  Please contact copyright holder for licensing information.
 *
 *******************************************************************************
 *  PROJECT          BCR2_CPM
 *  COMP_ABBREV      extended service
 ******************************************************************************/

/******************************************************************************/
/* DOCUMENTATION                                                              */
/******************************************************************************/
/** \file            extended service library
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
#include "extended_services.h"
#include "multiplication_library.h"
#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"
#include "esp_timer.h"
#include "math.h"

/******************************************************************************/
/* PUBLIC FUNCTION DEFINITIONS                                                */
/******************************************************************************/

/*********************************************************************
*  CRC Byte table for generator 0x2F
********************************************************************/
static uint8_t u8_Srvc_CRC_Byte_Tab[256] =
{
  0x00,0x2f,0x5e,0x71,0xbc,0x93,0xe2,0xcd,
  0x57,0x78,0x09,0x26,0xeb,0xc4,0xb5,0x9a,
  0xae,0x81,0xf0,0xdf,0x12,0x3d,0x4c,0x63,
  0xf9,0xd6,0xa7,0x88,0x45,0x6a,0x1b,0x34,
  0x73,0x5c,0x2d,0x02,0xcf,0xe0,0x91,0xbe,
  0x24,0x0b,0x7a,0x55,0x98,0xb7,0xc6,0xe9,
  0xdd,0xf2,0x83,0xac,0x61,0x4e,0x3f,0x10,
  0x8a,0xa5,0xd4,0xfb,0x36,0x19,0x68,0x47,
  0xe6,0xc9,0xb8,0x97,0x5a,0x75,0x04,0x2b,
  0xb1,0x9e,0xef,0xc0,0x0d,0x22,0x53,0x7c,
  0x48,0x67,0x16,0x39,0xf4,0xdb,0xaa,0x85,
  0x1f,0x30,0x41,0x6e,0xa3,0x8c,0xfd,0xd2,
  0x95,0xba,0xcb,0xe4,0x29,0x06,0x77,0x58,
  0xc2,0xed,0x9c,0xb3,0x7e,0x51,0x20,0x0f,
  0x3b,0x14,0x65,0x4a,0x87,0xa8,0xd9,0xf6,
  0x6c,0x43,0x32,0x1d,0xd0,0xff,0x8e,0xa1,
  0xe3,0xcc,0xbd,0x92,0x5f,0x70,0x01,0x2e,
  0xb4,0x9b,0xea,0xc5,0x08,0x27,0x56,0x79,
  0x4d,0x62,0x13,0x3c,0xf1,0xde,0xaf,0x80,
  0x1a,0x35,0x44,0x6b,0xa6,0x89,0xf8,0xd7,
  0x90,0xbf,0xce,0xe1,0x2c,0x03,0x72,0x5d,
  0xc7,0xe8,0x99,0xb6,0x7b,0x54,0x25,0x0a,
  0x3e,0x11,0x60,0x4f,0x82,0xad,0xdc,0xf3,
  0x69,0x46,0x37,0x18,0xd5,0xfa,0x8b,0xa4,
  0x05,0x2a,0x5b,0x74,0xb9,0x96,0xe7,0xc8,
  0x52,0x7d,0x0c,0x23,0xee,0xc1,0xb0,0x9f,
  0xab,0x84,0xf5,0xda,0x17,0x38,0x49,0x66,
  0xfc,0xd3,0xa2,0x8d,0x40,0x6f,0x1e,0x31,
  0x76,0x59,0x28,0x07,0xca,0xe5,0x94,0xbb,
  0x21,0x0e,0x7f,0x50,0x9d,0xb2,0xc3,0xec,
  0xd8,0xf7,0x86,0xa9,0x64,0x4b,0x3a,0x15,
  0x8f,0xa0,0xd1,0xfe,0x33,0x1c,0x6d,0x42
};


uint32_t tx_time_get()
{
  return (uint32_t)(esp_timer_get_time() / 1000);
} 
/**
***************************************************************************************************
* Function to Calculate the CRC of the Frame.
* It calculates the CRC of the given number of bytes and returns it
* \param pointer to the buffer
* \param length of the buffer
* \return uint8_t CRC
****************************************************************************************************
*/
uint8_t Srvc_CalcCRC(const uint8_t pu8_Buff[], const uint16_t u16_Lgth)
{
  uint8_t u8_CRC = 0;
  uint16_t u16_Ctr = 0;

  // Calculate CRC for a given frame, start CRC calculation with leading ones
  u8_CRC = u8_Srvc_CRC_Byte_Tab[0x00 ^ 0xFF ];

  for(u16_Ctr = 0; u16_Ctr < u16_Lgth; u16_Ctr++ )
  {
    u8_CRC = u8_Srvc_CRC_Byte_Tab[pu8_Buff[u16_Ctr] ^ u8_CRC ];
  }

  return u8_CRC;
}

/**
 * @brief Function to calculate CRC
 *
 * @params[in] char *buffer   pointer to buffer
 * @params[in] int size       number of bytes
 *
 * @return                    returns the CRC
 **/
uint16_t Srvc_calc_2sComplementcrc(const uint8_t* buffer, const uint8_t size )
{
  uint16_t calculated_crc = 0;

	for (uint8_t counter = 0; counter < size; counter++)
	{
		calculated_crc += (uint16_t)(buffer[counter]);
	}
  
	return (uint16_t)(0 - calculated_crc);
}

/**
 ***************************************************************************************************
 * Interpolation for maps with S16, S16 input and S16 output values.
 *
 * Searches X and Y within the input arrays (part of MapVal), passes the indexes and ratios of
 * the searchresults to Srvc_IpoGroupMapS16 and returns the interpolated value.
 *
 * \param           X_s32         Inputvalue in x direction
 * \param           Y_s32         Inputvalue in y direction
 * \param           MapVal  int16_t array with x,y,z values
 *                            Contents:
 *                            number of entries in x direction (Nx)
 *                            number of entries in x direction (Ny)
 *                            distribution in x direction (size: Nx)
 *                            distribution in y direction (size: Ny)
 *                            Nx * Ny sized array with z values at x,y distribution
 * \return                  returns the interpolated value in the map at X and Y
 * \sa         Srvx_MapS16_t
 ***************************************************************************************************
 */
int16_t Srvc_IpoMapS16S16(int32_t X_s32, int32_t Y_s32, Srvc_MapS16_t MapVal)
{
  return Srvc_IpoGroupMapS16(
    Srvc_DistrSearchS16(X_s32, MapVal[0], &MapVal[2]),
    Srvc_DistrSearchS16(Y_s32, MapVal[1], &MapVal[2 + MapVal[0]]),
    MapVal[1], &MapVal[2 + MapVal[0] + MapVal[1]]);
}

/**
 ***************************************************************************************************
 * interpolation of an int16_t map with input from distribution search.
 *
 * interpolation of an int16_t two dimensional array with input
 * from previous search of index and ratio of two given distributions.
 * Index and ratio are packed into XSearchRes and YSearchRes.
 *
 * \param       XSearchRes      Searchresult in x distribution
 * \param       YSearchRes      Searchresult in y distribution
 * \param       Num             Number of y entries
 * \param       MapVal          Values of map
 * \return                      result of interpolation int16_t
 * \sa     Srvc_SearchRes_t Srvc_ValS16_t
 ***************************************************************************************************
 */
int16_t Srvc_IpoGroupMapS16(
  Srvc_SearchRes_t XSearchRes,
  Srvc_SearchRes_t YSearchRes, int32_t Num, Srvc_ValS16_t MapVal)
{
  int32_t rX;  /* Ratio of X */
  int32_t rY;  /* Ratio of Y */
  int32_t Z0;  /* Z before desired position  */
  int32_t Z1;  /* Z after desired position  */
  const int16_t * MapVal_ps16; /* Pointer to data  */


  /* get index and ratio from parameter  */
  rX = (int32_t)((uint32_t)(XSearchRes) & 0xFFFFUL);
  rY = (int32_t)((uint32_t)(YSearchRes) & 0xFFFFUL);

  /* Set pointer in MapVal to X0 and get value there  */
  MapVal_ps16 = &MapVal[(Num * (XSearchRes / 65536L)) + (YSearchRes / 65536L)];
  Z0 = MapVal_ps16[0];

  if (rY != 0L) {
    Z0 += (((MapVal_ps16[1] - Z0) * rY) / 32768L);
  }
  if (rX != 0L) {
    /* Set pointer in MapVal to next X Index and read value  */
    MapVal_ps16 = &MapVal_ps16[Num];
    Z1 = MapVal_ps16[0];

    if (rY != 0L) {
      Z1 += (((MapVal_ps16[1] - Z1) * rY) / 32768L);
    }
    Z0 += (((Z1 - Z0) * rX) / 32768L);
  }
  return (int16_t)Z0;
}

/**
 ***************************************************************************************************
 * Searches the position of input within the given distribution and returns information that is
 * necessary for interpolation.
 *
 * Scans through the array Distr and returns the index of the setpoint (directly before input X)
 * and the ratio of distance input to setpoint and setpoint to next setpoint
 * ratio = (X-Distr[idx]) / (Distr[idx+ONE]-Distr[idx])
 *
 * \param           X       Input value that is searched for in the distribution
 * \param           Num     number of entries in distribution
 * \param           Distr   Pointer to distribution
 * \return                  Returns the index before X and ratio
 *                             Upper 16 Bit of the returnvalue is index
 *                            Lower 16 Bit of the returnvalue is (ratio * 2^15)
 * \sa         Srvc_DistribS16_t
 ***************************************************************************************************
*/
int32_t Srvc_DistrSearchS16(int32_t X, int32_t Num, Srvc_DistribS16_t Distr)
{
  int32_t RetVal;
  const int16_t * ptr_s16;  /* local pointer for scanning through distribution  */

  if (X <= *Distr) {
    RetVal = 0L;  /* X is lower than left boundary - return first index and ratio = 0   */
  } else {
    /* Set local pointer to last entry in distribution */

    /* MSRA RULE 44 VIOLATION:
       This - so called - "redundant" cast _IS_ necessary or we'll have a compiler warning:
       "warning: assignment discards qualifiers from pointer target type" */
    // ptr_s16 = (int16_t *)&Distr[--Num];
    ptr_s16 = &Distr[--Num];

    if (X >= *ptr_s16) {
      /* X is greater than last entry - return last index and ratio = 0  */
      RetVal = (int32_t)((uint32_t)Num << 16UL);
    } else {
      /* Search until entry is found that is just greater than X */
      do {
        ptr_s16--;
        Num--;
      } while (X < *ptr_s16);
      /* Calculate ratio to be used in interpolation and return index and ratio */
      RetVal = (
        (int32_t)(
          ((uint32_t)Num << 16UL) +
          (
            ((uint32_t)(X - ptr_s16[0]) << 15UL) /
            (uint32_t)(ptr_s16[1] - ptr_s16[0])
          )
        )
      );
    }
  }
  return RetVal;
}

/**
 ***************************************************************************************************
 * Debouncing of digital signals.
 *
 * Debounces a digital input signal and returns the state of the signal as a boolean value
 *
 * \param           b_X       Input value
 * \param           *State   Pointer to state structure
 * \param           *Param   Pointer to parameter structure. Content:
 *                          - TimeHighLow is the time needed to recognize a Low signal given in
 *                            same quantization as s32_DtTime_ms
 *                          - TimeLowHigh is the time needed to recognize a High signal given in
 *                            same quantization as s32_DtTime_ms
 *                          TimeHighLow and TimeLowHigh are given in 10ms
 *
 * \param           s32_DtTime_ms      Sample time. Given in ms.
 * \return                  Returns the debounced input value
 * \sa         Srvc_DebounceState_t Srvc_DebounceParam_t
 ***************************************************************************************************
 */
bool Srvc_Debounce(
  bool b_X, Srvc_DebounceState_t * State, const Srvc_DebounceParam_t * Param,
  int32_t s32_DtTime_ms)
{
  if (b_X == State->XOld) {  /* Input has not changed */
    State->Timer = 0L;  /* Stop timer  */
  } else {  /* Check if the running timer has run out */
    if (State->Timer >=
      ((b_X != false) ? (Param->TimeLowHigh * 1000) : (Param->TimeHighLow * 1000)))
    {
      State->XOld = b_X;
      State->Timer = 0L;
    } else {
      State->Timer += (s32_DtTime_ms * 1000);  /* actualize timer for low->high transition */
    }
  }
  return State->XOld;  /* Return internal state */
}

/**
 ***************************************************************************************************
 * Interpolation of an int16_t curve at a given position X.
 *
 * Interpolates the curve at position X by calculating:
 *
 *                 (y1-y0) * (X-x0)
 *  result = y0 + ------------------
                      (x1-x0)
 *   where:
 *   x0 = position before X
 *   x1 = position after X
 *   y0 = value at x0
 *   y1 = value at x1
 *    Sample code init
 *    Srvc_CurveS16_t Sam_Cur =
 *    {
 *       8,                                         //  No. of elements in curve
 *       0, 200, 400, 600, 1000, 1400, 2000, 2600,  //  X elements
 *       0, 164, 328, 819, 1147, 1638, 2130, 2621   //  Y elements
 *   },
 *
 * \param       s32_X         Input value, where the interpolation will be calculated at
 * \param       s16_Cur       Pointer to int16_t array with distribution and data
 * \return      int16_t
 * \retval      result of interpolation int16_t
 * \sa     Srvc_CurveS16_t
 ***************************************************************************************************
 */
int16_t Srvc_IpoCurveS16(int32_t s32_X, Srvc_CurveS16_t s16_Cur)
{
  int32_t s32_Num;            /* Number of data in array */
  const int16_t * ps16_Xval;  /* Pointer to X-data       */
  const int16_t * ps16_Yval;  /* Pointer to Y-data       */
  int16_t s16_Res;

  /* Get Number of data in curve  */
  s32_Num = s16_Cur[0];

  /* Set pointer to last distribution entry  */
  // ps16_Xval = (int16_t *)(&s16_Cur[Num]);
  ps16_Xval = &s16_Cur[s32_Num];

  if (s32_X <= s16_Cur[1]) {
    /* If input is less than first distribution entry then return first data entry  */
    s16_Res = (ps16_Xval[1]);
  } else {
    /* else: check if input is greater than last distribution entry or  */
    /* search position of input within curve */
    if (s32_X >= *ps16_Xval) {
      /* return last data entry in array */
      s16_Res = (ps16_Xval[s32_Num]);
    } else {
      /* search until the next greater distribution entry to X is found */
      do {
        ps16_Xval--;
      } while (s32_X < *ps16_Xval);

      /* Set pointer to data entry according to the distribution entry found by the         */
      /* search routine                                                                     */
      ps16_Yval = &ps16_Xval[s32_Num];

      /* To avoid overflow and the necessity to use a sint64 value, the numerator of the    */
      /* following calculation is limited to uint32_t. To avoid sign extension, a check       */
      /* if ps16_Yval[ONE] >= *ps16_Yval is done and the subtraction is always done that      */
      /* way, that the result is always positive.                                           */
      /* Of course, the possible sign of the subtraction is handed in the addition          */
      /* beforehand                                                                         */

      /* Return calculated interpolation value                                              */
      s16_Res = (int16_t)((int32_t)(*ps16_Yval) +
        Srvc_MulDiv32(
          (int32_t)(ps16_Yval[1] - *ps16_Yval),
          (s32_X - *ps16_Xval),
          (int32_t)(ps16_Xval[1] - *ps16_Xval)));
    }
  }
  return s16_Res;
}

/**
 ************************************************************************************************************************
 * Srvc_LimitS32
 *
 * \brief  Limit a int32_t value with Min & Max value of a int32_t
 *
 * Remarks
 *
 * \param       s32_X                - Value to be limited
 * \param       s32_Min              - Min Limit to be limited
 * \param       s32_Max              - Max Limit to be limited
 *
 * \return      s32_tmp              - Limited result
 ************************************************************************************************************************
 */
int32_t Srvc_LimitS32(int32_t s32_X, int32_t s32_Min, int32_t s32_Max)
{
  int32_t s32_tmp;
  s32_tmp = (((s32_X) > (s32_Max)) ? (s32_Max) : (s32_X));
  s32_tmp = (((s32_tmp) < (s32_Min)) ? (s32_Min) : (s32_tmp));
  return s32_tmp;
}

/**
 ************************************************************************************************************************
 * Srvc_LimitU32
 *
 * \brief  Limit a uint32_t value with Min & Max value of a uint32_t
 *
 * Remarks
 *
 * \param       u32_X                - Value to be limited
 * \param       u32_Min              - Min Limit to be limited
 * \param       u32_Max              - Max Limit to be limited
 *
 * \return      u32_tmp              - Limited result
 ************************************************************************************************************************
 */
uint32_t Srvc_LimitU32(uint32_t u32_X, uint32_t u32_Min, uint32_t u32_Max)
{
  uint32_t u32_tmp;
  u32_tmp = (((u32_X) > (u32_Max)) ? (u32_Max) : (u32_X));
  u32_tmp = (((u32_tmp) < (u32_Min)) ? (u32_Min) : (u32_tmp));
  return u32_tmp;
}

/**
 ************************************************************************************************************************
 * Srvc_StartSWTmrU32
 *
 * \brief stores current 32-bit reference time in *tmrPtr - start of the 32 timer *tmrPtr
 *
 * \param       *tmrPtr - pointer to a SW-timer struct
 * \return      none
 ************************************************************************************************************************
 */
void Srvc_StartSWTmrU32(Srvc_SWTmrU32_t * tmrPtr)
{
   (tmrPtr)->tiStrd = tx_time_get();
}

/**
 ************************************************************************************************************************
 * SrvB_DiffSWTmrS16
 *
 * \brief difference of current 16-bit reference time and stored timer value *tmrPtr.
 *
 * Remarks      No prevention of unsigned 8-bit timer overrun (positive values).
 *              Since zero means that timer is stopped and is therefore avoided
 *              for the reference timers a correction of a single step is necessary,
 *              if the stored timer is greater than the reference timer.
 *
 * \param        tmrPtr                         - pointer to a SW-timer struct
 * \return       u32_LocTim_ms	    - elapsed time since 8-bit timer *tmrPtr has been started
 ************************************************************************************************************************
 */
uint32_t Srvc_DiffSWTmrU32(const Srvc_SWTmrU32_t * tmrPtr)
{
  uint32_t u32_LocTim_ms;

  u32_LocTim_ms = tx_time_get();
  if (u32_LocTim_ms >= ((tmrPtr)->tiStrd)) {
    u32_LocTim_ms = (u32_LocTim_ms - ((tmrPtr)->tiStrd));
  } else {
    u32_LocTim_ms = ( ((tmrPtr)->tiStrd) - (u32_LocTim_ms + 1) );
    u32_LocTim_ms = (UINT32_MAX - u32_LocTim_ms);
  }
  return u32_LocTim_ms;
}

/**
 ************************************************************************************************************************
 * Srvc_TestSWTmrU32
 *
 * \brief test, if 32 bit SW-timer *tmrPtr is stopped
 *
 * \param        tmrPtr - pointer to a SW-timer struct
 * \return       FALSE: timer is running
 *               TRUE : timer is stopped
 ************************************************************************************************************************
 */
bool Srvc_TestSWTmrU32(const Srvc_SWTmrU32_t * tmrPtr)
{
  bool b_Res;
  if ( (tmrPtr)->tiStrd == 0) {
    b_Res = true;
  } else {
    b_Res = false;
  }
  return b_Res;
}

/**
 ************************************************************************************************************************
 * Srvc_StopSWTmrU32
 *
 * \brief sets *tmrPtr to zero - stops the 16-bit timer *tmrPtr
 *
 * \param       *tmrPtr - pointer to a SW-timer struct
 * \return      none
 ************************************************************************************************************************
 */
void Srvc_StopSWTmrU32(Srvc_SWTmrU32_t * tmrPtr)
{
  tmrPtr->tiStrd = 0;
}

/**
 ************************************************************************************************************************
 * Srvc_ulGetCurrentTime
 *
 * \brief Returns the current time in milliseconds
 *
 *
 *
 ************************************************************************************************************************
 */
uint32_t Srvc_ulGetCurrentTime( void )
{
  return (uint32_t)tx_time_get();
}

/**
 ************************************************************************************************************************
 *
 * \brief  Convert ms to OS ticks
 *
 * \param [in] ul_time_ms - time in ms to convert to os ticks
 * \return os tick
 * 
 ************************************************************************************************************************
 */
uint32_t service_tConvertMStoTicks(uint32_t const ul_time_ms)
{
  return ( ul_time_ms * TX_TIMER_TICKS_PER_SECOND ) / 1000;
}

/**
 ************************************************************************************************************************
 *
 * \brief  Convert OS ticks to ms
 *
 * \param [in] ul_ticks - os ticks to convert to ms
 * \return time in ms
 * 
 ************************************************************************************************************************
 */
uint32_t service_tConvertTickstoMS(uint32_t const ul_ticks)
{
  return ( ul_ticks * 1000 ) / TX_TIMER_TICKS_PER_SECOND;
}

/**
 **********************************************************************************************************************
 *
 * Srvc_Abs_S32_S32
 *
 * \brief Absolute value of int32_t operand with int32_t saturation.
 *
 * \param  s32_X
 * \return int32_t
 * \retval Absolute value of s32_X saturated to int32_t
 *
 **********************************************************************************************************************
 */
int32_t Srvc_Abs_S32_S32 (int32_t s32_X)
{
    int32_t s32_Res;

    if (s32_X >= 0L)
    {
        s32_Res = s32_X;
    }
    else
    {
        /* Saturation for the min value */
        s32_Res = ((s32_X == INT32_MIN ) ? INT32_MAX : -s32_X);
    }

    return (s32_Res);
}

/**
 **********************************************************************************************************************
 *
 * Srvc_RampUpDown
 *
 * \brief ramping up and down function for the given command velocity input.
 *
 * \param  u32_command_vel - command velocity 
 * \param b_Rampmode - true Rampup / False Rampdown
 * \param b_ResetRamp - true reset ramp parameters
 * \return uint32_t - result velocity
 *
 **********************************************************************************************************************
 */
//uint32_t Srvc_RampUpDown(uint32_t u32_command_vel,bool b_Rampmode, bool b_ResetRamp)
//{
//  static uint32_t u32_prev_target_vel;
//  static uint16_t u16_rampCnt = 0;
//  static uint32_t u32_m,u32_b; //the parameter of the quadratic ramp
//  static uint32_t u32_result_vel;
//  static uint32_t u32_ramp_Length = 0;
//  
//  // Reset ramp parameters
//  if(b_ResetRamp)
//  {
//    u16_rampCnt = 0;
//    u32_m = 0;
//    u32_b = 0;
//    u32_result_vel = 0;
//    u32_ramp_Length = 0;
//  }
//  
//  if(b_Rampmode)
//  {
//    // Check if there is a new target higher than previous and calculate the parameters
//    if (u32_command_vel != u32_prev_target_vel)
//    {
//      u32_ramp_Length = sqrt(u32_command_vel);
//      u16_rampCnt = 0;
//      u32_m = (u32_command_vel - u32_result_vel);
//      u32_m = u32_m /(uint32_t)(u32_ramp_Length*u32_ramp_Length);
//      u32_b = u32_result_vel;
//    }
//  
//    // Count up as long as not reached yet
//    if (u16_rampCnt < u32_ramp_Length)
//    {
//      u32_result_vel = u32_b + u32_m*((uint32_t)u16_rampCnt*((uint32_t)u16_rampCnt));
//      u16_rampCnt++;
//    }
//    // Otherwise target = current result
//    else
//    {
//      u32_result_vel = u32_command_vel;
//    }
//  
//    // Double check that there is no overshoot
//    if (((u32_result_vel > u32_command_vel) && (u32_m > 0)) ||
//        ((u32_result_vel < u32_command_vel) && (u32_m < 0)))
//    {
//      u32_result_vel = u32_command_vel;
//    }
//  
//    // Update previous target
//    u32_prev_target_vel = u32_command_vel;
//  }
//  else
//  {
//    // Check if there is a new target higher than previous and calculate the parameters
//    if (u32_command_vel != u32_prev_target_vel)
//    {
//        u32_ramp_Length = sqrt(u32_prev_target_vel);
//        u16_rampCnt = 0;
//        u32_m = (u32_result_vel - u32_command_vel);
//        u32_m = u32_m /(uint32_t)(u32_ramp_Length*u32_ramp_Length);
//        u32_b = u32_result_vel;
//    }
//    
//    // Count up as long as not reached yet
//    if (u16_rampCnt < u32_ramp_Length)
//    {
//      u32_result_vel = u32_b - u32_m*((uint32_t)u16_rampCnt*((uint32_t)u16_rampCnt));
//      u16_rampCnt++;
//    }
//    // Otherwise target = current result
//    else
//    {
//      u32_result_vel = u32_command_vel;
//    }
//
//    // Double check that there is no overshoot
//    if ((( u32_command_vel > u32_result_vel) && (u32_m > 0)) ||
//    (( u32_command_vel < u32_result_vel) && (u32_m < 0)))
//    {
//      u32_result_vel = u32_command_vel;
//    }
//    
//    // Update previous target
//    u32_prev_target_vel = u32_command_vel;
//  }
//
//  return u32_result_vel;
//}
/**
 ***************************************************************************************************
 * Interpolation of an sint32 curve at a given position X.
 *
 * Interpolates the curve at position X by calculating:
 *
 *                 (y1-y0) * (X-x0)
 *  result = y0 + ------------------
                      (x1-x0)
 *   where:
 *   x0 = position before X
 *   x1 = position after X
 *   y0 = value at x0
 *   y1 = value at x1
 *    Sample code init
 *    Srvc_CurveS16_t Sam_Cur =
 *    {
 *       8,                                         //  No. of elements in curve
 *       0, 200, 400, 600, 1000, 1400, 2000, 2600,  //  X elements
 *       0, 164, 328, 819, 1147, 1638, 2130, 2621   //  Y elements
 *   },
 *
 * \param       s32_X         Input value, where the interpolation will be calculated at
 * \param       s32_Cur       Pointer to sint32 array with distribution and data
 * \return      sint32
 * \retval		result of interpolation sint32
 * \sa     Srvc_CurveS32_t
 ***************************************************************************************************
 */

sint32 Srvc_IpoCurveS32(sint32 s32_X, Srvc_CurveS32_t s32_Cur)
{

    sint32 s32_Num;                           /* Number of data in array                          */
    const sint32 *ps32_Xval;                  /* Pointer to X-data                                */
    const sint32 *ps32_Yval;                  /* Pointer to Y-data                                */
    sint32 s32_Res;

    /* Get Number of data in curve                                                                */
    s32_Num = s32_Cur[0];

    /* Set pointer to last distribution entry                                                     */
    //ps16_Xval = (sint16 *)(&s16_Cur[Num]);
    ps32_Xval = &s32_Cur[s32_Num];

    if( s32_X <= s32_Cur[1])
    {
        /* If input is less than first distribution entry then return first data entry            */
        s32_Res = (ps32_Xval[1]);
    }
    else
    {
        /* else: check if input is greater than last distribution entry or                        */
        /* search position of input within curve                                                  */
        if (s32_X >= *ps32_Xval)
        {
            /* return last data entry in array                                                    */
            s32_Res = (ps32_Xval[s32_Num]);
        }
        else
        {
            /* search until the next greater distribution entry to X is found                     */
            do
            {
                ps32_Xval--;
            } while (s32_X < *ps32_Xval);

            /* Set pointer to data entry according to the distribution entry found by the         */
            /* search routine                                                                     */
            ps32_Yval = &ps32_Xval[s32_Num];

            /* To avoid overflow and the necessity to use a sint64 value, the numerator of the    */
            /* following calculation is limited to uint32. To avoid sign extension, a check       */
            /* if ps16_Yval[ONE] >= *ps16_Yval is done and the subtraction is always done that      */
            /* way, that the result is always positive.                                           */
            /* Of course, the possible sign of the subtraction is handed in the addition          */
            /* beforehand                                                                         */

            /* Return calculated interpolation value                                              */
            s32_Res = (sint32)((sint32)(*ps32_Yval) +
                         Srvc_MulDiv32((sint32)(ps32_Yval[1] - *ps32_Yval),
                                              (s32_X                - *ps32_Xval),
                                              (sint32)(ps32_Xval[1] - *ps32_Xval)));
        }
    }
    return s32_Res;
}
