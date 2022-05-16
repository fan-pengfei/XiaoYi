#ifndef __MY_LIB_H
#define __MY_LIB_H

#include "lcd_init.h"
#include "lcd.h"
#include "stdio.h"
#include "lvgl.h"
#include "lv_port_disp.h"
#include "lv_ex_conf.h"
#include "lv_examples.h"
#include "lv_demo_widgets.h"
void LCD_SET_LIGHT(int light);
void analog(lv_obj_t *win);
void test_lv_font(void);
void btnm_test(void);
#endif
