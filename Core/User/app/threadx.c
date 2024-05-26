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
#include "strain_gauges.h"
#include "spi.h"

extern frequency_t ChannelData[4];
extern aeroSensor_t AeroSensors[NUM_AERO_SENSORS];
extern const uint8_t adcMuxStates[];

TX_THREAD txMainThread;
TX_THREAD txAnalogThread;
TX_THREAD txAeroThread;
TX_THREAD txCAN500HzThread;
TX_THREAD txCAN100HzThread;

TX_SEMAPHORE semaphoreAnalog;
TX_SEMAPHORE semaphoreAero;
TX_SEMAPHORE semaphoreFrequency;
TX_SEMAPHORE semaphoreExADC1;
TX_SEMAPHORE semaphoreExADC2;
TX_SEMAPHORE semaphoreSPI;

uint8_t analogRxData[16];

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
						 TX_APP_THREAD_TIME_SLICE, TX_APP_THREAD_AUTO_START) != TX_SUCCESS
    ){
	    return TX_THREAD_ERROR;
	}

	if(tx_byte_allocate(bytePool, (VOID**) &pointer, TX_APP_STACK_SIZE, TX_NO_WAIT) != TX_SUCCESS){
	    return TX_POOL_ERROR;
    }

	if(tx_thread_create(&txAnalogThread, "txAnalogThread", txAnalogThreadEntry, 0, pointer,
						 TX_APP_STACK_SIZE, TX_ANALOG_PRIO, TX_APP_THREAD_PREEMPTION_THRESHOLD,
						 TX_APP_THREAD_TIME_SLICE, TX_APP_THREAD_AUTO_START) != TX_SUCCESS
    ){
	    return TX_THREAD_ERROR;
	}

    if(tx_byte_allocate(bytePool, (VOID**) &pointer, TX_APP_STACK_SIZE, TX_NO_WAIT) != TX_SUCCESS){
        return TX_POOL_ERROR;
    }

	if(tx_thread_create(&txAeroThread, "txAeroThread", txAeroThreadEntry, 0, pointer,
					   TX_APP_STACK_SIZE, 12, TX_APP_THREAD_PREEMPTION_THRESHOLD,
					   TX_APP_THREAD_TIME_SLICE, TX_APP_THREAD_AUTO_START) != TX_SUCCESS
    ){
		return TX_THREAD_ERROR;
	}

    if(tx_byte_allocate(bytePool, (VOID**) &pointer, TX_APP_STACK_SIZE, TX_NO_WAIT) != TX_SUCCESS){
        return TX_POOL_ERROR;
    }

	if(tx_thread_create(&txCAN500HzThread, "txCAN500Hz", txCAN500HzThreadEntry, 0, pointer,
					   TX_APP_STACK_SIZE, 13, TX_APP_THREAD_PREEMPTION_THRESHOLD,
					   TX_APP_THREAD_TIME_SLICE, TX_APP_THREAD_AUTO_START) != TX_SUCCESS
    ){
		return TX_THREAD_ERROR;
	}

    if(tx_byte_allocate(bytePool, (VOID**) &pointer, TX_APP_STACK_SIZE, TX_NO_WAIT) != TX_SUCCESS){
        return TX_POOL_ERROR;
    }

	if(tx_thread_create(&txCAN100HzThread, "txCAN100Hz", txCAN100HzThreadEntry, 0, pointer,
					   TX_APP_STACK_SIZE, 14, TX_APP_THREAD_PREEMPTION_THRESHOLD,
					   TX_APP_THREAD_TIME_SLICE, TX_APP_THREAD_AUTO_START) != TX_SUCCESS
    ){
		return TX_THREAD_ERROR;
	}

	tx_semaphore_create(&semaphoreAnalog, "semaphoreAnalog", 0);
	tx_semaphore_create(&semaphoreAero, "semaphoreAero", 0);
	tx_semaphore_create(&semaphoreFrequency, "semaphoreFrequency", 1);
	tx_semaphore_create(&semaphoreExADC1, "semaphoreExADC1", 0);
	tx_semaphore_create(&semaphoreExADC2, "semaphoreExADC2", 0);
	tx_semaphore_create(&semaphoreSPI, "semaphoreSPI", 0);
    

	return ret;
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
        HAL_ADC_Start_DMA(&hadc4, adcValues, NUM_ADC_CHANNELS);
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
//            StartSensorReading(&AeroSensors[i]);
        	SetChannel(i);
        }


        tx_thread_sleep(20);

//        for(int i = 0; i < NUM_AERO_SENSORS; i ++){
//            ReadData(&AeroSensors[i]);
//        }
        aeroData.pressure1 = AeroSensors[0].pressure;
        aeroData.pressure2 = AeroSensors[1].pressure;
        aeroData.pressure3 = AeroSensors[2].pressure;

        aeroData.temperature1 = AeroSensors[0].temperature;
        aeroData.temperature2 = AeroSensors[1].temperature;
        aeroData.temperature3 = AeroSensors[2].temperature;
        ucr_01_front_aero_pack(transmitData, &aeroData, UCR_01_FRONT_AERO_LENGTH);
        tx_thread_sleep(100);
