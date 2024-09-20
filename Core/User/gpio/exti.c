/*
 * exti.c
 *
 *  Created on: May 6, 2024
 *      Author: Steven
 */

#include "exti.h"
#include "stdint.h"
#include "main.h"
#include "threadx.h"
//
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
    if(GPIO_Pin == DRDY1_Pin){
        tx_semaphore_put(&semaphoreExADC1);
    }else if(GPIO_Pin == DRDY2_Pin){
        tx_semaphore_put(&semaphoreExADC2);
    }
}

