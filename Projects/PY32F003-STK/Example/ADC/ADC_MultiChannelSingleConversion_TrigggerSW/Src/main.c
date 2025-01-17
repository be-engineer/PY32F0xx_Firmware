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
ADC_HandleTypeDef AdcHandle;
uint32_t adc_value[3];

/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_SystemClockConfig(void);
static void APP_AdcInit(void);

/**
  * @brief  应用程序入口函数.
  * @retval int
  */
int main(void)
{
  /* 初始化所有外设，Flash接口，SysTick */
  HAL_Init();    
  
  /* 时钟初始化 */
  APP_SystemClockConfig(); 
  
  /* 初始化ADC */
  APP_AdcInit();     
  
  /* 初始化USART */
  DEBUG_USART_Config();                              
  while (1)
  {
    /* ADC开启 */
    HAL_ADC_Start(&AdcHandle);                       
    for (uint8_t i = 0; i < 3; i++)
    {
      /* 等待ADC转换 */
      HAL_ADC_PollForConversion(&AdcHandle, 10000); 
      /* 获取AD值 */
      adc_value[i] = HAL_ADC_GetValue(&AdcHandle);   
      printf("adc[%d]:%d\r\n", i, adc_value[i]);
    }
    HAL_Delay(1000);
  }
}

/**
  * @brief  系统时钟配置函数
  * @param  无
  * @retval 无
  */
static void APP_SystemClockConfig(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /* 配置HSI,HSE,LSI所有时钟 */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI | RCC_OSCILLATORTYPE_HSE | RCC_OSCILLATORTYPE_LSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;                                      /* 使能HSI */
  RCC_OscInitStruct.HSIDiv =    RCC_HSI_DIV1;                                   /* HSI预分频 */
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_8MHz;              /* 设置HSI输出时钟为8MHz,库会设置校准值 */
  RCC_OscInitStruct.HSEState = RCC_HSE_OFF;                                     /* 禁止HSE */
  RCC_OscInitStruct.HSEFreq =  RCC_HSE_16_32MHz;                                /* 设置HSE频率范围 */
  RCC_OscInitStruct.LSIState = RCC_LSI_OFF;                                     /* 禁止LSI */

  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)                          /* 配置时钟 */
  {
    APP_ErrorHandler();
  }

  /* 初始化AHB,APB总线时钟 */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;                        /* 配置AHB时钟源 */
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;                            /* 设置AHB预分频 */
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;                             /* 设置APB1预分频 */

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)       /* 配置总线 */
  {
    APP_ErrorHandler();
  }
}

/**
  * @brief  ADC初始化
  * @param  无
  * @retval 无
  */
static void APP_AdcInit(void)
{
  ADC_ChannelConfTypeDef sConfig = {0};
  __HAL_RCC_ADC_FORCE_RESET();
  __HAL_RCC_ADC_RELEASE_RESET();
  __HAL_RCC_ADC_CLK_ENABLE();

  AdcHandle.Instance = ADC1;
  /* ADC校准 */
  if (HAL_ADCEx_Calibration_Start(&AdcHandle) != HAL_OK)                 
  {
    APP_ErrorHandler();
  }

  AdcHandle.Instance = ADC1;
  AdcHandle.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;              /* 设置ADC时钟 */
  AdcHandle.Init.Resolution = ADC_RESOLUTION_12B;                        /* 转换分辨率12bit */
  AdcHandle.Init.DataAlign = ADC_DATAALIGN_RIGHT;                        /* 数据右对齐 */
  AdcHandle.Init.ScanConvMode = ADC_SCAN_DIRECTION_FORWARD;              /* 扫描方向设置 */
  AdcHandle.Init.EOCSelection = ADC_EOC_SINGLE_CONV;                     /* 单次采样 */
  AdcHandle.Init.LowPowerAutoWait = ENABLE;                              /* 等待转换模式开启 */
  AdcHandle.Init.ContinuousConvMode = DISABLE;                           /* 单次转换模式 */
  AdcHandle.Init.DiscontinuousConvMode = DISABLE;                        /* 不使能非连续模式 */
  AdcHandle.Init.ExternalTrigConv = ADC_SOFTWARE_START;                  /* 软件触发 */
  AdcHandle.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;   /* 触发边沿无 */
  AdcHandle.Init.DMAContinuousRequests = DISABLE;                        /* 关闭DMA */
  AdcHandle.Init.Overrun = ADC_OVR_DATA_OVERWRITTEN;                     /* 当过载发生时，覆盖上一个值  */
  AdcHandle.Init.SamplingTimeCommon=ADC_SAMPLETIME_239CYCLES_5;          /* 设置采样周期 */
  /* 初始化ADC */
  if (HAL_ADC_Init(&AdcHandle) != HAL_OK)                                
  {
    APP_ErrorHandler();
  }

  sConfig.Channel = ADC_CHANNEL_0;                                       /* ADC通道选择 */
  sConfig.Rank = ADC_RANK_CHANNEL_NUMBER;                                /* 设置加入规则组通道 */ 
  /* 配置ADC通道 */  
  if (HAL_ADC_ConfigChannel(&AdcHandle, &sConfig) != HAL_OK)            
  {
    APP_ErrorHandler();
  }

  sConfig.Channel = ADC_CHANNEL_1;                                       /* ADC通道选择 */
  sConfig.Rank = ADC_RANK_CHANNEL_NUMBER;                                /* 设置加入规则组通道 */
  /* 配置ADC通道 */  
  if (HAL_ADC_ConfigChannel(&AdcHandle, &sConfig) != HAL_OK)           
  {
    APP_ErrorHandler();
  }

  sConfig.Channel = ADC_CHANNEL_4;                                       /* ADC通道选择 */
  sConfig.Rank = ADC_RANK_CHANNEL_NUMBER;                                /* 设置加入规则组通道 */
  /* 配置ADC通道 */  
  if (HAL_ADC_ConfigChannel(&AdcHandle, &sConfig) != HAL_OK)           
  {
    APP_ErrorHandler();
  }
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
