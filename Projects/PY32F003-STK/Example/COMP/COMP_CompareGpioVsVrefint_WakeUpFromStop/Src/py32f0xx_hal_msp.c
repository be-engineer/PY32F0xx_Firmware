/**
  ******************************************************************************
  * @file    py32f0xx_hal_msp.c
  * @author  MCU Application Team
  * @brief   This file provides code for the MSP Initialization
  *          and de-Initialization codes.
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

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* External functions --------------------------------------------------------*/

/**
  * @brief 初始化全局MSP
  */
void HAL_MspInit(void)
{
  __HAL_RCC_PWR_CLK_ENABLE();                     /* PWR时钟使能 */
}

/**
  * @brief 初始化COMP相关MSP
  */
void HAL_COMP_MspInit(COMP_HandleTypeDef *hcomp)
{
  /* GPIO PA01配置 */
  GPIO_InitTypeDef COMPINPUT;

  COMPINPUT.Pin = GPIO_PIN_1;
  COMPINPUT.Mode = GPIO_MODE_ANALOG;     /* 模拟模式 */
  COMPINPUT.Speed = GPIO_SPEED_FREQ_HIGH;
  COMPINPUT.Pull = GPIO_PULLDOWN;        /* 下拉 */

  HAL_GPIO_Init(GPIOA,  &COMPINPUT);     /* GPIOA初始化 */

  COMPINPUT.Pin = GPIO_PIN_6;
  COMPINPUT.Mode = GPIO_MODE_AF_PP;      /* 复用推挽输出 */
  COMPINPUT.Speed = GPIO_SPEED_FREQ_HIGH;
  COMPINPUT.Pull = GPIO_PULLDOWN;        /* 下拉 */
  COMPINPUT.Alternate = GPIO_AF7_COMP1;  /* 复用COMP1输出功能 */

  HAL_GPIO_Init(GPIOA,  &COMPINPUT);     /* GPIOA初始化 */
}

/************************ (C) COPYRIGHT Puya *****END OF FILE******************/
