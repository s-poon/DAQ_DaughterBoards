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


/**
  * @brief  Input capture callback function.
  * @param htim: Timer handle
  * @retval void
  */
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
    // Check if first rising edge to begin capture
    if (is_first_captured[channel] == false){
        tx_timer_activate(&timers[channel]);
        IC_Val1[channel] = HAL_TIM_ReadCapturedValue(htim, hal_channel);
        // Set flag to indicate next value will be second rising edge
        is_first_captured[channel] = true;
    } else if (is_first_captured[channel] == true){
        // Stop the reset timer
        tx_timer_deactivate(&timers[channel]);
        IC_Val2[channel] = HAL_TIM_ReadCapturedValue(htim, hal_channel);
        // Check if the first capture was before the second
        if (IC_Val2[channel] > IC_Val1[channel]){
            // Calculate the difference
            difference[channel] = IC_Val2[channel] - IC_Val1[channel];
        } else if (IC_Val2[channel] < IC_Val1[channel]){
            difference[channel] = ((htim->Init.Period - IC_Val1[channel]) + IC_Val2[channel]) + 1;
        }
        // Reset the first capture state
        is_first_captured[channel] = false;
    }
    // Release the semaphore
    tx_semaphore_put(&semaphoreFrequency);
    // Reset the timer;
    tx_timer_change(&timers[channel], FREQUENCY_RESET_TIME, 0);
}

/**
  * @brief  Expiration function for frequency software timers. The purpose of these timers is to ensure that sensors will read 0
  * @param channel: the number of the timer
  * @retval void
  */
void timerExpiration(UINT channel){
    // Attempt to acquire the semaphore
    if(TX_SUCCESS != tx_semaphore_get(&semaphoreFrequency, TX_NO_WAIT)){
        return;
    }
    // Set the first capture and difference to zero
    is_first_captured[channel] = false;
    difference[channel] = 0;
    // Reset the timer
    tx_timer_deactivate(&timers[channel]);
    tx_timer_change(&timers[channel], FREQUENCY_RESET_TIME, 0);
    // Release the semaphore
    tx_semaphore_put(&semaphoreFrequency);
    return;
}





















