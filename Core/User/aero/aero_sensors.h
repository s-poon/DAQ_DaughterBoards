/*
 * AeroSensors.h
 *
 *  Created on: Apr 17, 2024
 *      Author: Steven
 */

#ifndef INC_AERO_SENSORS_H_
#define INC_AERO_SENSORS_H_

#include "main.h"
#include "aero_datatypes.h"

#define NUM_AERO_SENSORS        (3u)
#define ONE_BYTE                (1u)
#define I2C_TIMEOUT             (100u)
#define PRESSURE_MSB_OFFSET     (23u)
#define TEMPERATURE_MSB_OFFSET  (15u)
#define ONE_BYTE_OFFSET         (8u)
#define TWO_BYTE_OFFSET         (16u)

uint8_t AeroInit(void);
uint8_t StartSensorReading(aeroSensor_t* sensor);
uint8_t ReadData(aeroSensor_t* sensor);


#endif /* INC_AERO_SENSORS_H_ */
