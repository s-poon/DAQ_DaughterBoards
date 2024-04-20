/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    app_threadx.c
  * @author  MCD Application Team
  * @brief   ThreadX applicative file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2020-2021 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "app_threadx.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define NUMBER_ANALOG_CHANNELS
#define SET_12V         1
#define SET_5V          0
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
uint8_t voltageDividerStates[8] = {
        SET_12V,
        SET_12V,
        SET_12V,
        SET_12V,
        SET_12V,
        SET_12V,
        SET_12V,
        SET_12V
};
TX_THREAD txMainThread;
TX_THREAD txAnalogThread;
TX_THREAD txAeroThread;
TX_THREAD txCAN500HZThread;

TX_SEMAPHORE analogSemaphore;
TX_SEMAPHORE aeroSemaphore;

uint32_t adcValues[8];
uint8_t analogRxData[16];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/**
  * @brief  Application ThreadX Initialization.
  * @param memory_ptr: memory pointer
  * @retval int
  */
UINT App_ThreadX_Init(VOID *memory_ptr)
{
  UINT ret = TX_SUCCESS;
  /* USER CODE BEGIN App_ThreadX_MEM_POOL */
  TX_BYTE_POOL *bytePool = (TX_BYTE_POOL*)memory_ptr;
  CHAR *pointer;
  /* USER CODE END App_ThreadX_MEM_POOL */

  /* USER CODE BEGIN App_ThreadX_Init */
  if(tx_byte_allocate(bytePool, (VOID**) &pointer, TX_APP_STACK_SIZE, TX_NO_WAIT) != TX_SUCCESS){
	  return TX_POOL_ERROR;
  }

  if(tx_byte_allocate(bytePool, (VOID**) &pointer, TX_APP_STACK_SIZE, TX_NO_WAIT) != TX_SUCCESS){
	  return TX_POOL_ERROR;
  }

  if(tx_thread_create(&txMainThread, "txMainThread", txMainThreadEntry, 0, pointer,
                         TX_APP_STACK_SIZE, TX_APP_THREAD_PRIO, TX_APP_THREAD_PREEMPTION_THRESHOLD,
                         TX_APP_THREAD_TIME_SLICE, TX_APP_THREAD_AUTO_START) != TX_SUCCESS){
      return TX_THREAD_ERROR;
  }

  if(tx_thread_create(&txMainThread, "txAnalogThread", txAnalogThreadEntry, 0, pointer,
                         TX_APP_STACK_SIZE, TX_APP_THREAD_PRIO, TX_APP_THREAD_PREEMPTION_THRESHOLD,
                         TX_APP_THREAD_TIME_SLICE, TX_APP_THREAD_AUTO_START) != TX_SUCCESS){
      return TX_THREAD_ERROR;
  }

  if(tx_thread_create(&txMainThread, "txAeroThread", txAeroThreadEntry, 0, pointer,
                       TX_APP_STACK_SIZE, TX_APP_THREAD_PRIO, TX_APP_THREAD_PREEMPTION_THRESHOLD,
                       TX_APP_THREAD_TIME_SLICE, TX_APP_THREAD_AUTO_START) != TX_SUCCESS){
        return TX_THREAD_ERROR;
    }
  if(tx_thread_create(&txMainThread, "txCAN500HZ", txCAN500HZThreadEntry, 0, pointer,
                       TX_APP_STACK_SIZE, TX_APP_THREAD_PRIO, TX_APP_THREAD_PREEMPTION_THRESHOLD,
                       TX_APP_THREAD_TIME_SLICE, TX_APP_THREAD_AUTO_START) != TX_SUCCESS){
        return TX_THREAD_ERROR;
    }

  tx_semaphore_create(&analogSemaphore, "analogSemaphore", 0);
  tx_semaphore_create(&aeroSemaphore, "aeroSemaphore", 0);
  /* USER CODE END App_ThreadX_Init */

  return ret;
}

  /**
  * @brief  Function that implements the kernel's initialization.
  * @param  None
  * @retval None
  */
void MX_ThreadX_Init(void)
{
  /* USER CODE BEGIN  Before_Kernel_Start */

  /* USER CODE END  Before_Kernel_Start */

  tx_kernel_enter();

  /* USER CODE BEGIN  Kernel_Start_Error */

  /* USER CODE END  Kernel_Start_Error */
}

/* USER CODE BEGIN 1 */
void txMainThreadEntry(ULONG threadInput){

    HAL_FDCAN_Start(&hfdcan1);
	while(1){
	    HAL_GPIO_TogglePin(STATUS_LED_GPIO_Port, STATUS_LED_Pin);
	    tx_thread_sleep(1000);
	}
}

void txAnalogThreadEntry(ULONG threadInput){
    SetDividers(voltageDividerStates);
    while(1){
        HAL_ADC_Start_DMA(&hadc1, adcValues, NUM_ADC_CHANNELS);
        tx_semaphore_get(&analogSemaphore, TX_WAIT_FOREVER);
//        data will be processed and sent over CAN here
//        adcValues

        tx_thread_sleep(2);
    }
}

void txAeroThreadEntry(ULONG threadInput){

    while(1){

//        SetChannel(1);

    }
}

void txCAN500HZThreadEntry(ULONG threadInput){

    while(1){

    }
}























/* USER CODE END 1 */
