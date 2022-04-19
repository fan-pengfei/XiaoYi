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
#include "myFont.c"
void LCD_SET_LIGHT(int light)
{
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET);
}
LV_IMG_DECLARE(hour);
LV_IMG_DECLARE(minute);
LV_IMG_DECLARE(second);
lv_obj_t *lvMinute;
lv_obj_t *lvHour;
lv_obj_t *lvSecond;
uint8_t Minute = 59;
uint8_t Hour = 8;
uint8_t Second = 2;
extern Times my_rtc;
lv_obj_t *label1;
uint8_t text_temp[100];
static void update_time(lv_task_t *task)
{
    sprintf((uint8_t *)text_temp, "%02d:%02d:%02d", my_rtc.hour, my_rtc.min, my_rtc.sec);
    lv_label_set_text(label1, text_temp);
}
uint8_t test_data;
void analog(lv_obj_t *win)
{
    lv_obj_t *central = win;

    lv_obj_set_size(central, LV_HOR_RES_MAX, LV_VER_RES_MAX);
    lv_obj_set_pos(central, 0, 0);

    // lv_obj_t *img = lv_img_create(central, NULL);
    // lv_img_set_src(img, "F:/3.bin");

    // lv_obj_set_size(img, 240, 240);
    // lv_obj_set_auto_realign(img, true);
    // lv_obj_align(img, central, LV_ALIGN_CENTER, 0, 0);

    static lv_style_t font_style1;
    lv_style_init(&font_style1);
    lv_style_set_text_font(&font_style1, LV_STATE_DEFAULT, &lv_font_montserrat_32);
    
    label1 = lv_label_create(lv_scr_act(), NULL);

    sprintf((uint8_t *)text_temp, "%02d:%02d:%02d", my_rtc.hour, my_rtc.min, my_rtc.sec);
    lv_obj_add_style(label1, LV_LABEL_PART_MAIN, &font_style1);
    lv_label_set_align(label1, LV_LABEL_ALIGN_CENTER); /*Center aligned lines*/
    LV_FONT_DECLARE(myFont);
    lv_obj_set_style_local_text_font(label1, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &myFont);
    lv_label_set_text(label1, text_temp);
    lv_obj_align(label1, NULL, LV_ALIGN_CENTER, 0, 0);
    lv_task_t *task = lv_task_create(update_time, 1000, LV_TASK_PRIO_LOW, &test_data);
}