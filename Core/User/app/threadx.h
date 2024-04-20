/*
 * threadx.h
 *
 *  Created on: Apr 20, 2024
 *      Author: Steven
 */

#ifndef USER_APP_THREADX_H_
#define USER_APP_THREADX_H_

#include "app_threadx.h"

UINT ThreadX_Init(VOID *memory_ptr);

void txMainThreadEntry(ULONG threadInput);
void txAnalogThreadEntry(ULONG threadInput);
void txAeroThreadEntry(ULONG threadInput);
void txCAN500HzThreadEntry(ULONG threadInput);
void txCAN100HzThreadEntry(ULONG threadInput);
void txCAN50HzThreadEntry(ULONG threadInput);
void txCAN10HzThreadEntry(ULONG threadInput);
#endif /* USER_APP_THREADX_H_ */
