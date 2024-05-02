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

uint32_t difference[NUM_FREQUENCY_CHANNELS];

static frequency_t channelData[4];

uint8_t FrequencyInit(void){
    uint8_t retVal = UCR_OK;
    for(int i = 0; i < NUM_FREQUENCY_CHANNELS; i ++){
        channelData[i].firstValue = 0;
        channelData[i].secondValue = 0;
        channelData[i].isFirstCapture = false;
    }
    tx_timer_create(&channelData[0].resetTimer, "resetTimer1", timerExpiration, 0,
                    FREQUENCY_RESET_TIME, 0, TX_NO_ACTIVATE);
    tx_timer_create(&channelData[1].resetTimer, "resetTimer2", timerExpiration, 0,
                        FREQUENCY_RESET_TIME, 0, TX_NO_ACTIVATE);
    tx_timer_create(&channelData[2].resetTimer, "resetTimer3", timerExpiration, 0,
                        FREQUENCY_RESET_TIME, 0, TX_NO_ACTIVATE);
    tx_timer_create(&channelData[3].resetTimer, "resetTimer4", timerExpiration, 0,
                        FREQUENCY_RESET_TIME, 0, TX_NO_ACTIVATE);
    return retVal;
}


/**
  * @brief  Input capture callback function.
  * @param htim: Timer handle
  * @retval void
  */
void HAL_TIM_IC_CaptureCallback(
        TIM_HandleTypeDef *htim
){
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
    if (channelData[channel].isFirstCapture == false){
        if(TX_SUCCESS != tx_timer_activate(&channelData[channel].resetTimer)){
                   // ADD error handler stuff here;
        }
        channelData[channel].firstValue = HAL_TIM_ReadCapturedValue(htim, hal_channel);
        // Set flag to indicate next value will be second rising edge
        channelData[channel].isFirstCapture = true;
    } else if (true == channelData[channel].isFirstCapture){
        // Stop the reset timer
        if(TX_SUCCESS != tx_timer_deactivate(&channelData[channel].resetTimer)){
            // ADD error handler stuff here;
        }
        channelData[channel].secondValue = HAL_TIM_ReadCapturedValue(htim, hal_channel);
        // Check if the first capture was before the second
        if (channelData[channel].secondValue > channelData[channel].firstValue){
            // Calculate the difference
            difference[channel] = channelData[channel].secondValue - channelData[channel].firstValue;
        } else if (channelData[channel].secondValue < channelData[channel].firstValue){
            difference[channel] = ((htim->Init.Period - channelData[channel].firstValue) + channelData[channel].secondValue) + 1;
        }
        // Reset the first capture state
        channelData[channel].isFirstCapture = false;
    }
    // Release the semaphore
    if(TX_SUCCESS != tx_semaphore_put(&semaphoreFrequency)){
        // ADD error handler stuff here;
    }
    // Reset the timer;
    if(TX_SUCCESS != tx_timer_change(&channelData[channel].resetTimer, FREQUENCY_RESET_TIME, 0)){
        // ADD error handler stuff here;
    }
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
    channelData[channel].isFirstCapture = false;
    difference[channel] = 0;
    // Reset the timer
    tx_timer_deactivate(&channelData[channel].resetTimer);
    tx_timer_change(&channelData[channel].resetTimer, FREQUENCY_RESET_TIME, 0);
    // Release the semaphore
    tx_semaphore_put(&semaphoreFrequency);
    return;
}





















