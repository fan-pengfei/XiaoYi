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
uint8_t Minute = 59;
uint8_t Hour = 8;
uint8_t Second = 2;
extern Times my_rtc;
lv_obj_t *label1, *label2;
__attribute__((aligned(4))) uint8_t text_temp[500] = "";
// static void update_time(lv_task_t *task)
// {
//     sprintf((uint8_t *)text_temp, "%02d:%02d:%02d", my_rtc.hour, my_rtc.min, my_rtc.sec);
//     lv_label_set_text(label1, text_temp);
// }
// uint8_t test_data;
// void analog(lv_obj_t *win)
// {
//     lv_obj_t *central = win;

//     lv_obj_set_size(central, LV_HOR_RES_MAX, LV_VER_RES_MAX);
//     lv_obj_set_pos(central, 0, 0);

//     // lv_obj_t *img = lv_img_create(central, NULL);
//     // lv_img_set_src(img, "F:/3.bin");

//     // lv_obj_set_size(img, 240, 240);
//     // lv_obj_set_auto_realign(img, true);
//     // lv_obj_align(img, central, LV_ALIGN_CENTER, 0, 0);

//     static lv_style_t font_style1;
//     lv_style_init(&font_style1);
//     lv_style_set_text_font(&font_style1, LV_STATE_DEFAULT, &lv_font_montserrat_32);

//     label1 = lv_label_create(lv_scr_act(), NULL);

//     sprintf((uint8_t *)text_temp, "%02d:%02d:%02d", my_rtc.hour, my_rtc.min, my_rtc.sec);
//     lv_obj_add_style(label1, LV_LABEL_PART_MAIN, &font_style1);
//     lv_label_set_align(label1, LV_LABEL_ALIGN_CENTER); /*Center aligned lines*/
//     LV_FONT_DECLARE(myFont);
//     lv_obj_set_style_local_text_font(label1, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &myFont);
//     lv_label_set_text(label1, text_temp);
//     lv_obj_align(label1, NULL, LV_ALIGN_CENTER, 0, 0);
//     lv_task_t *task = lv_task_create(update_time, 1000, LV_TASK_PRIO_LOW, &test_data);
// }
// LV_FONT_DECLARE(myFont);   // 字体声明
// LV_FONT_DECLARE(myFont1);  // 字体声明
// LV_FONT_DECLARE(myFont45); // 字体声明,45号字体，30kb，仅有数字字母
// LV_FONT_DECLARE(myFont60); // 字体声明,60号字体,200kb开始，大小160kb
// LV_FONT_DECLARE(myFont35); // 字体声明,35号字体，数字字母加:.一二三四五六日年月
LV_FONT_DECLARE(myFont24); // 字体声明,35号字体，数字字母加:.一二三四五六日年月
lv_fs_res_t lv_res;
lv_fs_file_t lv_file;
uint32_t length_text = 0;

