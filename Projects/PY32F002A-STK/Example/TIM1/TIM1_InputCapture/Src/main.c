/**
  ******************************************************************************
  * @file    main.c
  * @author  MCU Application Team
  * @brief   Main program body
  * @date
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
TIM_HandleTypeDef    TimHandle;
TIM_IC_InitTypeDef   sICConfig;

/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/**
  * @brief  Main program.
  * @retval int
  */
int main(void)
{
  /* Reset of all peripherals, Initializes the Systick */
  HAL_Init(); 
  
  TimHandle.Instance = TIM1;                                           /* Select TIM1 */
  TimHandle.Init.Period            = 12800 - 1;                        /* Auto-reload value */
  TimHandle.Init.Prescaler         = 1000 - 1;                         /* 预分频为1000-1 */
  TimHandle.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;           /* Clock not divided */
  TimHandle.Init.CounterMode       = TIM_COUNTERMODE_UP;               /* Up-counting mode */
  TimHandle.Init.RepetitionCounter = 1 - 1;                            /* No repetition */
  TimHandle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;   /* Auto-reload register not buffered */
  if (HAL_TIM_Base_Init(&TimHandle) != HAL_OK)                         /* Initialize TIM1 */
  {
    APP_ErrorHandler();
  }

  /* 上升沿捕获*/
  sICConfig.ICPolarity  = TIM_ICPOLARITY_RISING;                               
  /* CC1通道配置为输入 */
  sICConfig.ICSelection = TIM_ICSELECTION_DIRECTTI;                             
  /* 输入不分配 */
  sICConfig.ICPrescaler = TIM_ICPSC_DIV1;                                      
  /* 输入无滤波 */
  sICConfig.ICFilter    = 0;                                                    
  /*通道1输入捕获配置 */
  if (HAL_TIM_IC_ConfigChannel(&TimHandle, &sICConfig, TIM_CHANNEL_1) != HAL_OK) 
  {
    APP_ErrorHandler();
  }
  /* 启动通道1输入捕获 */
  if (HAL_TIM_IC_Start_IT(&TimHandle, TIM_CHANNEL_1) != HAL_OK)                    
  {
    APP_ErrorHandler();
  }
  while (1)
  {

  }
}

/**
  * @brief  TIM执行函数，TIM1捕获中断后翻转LED
  * @param  None
  * @retval None
  */
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
   BSP_LED_Toggle(LED_GREEN);
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
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
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     for example: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* infinite loop */
  while (1)
  {
  }
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT Puya *****END OF FILE****/
