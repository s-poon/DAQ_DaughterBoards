/*
 * threadx.c
 *
 *  Created on: Apr 20, 2024
 *      Author: Steven
 */
#include "threadx.h"
#include "aero_sensors.h"
#include "ucr_common.h"
#include "analog_control_datatypes.h"


TX_THREAD txMainThread;
TX_THREAD txAnalogThread;
TX_THREAD txAeroThread;
TX_THREAD txCAN500HzThread;
TX_THREAD txCAN100HzThread;

TX_SEMAPHORE analogSemaphore;
TX_SEMAPHORE aeroSemaphore;


static const uint8_t analogSwitchStates[NUM_ADC_CHANNELS] = {
	SET_12V,
	SET_12V,
	SET_12V,
	SET_12V,
	SET_12V,
	SET_12V,
	SET_12V,
	SET_12V
};

uint32_t adcValues[8];
uint8_t analogRxData[16];


UINT ThreadX_Init(VOID *memory_ptr){
    UINT ret = TX_SUCCESS;

	TX_BYTE_POOL *bytePool = (TX_BYTE_POOL*)memory_ptr;
	CHAR *pointer;

	if(tx_byte_allocate(bytePool, (VOID**) &pointer, TX_APP_STACK_SIZE, TX_NO_WAIT) != TX_SUCCESS){
	  return TX_POOL_ERROR;
	}

	if(tx_byte_allocate(bytePool, (VOID**) &pointer, TX_APP_STACK_SIZE, TX_NO_WAIT) != TX_SUCCESS){
	  return TX_POOL_ERROR;
	}

	if(tx_thread_create(&txMainThread, "txMainThread", txMainThreadEntry, 0, pointer,
						 TX_APP_STACK_SIZE, TX_APP_THREAD_PRIO, TX_APP_THREAD_PREEMPTION_THRESHOLD,
						 TX_APP_THREAD_TIME_SLICE, TX_APP_THREAD_AUTO_START) != TX_SUCCESS){
	  return TX_THREAD_ERROR;
	}

	if(tx_thread_create(&txMainThread, "txAnalogThread", txAnalogThreadEntry, 0, pointer,
						 TX_APP_STACK_SIZE, TX_APP_THREAD_PRIO, TX_APP_THREAD_PREEMPTION_THRESHOLD,
						 TX_APP_THREAD_TIME_SLICE, TX_APP_THREAD_AUTO_START) != TX_SUCCESS){
	  return TX_THREAD_ERROR;
	}

	if(tx_thread_create(&txMainThread, "txAeroThread", txAeroThreadEntry, 0, pointer,
					   TX_APP_STACK_SIZE, TX_APP_THREAD_PRIO, TX_APP_THREAD_PREEMPTION_THRESHOLD,
					   TX_APP_THREAD_TIME_SLICE, TX_APP_THREAD_AUTO_START) != TX_SUCCESS){
		return TX_THREAD_ERROR;
	}
	if(tx_thread_create(&txMainThread, "txCAN500Hz", txCAN500HzThreadEntry, 0, pointer,
					   TX_APP_STACK_SIZE, TX_APP_THREAD_PRIO, TX_APP_THREAD_PREEMPTION_THRESHOLD,
					   TX_APP_THREAD_TIME_SLICE, TX_APP_THREAD_AUTO_START) != TX_SUCCESS){
		return TX_THREAD_ERROR;
	}

	if(tx_thread_create(&txMainThread, "txCAN100Hz", txCAN100HzThreadEntry, 0, pointer,
					   TX_APP_STACK_SIZE, TX_APP_THREAD_PRIO, TX_APP_THREAD_PREEMPTION_THRESHOLD,
					   TX_APP_THREAD_TIME_SLICE, TX_APP_THREAD_AUTO_START) != TX_SUCCESS){
		return TX_THREAD_ERROR;
	}

	tx_semaphore_create(&analogSemaphore, "analogSemaphore", 0);
	tx_semaphore_create(&aeroSemaphore, "aeroSemaphore", 0);
	/* USER CODE END App_ThreadX_Init */

	return ret;
}


void txMainThreadEntry(ULONG threadInput){

    HAL_FDCAN_Start(&hfdcan1);
	while(1){
	    HAL_GPIO_TogglePin(STATUS_LED_GPIO_Port, STATUS_LED_Pin);
	    tx_thread_sleep(1000);
	}
}

void txAnalogThreadEntry(ULONG threadInput){

    while(1){
        HAL_ADC_Start_DMA(&hadc1, adcValues, NUM_ADC_CHANNELS);
        tx_semaphore_get(&analogSemaphore, TX_WAIT_FOREVER);
//        data will be processed and sent over CAN here
        for(int i = 0; i < NUM_ADC_CHANNELS; i ++){
        	analogRxData[i * 2] = adcValues[i];
        	analogRxData[i * 2 + 1] = adcValues[i] >> 8;
        }

        tx_thread_sleep(2);
    }
}

void txAeroThreadEntry(ULONG threadInput){

    while(1){
//    	TransmitToAll();
//    	StartSensorReading();
//    	SetChannel(1);
//    	ReadData();
//    	SetChannel(2);
//		ReadData();
//		SetChannel(3);
//		ReadData();

		tx_thread_sleep(10);
    }
}

void txCAN500HzThreadEntry(ULONG threadInput){

    while(2){

    }
}

void txCAN100HzThreadEntry(ULONG threadInput){

    while(10){

    }
}