void test_lv_font(void) // UTF-8编码
{
    lv_res = lv_fs_open(&lv_file, "F:/T1.txt", LV_FS_MODE_RD);
    lv_fs_read(&lv_file, text_temp, 100, &length_text);

    // lv_style_t font_style_35;
    // lv_style_init(&font_style_35);
    // lv_style_set_text_font(&font_style_35, LV_STATE_DEFAULT, &myFont35);

    // lv_style_t font_style_45;
    // lv_style_init(&font_style_45);
    // lv_style_set_text_font(&font_style_45, LV_STATE_DEFAULT, &myFont45);

    // static lv_style_t font_style_60;
    // lv_style_init(&font_style_60);
    // lv_style_set_text_font(&font_style_60, LV_STATE_DEFAULT, &myFont60);

    static lv_style_t font_style_24;
    lv_style_init(&font_style_24);
    lv_style_set_text_font(&font_style_24, LV_STATE_DEFAULT, &myFont24);

    // // label1 = lv_label_create(lv_scr_act(), NULL);
    // // label2 = lv_label_create(lv_scr_act(), NULL);

    // // lv_obj_t *scr = lv_disp_get_scr_act(NULL); /* 获取当前屏幕 */

    // // lv_theme_t *th = lv_theme_material_init(LV_COLOR_BLACK, LV_COLOR_BLACK, 0,
    // //                                         &myFont45, &myFont45,
    // //                                         &myFont45, &myFont45);
    // // lv_theme_set_act(th);

    // // lv_scr_load(scr);

    // // lv_obj_t *label1 = lv_label_create(scr, NULL);     /* 创建 label 控件 */
    // // lv_obj_set_pos(label1, 100, 100);                  /* 设置控件的坐标 */
    // // lv_label_set_text(label1, "12:35:57");             /* 设置文字 */
    // // lv_obj_align(label1, NULL, LV_ALIGN_CENTER, 0, 0); /* 设置控件的对齐方式-相对坐标 */
    // // // 应用效果风格

    // // lv_obj_add_style(label2, LV_LABEL_PART_MAIN, &font_style_35);
    // // lv_obj_set_pos(label2, 100, 100);                  /* 设置控件的坐标 */
    // // lv_label_set_text(label2, "12:35:57");             /* 设置文字 */
    // // lv_obj_align(label2, NULL, LV_ALIGN_CENTER, 0, 50); /* 设置控件的对齐方式-相对坐标 */

    // // sprintf((uint8_t *)text_temp, "%02d:%02d:%02d", my_rtc.hour, my_rtc.min, my_rtc.sec);
    // // lv_obj_add_style(label1, LV_LABEL_PART_MAIN, &font_style_45);
    // // // lv_obj_set_style_local_text_font(label1, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &myFont35);
    // // lv_label_set_text(label1, text_temp);
    // // lv_obj_align(label1, NULL, LV_ALIGN_CENTER, 0, 0);

    // // lv_task_t *task = lv_task_create(update_time, 1000, LV_TASK_PRIO_LOW, &test_data);

    // // lv_res = lv_fs_open(&lv_file, "F:/T1.txt", LV_FS_MODE_RD);
    // // lv_fs_seek(&lv_file, 0);
    // // lv_fs_read(&lv_file, text_temp, 100, &length_text);

    lv_obj_t *scr = lv_disp_get_scr_act(NULL); /* 获取当前屏幕 */

    // lv_theme_t *th = lv_theme_material_init(LV_COLOR_BLACK, LV_COLOR_BLACK, 0,
    //                                         &myFont35, &myFont35,
    //                                         &myFont35, &myFont35);
    // lv_theme_set_act(th);

    // lv_scr_load(scr);

    lv_obj_t *label1 = lv_label_create(scr, NULL);                                         /* 创建 label 控件 */
    lv_obj_set_pos(label1, 0, 0);                                                          /* 设置控件的坐标 */
    lv_label_set_text(label1, text_temp);                                                  /* 设置文字 */
    lv_obj_align(label1, NULL, LV_ALIGN_CENTER, -50, -20); /* 设置控件的对齐方式-相对坐标 */ // 应用效果风格
    lv_obj_add_style(label1, LV_LABEL_PART_MAIN, &font_style_24);
    lv_fs_close(&lv_file);
    // lv_obj_t *label2 = lv_label_create(scr, NULL);                                       /* 创建 label 控件 */
    // lv_obj_set_pos(label2, 100, 100);                                                    /* 设置控件的坐标 */
    // lv_label_set_text(label2, "2022年5月14日\n   星期六\n");                                 /* 设置文字 */
    // lv_obj_align(label2, NULL, LV_ALIGN_CENTER, 0, 50); /* 设置控件的对齐方式-相对坐标 */ // 应用效果风格
    // lv_obj_add_style(label2, LV_LABEL_PART_MAIN, &font_style_35);

    // lv_obj_t *scr = lv_disp_get_scr_act(NULL); /* 获取当前屏幕 */

    // lv_theme_t *th = lv_theme_material_init(LV_COLOR_BLACK, LV_COLOR_BLACK, 0,
    //                                         &myFont24, &myFont24,
    //                                         &myFont24, &myFont24);
    // lv_theme_set_act(th);

    // lv_scr_load(scr);

    // lv_obj_t *label1 = lv_label_create(scr, NULL);                           /* 创建 label 控件 */
    // lv_obj_set_pos(label1, 0, 0);                                            /* 设置控件的坐标 */
    // lv_label_set_text(label1, "你好,里飞网:www.lfly.xyz\n参数\n配置\n维护"); /* 设置文字 */
    // lv_obj_align(label1, NULL, LV_ALIGN_IN_TOP_MID, 0, 0);                 /* 设置控件的对齐方式-相对坐标 */
}