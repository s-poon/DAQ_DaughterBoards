/*
 * frequency_sensors.h
 *
 *  Created on: Apr 20, 2024
 *      Author: steve
 */

#ifndef USER_FREQUENCY_FREQUENCY_SENSORS_H_
#define USER_FREQUENCY_FREQUENCY_SENSORS_H_

#include "main.h"
#include "frequency_datatypes.h"


void timerExpirationFrequency(ULONG thing);
uint8_t FrequencyInit(void);


extern uint32_t difference[4];
#endif /* USER_FREQUENCY_FREQUENCY_SENSORS_H_ */
