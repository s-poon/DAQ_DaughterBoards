/*
 * analog_control.c
 *
 *  Created on: Apr 19, 2024
 *      Author: Steven
 */


#include "analog_control.h"
#include "threadx.h"
#include "aero_sensors.h"


static const gpio_control_t analogSwitch1 = {
		.port = ANALOGSWITCH_1_GPIO_Port,
		.pin = ANALOGSWITCH_1_Pin
};
static const gpio_control_t analogSwitch2 = {
		.port = ANALOGSWITCH_2_GPIO_Port,
		.pin = ANALOGSWITCH_2_Pin
};
static const gpio_control_t analogSwitch3 = {
		.port = ANALOGSWITCH_3_GPIO_Port,
		.pin = ANALOGSWITCH_3_Pin
};
static const gpio_control_t analogSwitch4 = {
		.port = ANALOGSWITCH_4_GPIO_Port,
		.pin = ANALOGSWITCH_4_Pin
};
static const gpio_control_t analogSwitch5 = {
		.port = ANALOGSWITCH_5_GPIO_Port,
		.pin = ANALOGSWITCH_5_Pin
};
static const gpio_control_t analogSwitch6 = {
		.port = ANALOGSWITCH_6_GPIO_Port,
		.pin = ANALOGSWITCH_6_Pin
};
static const gpio_control_t analogSwitch7 = {
		.port = ANALOGSWITCH_7_GPIO_Port,
		.pin = ANALOGSWITCH_7_Pin
};
static const gpio_control_t analogSwitch8 = {
		.port = ANALOGSWITCH_8_GPIO_Port,
		.pin = ANALOGSWITCH_8_Pin
};

static gpio_control_t analogSwitches[NUM_ADC_CHANNELS] = {
	analogSwitch1,
	analogSwitch2,
	analogSwitch3,
	analogSwitch4,
	analogSwitch5,
	analogSwitch6,
	analogSwitch7,
	analogSwitch8
};

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc){
    tx_semaphore_put(&semaphoreAnalog);

}

uint8_t setAnalogSwitches(
	const uint8_t switchSettings[NUM_ADC_CHANNELS]
){
	uint8_t retval = UCR_OK;

	for(int i = 0; i < NUM_ADC_CHANNELS; i ++){
		if(switchSettings[i]){
			set12VSensor(&analogSwitches[i]);
		}else{
			set5VSensor(&analogSwitches[i]);
		}
	}
	return retval;
}

uint8_t set12VSensor(
	gpio_control_t *self
){
	uint8_t retval = UCR_OK;
	if(NULL == self){
		retval = UCR_NPTR;
	}
	HAL_GPIO_WritePin(&self->port, self->pin, SET_12V);
	return retval;
}

uint8_t set5VSensor(
	gpio_control_t *self
){
	uint8_t retval = UCR_OK;
	if(NULL == self){
		retval = UCR_NPTR;
	}
	HAL_GPIO_WritePin(&self->port, self->pin, SET_5V);
	return retval;
}
