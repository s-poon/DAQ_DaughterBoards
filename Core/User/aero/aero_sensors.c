/*
 * AeroSensors.c
 *
 *  Created on: Apr 17, 2024
 *      Author: Steven
 */

#include <aero_sensors.h>
#include <aero_datatypes.h>
#include "ucr_common.h"
#include "i2c.h"

aeroSensor_t AeroSensors[NUM_AERO_SENSORS];

extern TX_SEMAPHORE semaphoreAero;

//static uint8_t SetChannel(uint8_t sensor);

uint16_t pressureAddresses[3] = {
        DATA_MSB_ADDRESS,
        DATA_CSB_ADDRESS,
        DATA_LSB_ADDRESS
};

uint8_t AeroInit(void){
    uint8_t retVal = UCR_OK;
    for(int i = 0; i < NUM_AERO_SENSORS; i ++){
        AeroSensors[i].sensorNumber = i;
    }
    return retVal;
}

uint8_t SetChannel(
    uint8_t sensor
){
    uint8_t retVal = UCR_OK;
    if(sensor > NUM_AERO_SENSORS){
        retVal = UCR_NOT_OK;
        return retVal;
    }
    uint8_t data = 1 << (sensor);
    if(HAL_OK != HAL_I2C_Master_Transmit_IT(&hi2c4, SWITCH_ADDRESS, &data, ONE_BYTE)){
        return UCR_NOT_OK;
    }
    if(TX_NO_INSTANCE != tx_semaphore_get(&semaphoreAero, 10)){
        return UCR_NOT_OK;
    }
    return retVal;
}

uint8_t StartSensorReading(
    aeroSensor_t* sensor
){
    uint8_t retVal = UCR_OK;
    if(UCR_OK != SetChannel(sensor->sensorNumber)){
        retVal = UCR_NOT_OK;
        return retVal;
    }
    uint8_t data = START_SENSOR;
    if(HAL_OK != HAL_I2C_Mem_Write_IT(&hi2c4, SENSOR_ADDRESS, CMD_ADDRESS, ONE_BYTE, &data, 1)){
        return UCR_NOT_OK;
    }
    if(TX_NO_INSTANCE != tx_semaphore_get(&semaphoreAero, 10)){
        return UCR_NOT_OK;
    }
    return retVal;
}

uint8_t ReadData(
    aeroSensor_t* sensor
){
    uint8_t retVal = UCR_OK;
    if(UCR_OK != SetChannel(sensor->sensorNumber)){
        retVal = UCR_NOT_OK;
        return retVal;
    }
    int32_t pressureReading;
    int16_t temperatureReading;
    uint8_t pressureData[3];
    uint8_t temperatureData[2];
    for(int i = 0; i < NUM_AERO_SENSORS; i ++){
        if(HAL_OK != HAL_I2C_Mem_Read_IT(&hi2c4, SENSOR_ADDRESS, pressureAddresses[i], ONE_BYTE, &pressureData[i], ONE_BYTE)){
            return UCR_NOT_OK;
        }
        if(TX_NO_INSTANCE != tx_semaphore_get(&semaphoreAero, 10)){
            return UCR_NOT_OK;
        }
    }

    pressureReading = (pressureData[0] << TWO_BYTE_OFFSET) + (pressureData[1] << ONE_BYTE_OFFSET) + pressureData[2];
    if(pressureReading >> PRESSURE_MSB_OFFSET){
        pressureReading = pressureReading - 16777216;
    }
    sensor->pressure = pressureReading;

    HAL_I2C_Mem_Read_IT(&hi2c4, SENSOR_ADDRESS, TEMP_MSB_ADDRESS, ONE_BYTE, &temperatureData[0], ONE_BYTE);
    if(TX_NO_INSTANCE != tx_semaphore_get(&semaphoreAero, 10)){
        return UCR_NOT_OK;
    }
    HAL_I2C_Mem_Read_IT(&hi2c4, SENSOR_ADDRESS, TEMP_LSB_ADDRESS, ONE_BYTE, &temperatureData[1], ONE_BYTE);
    if(TX_NO_INSTANCE != tx_semaphore_get(&semaphoreAero, 10)){
        return UCR_NOT_OK;
    }
    temperatureReading = (temperatureData[0] << ONE_BYTE_OFFSET) + temperatureData[1];
    if(temperatureReading >> TEMPERATURE_MSB_OFFSET){
        temperatureReading = temperatureReading - 65536;
    }
    sensor->temperature = temperatureReading;

    return retVal;
}

void HAL_I2C_MasterTxCpltCallback(I2C_HandleTypeDef *hi2c){
//    tx_semaphore_ceiling_put(&semaphoreAero, 1);
    tx_semaphore_put(&semaphoreAero);
}

void HAL_I2C_MasterRxCpltCallback(I2C_HandleTypeDef *hi2c){
//    tx_semaphore_ceiling_put(&semaphoreAero, 1);
    tx_semaphore_put(&semaphoreAero);
}

void HAL_I2C_MemRxCpltCallback(I2C_HandleTypeDef *hi2c){
//    tx_semaphore_ceiling_put(&semaphoreAero, 1);
    tx_semaphore_put(&semaphoreAero);
}

void HAL_I2C_MemTxCpltCallback(I2C_HandleTypeDef *hi2c){
//    tx_semaphore_ceiling_put(&semaphoreAero, 1);
    tx_semaphore_put(&semaphoreAero);
}





