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
/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_SystemClockConfig(void);

/**
  * @brief   Main program.
  * @retval  int
  */
int main(void)
{
  /* Reset of all peripherals, Initializes the Systick */
  HAL_Init();
  
  /* Initialize button */
  BSP_PB_Init(BUTTON_KEY, BUTTON_MODE_GPIO);

  /* Configure PA01 pin as MCO1 function to output the system clock */
  HAL_RCC_MCOConfig(RCC_MCO2, RCC_MCO1SOURCE_SYSCLK, RCC_MCODIV_1); 

  /* Wait for the button to be pressed to enable HSE */
  while (BSP_PB_GetState(BUTTON_KEY) == 1)
  {
  }

  /* Configure system clock */
  APP_SystemClockConfig();

  while (1)
  {
  }
}

/**
  * @brief   Configure system clock
  * @param   None
  * @retval  None
  */
static void APP_SystemClockConfig(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /* Oscillator configuration */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE | RCC_OSCILLATORTYPE_HSI | RCC_OSCILLATORTYPE_LSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;                                                    /* Enable HSI */
  RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV1;                                                    /* No HSI division */
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_8MHz;                            /* Configure HSI clock as 8MHz */
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;                                                    /* Enable HSE */
  RCC_OscInitStruct.HSEFreq = RCC_HSE_16_32MHz;                                               /* HSE frequency range */
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;                                                    /* Enable LSI */

  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    APP_ErrorHandler();
  }

  /* Initialize CPU, AHB, and APB bus clocks */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1; /* RCC system clock types */
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSE;                                         /* SYSCLK source is HSE */
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;                                             /* AHB clock not divided */
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;                                              /* APB clock divided by 2 */

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)                        /* Initialize RCC system clock (FLASH_LATENCY_0=up to 24MHz; FLASH_LATENCY_1=up to 48MHz) */
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
  /* infinite loop */
  while (1)
  {
  }
}
#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     for example: printf("Wrong parameters value: file %s on line %d\r\n", file, line)  */
  /* infinite loop */
  while (1)
  {
  }
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT Puya *****END OF FILE******************/
