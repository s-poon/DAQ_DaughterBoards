/*
 * AeroSensors.h
 *
 *  Created on: Apr 17, 2024
 *      Author: Steven
 */

#ifndef INC_AERO_SENSORS_H_
#define INC_AERO_SENSORS_H_

#include "main.h"

#define NUM_AERO_SENSORS        (3u)
#define ONE_BYTE                (1u)
#define I2C_TIMEOUT             (100u)


typedef struct{
	int32_t pressure;
	int16_t temperature;
	uint8_t sensorNumber;
}aeroSensor_t;

uint8_t AeroInit(void);
uint8_t StartSensorReading(aeroSensor_t* sensor);
uint8_t ReadData(aeroSensor_t* sensor);


#endif /* INC_AERO_SENSORS_H_ */
