/**
  ******************************************************************************
  * @file    main.c
  * @author  MCU Application Team
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2023 Puya Semiconductor Co.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by Puya under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2016 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private define ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef         TimHandle;
TIM_OnePulse_InitTypeDef  sConfig;

/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_SystemClockConfig(void);

/**
  * @brief  Main program.
  * @retval int
  */
int main(void)
{
  /* Reset of all peripherals, Initializes the Systick */
  HAL_Init();
  
  /* System clock configuration */
  APP_SystemClockConfig(); 

  TimHandle.Instance = TIM1;                                           /* Select TIM1 */
  TimHandle.Init.Period            = 0xffff;                           /* Auto-reload value */
  TimHandle.Init.Prescaler         = 1 - 1;                            /* No prescaling */
  TimHandle.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;           /* No clock division */
  TimHandle.Init.CounterMode       = TIM_COUNTERMODE_UP;               /* Up counting */
  TimHandle.Init.RepetitionCounter = 1 - 1;                            /* No repetition counting */
  TimHandle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;   /* Auto-reload register not buffered */
  /* Initialize TIM1 for one-pulse mode */
  if (HAL_TIM_OnePulse_Init(&TimHandle, TIM_OPMODE_SINGLE) != HAL_OK)
  {
    APP_ErrorHandler();
  }
  sConfig.OCMode       = TIM_OCMODE_PWM2;                              /* PWM mode 2 */
  sConfig.OCPolarity   = TIM_OCPOLARITY_HIGH;                          /* OC output is active high level */
  sConfig.Pulse        = 16383;                                        /* Pulse width */
  sConfig.ICPolarity   = TIM_ICPOLARITY_RISING;                        /* IC1 capture signal is not inverted */
  sConfig.ICSelection  = TIM_ICSELECTION_DIRECTTI;                     /* CC1 channel is configured as input IC1 mapped on TI1 */
  sConfig.ICFilter     = 0;                                            /* No input capture filter */
  sConfig.OCNPolarity  = TIM_OCNPOLARITY_HIGH;                         /* OCN output is active high level */
  sConfig.OCIdleState  = TIM_OCIDLESTATE_RESET;                        /* Output idle state is 1 (OC1 output) */
  sConfig.OCNIdleState = TIM_OCNIDLESTATE_RESET;                       /* Output idle state is 1 (OC1N output) */
  /* Configure TIM1 one-pulse channel parameters */
  if (HAL_TIM_OnePulse_ConfigChannel(&TimHandle, &sConfig, TIM_CHANNEL_1, TIM_CHANNEL_2) != HAL_OK)
  {
    APP_ErrorHandler();
  }
  
  /* Start TIM1 for one-pulse mode */
  if (HAL_TIM_OnePulse_Start(&TimHandle, TIM_CHANNEL_1) != HAL_OK)
  {
    APP_ErrorHandler();
  }
  
  /* Infinite loop */
  while (1)
  {
  }
}

/**
  * @brief  System clock configuration function
  * @param  None
  * @retval None
  */
static void APP_SystemClockConfig(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /* Oscillator configuration */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE | RCC_OSCILLATORTYPE_HSI | RCC_OSCILLATORTYPE_LSI | RCC_OSCILLATORTYPE_LSE; /* Select oscillators HSE, HSI, LSI, LSE */
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;                          /* Enable HSI */
  RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV1;                          /* HSI not divided */
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_16MHz; /* Configure HSI clock as 16MHz */
  RCC_OscInitStruct.HSEState = RCC_HSE_OFF;                         /* Disable HSE */
  /*RCC_OscInitStruct.HSEFreq = RCC_HSE_16_32MHz;*/
  RCC_OscInitStruct.LSIState = RCC_LSI_OFF;                         /* Disable LSI */
  RCC_OscInitStruct.LSEState = RCC_LSE_OFF;                         /* Disable LSE */
  /*RCC_OscInitStruct.LSEDriver = RCC_LSEDRIVE_MEDIUM;*/
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;                      /* Enable PLL */
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;              /* Select HSI as PLL source */
  /* Configure oscillators */
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    APP_ErrorHandler();
  }

  /* Clock source configuration */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1; /* Select clock types HCLK, SYSCLK, PCLK1 */
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK; /* Select PLL as system clock */
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;        /* AHB  clock not divided */
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;         /* APB  clock not divided */
  /* Configure clock source */
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    APP_ErrorHandler();
  }
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void APP_ErrorHandler(void)
{
  while (1)
  {
  }
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
  /* User can add his own implementation to report the file name and line number,
     for example: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* Infinite loop */
  while (1)
  {
  }
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT Puya *****END OF FILE******************/
