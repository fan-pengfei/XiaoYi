#include "my_lib.h"
#include "tim.h"
#include "lcd_init.h"
#include "lcd.h"
#include "stdio.h"
#include "lvgl.h"
#include "lv_port_disp.h"
#include "lv_ex_conf.h"
#include "lv_examples.h"
#include "lv_demo_widgets.h"
#include "lv_port_indev.h"
void LCD_SET_LIGHT(int light)
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET);
}