/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define count_row 6
#define count_colunm 6
#define buffer_size 5
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
struct keys_struct
{
        unsigned k_q         : 1;  //  |
        unsigned k_w         : 1;  //  |
        unsigned k_e         : 1;  //  |
        unsigned k_r         : 3;  //  |
        unsigned k_t         : 1;  //  |
        unsigned k_y         : 1;  //   >  First row
        unsigned k_u         : 1;  //  |
        unsigned k_i         : 1;  //  |
        unsigned k_o         : 1;  //  |
        unsigned k_p         : 1;  //  |

        unsigned k_a         : 1;  //  |
        unsigned k_s         : 1;  //  |
        unsigned k_d         : 1;  //  |
        unsigned k_f         : 1;  //  |
        unsigned k_g         : 1;  //   >  Second row
        unsigned k_h         : 1;  //  |
        unsigned k_j         : 1;  //  |
        unsigned k_k         : 1;  //  |
        unsigned k_l         : 1;  //  |

        unsigned k_shift     : 1;  //  |
        unsigned k_z         : 1;  //  |
        unsigned k_x         : 1;  //  |
        unsigned k_c         : 1;  //  |
        unsigned k_v         : 1;  //  |
        unsigned k_b         : 1;  //   >  Thrid row
        unsigned k_n         : 1;  //  |
        unsigned k_m         : 1;  //  |
        unsigned k_comma     : 1;  //  |
        unsigned k_dot       : 1;  //  |

        unsigned k_ctrl      : 1;  //  |
        unsigned k_alt       : 1;  //  |
        unsigned k_fn1       : 1;  //  |
        unsigned k_space     : 1;  //   >  Fourth row
        unsigned k_fn2       : 1;  //  |
        unsigned k_fn3       : 1;  //  |
        unsigned k_fn4       : 1;  //  |
        unsigned dop_bits    : 4;
};

union keys
{
        struct keys_struct key;
        uint8_t array[5];

};

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
union keys keyboard={
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0,       0,    0, 0, 0,
        0
};

