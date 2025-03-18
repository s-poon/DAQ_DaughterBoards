/*
 * threadx.c
 *
 *  Created on: Apr 20, 2024
 *      Author: Steven
 */
#include "threadx.hpp"

extern "C"{
    #include "ucr_common.h"
    #include "analog_control_datatypes.h"
    #include "analog_control.h"
    #include "aero_sensors.h"
    #include "frequency_sensors.h"
    #include "tim.h"
    #include "../../vendor_generated/can_tools/can.h"
    #include "strain_gauges.h"
    #include "spi.h"
    #include "fdcan.h"
    #include "adc.h"
    //#include "GPIOPin.hpp"
    #include "ADS124S08.hpp"

    #include "../../vendor_generated/can_tools/can_api.h"

    extern frequency_t ChannelData[4];
    extern aeroSensor_t AeroSensors[NUM_AERO_SENSORS];
    extern const uint8_t adcMuxStates[];
}

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
int32_t thing;
double thingConverted;

static const uint8_t analogSwitchStates[NUM_ADC_CHANNELS] = {
	SET_5V,
	SET_5V,
	SET_12V,
	SET_12V,
	SET_12V,
	SET_12V,
	SET_5V,
	SET_12V
};

float lookUp[] = {
        -1.119, -1.081, -1.043, -1.006, -0.968, -0.930, -0.892, -0.854, -0.816, -0.778,
        -0.739, -0.701, -0.663, -0.624, -0.586, -0.547, -0.508, -0.470, -0.431, -0.392,
        -0.353, -0.314, -0.275, -0.236, -0.197, -0.157, -0.118, -0.079, -0.039,
        0.000, 0.039, 0.079, 0.119, 0.158, 0.198, 0.238, 0.277, 0.317, 0.357,
        0.397, 0.437, 0.477, 0.517, 0.557, 0.597, 0.637, 0.677, 0.718, 0.758,
        0.798, 0.838, 0.879, 0.919, 0.960, 1.000, 1.041, 1.081, 1.122, 1.163,
        1.203, 1.244, 1.285, 1.326, 1.366, 1.407, 1.448, 1.489, 1.530, 1.571,
        1.612, 1.653, 1.694, 1.735, 1.776, 1.817, 1.858, 1.899, 1.941, 1.982,
        2.023, 2.064, 2.106, 2.147, 2.188, 2.230, 2.271, 2.312, 2.354, 2.395,
        2.436, 2.478, 2.519, 2.561, 2.602, 2.644, 2.685, 2.727, 2.768, 2.810,
        2.851, 2.893, 2.934, 2.976, 3.017, 3.059, 3.100, 3.142, 3.184, 3.225,
        3.267, 3.308, 3.350, 3.391, 3.433, 3.474, 3.516, 3.557, 3.599, 3.640,
        3.682, 3.723, 3.765, 3.806, 3.848, 3.889, 3.931, 3.972, 4.013, 4.055,
        4.096, 4.138, 4.179, 4.220, 4.262, 4.303, 4.344, 4.385, 4.427, 4.468,
        4.509, 4.550, 4.591, 4.633, 4.674, 4.715, 4.756, 4.797, 4.838, 4.879,
        4.920, 4.961, 5.002, 5.043, 5.084, 5.124, 5.165, 5.206, 5.247, 5.288,
        5.328, 5.369, 5.410, 5.450, 5.491, 5.532, 5.572, 5.613, 5.653, 5.694,
        5.735, 5.775, 5.815, 5.856, 5.896, 5.937, 5.977, 6.017, 6.058, 6.098,
        6.138, 6.179, 6.219, 6.259, 6.299, 6.339, 6.380, 6.420, 6.460, 6.500,
        6.540, 6.580, 6.620, 6.660, 6.701, 6.741, 6.781, 6.821, 6.861, 6.901,
        6.941, 6.981, 7.021, 7.060, 7.100, 7.140, 7.180, 7.220, 7.260, 7.300,
        7.340, 7.380, 7.420, 7.460, 7.500, 7.540, 7.579, 7.619, 7.659, 7.699,
        7.739, 7.779, 7.819, 7.859, 7.899, 7.939, 7.979, 8.019, 8.059, 8.099,
        8.138, 8.178, 8.218, 8.258, 8.298, 8.338, 8.378, 8.418, 8.458, 8.499,
        8.539, 8.579, 8.619, 8.659, 8.699, 8.739, 8.779, 8.819, 8.860, 8.900,
        8.940, 8.980, 9.020, 9.061, 9.101, 9.141, 9.181, 9.222, 9.262, 9.302,
        9.343, 9.383, 9.423, 9.464, 9.504, 9.545, 9.585, 9.626, 9.666, 9.707,
        9.747, 9.788, 9.828, 9.869, 9.909, 9.950, 9.991, 10.031, 10.072, 10.113,
        10.153, 10.194, 10.235, 10.276, 10.316, 10.357, 10.398, 10.439, 10.480, 10.520,
        10.561, 10.602, 10.643, 10.684, 10.725, 10.766, 10.807, 10.848, 10.889, 10.930,
        10.971, 11.012, 11.053, 11.094, 11.135, 11.176, 11.217, 11.259, 11.300, 11.341,
        11.382, 11.423, 11.465, 11.506, 11.547, 11.588, 11.630, 11.671, 11.712, 11.753,
        11.795, 11.836, 11.877, 11.919, 11.960, 12.001, 12.043, 12.084, 12.126, 12.167,
        12.209, 12.250, 12.291, 12.333, 12.374, 12.416, 12.457, 12.499, 12.540, 12.582,
        12.624, 12.665, 12.707, 12.748, 12.790, 12.831, 12.873, 12.915, 12.956, 12.998,
        13.040, 13.081, 13.123, 13.165, 13.206, 13.248, 13.290, 13.331, 13.373, 13.415,
        13.457, 13.498, 13.540, 13.582, 13.624, 13.665, 13.707, 13.749, 13.791, 13.833,
        13.874, 13.916, 13.958, 14.000, 14.042, 14.084, 14.126, 14.167, 14.209, 14.251,
        14.293, 14.335, 14.377, 14.419, 14.461, 14.503, 14.545, 14.587, 14.629, 14.671,
        14.713, 14.755, 14.797, 14.839, 14.881, 14.923, 14.965, 15.007, 15.049, 15.091,
        15.133, 15.175, 15.217, 15.259, 15.301, 15.343, 15.385, 15.427, 15.469, 15.511,
        15.554, 15.596, 15.638, 15.680, 15.722, 15.764, 15.806, 15.849, 15.891, 15.933,
        15.975, 16.017, 16.059, 16.102, 16.144, 16.186, 16.228, 16.270, 16.313, 16.355,
};

