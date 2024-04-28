/*
 * frequency_sensors.c
 *
 *  Created on: Apr 20, 2024
 *      Author: steve
 */

#include "frequency_sensors.h"
#include "app_threadx.h"
#include "threadx.h"
#include "frequency_datatypes.h"
#include "tim.h"
#include <stdbool.h>

uint32_t IC_Val1[NUM_FREQUENCY_CHANNELS];
uint32_t IC_Val2[NUM_FREQUENCY_CHANNELS];
uint32_t difference[NUM_FREQUENCY_CHANNELS];
uint8_t is_first_captured[NUM_FREQUENCY_CHANNELS];


void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim){
	if(TX_SUCCESS != tx_semaphore_get(&semaphoreFrequency, TX_NO_WAIT)){
		return;
	}
    uint8_t channel = 0;
    uint8_t hal_channel = 0u;

    if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1){
        channel = 0;
        hal_channel = TIM_CHANNEL_1;
    } else if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2){
        channel = 1;
        hal_channel = TIM_CHANNEL_2;
    } else if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_3){
        channel = 2;
        hal_channel = TIM_CHANNEL_3;
    } else if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_4){
        channel = 3;
        hal_channel = TIM_CHANNEL_4;
    }

    if (is_first_captured[channel] == false) {  // check if first rising edge to begin capture
        tx_timer_activate(&timers[channel]);
        IC_Val1[channel] = HAL_TIM_ReadCapturedValue(htim, hal_channel);
        is_first_captured[channel] = true; // set flag to indicate next value will be second rising edge
    } else if (is_first_captured[channel] == true) {   // second rising edge
        tx_timer_deactivate(&timers[channel]);
        IC_Val2[channel] = HAL_TIM_ReadCapturedValue(htim, hal_channel);
        if (IC_Val2[channel] > IC_Val1[channel]) {  // first capture before second
            difference[channel] = IC_Val2[channel] - IC_Val1[channel];
        } else if (IC_Val2[channel] < IC_Val1[channel]) {   // first capture after second robust check
            difference[channel] = ((htim->Init.Period - IC_Val1[channel]) + IC_Val2[channel]) + 1;
        }
        is_first_captured[channel] = false;
    }
    tx_semaphore_put(&semaphoreFrequency);
    tx_timer_change(&timers[channel], FREQUENCY_RESET_TIME, 0);
}

void timerExpiration(UINT channel){
    if(TX_SUCCESS != tx_semaphore_get(&semaphoreFrequency, TX_NO_WAIT)){
        return;
    }
    is_first_captured[channel] = false;
    difference[channel] = 0;
    tx_timer_deactivate(&timers[channel]);
    tx_timer_change(&timers[channel], FREQUENCY_RESET_TIME, 0);
    tx_semaphore_put(&semaphoreFrequency);
    return;
}





















