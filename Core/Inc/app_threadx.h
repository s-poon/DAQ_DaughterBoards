/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    app_threadx.h
  * @author  MCD Application Team
  * @brief   ThreadX applicative header file
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __APP_THREADX_H__
#define __APP_THREADX_H__

#ifdef __cplusplus
extern "C" {
#endif
/* Includes ------------------------------------------------------------------*/
#include "tx_api.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdint.h>
#include "adc.h"
#include "fdcan.h"
#include <analog_control.h>
#include <aero_sensors.h>
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Private defines -----------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define TX_APP_STACK_SIZE                       512
#define TX_APP_THREAD_PRIO                      10
/* USER CODE END PD */

/* Main thread defines -------------------------------------------------------*/
/* USER CODE BEGIN MTD */
#ifndef TX_APP_THREAD_PREEMPTION_THRESHOLD
#define TX_APP_THREAD_PREEMPTION_THRESHOLD      TX_APP_THREAD_PRIO
#endif

#ifndef TX_APP_THREAD_TIME_SLICE
#define TX_APP_THREAD_TIME_SLICE                TX_NO_TIME_SLICE
#endif
#ifndef TX_APP_THREAD_AUTO_START
#define TX_APP_THREAD_AUTO_START                TX_AUTO_START
#endif


/* USER CODE END MTD */

/* Exported macro ------------------------------------------------------------*/

/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
UINT App_ThreadX_Init(VOID *memory_ptr);
void MX_ThreadX_Init(void);
/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* USER CODE BEGIN 1 */
extern TX_SEMAPHORE semaphoreAnalog;
/* USER CODE END 1 */

#ifdef __cplusplus
}
#endif
#endif /* __APP_THREADX_H__ */
