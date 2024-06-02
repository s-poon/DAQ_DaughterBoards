/*
 * aero_datatypes.h
 *
 *  Created on: Apr 20, 2024
 *      Author: Steven
 */

#ifndef USER_AERO_AERO_DATATYPES_H_
#define USER_AERO_AERO_DATATYPES_H_

#define SENSOR_ADDRESS      0x6D << 1
#define SWITCH_ADDRESS      0x70 << 1

#define DATA_MSB_ADDRESS    0x06
#define DATA_CSB_ADDRESS    0x07
#define DATA_LSB_ADDRESS    0x08

#define TEMP_MSB_ADDRESS    0x09
#define TEMP_LSB_ADDRESS    0x0A

#define CMD_ADDRESS         0x30
#define SYS_CONFIG_ADDRESS  0xA5 << 1
#define P_CONFIG_ADDRESS    0xA6 << 1

#define START_SENSOR        0x0A


typedef struct{
    int32_t pressure;
    int16_t temperature;
    uint8_t sensorNumber;
}aeroSensor_t;

#endif /* USER_AERO_AERO_DATATYPES_H_ */