union keys keyboard_flags={
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0,       0,    0, 0, 0,
        0
};


  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
  uint8_t current_row=1;
  uint8_t buffer[buffer_size];
  for(uint8_t i=0;i<buffer_size;i++)
          buffer[i]=0;
  
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  uint32_t j=0;
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    j++;
    WriteRow(current_row, GPIO_PIN_SET);
    ReadColunm(current_row,&keyboard);
    WriteRow(current_row, GPIO_PIN_RESET);

    current_row++;
    if(current_row > count_row)
        current_row=1;

    if(j>500)
    {
            j=0;
        
//////////////////// q
        if(keyboard.key.k_q && !keyboard_flags.key.k_q)
        {
            keyboard_flags.key.k_q=1;
            HAL_UART_Transmit(&huart1, (uint8_t*)"q", 1, 1000);
        }
        if(!keyboard.key.k_q && keyboard_flags.key.k_q)
        {
            keyboard_flags.key.k_q=0;
        }
//////////////////// w
        if(keyboard.key.k_w && !keyboard_flags.key.k_w)
        {
            keyboard_flags.key.k_w=1;
            HAL_UART_Transmit(&huart1, (uint8_t*)"w", 1, 1000);
        }
        if(!keyboard.key.k_w && keyboard_flags.key.k_w)
        {
            keyboard_flags.key.k_w=0;
        }
//////////////////// e
        if(keyboard.key.k_e && !keyboard_flags.key.k_e)
        {
            keyboard_flags.key.k_e=1;
            HAL_UART_Transmit(&huart1, (uint8_t*)"e", 1, 1000);
        }
        if(!keyboard.key.k_e && keyboard_flags.key.k_e)
        {
            keyboard_flags.key.k_e=0;
        }
//////////////////// r
        if(keyboard.key.k_r && !keyboard_flags.key.k_r)
        {
            keyboard_flags.key.k_r=1;
            HAL_UART_Transmit(&huart1, (uint8_t*)"r", 1, 1000);
        }
        if(!keyboard.key.k_r && keyboard_flags.key.k_r)
        {
            keyboard_flags.key.k_r=0;
        }
//////////////////// t
        if(keyboard.key.k_t && !keyboard_flags.key.k_t)
        {
            keyboard_flags.key.k_t=1;
            HAL_UART_Transmit(&huart1, (uint8_t*)"t", 1, 1000);
        }
        if(!keyboard.key.k_t && keyboard_flags.key.k_t)
        {
            keyboard_flags.key.k_t=0;
        }
//////////////////// y
        if(keyboard.key.k_y && !keyboard_flags.key.k_y)
        {
            keyboard_flags.key.k_y=1;
            HAL_UART_Transmit(&huart1, (uint8_t*)"y", 1, 1000);
        }
        if(!keyboard.key.k_y && keyboard_flags.key.k_y)
        {
            keyboard_flags.key.k_y=0;
        }
//////////////////// u
        if(keyboard.key.k_u && !keyboard_flags.key.k_u)
        {
            keyboard_flags.key.k_u=1;
            HAL_UART_Transmit(&huart1, (uint8_t*)"u", 1, 1000);
        }
        if(!keyboard.key.k_u && keyboard_flags.key.k_u)
        {
            keyboard_flags.key.k_u=0;
        }
//////////////////// i
        if(keyboard.key.k_i && !keyboard_flags.key.k_i)
        {
            keyboard_flags.key.k_i=1;
            HAL_UART_Transmit(&huart1, (uint8_t*)"i", 1, 1000);
        }
        if(!keyboard.key.k_i && keyboard_flags.key.k_i)
        {
            keyboard_flags.key.k_i=0;
        }
//////////////////// o
        if(keyboard.key.k_o && !keyboard_flags.key.k_o)
        {
            keyboard_flags.key.k_o=1;
            HAL_UART_Transmit(&huart1, (uint8_t*)"o", 1, 1000);
        }
        if(!keyboard.key.k_o && keyboard_flags.key.k_o)
        {
            keyboard_flags.key.k_o=0;
        }
//////////////////// p
        if(keyboard.key.k_p && !keyboard_flags.key.k_p)
        {
            keyboard_flags.key.k_p=1;
            HAL_UART_Transmit(&huart1, (uint8_t*)"p", 1, 1000);
        }
        if(!keyboard.key.k_p && keyboard_flags.key.k_p)
        {
            keyboard_flags.key.k_p=0;
        }
//////////////////// a
        if(keyboard.key.k_a && !keyboard_flags.key.k_a)
        {
            keyboard_flags.key.k_a=1;
            HAL_UART_Transmit(&huart1, (uint8_t*)"a", 1, 1000);
        }
        if(!keyboard.key.k_a && keyboard_flags.key.k_a)
        {
            keyboard_flags.key.k_a=0;
        }
//////////////////// s
        if(keyboard.key.k_s && !keyboard_flags.key.k_s)
        {
            keyboard_flags.key.k_s=1;
            HAL_UART_Transmit(&huart1, (uint8_t*)"s", 1, 1000);
        }
        if(!keyboard.key.k_s && keyboard_flags.key.k_s)
        {
            keyboard_flags.key.k_s=0;
        }
//////////////////// d
        if(keyboard.key.k_d && !keyboard_flags.key.k_d)
        {
            keyboard_flags.key.k_d=1;
            HAL_UART_Transmit(&huart1, (uint8_t*)"d", 1, 1000);
        }
        if(!keyboard.key.k_d && keyboard_flags.key.k_d)
        {
            keyboard_flags.key.k_d=0;
        }
//////////////////// f
        if(keyboard.key.k_f && !keyboard_flags.key.k_f)
        {
            keyboard_flags.key.k_f=1;
            HAL_UART_Transmit(&huart1, (uint8_t*)"f", 1, 1000);
        }
        if(!keyboard.key.k_f && keyboard_flags.key.k_f)
        {
            keyboard_flags.key.k_f=0;
        }
//////////////////// g
        if(keyboard.key.k_g && !keyboard_flags.key.k_g)
        {
            keyboard_flags.key.k_g=1;
            HAL_UART_Transmit(&huart1, (uint8_t*)"g", 1, 1000);
        }
        if(!keyboard.key.k_g && keyboard_flags.key.k_g)
        {
            keyboard_flags.key.k_g=0;
        }
//////////////////// h
        if(keyboard.key.k_h && !keyboard_flags.key.k_h)
        {
            keyboard_flags.key.k_h=1;
            HAL_UART_Transmit(&huart1, (uint8_t*)"h", 1, 1000);
        }
        if(!keyboard.key.k_h && keyboard_flags.key.k_h)
        {
            keyboard_flags.key.k_h=0;
        }
//////////////////// j
        if(keyboard.key.k_j && !keyboard_flags.key.k_j)
        {
            keyboard_flags.key.k_j=1;
            HAL_UART_Transmit(&huart1, (uint8_t*)"j", 1, 1000);
        }
        if(!keyboard.key.k_j && keyboard_flags.key.k_j)
        {
            keyboard_flags.key.k_j=0;
        }
//////////////////// k
        if(keyboard.key.k_k && !keyboard_flags.key.k_k)
        {
            keyboard_flags.key.k_k=1;
            HAL_UART_Transmit(&huart1, (uint8_t*)"k", 1, 1000);
        }
        if(!keyboard.key.k_k && keyboard_flags.key.k_k)
        {
            keyboard_flags.key.k_k=0;
        }
//////////////////// l
        if(keyboard.key.k_l && !keyboard_flags.key.k_l)
        {
            keyboard_flags.key.k_l=1;
            HAL_UART_Transmit(&huart1, (uint8_t*)"l", 1, 1000);
        }
        if(!keyboard.key.k_l && keyboard_flags.key.k_l)
        {
            keyboard_flags.key.k_l=0;
        }
//////////////////// z
        if(keyboard.key.k_z && !keyboard_flags.key.k_z)
        {
            keyboard_flags.key.k_z=1;
            HAL_UART_Transmit(&huart1, (uint8_t*)"z", 1, 1000);
        }
        if(!keyboard.key.k_z && keyboard_flags.key.k_z)
        {
            keyboard_flags.key.k_z=0;
        }
//////////////////// x
        if(keyboard.key.k_x && !keyboard_flags.key.k_x)
        {
            keyboard_flags.key.k_x=1;
            HAL_UART_Transmit(&huart1, (uint8_t*)"x", 1, 1000);
        }
        if(!keyboard.key.k_x && keyboard_flags.key.k_x)
        {
            keyboard_flags.key.k_x=0;
        }
//////////////////// c
        if(keyboard.key.k_c && !keyboard_flags.key.k_c)
        {
            keyboard_flags.key.k_c=1;
            HAL_UART_Transmit(&huart1, (uint8_t*)"c", 1, 1000);
        }

        if(!keyboard.key.k_c && keyboard_flags.key.k_c)
        {
            keyboard_flags.key.k_c=0;
        }
//////////////////// v
        if(keyboard.key.k_v && !keyboard_flags.key.k_v)
        {
            keyboard_flags.key.k_v=1;
            HAL_UART_Transmit(&huart1, (uint8_t*)"v", 1, 1000);
        }
        if(!keyboard.key.k_v && keyboard_flags.key.k_v)
        {
            keyboard_flags.key.k_v=0;
        }
//////////////////// b
        if(keyboard.key.k_b && !keyboard_flags.key.k_b)
        {
            keyboard_flags.key.k_b=1;
            HAL_UART_Transmit(&huart1, (uint8_t*)"b", 1, 1000);
        }
        if(!keyboard.key.k_b && keyboard_flags.key.k_b)
        {
            keyboard_flags.key.k_b=0;
        }
//////////////////// n
        if(keyboard.key.k_n && !keyboard_flags.key.k_n)
        {
            keyboard_flags.key.k_n=1;
            HAL_UART_Transmit(&huart1, (uint8_t*)"n", 1, 1000);
        }
        if(!keyboard.key.k_n && keyboard_flags.key.k_n)
        {
            keyboard_flags.key.k_n=0;
        }
//////////////////// m
        if(keyboard.key.k_m && !keyboard_flags.key.k_m)
        {
            keyboard_flags.key.k_m=1;
            HAL_UART_Transmit(&huart1, (uint8_t*)"m", 1, 1000);
        }
        if(!keyboard.key.k_m && keyboard_flags.key.k_m)
        {
            keyboard_flags.key.k_m=0;
        }


//////////////////// space pressed
        if(keyboard.key.k_space && !keyboard_flags.key.k_space)
        {
            keyboard_flags.key.k_space=1;
            HAL_UART_Transmit(&huart1, (uint8_t*)" ", 1, 1000);
        }
        if(!keyboard.key.k_space && keyboard_flags.key.k_space)
        {
            keyboard_flags.key.k_space=0;
        }
//////////////////// comma pressed
        if(keyboard.key.k_comma && !keyboard_flags.key.k_comma)
        {
            keyboard_flags.key.k_comma=1;
            HAL_UART_Transmit(&huart1, (uint8_t*)",", 1, 1000);
        }
        if(!keyboard.key.k_comma && keyboard_flags.key.k_comma)
        {
            keyboard_flags.key.k_comma=0;
        }
//////////////////// dot pressed
        if(keyboard.key.k_dot && !keyboard_flags.key.k_dot)
        {
            keyboard_flags.key.k_dot=1;
            HAL_UART_Transmit(&huart1, (uint8_t*)".", 1, 1000);
        }
        if(!keyboard.key.k_dot && keyboard_flags.key.k_dot)
        {
            keyboard_flags.key.k_dot=0;
        }


//////////////////// shift pressed
        if(keyboard.key.k_shift && !keyboard_flags.key.k_shift)
        {
            keyboard_flags.key.k_shift=1;
            HAL_UART_Transmit(&huart1, (uint8_t*)"\nshift pressed\n", 15, 1000);
        }
        if(!keyboard.key.k_shift && keyboard_flags.key.k_shift)
        {
            keyboard_flags.key.k_shift=0;
        }
//////////////////// ctrl pressed
        if(keyboard.key.k_ctrl && !keyboard_flags.key.k_ctrl)
        {
            keyboard_flags.key.k_ctrl=1;
            HAL_UART_Transmit(&huart1, (uint8_t*)"\nctrl pressed\n", 14, 1000);
        }
        if(!keyboard.key.k_ctrl && keyboard_flags.key.k_ctrl)
        {
            keyboard_flags.key.k_ctrl=0;
        }
//////////////////// alt pressed
        if(keyboard.key.k_alt && !keyboard_flags.key.k_alt)
        {
            keyboard_flags.key.k_alt=1;
            HAL_UART_Transmit(&huart1, (uint8_t*)"\nalt pressed\n", 13, 1000);
        }
        if(!keyboard.key.k_alt && keyboard_flags.key.k_alt)
        {
            keyboard_flags.key.k_alt=0;
        }
//////////////////// fn1 pressed
        if(keyboard.key.k_fn1 && !keyboard_flags.key.k_fn1)
        {
            keyboard_flags.key.k_fn1=1;
            HAL_UART_Transmit(&huart1, (uint8_t*)"\nfn1 pressed\n", 13, 1000);
        }
        if(!keyboard.key.k_fn1 && keyboard_flags.key.k_fn1)
        {
            keyboard_flags.key.k_fn1=0;
        }
//////////////////// fn2 pressed
        if(keyboard.key.k_fn2 && !keyboard_flags.key.k_fn2)
        {
            keyboard_flags.key.k_fn2=1;
            HAL_UART_Transmit(&huart1, (uint8_t*)"\nfn2 pressed\n", 13, 1000);
        }
        if(!keyboard.key.k_fn2 && keyboard_flags.key.k_fn2)
        {
            keyboard_flags.key.k_fn2=0;
        }
//////////////////// fn3 pressed
        if(keyboard.key.k_fn3 && !keyboard_flags.key.k_fn3)
        {
            keyboard_flags.key.k_fn3=1;
            HAL_UART_Transmit(&huart1, (uint8_t*)"\nfn3 pressed\n", 13, 1000);
        }
        if(!keyboard.key.k_fn3 && keyboard_flags.key.k_fn3)
        {
            keyboard_flags.key.k_fn3=0;
        }
//////////////////// fn3 pressed
        if(keyboard.key.k_fn4 && !keyboard_flags.key.k_fn4)
        {
            keyboard_flags.key.k_fn4=1;
            HAL_UART_Transmit(&huart1, (uint8_t*)"\nfn4 pressed\n", 13, 1000);
        }
        if(!keyboard.key.k_fn4 && keyboard_flags.key.k_fn4)
        {
            keyboard_flags.key.k_fn4=0;
        }
    }
    //HAL_GPIO_ReadPin()
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL12;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_HalfDuplex_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOF, row_5_Pin|row_6_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, row_1_Pin|row_2_Pin|row_3_Pin|row_4_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : row_5_Pin row_6_Pin */
  GPIO_InitStruct.Pin = row_5_Pin|row_6_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  /*Configure GPIO pins : row_1_Pin row_2_Pin row_3_Pin row_4_Pin */
  GPIO_InitStruct.Pin = row_1_Pin|row_2_Pin|row_3_Pin|row_4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : colunm_6_Pin colunm_5_Pin colunm_4_Pin colunm_2_Pin
                           colunm_1_Pin */
  GPIO_InitStruct.Pin = colunm_6_Pin|colunm_5_Pin|colunm_4_Pin|colunm_2_Pin
                          |colunm_1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : colunm_3_Pin */
  GPIO_InitStruct.Pin = colunm_3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(colunm_3_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

void WriteRow(uint8_t n, GPIO_PinState s)
{
        switch(n)
        {
                case 1:
                        HAL_GPIO_WritePin(row_1_GPIO_Port, row_1_Pin, s);
                        break;                                  
                case 2:                                         
                        HAL_GPIO_WritePin(row_2_GPIO_Port, row_2_Pin, s);
                        break;                                  
                case 3:                                         
                        HAL_GPIO_WritePin(row_3_GPIO_Port, row_3_Pin, s);
                        break;                                  
                case 4:                                         
                        HAL_GPIO_WritePin(row_4_GPIO_Port, row_4_Pin, s);
                        break;                                  
                case 5:                                         
                        HAL_GPIO_WritePin(row_5_GPIO_Port, row_5_Pin, s);
                        break;                                  
                case 6:                                         
                        HAL_GPIO_WritePin(row_6_GPIO_Port, row_6_Pin, s);
                        break;
                default:
                        break;
        }
}


void ReadColunm(uint8_t n, union keys *kb)
{
        //uint8_t b[6]={0,0,0,0,0,0};
        uint8_t b=0;
        uint8_t cur;
        cur=HAL_GPIO_ReadPin(colunm_1_GPIO_Port,colunm_1_Pin);
        if(cur)
             //   b[0]=1;
            b|=1<<0;
        cur=HAL_GPIO_ReadPin(colunm_2_GPIO_Port,colunm_2_Pin);
        if(cur)                                         
             //   b[1]=1;
            b|=1<<1;                                    
        cur=HAL_GPIO_ReadPin(colunm_3_GPIO_Port,colunm_3_Pin);
        if(cur)                                         
             //   b[2]=1;
            b|=1<<2;                                    
        cur=HAL_GPIO_ReadPin(colunm_4_GPIO_Port,colunm_4_Pin);
        if(cur)                                         
             //   b[3]=1;
            b|=1<<3;                                    
        cur=HAL_GPIO_ReadPin(colunm_5_GPIO_Port,colunm_5_Pin);
        if(cur)                                         
             //   b[4]=1;
            b|=1<<4;                                    
        cur=HAL_GPIO_ReadPin(colunm_6_GPIO_Port,colunm_6_Pin);
        if(cur)
             //   b[5]=1;
            b|=1<<5;
        switch(n)
        {
                case 1:
                        kb->key.k_o =    (b&(1<<0))>>0;//b[0]; 
                        kb->key.k_i =    (b&(1<<1))>>1;//b[1]; 
                        kb->key.k_y =    (b&(1<<2))>>2;//b[2]; 
                        kb->key.k_t =    (b&(1<<3))>>3;//b[3]; 
                        kb->key.k_e =    (b&(1<<4))>>4;//b[4]; 
                        kb->key.k_w =    (b&(1<<5))>>5;//b[5]; 
                        break;                                 
                case 2:                                        
                        kb->key.k_p =    (b&(1<<0))>>0;//b[0]; 
                        kb->key.k_j =    (b&(1<<1))>>1;//b[1]; 
                        kb->key.k_u =    (b&(1<<2))>>2;//b[2]; 
                        kb->key.k_r =    (b&(1<<3))>>3;//b[3]; 
                        kb->key.k_d =    (b&(1<<4))>>4;//b[4]; 
                        kb->key.k_q =    (b&(1<<5))>>5;//b[5]; 
                        break;                                  
                case 3:                                         
                        kb->key.k_dot =  (b&(1<<0))>>0;//b[0]; 
                        kb->key.k_comma =(b&(1<<1))>>1;//b[1]; 
                        kb->key.k_h =    (b&(1<<2))>>2;//b[2]; 
                        kb->key.k_f =    (b&(1<<3))>>3;//b[3]; 
                        kb->key.k_z =    (b&(1<<4))>>4;//b[4]; 
                        kb->key.k_shift =(b&(1<<5))>>5;//b[5]; 
                        break;                                  
                case 4:                                         
                        kb->key.k_fn4 =  (b&(1<<0))>>0;//b[0]; 
                        kb->key.k_m =    (b&(1<<1))>>1;//b[1]; 
                        kb->key.k_n =    (b&(1<<2))>>2;//b[2]; 
                        kb->key.k_c =    (b&(1<<3))>>3;//b[3]; 
                        kb->key.k_x =    (b&(1<<4))>>4;//b[4]; 
                        kb->key.k_ctrl = (b&(1<<5))>>5;//b[5]; 
                        break;                                  
                case 5:                                         
                        kb->key.k_fn3 =  (b&(1<<0))>>0;//b[0]; 
                        kb->key.k_fn2 =  (b&(1<<1))>>1;//b[1]; 
                        kb->key.k_b =    (b&(1<<2))>>2;//b[2]; 
                        kb->key.k_space =(b&(1<<3))>>3;//b[3]; 
                        kb->key.k_fn1 =  (b&(1<<4))>>4;//b[4]; 
                        kb->key.k_alt =  (b&(1<<5))>>5;//b[5]; 
                        break;                                 
                case 6:                                        
                        kb->key.k_l =    (b&(1<<0))>>0;//b[0]; 
                        kb->key.k_k =    (b&(1<<1))>>1;//b[1]; 
                        kb->key.k_g =    (b&(1<<2))>>2;//b[2]; 
                        kb->key.k_v =    (b&(1<<3))>>3;//b[3]; 
                        kb->key.k_s =    (b&(1<<4))>>4;//b[4]; 
                        kb->key.k_a =    (b&(1<<5))>>5;//b[5]; 
                        break;
                default:
                        break;
        }
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
