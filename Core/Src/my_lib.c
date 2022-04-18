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
LV_IMG_DECLARE(hour);
LV_IMG_DECLARE(minute);
LV_IMG_DECLARE(second);
lv_obj_t *lvMinute;
lv_obj_t *lvHour;
lv_obj_t *lvSecond;
uint8_t Minute = 59;
uint8_t Hour = 8;
uint8_t Second = 2;
static void update_time(lv_task_t * task)
{
    char strftime_buf[64];
    if (lvHour != NULL)
    {
        // Hour,Minute,Second;
        uint16_t h = Hour * 300 + Minute / 12 % 12 * 60;
        lv_img_set_angle(lvHour, h);
        lv_img_set_angle(lvMinute, Minute * 6 * 10);
        lv_img_set_angle(lvSecond, Second * 6 * 10);
        // printf("h %d m %d s %d\n", Hour, Minute, Second);
    }

    if (++Second >= 60)
    {
        Second = 0;
        if (++Minute >= 60)
        {
            Minute = 0;
            if (++Hour >= 12)
                Hour = 0;
        }
    }
}
uint8_t test_data;
void analog(lv_obj_t *win)
{
    lv_obj_t *central = win;

    lv_obj_set_size(central, LV_HOR_RES_MAX, LV_VER_RES_MAX);
    lv_obj_set_pos(central, 0, 0);

    lv_obj_t *img = lv_img_create(central, NULL);
    lv_img_set_src(img, "F:/3.bin");

    lv_obj_set_size(img, 240, 240);
    lv_obj_set_auto_realign(img, true);
    lv_obj_align(img, central, LV_ALIGN_CENTER, 0, 0);

    lvHour = lv_img_create(central, NULL);
    lv_img_set_src(lvHour, &hour);
    lv_obj_align(lvHour, img, LV_ALIGN_CENTER, 0, 0);
    uint16_t h = Hour * 300 + Minute / 12 % 12 * 60;
    lv_img_set_angle(lvHour, h);

    lvMinute = lv_img_create(central, NULL);
    lv_img_set_src(lvMinute, &minute);
    lv_obj_align(lvMinute, img, LV_ALIGN_CENTER, 0, 0);
    lv_img_set_angle(lvHour, Minute * 60);

    lvSecond = lv_img_create(central, NULL);

    lv_img_set_src(lvSecond, &second);
    lv_obj_align(lvSecond, img, LV_ALIGN_CENTER, 0, 0);
    lv_img_set_angle(lvSecond, Second * 60);

    lv_task_t *task=lv_task_create(update_time, 1000, LV_TASK_PRIO_LOW, &test_data);
}