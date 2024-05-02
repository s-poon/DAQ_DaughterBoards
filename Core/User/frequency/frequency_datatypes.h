/*
 * frequency_datatypes.h
 *
 *  Created on: Apr 20, 2024
 *      Author: steve
 */

#ifndef USER_FREQUENCY_FREQUENCY_DATATYPES_H_
#define USER_FREQUENCY_FREQUENCY_DATATYPES_H_

#include <stdbool.h>
#include <stdint.h>
#include "threadx.h"

#define NUM_FREQUENCY_CHANNELS		(4u)
#define FREQUENCY_RESET_TIME        (500u)

typedef struct{
        uint32_t firstValue;
        uint32_t secondValue;
        bool isFirstCapture;
        TX_TIMER resetTimer;
        uint8_t halChannel;
        uint32_t difference;
}frequency_t;

#endif /* USER_FREQUENCY_FREQUENCY_DATATYPES_H_ */
