/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "app_threadx.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define FIRMWARECHECK_Pin GPIO_PIN_3
#define FIRMWARECHECK_GPIO_Port GPIOA
#define STARTSYNC_1_Pin GPIO_PIN_4
#define STARTSYNC_1_GPIO_Port GPIOC
#define CS1_Pin GPIO_PIN_5
#define CS1_GPIO_Port GPIOC
#define DRDY1_Pin GPIO_PIN_0
#define DRDY1_GPIO_Port GPIOB
#define RESET1_Pin GPIO_PIN_1
#define RESET1_GPIO_Port GPIOB
#define STARTSYNC_2_Pin GPIO_PIN_7
#define STARTSYNC_2_GPIO_Port GPIOE
#define CS2_Pin GPIO_PIN_8
#define CS2_GPIO_Port GPIOE
#define DRDY2_Pin GPIO_PIN_9
#define DRDY2_GPIO_Port GPIOE
#define RESET2_Pin GPIO_PIN_10
#define RESET2_GPIO_Port GPIOE
#define ANALOGSWITCH_6_Pin GPIO_PIN_13
#define ANALOGSWITCH_6_GPIO_Port GPIOB
#define ANALOGSWITCH_7_Pin GPIO_PIN_14
#define ANALOGSWITCH_7_GPIO_Port GPIOB
#define ANALOG_1_Pin GPIO_PIN_15
#define ANALOG_1_GPIO_Port GPIOB
#define ANALOG_2_Pin GPIO_PIN_8
#define ANALOG_2_GPIO_Port GPIOD
#define ANALOG_5_Pin GPIO_PIN_9
#define ANALOG_5_GPIO_Port GPIOD
#define ANALOG_6_Pin GPIO_PIN_10
#define ANALOG_6_GPIO_Port GPIOD
#define ANALOG_7_Pin GPIO_PIN_11
#define ANALOG_7_GPIO_Port GPIOD
#define ANALOG_8_Pin GPIO_PIN_12
#define ANALOG_8_GPIO_Port GPIOD
#define ANALOG_3_Pin GPIO_PIN_13
#define ANALOG_3_GPIO_Port GPIOD
#define ANALOG_4_Pin GPIO_PIN_14
#define ANALOG_4_GPIO_Port GPIOD
#define ANALOGSWITCH_5_Pin GPIO_PIN_15
#define ANALOGSWITCH_5_GPIO_Port GPIOD
#define ANALOGSWITCH_8_Pin GPIO_PIN_8
#define ANALOGSWITCH_8_GPIO_Port GPIOC
#define ANALOGSWITCH_2_Pin GPIO_PIN_9
#define ANALOGSWITCH_2_GPIO_Port GPIOC
#define ANALOGSWITCH_3_Pin GPIO_PIN_8
#define ANALOGSWITCH_3_GPIO_Port GPIOA
#define ANALOGSWITCH_1_Pin GPIO_PIN_9
#define ANALOGSWITCH_1_GPIO_Port GPIOA
#define ANALOGSWITCH_4_Pin GPIO_PIN_10
#define ANALOGSWITCH_4_GPIO_Port GPIOA
#define ERROR_LED_Pin GPIO_PIN_10
#define ERROR_LED_GPIO_Port GPIOC
#define CAN_LED_Pin GPIO_PIN_11
#define CAN_LED_GPIO_Port GPIOC
#define STATUS_LED_Pin GPIO_PIN_12
#define STATUS_LED_GPIO_Port GPIOC
#define FREQUENCY_3_Pin GPIO_PIN_3
#define FREQUENCY_3_GPIO_Port GPIOD
#define FREQUENCY_2_Pin GPIO_PIN_4
#define FREQUENCY_2_GPIO_Port GPIOD
#define FREQUENCY_1_Pin GPIO_PIN_6
#define FREQUENCY_1_GPIO_Port GPIOD
#define FREQUENCY_4_Pin GPIO_PIN_7
#define FREQUENCY_4_GPIO_Port GPIOD

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
