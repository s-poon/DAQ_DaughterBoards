/*
 * analog_control.h
 *
 *  Created on: Apr 19, 2024
 *      Author: Steven
 */

#ifndef INC_ANALOG_CONTROL_H_
#define INC_ANALOG_CONTROL_H_

#include "main.h"
#include "analog_control_datatypes.h"
#include "ucr_common.h"

uint8_t setAnalogSwitches(
	const uint8_t switchSettings[NUM_ADC_CHANNELS]
);

uint8_t set12VSensor(
		gpio_control_t *self
);
uint8_t set5VSensor(
		gpio_control_t *self
);
#endif /* INC_ANALOG_CONTROL_H_ */
