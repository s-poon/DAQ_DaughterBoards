/*
 * frequency_sensors.c
 *
 *  Created on: Apr 20, 2024
 *      Author: steve
 */

#include "frequency_sensors.h"
#include "app_threadx.h"
#include "threadx.h"
#include "tim.h"
#include <stdbool.h>
#include <stdio.h>

frequency_t channelData[4];

static uint8_t CalculateFrequency(
        frequency_t* channel,
        TIM_HandleTypeDef* htim
);

uint8_t FrequencyInit(void){
    uint8_t retVal = UCR_OK;
    for(int i = 0; i < NUM_FREQUENCY_CHANNELS; i ++){
        channelData[i].firstValue = 0;
        channelData[i].secondValue = 0;
        channelData[i].isFirstCapture = false;
    }
    channelData[0].halChannel = HAL_TIM_ACTIVE_CHANNEL_1;
    channelData[1].halChannel = HAL_TIM_ACTIVE_CHANNEL_2;
    channelData[2].halChannel = HAL_TIM_ACTIVE_CHANNEL_3;
    channelData[3].halChannel = HAL_TIM_ACTIVE_CHANNEL_4;

    tx_timer_create(&channelData[0].resetTimer, "resetTimer1", timerExpirationFrequency, 0,
                    FREQUENCY_RESET_TIME, 0, TX_NO_ACTIVATE);
    tx_timer_create(&channelData[1].resetTimer, "resetTimer2", timerExpirationFrequency, 1,
                        FREQUENCY_RESET_TIME, 0, TX_NO_ACTIVATE);
    tx_timer_create(&channelData[2].resetTimer, "resetTimer3", timerExpirationFrequency, 2,
                        FREQUENCY_RESET_TIME, 0, TX_NO_ACTIVATE);
    tx_timer_create(&channelData[3].resetTimer, "resetTimer4", timerExpirationFrequency, 3,
                        FREQUENCY_RESET_TIME, 0, TX_NO_ACTIVATE);
    return retVal;
}


/**
  * @brief  Input capture callback function.
  * @param htim: Timer handle
  * @retval void
  */
void HAL_TIM_IC_CaptureCallback(
        TIM_HandleTypeDef* htim
){
    uint8_t channel = 0;
    switch (htim->Channel){
        case HAL_TIM_ACTIVE_CHANNEL_1:
            channel = 0;
            break;
        case HAL_TIM_ACTIVE_CHANNEL_2:
            channel = 1;
            break;
        case HAL_TIM_ACTIVE_CHANNEL_3:
            channel = 2;
            break;
        case HAL_TIM_ACTIVE_CHANNEL_4:
            channel = 3;
            break;
        default:
            return;
    }
    CalculateFrequency(&channelData[channel], htim);
}

static uint8_t CalculateFrequency(
        frequency_t* channel,
        TIM_HandleTypeDef* htim
){
    uint8_t retVal = UCR_OK;
    // Check if first rising edge to begin capture
    if(TX_SUCCESS != tx_semaphore_get(&semaphoreFrequency, TX_NO_WAIT)){
        retVal = UCR_NOT_OK;
        return retVal;
    }
    if (channel->isFirstCapture == false){
        if(TX_SUCCESS != tx_timer_activate(&channel->resetTimer)){
                   // ADD error handler stuff here;
        }
        channel->firstValue = HAL_TIM_ReadCapturedValue(htim, channel->halChannel);
        // Set flag to indicate next value will be second rising edge
        channel->isFirstCapture = true;
    } else if (true == channel->isFirstCapture){
        // Stop the reset timer
        if(TX_SUCCESS != tx_timer_deactivate(&channel->resetTimer)){
            // ADD error handler stuff here;
        }
        channel->secondValue = HAL_TIM_ReadCapturedValue(htim, channel->halChannel);
        // Check if the first capture was before the second
        if (channel->secondValue > channel->firstValue){
            // Calculate the difference
            channel->difference = channel->secondValue - channel->firstValue;
        } else if (channel->secondValue < channel->firstValue){
            channel->difference = ((htim->Init.Period - channel->firstValue) + channel->secondValue) + 1;
        }
        // Reset the first capture state
        channel->isFirstCapture = false;
    }
    // Release the semaphore
    if(TX_SUCCESS != tx_semaphore_put(&semaphoreFrequency)){
        // ADD error handler stuff here;
    }
    // Reset the timer;
    if(TX_SUCCESS != tx_timer_change(&channel->resetTimer, FREQUENCY_RESET_TIME, 0)){
        // ADD error handler stuff here;
    }
    return retVal;
}

/**
  * @brief  Expiration function for frequency software timers. The purpose of these timers is to ensure that sensors will read 0
  * @param channel: the number of the timer
  * @retval void
  */
void timerExpirationFrequency(
        ULONG channel
){
    // Attempt to acquire the semaphore
    if(TX_SUCCESS != tx_semaphore_get(&semaphoreFrequency, TX_NO_WAIT)){
        return;
    }
    // Set the first capture and difference to zero
    channelData[channel].isFirstCapture = false;
    channelData[channel].difference = 0;
    // Reset the timer
    tx_timer_deactivate(&channelData[channel].resetTimer);
    tx_timer_change(&channelData[channel].resetTimer, FREQUENCY_RESET_TIME, 0);
    // Release the semaphore
    tx_semaphore_put(&semaphoreFrequency);
    return;
}





















