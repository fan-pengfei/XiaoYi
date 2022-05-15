/**
 ******************************************************************************
 * @file    tim.c
 * @brief   This file provides code for the configuration
 *          of the TIM instances.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under Ultimate Liberty license
 * SLA0044, the "License"; You may not use this file except in compliance with
 * the License. You may obtain a copy of the License at:
 *                             www.st.com/SLA0044
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "tim.h"

/* USER CODE BEGIN 0 */
#include "lcd.h"
#include "stdio.h"
#include "main.h"
#include "lvgl.h"
#include "my_lib.h"
/* USER CODE END 0 */

TIM_HandleTypeDef htim10;

/* TIM10 init function */
void MX_TIM10_Init(void)
{

    /* USER CODE BEGIN TIM10_Init 0 */

    /* USER CODE END TIM10_Init 0 */

    /* USER CODE BEGIN TIM10_Init 1 */

    /* USER CODE END TIM10_Init 1 */
    htim10.Instance = TIM10;
    htim10.Init.Prescaler = 72 - 1;
    htim10.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim10.Init.Period = 1000 - 1;
    htim10.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim10.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
    if (HAL_TIM_Base_Init(&htim10) != HAL_OK)
    {
        Error_Handler();
    }
    /* USER CODE BEGIN TIM10_Init 2 */

    /* USER CODE END TIM10_Init 2 */
}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *tim_baseHandle)
{

    if (tim_baseHandle->Instance == TIM10)
    {
        /* USER CODE BEGIN TIM10_MspInit 0 */

        /* USER CODE END TIM10_MspInit 0 */
        /* TIM10 clock enable */
        __HAL_RCC_TIM10_CLK_ENABLE();

        /* TIM10 interrupt Init */
        HAL_NVIC_SetPriority(TIM1_UP_TIM10_IRQn, 1, 0);
        HAL_NVIC_EnableIRQ(TIM1_UP_TIM10_IRQn);
        /* USER CODE BEGIN TIM10_MspInit 1 */

        /* USER CODE END TIM10_MspInit 1 */
    }
}

void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef *tim_baseHandle)
{

    if (tim_baseHandle->Instance == TIM10)
    {
        /* USER CODE BEGIN TIM10_MspDeInit 0 */

        /* USER CODE END TIM10_MspDeInit 0 */
        /* Peripheral clock disable */
        __HAL_RCC_TIM10_CLK_DISABLE();

        /* TIM10 interrupt Deinit */
        HAL_NVIC_DisableIRQ(TIM1_UP_TIM10_IRQn);
        /* USER CODE BEGIN TIM10_MspDeInit 1 */

        /* USER CODE END TIM10_MspDeInit 1 */
    }
}

/* USER CODE BEGIN 1 */
Times time_tick = {0, 0, 0, 0};
uint16_t flag_key[4] = {0}, cnt_key[4] = {0};
uint16_t light_lcd = 500;
RTC_DateTypeDef GetData;
RTC_TimeTypeDef GetTime;
char key1, key2, key3, key4;
uint8_t text[50];
extern RTC_HandleTypeDef hrtc;
extern int8_t my_day;
Times times_temp[3] = {0};
Times my_rtc;
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    static uint16_t ms = 0;
    if (htim == (&htim10))
    {
        lv_tick_inc(1);
        ms++;
        if (ms == 1000)
        {
            ms = 0;
            my_rtc.sec++;
            if (my_rtc.sec == 60)
            {
                my_rtc.min++;
                my_rtc.sec = 0;
                if (my_rtc.min == 60)
                {
                    my_rtc.hour++;
                    my_rtc.min = 0;
                }
            }
        }
        if (ms % 100 == 0)
        {
            // HAL_RTC_GetTime(&hrtc, &GetTime, RTC_FORMAT_BIN);
            // HAL_RTC_GetDate(&hrtc, &GetData, RTC_FORMAT_BIN);
            HAL_GPIO_TogglePin(User_Led_GPIO_Port, User_Led_Pin);
            // usb_printf("OK\r\n");
            // usb_printf("%d,%d,%d,%d\r\n", key1, key2, key3, key4);
        }
    }
}

/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
