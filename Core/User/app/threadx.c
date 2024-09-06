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

#include "../../vendor_generated/can_tools/can_api.h"

extern frequency_t ChannelData[4];
extern aeroSensor_t AeroSensors[NUM_AERO_SENSORS];
extern const uint8_t adcMuxStates[];

TX_THREAD txMainThread;
TX_THREAD txAnalogThread;
TX_THREAD txAeroThread;
TX_THREAD txCAN500HzThread;
TX_THREAD txCAN100HzThread;
TX_THREAD txStrainThread;

TX_SEMAPHORE semaphoreAnalog;
TX_SEMAPHORE semaphoreAero;
TX_SEMAPHORE semaphoreFrequency;
TX_SEMAPHORE semaphoreExADC1;
TX_SEMAPHORE semaphoreExADC2;
TX_SEMAPHORE semaphoreSPI;

uint8_t analogRxData[16];
int32_t stuff;

static const uint8_t analogSwitchStates[NUM_ADC_CHANNELS] = {
	SET_12V,
	SET_5V,
	SET_12V,
	SET_12V,
	SET_12V,
	SET_5V,
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

//    if(tx_byte_allocate(bytePool, (VOID**) &pointer, TX_APP_STACK_SIZE, TX_NO_WAIT) != TX_SUCCESS){
//        return TX_POOL_ERROR;
//    }

//	if(tx_thread_create(&txStrainThread, "txStrainThread", txADS1ThreadInput, 0, pointer,
//                       TX_APP_STACK_SIZE, 15, TX_APP_THREAD_PREEMPTION_THRESHOLD,
//                       TX_APP_THREAD_TIME_SLICE, TX_APP_THREAD_AUTO_START) != TX_SUCCESS
//    ){
//        return TX_THREAD_ERROR;
//    }

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
    uint8_t analogRxData[ANALOG_DATA_LENGTH];
    uint32_t adcValues[NUM_ADC_CHANNELS];
    setAnalogSwitches(analogSwitchStates);

    FDCAN_TxHeaderTypeDef analogHeader = {
            .Identifier = ANALOG_CANID,
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
        struct analogData_t analogStruct = {
            .analog1 = adcValues[0],
            .analog2 = adcValues[1],
            .analog3 = adcValues[2],
            .analog4 = adcValues[3],
            .analog5 = adcValues[4],
            .analog6 = adcValues[5],
            .analog7 = adcValues[6],
            .analog8 = adcValues[7]
        };
        analogPack(analogRxData, &analogStruct, ANALOG_DATA_LENGTH);
        HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &analogHeader, analogRxData);
        tx_thread_sleep(4);
    }
}

void txAeroThreadEntry(
   ULONG threadInput
){
    if(UCR_OK != AeroInit()){

    }
    struct aero_t aeroData;
    uint8_t transmitData[AERO_DATA_LENGTH];
    FDCAN_TxHeaderTypeDef aeroHeader = {
        .Identifier = AERO_CANID,
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
        aeroPack(transmitData, &aeroData, AERO_DATA_LENGTH);
        tx_thread_sleep(80);
        HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &aeroHeader, transmitData);
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
	float frequency[NUM_FREQUENCY_CHANNELS];
	uint8_t frequencyData[FREQUENCY_DATA_LENGTH];
	FDCAN_TxHeaderTypeDef frequencyHeader = {
	        .Identifier = FREQUENCY_CANID,
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
    	    if(!ChannelData[i].difference){
    	        frequency[i] = 0;
    	    }else{
    	        frequency[i] = refClock / ChannelData[i].difference;
    	    }
    	}
    	struct frequencyData_t frequencyStruct = {
    	        .freq1 = frequency[0],
    	        .freq2 = frequency[1],
    	        .freq3 = frequency[2],
    	        .freq4 = frequency[3]
    	};
    	frequencyPack(frequencyData, &frequencyStruct, FREQUENCY_DATA_LENGTH);
    	tx_semaphore_put(&semaphoreFrequency);
    	HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &frequencyHeader, frequencyData);

        tx_thread_sleep(10);
    }
}

