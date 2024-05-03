/*
 * strain_gauges_datatypes.h
 *
 *  Created on: May 2, 2024
 *      Author: Steven
 */

#ifndef USER_STRAIN_GAUGES_STRAIN_GAUGES_DATATYPES_H_
#define USER_STRAIN_GAUGES_STRAIN_GAUGES_DATATYPES_H_

#include <stdint.h>
#include "main.h"

#define NUM_REGISTERS       (18u)

typedef struct{
    uint8_t registers[NUM_REGISTERS];
    GPIO_TypeDef* startSyncPinPort;
    uint16_t startSyncPin;
    GPIO_TypeDef* csPinPort;
    uint16_t csPin;
    GPIO_TypeDef* drdyPinPort;
    uint16_t drdyPin;
    GPIO_TypeDef* resetPinPort;
    uint16_t resetPin;
}ads124S08Control_t;

#endif /* USER_STRAIN_GAUGES_STRAIN_GAUGES_DATATYPES_H_ */
