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
#include "py32f003xx_ll_Start_Kit.h"

/* Private define ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_SystemClockConfig(void);
static void APP_WwdgConfig(void);

/**
  * @brief  应用程序入口函数.
  * @retval int
  */
int main(void)
{
  /* PWR时钟使能 */
  LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_SYSCFG);
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);

  /* 时钟初始化,配置系统时钟为HSI */
  APP_SystemClockConfig();

  /* 初始化LED */
  BSP_LED_Init(LED_GREEN);
  
  /* WWDG配置 */
  APP_WwdgConfig();
  
  while (1)
  {
    LL_mDelay(500);
    BSP_LED_Toggle(LED_GREEN);
  }
}

/**
  * @brief  系统时钟配置函数
  * @param  无
  * @retval 无
  */
static void APP_SystemClockConfig(void)
{
  /* HSI使能及初始化 */
  LL_RCC_HSI_Enable();
  while(LL_RCC_HSI_IsReady() != 1)
  {
  }
  
  /* 设置AHB分频*/
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);

  /* 配置HSISYS为系统时钟及初始化 */
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_HSISYS);
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_HSISYS)
  {
  }

  LL_FLASH_SetLatency(LL_FLASH_LATENCY_0);
  
  /* 设置APB1分频及初始化 */
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
  LL_Init1msTick(8000000);
  /* 更新系统时钟全局变量SystemCoreClock(也可以通过调用SystemCoreClockUpdate函数更新) */
  LL_SetSystemCoreClock(8000000);
}

/**
  * @brief  配置LED翻转
  * @param  无
  * @retval 无
  */
void APP_LedToggleCallback(void)
{
  LL_GPIO_TogglePin(GPIOB, LL_GPIO_PIN_5); 
}

/**
  * @brief  WWDG配置函数
  * @param  无
  * @retval 无
  */
static void APP_WwdgConfig(void)
{
  /* 使能WWDG时钟 */
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_WWDG);
  
  /* 设置计数器 */
  LL_WWDG_SetCounter(WWDG, 0x7F);
  /* 设置分频 */
  LL_WWDG_SetPrescaler(WWDG, LL_WWDG_PRESCALER_8);
  /* 设置窗口值 */
  LL_WWDG_SetWindow(WWDG, 0x7F);
  /* 使能提前中断 */
  LL_WWDG_EnableIT_EWKUP(WWDG);
  
  /* 设置中断优先级 */
  NVIC_SetPriority(WWDG_IRQn,0);
  /* 使能中断 */
  NVIC_EnableIRQ(WWDG_IRQn);
  /* 使能WWDG */
  LL_WWDG_Enable(WWDG);
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