void txADS1ThreadInput(
    ULONG threadInput
){
//    uint8_t rxData[3];
//    uint8_t inputSet = 0;
//    uint8_t canTxData[20];
//    uint64_t combinedData[6];
    externalADC1.csPinPort = CS1_GPIO_Port;
    externalADC1.csPin = CS1_Pin;
    externalADC1.startSyncPinPort = STARTSYNC_1_GPIO_Port;
    externalADC1.startSyncPin = STARTSYNC_1_Pin;
    externalADC1.resetPinPort = RESET1_GPIO_Port;
    externalADC1.resetPin = RESET1_Pin;
    externalADC1.drdyPinPort = DRDY1_GPIO_Port;
    externalADC1.drdyPin = DRDY1_Pin;

    HAL_GPIO_WritePin(CS1_GPIO_Port, CS1_Pin, SET);
    HAL_GPIO_WritePin(CS2_GPIO_Port, CS2_Pin, SET);
    HAL_GPIO_WritePin(STARTSYNC_1_GPIO_Port, STARTSYNC_1_Pin, RESET);
    HAL_GPIO_WritePin(STARTSYNC_2_GPIO_Port, STARTSYNC_2_Pin, RESET);
    // Delay to allow power supplies to settle
    tx_thread_sleep(5);

    // Set up registers
    StartUpRoutine(&externalADC1);

//    WriteRegister(&externalADC1, STATUS_ADDR_MASK, data);
//
//    // Set the PGA
    uint8_t data = ADS_DELAY_14 + ADS_PGA_ENABLED + ADS_GAIN_128;
    WriteRegister(&externalADC1, REG_ADDR_PGA, data);
//
//    // Use single shot conversions
    data = ADS_CONVMODE_SS + ADS_DR_4000 + ADS_FILTERTYPE_LL;
    WriteRegister(&externalADC1, REG_ADDR_DATARATE, data);

    data = ADS_REFP_BYP_DISABLE + ADS_REFN_BYP_DISABLE + ADS_REFSEL_INT + ADS_REFINT_ON_PDWN;
    WriteRegister(&externalADC1, REG_ADDR_REF, data);

    data = ADS_P_AIN2 + ADS_N_AIN3;
    WriteRegister(&externalADC1, REG_ADDR_INPMUX, data);

//
//    // Start Conversions
//    SendCommand(&externalADC1, OPC
//    uint8_t txData[3] = {
//        REGWR_OPCODE_MASK + INPMUX_ADDR_MASK,
//        0x00,
//        adcMuxStates[inputSet]
//    };
//    uint32_t combinedData[6];
//    FDCAN_TxHeaderTypeDef exADC1Header = {
//        .Identifier = UCR_01_FRONT_STRAIN_GAUGES1_FRAME_ID,
//        .IdType = FDCAN_STANDARD_ID,
//        .TxFrameType = FDCAN_DATA_FRAME,
//        .DataLength = FDCAN_DLC_BYTES_20,
//        .ErrorStateIndicator = FDCAN_ESI_ACTIVE,
//        .BitRateSwitch = FDCAN_BRS_ON,
//        .FDFormat = FDCAN_FD_CAN,
//        .TxEventFifoControl = FDCAN_NO_TX_EVENTS,
//        .MessageMarker = 0
//    };
//    uint32_t thing = 0;
    uint8_t thing[1] = {0};

    while(1){
//        SendCommand(&externalADC1, OPCODE_START);
//        tx_semaphore_get(&semaphoreExADC1, TX_WAIT_FOREVER);
//        stuff = ReadADCData(&externalADC1, thing, COMMAND);
//        for(int i = 0; i < 6; i ++){
//            WriteRegister(&externalADC1, ADC_MUX)
//        }
        // Wait for conversion to finish
//        tx_semaphore_get(&semaphoreExADC1, TX_WAIT_FOREVER);
        // Start send receive
//        HAL_GPIO_WritePin(externalADC1.csPinPort, externalADC1.csPin, 1);
//        // Receive data and also set the inputs to the next inputs
////        HAL_SPI_TransmitReceive_DMA(&hspi4, txData, rxData, 4);
//        HAL_SPI_Transmit(&hspi4, txData, Size, Timeout)
        // Wait for data reception
//        tx_semaphore_get(&semaphoreExADC1, TX_WAIT_FOREVER);
//        combinedData[inputSet] = (rxData[0] << 16) + (rxData[1] << 8) + rxData[2];
//        txData[2] = adcMuxStates[inputSet++];
//        if(inputSet == 6){
//            inputSet = 0;
//        }
//        if(inputSet == 6){
//            struct ucr_01_front_strain_gauges1_t stuff = {
//                .gauge1 = combinedData[0],
//                .gauge2 = combinedData[1],
//                .gauge3 = combinedData[2],
//                .gauge4 = combinedData[3],
//                .gauge5 = combinedData[4],
//                .gauge6 = combinedData[5]
//            };
//            ucr_01_front_strain_gauges1_pack(canTxData, &stuff, UCR_01_FRONT_STRAIN_GAUGES1_LENGTH);
////            HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &exADC1Header, canTxData);
//            inputSet = 0;
//            tx_thread_sleep(10);
////        for(int i = 0; i < 6; i++){
////            combinedData[i] = thing;
////        }
////        thing ++;
////        struct ucr_01_front_strain_gauges1_t stuff = {
////            .gauge1 = combinedData[0],
////            .gauge2 = combinedData[1],
////            .gauge3 = combinedData[2],
////            .gauge4 = combinedData[3],
////            .gauge5 = combinedData[4],
////            .gauge6 = combinedData[5]
////        };
////        ucr_01_front_strain_gauges1_pack(canTxData, &stuff, UCR_01_FRONT_STRAIN_GAUGES1_LENGTH);
////        HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &exADC1Header, canTxData);
//        }
        tx_thread_sleep(250);
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















