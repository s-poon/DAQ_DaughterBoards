/*
 * analog_control.h
 *
 *  Created on: Apr 19, 2024
 *      Author: Steven
 */

#ifndef INC_ANALOG_CONTROL_H_
#define INC_ANALOG_CONTROL_H_

#include "main.h"


void SetDividers(uint8_t voltageModes[]);

uint8_t set_divider_voltage_mode_12_volt(
    analog_control_t* self);

uint8_t set_divider_votlage_mode_5_volt(
    analog_control_t* self);

// TODO: Move to a analog_control_datatypes.h file
#define SET_12V         (1u)
#define SET_5V          (0u)

typedef struct {
    GPIO_TypeDef    pin_port;
    uint16_t        pin;
}analog_control_t;

#endif /* INC_ANALOG_CONTROL_H_ */
