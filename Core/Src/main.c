/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under Ultimate Liberty license
 * SLA0044, the "License"; You may not use this file except in compliance with
 * the License. You may obtain a copy of the License at:
 *                             www.st.com/SLA0044
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "dma.h"
#include "fatfs.h"
#include "rtc.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "usb_device.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "w25qxx.h"
#include "lcd_init.h"
#include "lcd.h"
#include "pic.h"
#include "stdio.h"
#include "lvgl.h"
#include "lv_port_disp.h"
#include "lv_ex_conf.h"
#include "lv_examples.h"
#include "lv_demo_widgets.h"
#include "my_lib.h"
#include "lv_port_indev.h"
#include "lcdfont.h"
//#include "tt0.h"
//#include "tt1.h"
//#include "tt2.h"
//#include "tt3.h"
//#include "tt4.h"
//#include "tt5.h"
//#include "tt6.h"
#include "delay.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
extern uint16_t light_lcd;
extern RTC_DateTypeDef GetData;
extern RTC_TimeTypeDef GetTime;
extern uint8_t text[50];
LV_FONT_DECLARE(myFont);
#pragma execution_character_set("utf-8")
const char *str1 = "长风破浪会有时\n直挂云帆济沧海";
unsigned char text_usart2[8] = {0xaa, 0x55, 0x01, 0x01, 0x02, 0x03, 0x55, 0xaa};
uint8_t Data1[2] = {0x12, 0x13};
uint8_t Data2[2] = {0x00};
/****************************/

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{
    /* USER CODE BEGIN 1 */
    /* USER CODE END 1 */

    /* MCU Configuration--------------------------------------------------------*/

    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init();

    /* USER CODE BEGIN Init */

    /* USER CODE END Init */

    /* Configure the system clock */
    SystemClock_Config();

    /* USER CODE BEGIN SysInit */
    my_init();
    /* USER CODE END SysInit */

    /* Initialize all configured peripherals */
    MX_GPIO_Init();
    MX_RTC_Init();
    MX_TIM10_Init();
    MX_DMA_Init();
    MX_SPI1_Init();
    MX_USART2_UART_Init();
    MX_FATFS_Init();
    MX_USB_DEVICE_Init();
    /* USER CODE BEGIN 2 */

    delay_init(72);
    HAL_TIM_Base_Start_IT(&htim10);
    // W25QXX_Write(Data1, 0xffff, 2);
    //	W25QXX_Read(Data2, 0xffff, 2);

    LCD_Init();
    FatfsTest();
    // LCD_ShowPicture(1, 1, 128, 160, gImage_test);
    //    lv_init();
    //    lv_port_disp_init();
    //    lv_port_indev_init();
    //    lv_obj_t *label_dl_1 = lv_label_create(lv_scr_act(), NULL);
    //    lv_obj_set_style_local_text_font(label_dl_1, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &myFont);
    //    lv_label_set_text(label_dl_1, "#ff0000 CO2浓度：#");

    // lv_label_set_text(label_dl_1, "ABC\xE4\xB8\x80\xE4\xB8\x83ZZZ"); //"一七"

    //    lv_obj_center(label_dl_1);
    //    lv_style_set_text_font(label_dl_1, &myFont, 0);
    // lv_obj_set_style_text_font();
    // lv_obj_set_style_text_color(label_dl_1, lv_color_make(0xff, 0x00, 0x00), 0);

    /* USER CODE END 2 */

    /* Infinite loop */
    /* USER CODE BEGIN WHILE */
    while (1)
    {
        /* USER CODE END WHILE */

        /* USER CODE BEGIN 3 */
        HAL_Delay(500);
        // HAL_UART_Transmit(&huart2, text_usart2, 8, 100);
        // HAL_Delay(8000);
        //        LCD_ShowPicture(x_sta, y_sta, 100, 100, gImage_tt0);
        //        HAL_Delay(tim);
        //        LCD_ShowPicture(x_sta, y_sta, 100, 100, gImage_tt1);
        //        HAL_Delay(tim);
        //        LCD_ShowPicture(x_sta, y_sta, 100, 100, gImage_tt2);
        //        HAL_Delay(tim);
        //        LCD_ShowPicture(x_sta, y_sta, 100, 100, gImage_tt3);
        //        HAL_Delay(tim);
        //        LCD_ShowPicture(x_sta, y_sta, 100, 100, gImage_tt4);
        //        HAL_Delay(tim);
        //        LCD_ShowPicture(x_sta, y_sta, 100, 100, gImage_tt5);
        //        HAL_Delay(tim * 1.5);
        //        LCD_ShowPicture(x_sta, y_sta, 100, 100, gImage_tt6);
        //        HAL_Delay(tim);
    }
    /* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    /** Configure the main internal regulator output voltage
     */
    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);
    /** Initializes the RCC Oscillators according to the specified parameters
     * in the RCC_OscInitTypeDef structure.
     */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE | RCC_OSCILLATORTYPE_LSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.LSEState = RCC_LSE_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = 25;
    RCC_OscInitStruct.PLL.PLLN = 144;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
    RCC_OscInitStruct.PLL.PLLQ = 3;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }
    /** Initializes the CPU, AHB and APB buses clocks
     */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
    {
        Error_Handler();
    }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void)
{
    /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */
    __disable_irq();
    while (1)
    {
    }
    /* USER CODE END Error_Handler_Debug */
}

#ifdef USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line)
{
    /* USER CODE BEGIN 6 */
    /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
    /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
