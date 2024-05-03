/*
 * threadx.c
 *
 *  Created on: Apr 20, 2024
 *      Author: Steven
 */
#include "threadx.h"
#include "ucr_common.h"
#include "analog_control_datatypes.h"
#include "aero_sensors.h"
#include "frequency_sensors.h"
#include "tim.h"
#include "../../vendor_generated/can_tools/can.h"

extern frequency_t ChannelData[4];
extern aeroSensor_t AeroSensors[NUM_AERO_SENSORS];

TX_THREAD txMainThread;
TX_THREAD txAnalogThread;
TX_THREAD txAeroThread;
TX_THREAD txCAN500HzThread;
TX_THREAD txCAN100HzThread;

TX_SEMAPHORE semaphoreAnalog;
TX_SEMAPHORE semaphoreAero;
TX_SEMAPHORE semaphoreFrequency;



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



uint8_t frequencyData[16];


UINT ThreadX_Init(
        VOID *memory_ptr
){
    UINT ret = TX_SUCCESS;

	TX_BYTE_POOL *bytePool = (TX_BYTE_POOL*)memory_ptr;
	CHAR *pointer;

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

	tx_semaphore_create(&semaphoreAnalog, "semaphoreAnalog", 0);
	tx_semaphore_create(&semaphoreAero, "semaphoreAero", 0);
	tx_semaphore_create(&semaphoreFrequency, "semaphoreFrequency", 1);

	return retVal;
}


void txMainThreadEntry(
    ULONG threadInput
){
    HAL_FDCAN_Start(&hfdcan1);
    HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_1);
    HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_2);
    HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_3);
    HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_4);

	while(1){
	    HAL_GPIO_TogglePin(STATUS_LED_GPIO_Port, STATUS_LED_Pin);
	    tx_thread_sleep(1000);
	}
}

void txAnalogThreadEntry(ULONG threadInput){
    uint8_t analogRxData[UCR_01_FRONT_ANALOG_LENGTH];
    uint32_t adcValues[NUM_ADC_CHANNELS];
    setAnalogSwitches(analogSwitchStates);

    FDCAN_TxHeaderTypeDef analogHeader = {
            .Identifier = UCR_01_FRONT_ANALOG_FRAME_ID,
            .IdType = FDCAN_STANDARD_ID,
            .TxFrameType = FDCAN_DATA_FRAME,
            .DataLength = FDCAN_DLC_BYTES_16,
            .ErrorStateIndicator = FDCAN_ESI_ACTIVE,
            .BitRateSwitch = FDCAN_BRS_ON,
            .FDFormat = FDCAN_FD_CAN,
            .TxEventFifoControl = FDCAN_NO_TX_EVENTS,
            .MessageMarker = 0
    };

    while(1){
        HAL_ADC_Start_DMA(&hadc1, adcValues, NUM_ADC_CHANNELS);
        tx_semaphore_get(&semaphoreAnalog, TX_WAIT_FOREVER);
        struct ucr_01_front_analog_t analogStruct = {
            .analog1 = adcValues[0],
            .analog2 = adcValues[1],
            .analog3 = adcValues[2],
            .analog4 = adcValues[3],
            .analog5 = adcValues[4],
            .analog6 = adcValues[5],
            .analog7 = adcValues[6],
            .analog8 = adcValues[7]
        };
        ucr_01_front_analog_pack(analogRxData, &analogStruct, UCR_01_FRONT_ANALOG_LENGTH);
        HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &analogHeader, analogRxData);
        tx_thread_sleep(2);
    }
}

void txAeroThreadEntry(
   ULONG threadInput
){
    if(UCR_OK != AeroInit()){

    }
    struct ucr_01_front_aero_t aeroData;
    uint8_t transmitData[UCR_01_FRONT_AERO_LENGTH];
    FDCAN_TxHeaderTypeDef aeroHeader = {
        .Identifier = UCR_01_FRONT_AERO_FRAME_ID,
        .IdType = FDCAN_STANDARD_ID,
        .TxFrameType = FDCAN_DATA_FRAME,
        .DataLength = FDCAN_DLC_BYTES_16,
        .ErrorStateIndicator = FDCAN_ESI_ACTIVE,
        .BitRateSwitch = FDCAN_BRS_ON,
        .FDFormat = FDCAN_FD_CAN,
        .TxEventFifoControl = FDCAN_NO_TX_EVENTS,
        .MessageMarker = 0
    };

    while(1){
        for(int i = 0; i < NUM_AERO_SENSORS; i ++){
            StartSensorReading(&AeroSensors[i]);
        }

        tx_thread_sleep(20);

        for(int i = 0; i < NUM_AERO_SENSORS; i ++){
            ReadData(&AeroSensors[i]);
        }
        aeroData.pressure1 = AeroSensors[0].pressure;
        aeroData.pressure2 = AeroSensors[1].pressure;
        aeroData.pressure3 = AeroSensors[2].pressure;

        aeroData.temperature1 = AeroSensors[0].temperature;
        aeroData.temperature2 = AeroSensors[1].temperature;
        aeroData.temperature3 = AeroSensors[2].temperature;
        ucr_01_front_aero_pack(transmitData, &aeroData, UCR_01_FRONT_AERO_LENGTH);
        HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &aeroHeader, transmitData);
    }
}

void txCAN500HzThreadEntry(ULONG threadInput){

    while(1){

    }
}

void txCAN100HzThreadEntry(
    ULONG threadInput
){
    if(UCR_OK != FrequencyInit()){

    }
	uint8_t preScalar = htim2.Init.Prescaler + 1;
    float refClock = TIMCLOCK/(preScalar);
	uint32_t frequency[NUM_FREQUENCY_CHANNELS];
	uint8_t frequencyData[UCR_01_FRONT_FREQUENCY_LENGTH];
	FDCAN_TxHeaderTypeDef frequencyHeader = {
	        .Identifier = UCR_01_FRONT_FREQUENCY_FRAME_ID,
	        .IdType = FDCAN_STANDARD_ID,
	        .TxFrameType = FDCAN_DATA_FRAME,
	        .DataLength = FDCAN_DLC_BYTES_16,
	        .ErrorStateIndicator = FDCAN_ESI_ACTIVE,
	        .BitRateSwitch = FDCAN_BRS_ON,
	        .FDFormat = FDCAN_FD_CAN,
	        .TxEventFifoControl = FDCAN_NO_TX_EVENTS,
	        .MessageMarker = 0
	};

    while(1){
        // Acquire the semaphore
    	tx_semaphore_get(&semaphoreFrequency, TX_WAIT_FOREVER);
    	// Convert the data to frequency and encode it
    	for(int i = 0; i < 4; i ++){
			float value = refClock / ChannelData[i].difference;
			frequency[i] = ucr_01_front_frequency_frequency1_encode(value);
    	}
    	struct ucr_01_front_frequency_t frequencyStruct = {
    	        .frequency1 = frequency[0],
    	        .frequency2 = frequency[1],
    	        .frequency3 = frequency[2],
    	        .frequency4 = frequency[3]
    	};
    	ucr_01_front_frequency_pack(frequencyData, &frequencyStruct, UCR_01_FRONT_FREQUENCY_LENGTH);
    	tx_semaphore_put(&semaphoreFrequency);
    	HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &frequencyHeader, frequencyData);
    	tx_thread_sleep(10);
    }
}
















