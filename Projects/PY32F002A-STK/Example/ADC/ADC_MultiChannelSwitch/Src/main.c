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
/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef             AdcHandle;
ADC_ChannelConfTypeDef        sConfig;
volatile uint32_t             aADCxConvertedData;

/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_ADCConfig(void);
static uint32_t APP_ADCConvert(uint32_t Channel);

/**
  * @brief  Main program.
  * @retval int
  */
int main(void)
{
  /* Reset of all peripherals, Initializes the Systick */
  HAL_Init();
  
  APP_ADCConfig();

  /* Initialize UART */
  BSP_USART_Config();

  /* infinite loop */
  while (1)
  {
    aADCxConvertedData = APP_ADCConvert(ADC_CHANNEL_5);
    /* print channel5 value */
    printf("Channe5 value:%u \r\n",(unsigned int)aADCxConvertedData);
    
    aADCxConvertedData = APP_ADCConvert(ADC_CHANNEL_4);
    /* print channel4 value */
    printf("Channe4 value:%u \r\n",(unsigned int)aADCxConvertedData);
    HAL_Delay(1000);
  }
}

/**
  * @brief  ADC convert function
  * @param  Channel: The channel to be converted 
  * @retval ADC converted value
  */
static uint32_t APP_ADCConvert(uint32_t Channel)
{
  uint16_t adcvalue = 0;
  
  /* Clear all channels */
  WRITE_REG(ADC1->CHSELR,0);
  
  /* Config selected channels */
  sConfig.Rank         = ADC_RANK_CHANNEL_NUMBER;                             
  sConfig.Channel      = Channel;                                      
  if (HAL_ADC_ConfigChannel(&AdcHandle, &sConfig) != HAL_OK)       
  {
    APP_ErrorHandler();
  }
  
  /* ADC Start */
  HAL_ADC_Start(&AdcHandle);  
  
  /* Polling for ADC Conversion */
  HAL_ADC_PollForConversion(&AdcHandle, 1000000);        
  
  /* Get ADC Value */
  adcvalue = HAL_ADC_GetValue(&AdcHandle);     
  
  /* Clear all channels */
  WRITE_REG(ADC1->CHSELR,0);
  
  return (uint32_t)adcvalue;
}

/**
  * @brief  ADC configuration function
  * @param  None
  * @retval None
  */
void APP_ADCConfig(void)
{
  __HAL_RCC_ADC_FORCE_RESET();
  __HAL_RCC_ADC_RELEASE_RESET();
  __HAL_RCC_ADC_CLK_ENABLE();                                                     /* Enable ADC clock */

  AdcHandle.Instance = ADC1;
  if (HAL_ADCEx_Calibration_Start(&AdcHandle) != HAL_OK)                          /* ADC calibration */
  {
    APP_ErrorHandler();
  }
  AdcHandle.Instance                   = ADC1;                                    /* ADC*/
  AdcHandle.Init.ClockPrescaler        = ADC_CLOCK_SYNC_PCLK_DIV4;                /* Set ADC clock*/
  AdcHandle.Init.Resolution            = ADC_RESOLUTION_12B;                      /* 12-bit resolution for converted data*/
  AdcHandle.Init.DataAlign             = ADC_DATAALIGN_RIGHT;                     /* Right-alignment for converted data */
  AdcHandle.Init.ScanConvMode          = ADC_SCAN_DIRECTION_FORWARD;              /* Scan sequence direction: forward*/
  AdcHandle.Init.EOCSelection          = ADC_EOC_SINGLE_CONV;                     /* Single sampling*/
  AdcHandle.Init.LowPowerAutoWait      = ENABLE;                                  /* Enable wait for conversion mode */
  AdcHandle.Init.ContinuousConvMode    = DISABLE;                                 /* Single conversion mode */
  AdcHandle.Init.DiscontinuousConvMode = DISABLE;                                 /* Disable discontinuous mode */
  AdcHandle.Init.ExternalTrigConv      = ADC_SOFTWARE_START;                      /* Software triggering */
  AdcHandle.Init.ExternalTrigConvEdge  = ADC_EXTERNALTRIGCONVEDGE_NONE;           /* No external trigger edge */
  AdcHandle.Init.Overrun               = ADC_OVR_DATA_OVERWRITTEN;                /* When an overload occurs, overwrite the previous value*/
  AdcHandle.Init.SamplingTimeCommon    = ADC_SAMPLETIME_239CYCLES_5;              /* Set sampling time */
  if (HAL_ADC_Init(&AdcHandle) != HAL_OK)                                         /* ADC initialization*/
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
