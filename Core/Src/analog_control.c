/*
 * analog_control.c
 *
 *  Created on: Apr 19, 2024
 *      Author: Steven
 */

#include "analog_control.h"
#include "sr_common.h"

static uint32_t analogPins[8][2] = {
        {ANALOGSWITCH_1_GPIO_Port, ANALOGSWITCH_1_Pin},
        {ANALOGSWITCH_2_GPIO_Port, ANALOGSWITCH_2_Pin},
        {ANALOGSWITCH_3_GPIO_Port, ANALOGSWITCH_3_Pin},
        {ANALOGSWITCH_4_GPIO_Port, ANALOGSWITCH_4_Pin},
        {ANALOGSWITCH_5_GPIO_Port, ANALOGSWITCH_5_Pin},
        {ANALOGSWITCH_6_GPIO_Port, ANALOGSWITCH_6_Pin},
        {ANALOGSWITCH_7_GPIO_Port, ANALOGSWITCH_7_Pin},
        {ANALOGSWITCH_8_GPIO_Port, ANALOGSWITCH_8_Pin}
};

void SetDividers(uint8_t voltageModes[]){
//    uint8_t size = sizeof(voltageModes) / sizeof(voltageModes[0]);
//    for(int i = 0; i < size; i ++){
//        HAL_GPIO_WritePin((GPIO_TypeDef *)analogPins[i][0], analogPins[i][1], voltageModes[i]);
//    }
    HAL_GPIO_WritePin(ANALOGSWITCH_1_GPIO_Port, ANALOGSWITCH_1_Pin, voltageModes[1]);

}

uint8_t set_divider_voltage_mode_12_volt(
    analog_control_t* self)
{
    uint8_t retval = SR_OK;

    if (NULL ==self)
    {
        retval = SR_NPTR;
    }
    else if (HAL_OK != HAL_GPIO_WritePin(&(self->pin_port), self.pin, SET_12V))
    {
        retval = SR_NOT_OK;
    }

    return retval;
}

uint8_t set_divider_votlage_mode_5_volt(
    analog_control_t* self)
{
    uint8_t retval = SR_OK;

    if (NULL ==self)
    {
        retval = SR_NPTR;
    }
    else if (HAL_OK != HAL_GPIO_WritePin(&(self->pin_port), self.pin, SET_5V))
    {
        retval = SR_NOT_OK;
    }

    return retval;
}