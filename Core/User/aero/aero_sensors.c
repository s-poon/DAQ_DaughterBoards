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


uint16_t pressureAddresses[3] = {
        DATA_MSB_ADDRESS,
        DATA_CSB_ADDRESS,
        DATA_LSB_ADDRESS
};

void SetChannel(uint8_t sensor){
    uint8_t data = 1 << (sensor - 1);
    HAL_I2C_Master_Transmit(&hi2c4, SWITCH_ADDRESS, &data, 1, 1000);
}

uint8_t TransmitToAll(){
    uint8_t data = 0b00000111;
    HAL_I2C_Master_Transmit(&hi2c4, SWITCH_ADDRESS, &data, 1, 1000);
    return UCR_OK;
}

void StartSensorReading(){
    uint8_t data = START_SENSOR;
    HAL_I2C_Mem_Write_IT(&hi2c4, SENSOR_ADDRESS, CMD_ADDRESS, 1, &data, 1);
}

uint8_t ReadData(){
    uint8_t pressureData[3];
    uint8_t temperatureData[2];
    for(int i = 0; i < 3; i ++){
        HAL_I2C_Mem_Read_IT(&hi2c4, SENSOR_ADDRESS, pressureAddresses[i], 1, &pressureData[i], 1);     //PAGE 561 of HAL manual
    }
//    uint32_t pressureReading = pressureData[0] * 65536 + pressureData[1] * 256 + pressureData[2];

    for(int i = 0; i < 2; i ++){
        HAL_I2C_Mem_Read_IT(&hi2c4, SENSOR_ADDRESS, DATA_MSB_ADDRESS, 1, &temperatureData[0], 1);
        HAL_I2C_Mem_Read_IT(&hi2c4, SENSOR_ADDRESS, DATA_MSB_ADDRESS, 1, &temperatureData[1], 1);
    }
    return 0;
}

