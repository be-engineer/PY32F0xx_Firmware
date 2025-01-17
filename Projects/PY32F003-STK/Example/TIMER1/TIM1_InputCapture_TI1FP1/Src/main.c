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
#include "py32f0xx_hal_flash.h"

/* Private define ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef    TimHandle;
TIM_IC_InitTypeDef sICConfig;

/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/**
  * @brief  应用程序入口函数.
  * @retval int
  */
int main(void)
{
  /* 初始化所有外设，Flash接口，SysTick */
  HAL_Init();

  /* 初始化LED */
  BSP_LED_Init(LED_GREEN);

  TimHandle.Instance = TIM1;                                                     /* 选择TIM1 */
  TimHandle.Init.Period            = 12800 - 1;                                  /* 自动重装载值 */
  TimHandle.Init.Prescaler         = 1000 - 1;                                   /* 预分频为1000-1 */
  TimHandle.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;                     /* 时钟不分频 */
  TimHandle.Init.CounterMode       = TIM_COUNTERMODE_UP;                         /* 向上计数 */
  TimHandle.Init.RepetitionCounter = 1 - 1;                                      /* 不重复计数 */
  TimHandle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;             /* 自动重装载寄存器没有缓冲 */
  if (HAL_TIM_Base_Init(&TimHandle) != HAL_OK)                                   /* TIM1初始化 */
  {
    APP_ErrorHandler();
  }
  sICConfig.ICPolarity  = TIM_ICPOLARITY_RISING;                                 /* 上升沿捕获 */
  sICConfig.ICSelection = TIM_ICSELECTION_DIRECTTI;                              /* CC1通道配置为输入 */
  sICConfig.ICPrescaler = TIM_ICPSC_DIV1;                                        /* 输入不分频 */
  sICConfig.ICFilter    = 0;                                                     /* 输入无滤波 */
  if (HAL_TIM_IC_ConfigChannel(&TimHandle, &sICConfig, TIM_CHANNEL_1) != HAL_OK) /* 通道1输入捕获配置 */
  {
    APP_ErrorHandler();
  }
  if (HAL_TIM_IC_Start_IT(&TimHandle, TIM_CHANNEL_1) != HAL_OK)                  /* 启动通道1输入捕获 */
  {
    APP_ErrorHandler();
  }
  while (1)
  {
  }
}

/**
  * @brief  TIM捕获中断回调函数
  * @param  htim：TIM句柄
  * @retval 无
  */
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
  BSP_LED_Toggle(LED_GREEN);
}

/**
  * @brief  错误执行函数
  * @param  无
  * @retval 无
  */
void APP_ErrorHandler(void)
{
  /* 无限循环 */
  while (1)
  {
  }
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  输出产生断言错误的源文件名及行号
  * @param  file：源文件名指针
  * @param  line：发生断言错误的行号
  * @retval 无
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* 用户可以根据需要添加自己的打印信息,
     例如: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* 无限循环 */
  while (1)
  {
  }
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT Puya *****END OF FILE******************/