//        HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &aeroHeader, transmitData);
    }
}

void txCAN500HzThreadEntry(ULONG threadInput){

    while(1){
    	tx_thread_sleep(1000);
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
//    	HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &frequencyHeader, frequencyData);
    	tx_thread_sleep(10);
    }
}

void txADS1ThreadInput(
    ULONG threadInput
){
    uint8_t rxData[3];
    uint8_t inputSet = 0;
    uint8_t canTxData[20];
    InitDevice();
    // Set up registers
    // clear Power on reset flag
    uint8_t data = 0x00;
    WriteRegister(&externalADC1, STATUS_ADDR_MASK, data);

    // Set the PGA
    data = ADS_DELAY_14 + ADS_PGA_ENABLED + ADS_GAIN_4;
    WriteRegister(&externalADC1, PGA_ADDR_MASK, data);
    // Use single shot conversions
    data = ADS_CONVMODE_SS + ADS_DR_4000;
    WriteRegister(&externalADC1, DATARATE_ADDR_MASK, data);

    // Start Conversions
    SendCommand(&externalADC1, START_OPCODE_MASK);
    uint8_t txData[3] = {
        REGWR_OPCODE_MASK + INPMUX_ADDR_MASK,
        0x00,
        adcMuxStates[inputSet]
    };
    uint32_t combinedData[6];
    FDCAN_TxHeaderTypeDef exADC1Header = {
        .Identifier = UCR_01_FRONT_STRAIN_GAUGES1_FRAME_ID,
        .IdType = FDCAN_STANDARD_ID,
        .TxFrameType = FDCAN_DATA_FRAME,
        .DataLength = FDCAN_DLC_BYTES_20,
        .ErrorStateIndicator = FDCAN_ESI_ACTIVE,
        .BitRateSwitch = FDCAN_BRS_ON,
        .FDFormat = FDCAN_FD_CAN,
        .TxEventFifoControl = FDCAN_NO_TX_EVENTS,
        .MessageMarker = 0
    };

    while(1){
        // Wait for conversion to finish
        tx_semaphore_get(&semaphoreExADC1, TX_WAIT_FOREVER);
        // Start send receive
        HAL_GPIO_WritePin(externalADC1.csPinPort, externalADC1.csPin, 1);
        // Receive data and also set the inputs to the next inputs
        HAL_SPI_TransmitReceive_DMA(&hspi4, txData, rxData, 4);
        // Wait for data reception
        tx_semaphore_get(&semaphoreExADC1, TX_WAIT_FOREVER);
        combinedData[inputSet] = (rxData[0] << 16) + (rxData[1] << 8) + rxData[2];
        txData[2] = adcMuxStates[inputSet++];
        if(inputSet == 6){
            struct ucr_01_front_strain_gauges1_t stuff = {
                .gauge1 = combinedData[0],
                .gauge2 = combinedData[1],
                .gauge3 = combinedData[2],
                .gauge4 = combinedData[3],
                .gauge5 = combinedData[4],
                .gauge6 = combinedData[5]
            };
            ucr_01_front_strain_gauges1_pack(canTxData, &stuff, UCR_01_FRONT_STRAIN_GAUGES1_LENGTH);
//            HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &exADC1Header, canTxData);
            inputSet = 0;
            tx_thread_sleep(10);
        }

    }
}

void txADS2ThreadInput(
    ULONG threadInput
){
//    uint8_t rxData[3];
//    uint8_t inputSet = 0;
//    uint8_t canTxData[20];
////    InitDevice();
//    // Set up registers
//    // clear Power on reset flag
//    uint8_t data = 0x00;
//    WriteRegister(&externalADC2, STATUS_ADDR_MASK, data);
//
//    // Set the PGA
//    data = ADS_DELAY_14 + ADS_PGA_ENABLED + ADS_GAIN_4;
//    WriteRegister(&externalADC2, PGA_ADDR_MASK, data);
//    // Use single shot conversions
//    data = ADS_CONVMODE_SS + ADS_DR_4000;
//    WriteRegister(&externalADC2, DATARATE_ADDR_MASK, data);
//
//    // Start Conversions
//    SendCommand(&externalADC2, START_OPCODE_MASK);
//    uint8_t txData[3] = {
//        REGWR_OPCODE_MASK + INPMUX_ADDR_MASK,
//        0x00,
//        adcMuxStates[inputSet]
//    };
//    uint32_t combinedData[6];
//    FDCAN_TxHeaderTypeDef exADC1Header = {
//        .Identifier = UCR_01_FRONT_STRAIN_GAUGES2_FRAME_ID,
//        .IdType = FDCAN_STANDARD_ID,
//        .TxFrameType = FDCAN_DATA_FRAME,
//        .DataLength = FDCAN_DLC_BYTES_20,
//        .ErrorStateIndicator = FDCAN_ESI_ACTIVE,
//        .BitRateSwitch = FDCAN_BRS_ON,
//        .FDFormat = FDCAN_FD_CAN,
//        .TxEventFifoControl = FDCAN_NO_TX_EVENTS,
//        .MessageMarker = 0
//    };

    while(1){
        tx_semaphore_get(&semaphoreExADC2, TX_WAIT_FOREVER);
    }
}















