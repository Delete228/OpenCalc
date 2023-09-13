/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#include "stm32f0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
void WriteRow(uint8_t n, GPIO_PinState s);
void ScanColunm(uint8_t r, uint8_t *buf);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define row_5_Pin GPIO_PIN_0
#define row_5_GPIO_Port GPIOF
#define row_6_Pin GPIO_PIN_1
#define row_6_GPIO_Port GPIOF
#define row_1_Pin GPIO_PIN_0
#define row_1_GPIO_Port GPIOA
#define row_2_Pin GPIO_PIN_1
#define row_2_GPIO_Port GPIOA
#define row_3_Pin GPIO_PIN_3
#define row_3_GPIO_Port GPIOA
#define row_4_Pin GPIO_PIN_4
#define row_4_GPIO_Port GPIOA
#define colunm_6_Pin GPIO_PIN_5
#define colunm_6_GPIO_Port GPIOA
#define colunm_5_Pin GPIO_PIN_6
#define colunm_5_GPIO_Port GPIOA
#define colunm_4_Pin GPIO_PIN_7
#define colunm_4_GPIO_Port GPIOA
#define colunm_3_Pin GPIO_PIN_1
#define colunm_3_GPIO_Port GPIOB
#define colunm_2_Pin GPIO_PIN_9
#define colunm_2_GPIO_Port GPIOA
#define colunm_1_Pin GPIO_PIN_10
#define colunm_1_GPIO_Port GPIOA
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
