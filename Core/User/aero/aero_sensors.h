/*
 * AeroSensors.h
 *
 *  Created on: Apr 17, 2024
 *      Author: Steven
 */

#ifndef INC_AERO_SENSORS_H_
#define INC_AERO_SENSORS_H_

#include "main.h"


typedef struct{
	uint32_t pressure;
	uint16_t temperature;
}aeroData_t;

void TransmitToAll();
void StartSensorReading();
void SetChannel(uint8_t sensor);
uint8_t ReadData();

#endif /* INC_AERO_SENSORS_H_ */
