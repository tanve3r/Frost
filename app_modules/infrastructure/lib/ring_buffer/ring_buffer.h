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

#ifndef RING_BUFFER_H_
#define RING_BUFFER_H_

#ifdef __cplusplus
extern "C" {
#endif


/******************************************************************************/
/* DOCUMENTATION                                                              */
/******************************************************************************/
/** \file
 *
 *
 *  \ingroup  ring_buffer.h
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

/*!
 * \brief cicular buffer management structure
 */
enum ringbufferIndex
{
  RING_BUFFER_SHELL = 0,
  RING_BUFFER_CONSOLE,
  RING_BUFFER_TOUCH_COMMS,

  RING_BUFFER_MAX_IDX 
};

/******************************************************************************/
/* PUBLIC FUNCTION DECLARATIONS                                               */
/******************************************************************************/
void RingBuffer_vInit(enum ringbufferIndex Indx, uint8_t* pv_buffer, uint16_t pv_bufferSize);
void RingBuffer_Push(enum ringbufferIndex Indx, uint8_t pv_data);
uint16_t RingBuffer_GetFilledCount(enum ringbufferIndex Indx);
uint8_t* RingBuffer_ReadPtr(enum ringbufferIndex Indx);
void RingBuffer_UpdateReadPtr(enum ringbufferIndex Indx);

#ifdef __cplusplus
}
#endif

#endif  // RING_BUFFER_H_
