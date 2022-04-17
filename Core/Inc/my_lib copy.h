#ifndef __MY_LIB_H
#define __MY_LIB_H
#include "my_lib.h"
#include "lcd_init.h"
#include "lcd.h"
#include "stdio.h"
#include "lvgl.h"
#include "lv_port_disp.h"
#include "lv_ex_conf.h"
#include "lv_examples.h"
#include "lv_demo_widgets.h"
#include "usbd_cdc_if.h"
void lv_port_indev_init(void);
void lv_ex_calendar_1(void);
void mbox_test(void);
void list_test(void);
void btnm_test(void);
void lv_ex_textarea_1(void);
void lvgl_keyboard_mode_test(void);
void label_test(void);
void User_task(void);

void LOCK(void);
void UNLOCK(void);
void lv_ex_textarea_2(void);
void lvgl_keyboard_mode_test2(void);
#endif
