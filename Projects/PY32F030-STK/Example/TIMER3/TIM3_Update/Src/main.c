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
TIM_HandleTypeDef    TimHandle;

/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_SystemClockConfig(void);

/**
  * @brief   Main program
  * @retval  int
  */
int main(void)
{
  /* Reset of all peripherals, Initializes the Systick */
  HAL_Init();
  
  /* System clock configuration */
  APP_SystemClockConfig(); 
  
  /* Initialize LED */
  BSP_LED_Init(LED_GREEN);

  TimHandle.Instance = TIM3;                                           /* Select TIM3 */
  TimHandle.Init.Period            = 3200 - 1;                         /* Auto-reload value */
  TimHandle.Init.Prescaler         = 1000 - 1;                         /* Prescaler is set to 1000-1 */
  TimHandle.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;           /* No clock division */
  TimHandle.Init.CounterMode       = TIM_COUNTERMODE_UP;               /* Up counting mode */
  TimHandle.Init.RepetitionCounter = 1 - 1;                            /* No repetition counter */
  TimHandle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;   /* Auto-reload register not buffered */
  /* TIM3 initialization */
  if (HAL_TIM_Base_Init(&TimHandle) != HAL_OK)
  {
    APP_ErrorHandler();
  }

  /* Start TIM3 and enable interrupts */
  if (HAL_TIM_Base_Start_IT(&TimHandle) != HAL_OK)
  {
    APP_ErrorHandler();
  }
  
  /* Infinite loop */
  while (1)
  {
  }
}

/**
  * @brief   Period elapsed callback in non blocking mode
  * @param   htim：TIM handle
  * @retval  None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  BSP_LED_Toggle(LED_GREEN);
}

/**
  * @brief   System clock configuration function
  * @param   None
  * @retval  None
  */
static void APP_SystemClockConfig(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE | RCC_OSCILLATORTYPE_HSI \
                                   | RCC_OSCILLATORTYPE_LSI | RCC_OSCILLATORTYPE_LSE;  /* Configure HSE, HSI, LSI, LSE */
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;                                             /* Enable HSI */
  RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV1;                                             /* HSI not divided */
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_16MHz;                    /* HSI calibration frequency 16MHz */
  RCC_OscInitStruct.HSEState = RCC_HSE_OFF;                                            /* Disable HSE */
  /* RCC_OscInitStruct.HSEFreq = RCC_HSE_16_32MHz; */                                  /* HSE frequency range: 16~32MHz */
  RCC_OscInitStruct.LSIState = RCC_LSI_OFF;                                            /* Disable LSI */
  RCC_OscInitStruct.LSEState = RCC_LSE_OFF;                                            /* Disable LSE */
  /* RCC_OscInitStruct.LSEDriver = RCC_LSEDRIVE_MEDIUM; */                             /* Default LSE drive capability */
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;                                         /* Enable PLL */
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;                                 /* PLL clock source HSI */
  /* Configure oscillators */
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    APP_ErrorHandler();
  }

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1;/* Configure SYSCLK, HCLK, PCLK */
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;                                     /* Configure system clock as PLL */
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;                                            /* AHBNo clock division */
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;                                             /* APBNo clock division */
  /* Configure clock source */
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    APP_ErrorHandler();
  }
}

/**
  * @brief   This function is executed in case of error occurrence.
  * @param   None
  * @retval  None
  */
void APP_ErrorHandler(void)
{
  /* Infinite loop */
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
