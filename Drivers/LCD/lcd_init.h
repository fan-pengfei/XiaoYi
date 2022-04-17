/*
 * @Author: your name
 * @Date: 2021-12-30 22:21:53
 * @LastEditTime: 2021-12-31 11:51:50
 * @LastEditors: Please set LastEditors
 * @Description: ��koroFileHeader�鿴���� ��������: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \����\Drivers\LCD\lcd_init.h
 */
#ifndef __LCD_INIT_H
#define __LCD_INIT_H

#include "main.h"

#define USE_HORIZONTAL 1 //���ú�������������ʾ 0��1Ϊ���� 2��3Ϊ����
#define USE_SOFT_SPI 0


#define LCD_W 240
#define LCD_H 240


#if USE_SOFT_SPI
//-----------------LCD�˿ڶ���----------------

// #define LCD_SCLK_Clr() HAL_GPIO_WritePin(LCD_SCL_GPIO_Port, LCD_SCL_Pin, GPIO_PIN_RESET)
// #define LCD_SCLK_Set() HAL_GPIO_WritePin(LCD_SCL_GPIO_Port, LCD_SCL_Pin, GPIO_PIN_SET)

// #define LCD_MOSI_Clr() HAL_GPIO_WritePin(LCD_SDA_GPIO_Port, LCD_SDA_Pin, GPIO_PIN_RESET)
// #define LCD_MOSI_Set() HAL_GPIO_WritePin(LCD_SDA_GPIO_Port, LCD_SDA_Pin, GPIO_PIN_SET)

// #define LCD_RES_Clr() HAL_GPIO_WritePin(LCD_RES_GPIO_Port, LCD_RES_Pin, GPIO_PIN_RESET)
// #define LCD_RES_Set() HAL_GPIO_WritePin(LCD_RES_GPIO_Port, LCD_RES_Pin, GPIO_PIN_SET)

// #define LCD_DC_Clr() HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_RESET)
// #define LCD_DC_Set() HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_SET)

// #define LCD_CS_Clr() HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET)
// #define LCD_CS_Set() HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET)

// #define LCD_BLK_Clr() HAL_GPIO_WritePin(LCD_BLK_GPIO_Port, LCD_BLK_Pin, GPIO_PIN_RESET)
// #define LCD_BLK_Set() HAL_GPIO_WritePin(LCD_BLK_GPIO_Port, LCD_BLK_Pin, GPIO_PIN_SET)
#define LCD_SCLK_Clr() GPIOB->ODR &= ~(1 << 3)
#define LCD_SCLK_Set() GPIOB->ODR |= 1 << 3

#define LCD_MOSI_Clr() GPIOB->ODR &= ~(1 << 5)
#define LCD_MOSI_Set() GPIOB->ODR |= 1 << 5

#define LCD_RES_Clr() GPIOB->ODR &= ~(1 << 9)
#define LCD_RES_Set() GPIOB->ODR |= 1 << 9

#define LCD_DC_Clr() GPIOB->ODR &= ~(1 << 8)
#define LCD_DC_Set() GPIOB->ODR |= 1 << 8

#define LCD_CS_Clr() GPIOB->ODR &= ~(1 << 6)
#define LCD_CS_Set() GPIOB->ODR |= 1 << 6

#define LCD_BLK_Clr() GPIOB->ODR &= ~(1 << 7)
#define LCD_BLK_Set() GPIOB->ODR |= 1 << 7

#else

#define LCD_RES_Clr() GPIOB->ODR &= ~(1 << 9)
#define LCD_RES_Set() GPIOB->ODR |= 1 << 9

#define LCD_DC_Clr() GPIOB->ODR &= ~(1 << 8)
#define LCD_DC_Set() GPIOB->ODR |= 1 << 8

#define LCD_CS_Clr() GPIOB->ODR &= ~(1 << 6)
#define LCD_CS_Set() GPIOB->ODR |= 1 << 6

#define LCD_BLK_Clr() GPIOB->ODR &= ~(1 << 7)
#define LCD_BLK_Set() GPIOB->ODR |= 1 << 7


#endif


void LCD_GPIO_Init(void);                                                 //��ʼ��GPIO
void LCD_Writ_Bus(uint8_t dat);                                           //ģ��SPIʱ��
void LCD_WR_DATA8(uint8_t dat);                                           //д��һ���ֽ�
void LCD_WR_DATA(uint16_t dat);                                           //д�������ֽ�
void LCD_WR_REG(uint8_t dat);                                             //д��һ��ָ��
void LCD_Address_Set(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2); //�������꺯��
void LCD_Init(void);        
#endif
