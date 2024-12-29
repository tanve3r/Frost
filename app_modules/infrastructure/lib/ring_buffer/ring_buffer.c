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
 *  COMP_ABBREV      ring_buffer library
 ******************************************************************************/

/******************************************************************************/
/* DOCUMENTATION                                                              */
/******************************************************************************/
/** \file          ring_buffer.c 
 *
 *  \brief
 *
 *  \details
 *
 */

/******************************************************************************/
/* INCLUDES                                                                   */
/******************************************************************************/
#include "ring_buffer.h"

/******************************************************************************/
/* PRIVATE DEFINITIONS                                                        */
/******************************************************************************/

/******************************************************************************/
/* PRIVATE TYPE DEFINITIONS                                                   */
/******************************************************************************/

/******************************************************************************/
/* PRIVATE FUNCTION DECLARATIONS AND PRIVATE MACRO FUNCTION DEFINITIONS       */
/******************************************************************************/

/******************************************************************************/
/* EXTERN VARIABLE DEFINTIONS                                                 */
/******************************************************************************/

/******************************************************************************/
/* PRIVATE DATA DEFINTIONS                                                    */
/******************************************************************************/
/*!
 * \brief cicular buffer management structure
 */
struct RingBuffer_Ctrl_st
{
  uint8_t*  u8StrtPtr;     // Start Pointer (fixed)
  uint8_t*  u8EndPtr;      // End Pointer (fixed)
  uint8_t*  u8WritePtr;    // Write Pointer (dynamic)
  uint8_t*  u8ReadPtr;     // Read Pointer (dynamic)
};

static struct RingBuffer_Ctrl_st RingBufferData[RING_BUFFER_MAX_IDX];
/******************************************************************************/
/* PUBLIC FUNCTION DEFINITIONS                                                */
/******************************************************************************/


/*****************************************************************************/
/*!
 * \brief Initialise circular buffer
 *
 * \param [in] ringbufferIndex - Buffer Index
 * \param [in] pv_buffer - pointer to memory for circular buffer
 * \param [in] pv_bufferSize - size of buffer
 *****************************************************************************/
void RingBuffer_vInit(enum ringbufferIndex Indx, uint8_t * pv_buffer, uint16_t pv_bufferSize)
{
  // Initialize pointers (START and END)
  RingBufferData[Indx].u8StrtPtr = pv_buffer;
  RingBufferData[Indx].u8EndPtr = RingBufferData[Indx].u8StrtPtr + pv_bufferSize - 1;

  // Initialize shell pointers (READ and WRITE)
  RingBufferData[Indx].u8WritePtr = RingBufferData[Indx].u8StrtPtr;
  RingBufferData[Indx].u8ReadPtr = RingBufferData[Indx].u8StrtPtr;
}

/*****************************************************************************/
/*!
 * \brief Push data to buffer
 *
 * \param [in] ringbufferIndex - Buffer Index
 * \param [in] pv_data - poiner to data
 *
 *****************************************************************************/
void RingBuffer_Push(enum ringbufferIndex Indx, uint8_t pv_data)
{

  *RingBufferData[Indx].u8WritePtr = pv_data; // Write into buffer
  RingBufferData[Indx].u8WritePtr++;                               // Increment write pointer

  if (RingBufferData[Indx].u8WritePtr > RingBufferData[Indx].u8EndPtr)          // If end is reached
  {
    RingBufferData[Indx].u8WritePtr = RingBufferData[Indx].u8StrtPtr;           // Re-assign to start pointer
  }

}

/*****************************************************************************/
/*!
 * \brief Get filled count
 *
 * \param [in] ringbufferIndex - Buffer Index
 * \return number of filled bytes
 *
 *****************************************************************************/
uint16_t RingBuffer_GetFilledCount(enum ringbufferIndex Indx)
{
  uint16_t u16NumByetsToRead = 0;

  if(RingBufferData[Indx].u8ReadPtr < RingBufferData[Indx].u8WritePtr)
  {
    // Calculate number of bytes to be read
    u16NumByetsToRead = (uint16_t)(RingBufferData[Indx].u8WritePtr - RingBufferData[Indx].u8ReadPtr);
  }
  else if (RingBufferData[Indx].u8ReadPtr > RingBufferData[Indx].u8WritePtr)
  {
    // Calculate number of bytes to be read
    u16NumByetsToRead = (uint8_t)(RingBufferData[Indx].u8EndPtr - RingBufferData[Indx].u8ReadPtr + 1);
  }
  else
  {
    // Do nothing
  }

  return (u16NumByetsToRead);
}

/*****************************************************************************/
/*!
 * \brief Get Read Pointer
 *
 * \param [in] ringbufferIndex - Buffer Index
 * \return read pointer
 *
 *****************************************************************************/
uint8_t* RingBuffer_ReadPtr(enum ringbufferIndex Indx)
{
  return RingBufferData[Indx].u8ReadPtr;
}

/*****************************************************************************/
/*!
 * \brief update read pointer
 *
 * \param [in] ringbufferIndex - Buffer Index
 *
 *****************************************************************************/
void RingBuffer_UpdateReadPtr(enum ringbufferIndex Indx)
{
  if(RingBufferData[Indx].u8ReadPtr < RingBufferData[Indx].u8WritePtr)
  {
    // Assign read pointer to write pointer
    RingBufferData[Indx].u8ReadPtr = RingBufferData[Indx].u8WritePtr;
  }
  else if (RingBufferData[Indx].u8ReadPtr > RingBufferData[Indx].u8WritePtr)
  {
    // Assign read pointer to start pointer
    RingBufferData[Indx].u8ReadPtr = RingBufferData[Indx].u8StrtPtr;
  }
  else
  {
    // Do nothing
  }
}