extern "C"{
    UINT ThreadX_Init(
            VOID *memory_ptr
    ){
        UINT ret = TX_SUCCESS;
        TX_BYTE_POOL *bytePool = (TX_BYTE_POOL*)memory_ptr;
        CHAR *pointer;

        if(tx_byte_allocate(bytePool, (VOID**) &pointer, TX_APP_STACK_SIZE, TX_NO_WAIT) != TX_SUCCESS){
            return TX_POOL_ERROR;
        }

        if(tx_thread_create(&txMainThread, (char*)"txMainThread", txMainThreadEntry, 0, pointer,
                            TX_APP_STACK_SIZE, TX_APP_THREAD_PRIO, TX_APP_THREAD_PREEMPTION_THRESHOLD,
                            TX_APP_THREAD_TIME_SLICE, TX_APP_THREAD_AUTO_START) != TX_SUCCESS
        ){
            return TX_THREAD_ERROR;
        }

        if(tx_byte_allocate(bytePool, (VOID**) &pointer, TX_APP_STACK_SIZE, TX_NO_WAIT) != TX_SUCCESS){
            return TX_POOL_ERROR;
        }

        if(tx_thread_create(&txAnalogThread, (char*)"txAnalogThread", txAnalogThreadEntry, 0, pointer,
                            TX_APP_STACK_SIZE, TX_ANALOG_PRIO, TX_APP_THREAD_PREEMPTION_THRESHOLD,
                            TX_APP_THREAD_TIME_SLICE, TX_APP_THREAD_AUTO_START) != TX_SUCCESS
        ){
            return TX_THREAD_ERROR;
        }

        if(tx_byte_allocate(bytePool, (VOID**) &pointer, TX_APP_STACK_SIZE, TX_NO_WAIT) != TX_SUCCESS){
            return TX_POOL_ERROR;
        }

    //	if(tx_thread_create(&txAeroThread, "txAeroThread", txAeroThreadEntry, 0, pointer,
    //					   TX_APP_STACK_SIZE, 12, TX_APP_THREAD_PREEMPTION_THRESHOLD,
    //					   TX_APP_THREAD_TIME_SLICE, TX_APP_THREAD_AUTO_START) != TX_SUCCESS
    //    ){
    //		return TX_THREAD_ERROR;
    //	}

    //    if(tx_byte_allocate(bytePool, (VOID**) &pointer, TX_APP_STACK_SIZE, TX_NO_WAIT) != TX_SUCCESS){
    //        return TX_POOL_ERROR;
    //    }
    //
    //	if(tx_thread_create(&txCAN500HzThread, "txCAN500Hz", txCAN500HzThreadEntry, 0, pointer,
    //					   TX_APP_STACK_SIZE, 13, TX_APP_THREAD_PREEMPTION_THRESHOLD,
    //					   TX_APP_THREAD_TIME_SLICE, TX_APP_THREAD_AUTO_START) != TX_SUCCESS
    //    ){
    //		return TX_THREAD_ERROR;
    //	}

        if(tx_byte_allocate(bytePool, (VOID**) &pointer, TX_APP_STACK_SIZE, TX_NO_WAIT) != TX_SUCCESS){
            return TX_POOL_ERROR;
        }

        if(tx_thread_create(&txCAN100HzThread, (char*)"txCAN100Hz", txCAN100HzThreadEntry, 0, pointer,
                        TX_APP_STACK_SIZE, 12, TX_APP_THREAD_PREEMPTION_THRESHOLD,
                        TX_APP_THREAD_TIME_SLICE, TX_APP_THREAD_AUTO_START) != TX_SUCCESS
        ){
            return TX_THREAD_ERROR;
        }

        if(tx_byte_allocate(bytePool, (VOID**) &pointer, TX_APP_STACK_SIZE, TX_NO_WAIT) != TX_SUCCESS){
            return TX_POOL_ERROR;
        }

        if(tx_thread_create(&txStrainThread, (char*)"txStrainThread", txADS1ThreadInput, 0, pointer,
                        TX_APP_STACK_SIZE, 15, TX_APP_THREAD_PREEMPTION_THRESHOLD,
                        TX_APP_THREAD_TIME_SLICE, TX_APP_THREAD_AUTO_START) != TX_SUCCESS
        ){
            return TX_THREAD_ERROR;
        }

        tx_semaphore_create(&semaphoreAnalog, (char*)"semaphoreAnalog", 0);
        tx_semaphore_create(&semaphoreAero, (char*)"semaphoreAero", 0);
        tx_semaphore_create(&semaphoreFrequency, (char*)"semaphoreFrequency", 1);
        tx_semaphore_create(&semaphoreExADC1, (char*)"semaphoreExADC1", 0);
        tx_semaphore_create(&semaphoreExADC2, (char*)"semaphoreExADC2", 0);
        tx_semaphore_create(&semaphoreSPI, (char*)"semaphoreSPI", 0);
        

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
                .analog1 = (uint16_t)adcValues[0],
                .analog2 = (uint16_t)adcValues[1],
                .analog3 = (uint16_t)adcValues[2],
                .analog4 = (uint16_t)adcValues[3],
                .analog5 = (uint16_t)adcValues[4],
                .analog6 = (uint16_t)adcValues[5],
                .analog7 = (uint16_t)adcValues[6],
                .analog8 = (uint16_t)adcValues[7]
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
            for(unsigned int i = 0; i < NUM_AERO_SENSORS; i ++){
                StartSensorReading(&AeroSensors[i]);
            }
            tx_thread_sleep(20);

            for(unsigned int i = 0; i < NUM_AERO_SENSORS; i ++){
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
    uint32_t data1[6];
    uint32_t data2[6];
    
    void txADS1ThreadInput(
        ULONG threadInput
    ){
    //    uint8_t rxData[3];
    //    uint8_t inputSet = 0;
        uint8_t canTxData[20];
    //    uint64_t combinedData[6];


        GPIOPin exADC1CSPin = GPIOPin(CS1_GPIO_Port, CS1_Pin);
        GPIOPin exADC1StartSyncPin = GPIOPin(STARTSYNC_1_GPIO_Port, STARTSYNC_1_Pin);
        GPIOPin exADC1ResetPin = GPIOPin(RESET1_GPIO_Port, RESET1_Pin);
        GPIOPin exADC1DRDYPin = GPIOPin(DRDY1_GPIO_Port, DRDY1_Pin);

        GPIOPin exADC2CSPin = GPIOPin(CS2_GPIO_Port, CS2_Pin);
        GPIOPin exADC2StartSyncPin = GPIOPin(STARTSYNC_2_GPIO_Port, STARTSYNC_2_Pin);
        GPIOPin exADC2ResetPin = GPIOPin(RESET2_GPIO_Port, RESET2_Pin);
        GPIOPin exADC2DRDYPin = GPIOPin(DRDY2_GPIO_Port, DRDY2_Pin);

        ADS124S08 adc1(exADC1StartSyncPin, exADC1CSPin, exADC1DRDYPin, exADC1ResetPin);
        ADS124S08 adc2(exADC2StartSyncPin, exADC2CSPin, exADC2DRDYPin, exADC2ResetPin);


        adc1.csPin.Set();
        adc2.csPin.Set();

        adc1.startSyncPin.Clear();
        adc2.startSyncPin.Clear();

        // Delay to allow power supplies to settle
        tx_thread_sleep(1000);

        // Set up registers
    //    StartUpRoutine(&externalADC1);
    //    StartUpRoutine(&externalADC2);

        adc1.StartUpRoutine();
        adc2.StartUpRoutine();

    //    WriteRegister(&externalADC1, STATUS_ADDR_MASK, data);
    //
    //    // Set the PGA
        uint8_t data = ADS_DELAY_14 + ADS_PGA_ENABLED + ADS_GAIN_32;
        adc1.WriteRegister(REG_ADDR_PGA, data);
        adc2.WriteRegister(REG_ADDR_PGA, data);
    //    WriteRegister(&externalADC1, REG_ADDR_PGA, data);
    //    WriteRegister(&externalADC2, REG_ADDR_PGA, data);
    ////
    ////    // Use single shot conversions/
       data = ADS_CONVMODE_SS + ADS_DR_4000 + ADS_FILTERTYPE_LL;
       adc1.WriteRegister(REG_ADDR_DATARATE, data);
       adc2.WriteRegister(REG_ADDR_DATARATE, data);
    //    WriteRegister(&externalADC1, REG_ADDR_DATARATE, data);
    //    WriteRegister(&externalADC2, REG_ADDR_DATARATE, data);
    //
       data = ADS_REFP_BYP_DISABLE + ADS_REFN_BYP_DISABLE + ADS_REFSEL_INT + ADS_REFINT_ON_PDWN;
       adc1.WriteRegister(REG_ADDR_REF, data);
       adc2.WriteRegister(REG_ADDR_REF, data);
    //    WriteRegister(&externalADC1, REG_ADDR_REF, data);
    //    WriteRegister(&externalADC2, REG_ADDR_REF, data);
    //
       data = ADS_P_AIN7 + ADS_N_AIN6;
       adc1.WriteRegister(REG_ADDR_INPMUX, data);
       adc2.WriteRegister(REG_ADDR_INPMUX, data);

//       data = ADS_VB_AIN1 + ADS_VBIAS_LVL_DIV2;
//
//       adc1.WriteRegister(REG_ADDR_VBIAS, data);
//       adc2.WriteRegister(REG_ADDR_VBIAS, data);
    //    WriteRegister(&externalADC1, REG_ADDR_INPMUX, data);
    //    WriteRegister(&externalADC2, REG_ADDR_INPMUX, data);

    //
    //    // Start Conversions
    //    SendCommand(&externalADC1, OPC
    //    uint8_t txData[3] = {
    //        REGWR_OPCODE_MASK + INPMUX_ADDR_MASK,
    //        0x00,
    //        adcMuxStates[inputSet]
    //    };
    //    uint32_t combinedData[6];
//       FDCAN_TxHeaderTypeDef exADC1Header = {
//           .Identifier = UCR_01_FRONT_STRAIN_GAUGES1_FRAME_ID,
//           .IdType = FDCAN_STANDARD_ID,
//           .TxFrameType = FDCAN_DATA_FRAME,
//           .DataLength = FDCAN_DLC_BYTES_20,
//           .ErrorStateIndicator = FDCAN_ESI_ACTIVE,
//           .BitRateSwitch = FDCAN_BRS_ON,
//           .FDFormat = FDCAN_FD_CAN,
//           .TxEventFifoControl = FDCAN_NO_TX_EVENTS,
//           .MessageMarker = 0
//       };
//
//       FDCAN_TxHeaderTypeDef exADC2Header = {
//           .Identifier = UCR_01_FRONT_STRAIN_GAUGES2_FRAME_ID,
//           .IdType = FDCAN_STANDARD_ID,
//           .TxFrameType = FDCAN_DATA_FRAME,
//           .DataLength = FDCAN_DLC_BYTES_20,
//           .ErrorStateIndicator = FDCAN_ESI_ACTIVE,
//           .BitRateSwitch = FDCAN_BRS_ON,
//           .FDFormat = FDCAN_FD_CAN,
//           .TxEventFifoControl = FDCAN_NO_TX_EVENTS,
//           .MessageMarker = 0
//       };
    //    uint32_t thing = 0;
        uint8_t status[1] = {0};


        while(1){
            adc1.SendCommand(OPCODE_START);
            tx_thread_sleep(1);
            thing = adc1.ReadADCData(status, COMMAND);
            thingConverted = (thing * 2.5) / (8388608.0 * 32.0) * 1000;


            for(unsigned int i = 0; i < 429 - 1; i++){
                if(lookUp[i] < thingConverted && lookUp[i + 1] > thingConverted){
                    stuff = i - 29;
                    break;
                }
            }

    //    	for(int i = 0; i < 6; i ++){
//        		WriteRegister(&externalADC1, REG_ADDR_INPMUX, adcMuxStates[i]);
    //			WriteRegister(&externalADC2, REG_ADDR_INPMUX, adcMuxStates[i]);
    ////			tx_thread_sleep(1);
    //			SendCommand(&externalADC1, OPCODE_START);
    //	        SendCommand(&externalADC2, OPCODE_START);
    //	        tx_thread_sleep(1);
    //	        data1[i] = ReadADCData(&externalADC1, status, COMMAND);
    //	        data2[i] = ReadADCData(&externalADC2, status, COMMAND);
    //    	}

//        for(int i = 0; i < 6; i ++){
//            adc1.WriteRegister(REG_ADDR_INPMUX, adcMuxStates[i]);
//            adc2.WriteRegister(REG_ADDR_INPMUX, adcMuxStates[i]);
//    //			tx_thread_sleep(1);
//            adc1.SendCommand(OPCODE_START);
//            adc2.SendCommand(OPCODE_START);
//            tx_thread_sleep(1);
//            data1[i] = adc1.ReadADCData(status, COMMAND);
//            data2[i] = adc2.ReadADCData(status, COMMAND);
//        }



    //        tx_thread_sleep(1);
    //        tx_semaphore_get(&semaphoreExADC1, TX_WAIT_FOREVER);
            // for(int i = 0; i < 6; i ++){

            // }
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
//            struct ucr_01_front_strain_gauges1_t set1 = {
//                .gauge1 = data1[0],
//                .gauge2 = data1[1],
//                .gauge3 = data1[2],
//                .gauge4 = data1[3],
//                .gauge5 = data1[4],
//                .gauge6 = data1[5]
//            };
//
//            struct ucr_01_front_strain_gauges2_t set2 = {
//                .gauge1 = data2[0],
//                .gauge2 = data2[1],
//                .gauge3 = data2[2],
//                .gauge4 = data2[3],
//                .gauge5 = data2[4],
//                .gauge6 = data2[5]
//            };
//            ucr_01_front_strain_gauges1_pack(canTxData, &set1, UCR_01_FRONT_STRAIN_GAUGES1_LENGTH);
//            HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &exADC1Header, canTxData);
//            ucr_01_front_strain_gauges2_pack(canTxData, &set2, UCR_01_FRONT_STRAIN_GAUGES1_LENGTH);
//            HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &exADC2Header, canTxData);
    //		tx_thread_sleep();
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
            tx_thread_sleep(500);
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















