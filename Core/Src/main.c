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
#include "bmp.h"
#include "lv_port_fs.h"
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
extern uint8_t aRxBuffer[5];

extern lv_fs_res_t lv_res;
extern lv_fs_file_t lv_file;
uint32_t num_f;
/****************************/
void my_lvgl_fs_test(void)
{
    lv_fs_file_t lv_file;

    lv_res = lv_fs_open(&lv_file, "F:/myFont.bin", LV_FS_MODE_RD);
    lv_fs_read(&lv_file, text, 50, &num_f);
    lv_fs_close(&lv_file);
}

static void my_lvgl_test(void)
{
    /* 创建img btn */
    lv_obj_t *imgbtn = lv_imgbtn_create(lv_scr_act(), NULL);
    /* 设置imgbtn在被按下时显示所调用的图片 */
    lv_imgbtn_set_src(imgbtn, LV_BTN_STATE_PRESSED, "F:/1.bin");
    /* 设置imgbtn在被释放时显示所调用的图片 */
    lv_imgbtn_set_src(imgbtn, LV_BTN_STATE_RELEASED, "F:/1.bin");
    /* 居中对齐 */
    lv_obj_align(imgbtn, NULL, LV_ALIGN_CENTER, 0, 0);
}

static void lvgl_init(void)
{
    lv_init();
    lv_port_disp_init();  // 显示器初始化
    lv_port_indev_init(); // 输入设备初始化
    lv_port_fs_init();    // 文件系统设备初始化
}
uint32_t resCount = 0;
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
    MX_FATFS_Init();
    MX_USB_DEVICE_Init();
    MX_SPI2_Init();
    /* USER CODE BEGIN 2 */
    //记得修改MX_FATFS_Init，为spidriver
    SPI_ReadWriteByte(0xff);
    W25QXX_Init();
    delay_init(72);
    HAL_TIM_Base_Start_IT(&htim10);
    LCD_Init();
    LCD_Fill(0, 0, 239, 239, WHITE);
    // while(1)
    // {
    // 		LCD_Fill(0,0,100,100,RED);
    // 		LCD_Fill(0,0,100,100,BLUE);
    // }
    //lvgl_init();
    // my_lvgl_fs_test();
    // FatfsTest();
    // 	lv_res = lv_fs_open(&lv_file,"F:/hello.txt", LV_FS_MODE_WR);// 创建一个文件
    // 	lv_res = lv_fs_write(&lv_file,"hellobug esp32", sizeof("hellobug esp32"), &resCount);// 创建一个文件
    // lv_fs_close(&lv_file);
    // analog(lv_scr_act());
    //  my_lvgl_fs_test();
    // analog();
    // test_lv_font();
    //    HAL_Delay(100);
    //
    //    my_lvgl_fs_test();
    //	my_lvgl_test();
    FatfsTest();
    //    lv_init();
    //    lv_port_disp_init();
    //    lv_port_indev_init();

    /* USER CODE END 2 */

    /* Infinite loop */
    /* USER CODE BEGIN WHILE */
    while (1)
    {
        /* USER CODE END WHILE */

        /* USER CODE BEGIN 3 */
        // update_time(NULL);
        HAL_Delay(500);
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
    RCC_OscInitStruct.PLL.PLLN = 336;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
    RCC_OscInitStruct.PLL.PLLQ = 7;
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

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
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
