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
uint8_t text_temp[500] = "";
// static lv_style_t font_style_35;
// static lv_style_t font_style_45;
// static lv_style_t font_style_60;
static lv_style_t font_style_24;
static lv_style_t font_style_50;
static lv_task_t *Tim_Task; //创建一个实时读取温度的任务。
static void update_time(lv_task_t *task)
{
    sprintf((uint8_t *)text_temp, "%02d:%02d:%02d", my_rtc.hour, my_rtc.min, my_rtc.sec);
    lv_label_set_text(label1, text_temp); /* 设置文字 */
}
// LV_FONT_DECLARE(myFont45); // 字体声明,45号字体，30kb，仅有数字字母
// LV_FONT_DECLARE(myFont60); // 字体声明,60号字体,200kb开始，大小160kb
// LV_FONT_DECLARE(myFont35); // 字体声明,35号字体，数字字母加:.一二三四五六日年月
LV_FONT_DECLARE(myFont24); // 字体声明,35号字体，数字字母加:.一二三四五六日年月
LV_FONT_DECLARE(myFont50); // 字体声明,35号字体，数字字母加:.一二三四五六日年月

lv_fs_res_t lv_res;
lv_fs_file_t lv_file;
uint32_t length_text = 0;
uint8_t test_data = 0;
void test_lv_font(void) // UTF-8编码
{
    // lv_res = lv_fs_open(&lv_file, "F:/T1.txt", LV_FS_MODE_RD);
    // lv_fs_read(&lv_file, text_temp, 100, &length_text);

    // lv_style_init(&font_style_35);
    // lv_style_set_text_font(&font_style_35, LV_STATE_DEFAULT, &myFont35);

    // lv_style_init(&font_style_45);
    // lv_style_set_text_font(&font_style_45, LV_STATE_DEFAULT, &myFont45);

    // lv_style_init(&font_style_60);
    // lv_style_set_text_font(&font_style_60, LV_STATE_DEFAULT, &myFont60);

    lv_style_init(&font_style_24);
    lv_style_set_text_font(&font_style_24, LV_STATE_DEFAULT, &myFont24);

    lv_style_init(&font_style_50);
    lv_style_set_text_font(&font_style_50, LV_STATE_DEFAULT, &myFont50);

    lv_obj_t *scr = lv_disp_get_scr_act(NULL); /* 获取当前屏幕 */

    // lv_theme_t *th = lv_theme_material_init(LV_COLOR_BLACK, LV_COLOR_BLACK, 0,
    //                                         &myFont35, &myFont35,
    //                                         &myFont35, &myFont35);
    // lv_theme_set_act(th);

    // lv_scr_load(scr);

    lv_obj_t *label1 = lv_label_create(scr, NULL); /* 创建 label 控件 */
    lv_obj_set_pos(label1, 0, 0);
    lv_obj_align(label1, NULL, LV_ALIGN_CENTER, -60, -60); /* 设置控件的对齐方式-相对坐标 */ // 应用效果风格
    lv_obj_add_style(label1, LV_LABEL_PART_MAIN, &font_style_50);
    sprintf((uint8_t *)text_temp, "%02d:%02d:%02d", my_rtc.hour, my_rtc.min, my_rtc.sec);
    lv_label_set_text(label1, text_temp); /* 设置文字 */

    lv_obj_t *label2 = lv_label_create(scr, NULL);                                         /* 创建 label 控件 */
    lv_obj_set_pos(label2, 0, 0);                                                          /* 设置控件的坐标 */
    lv_label_set_text(label2, "2022年5月15日\n   星期日");                                 /* 设置文字 */
    lv_obj_align(label2, NULL, LV_ALIGN_CENTER, -30, 0); /* 设置控件的对齐方式-相对坐标 */ // 应用效果风格
    lv_obj_add_style(label2, LV_LABEL_PART_MAIN, &font_style_24);
    // lv_fs_close(&lv_file);

    Tim_Task = lv_task_create(update_time, 10, LV_TASK_PRIO_MID, &test_data);
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

    static lv_style_t font_style_50;
    lv_style_init(&font_style_50);
    lv_style_set_text_font(&font_style_50, LV_STATE_DEFAULT, &myFont50);

    static lv_style_t font_style_24;
    lv_style_init(&font_style_24);
    lv_style_set_text_font(&font_style_24, LV_STATE_DEFAULT, &myFont24);

    label1 = lv_label_create(lv_scr_act(), NULL);

    sprintf((uint8_t *)text_temp, "%02d:%02d:%02d", my_rtc.hour, my_rtc.min, my_rtc.sec);
    lv_obj_add_style(label1, LV_LABEL_PART_MAIN, &font_style_50);
    lv_label_set_long_mode(label1, LV_LABEL_LONG_BREAK); /*Break the long lines*/
                                                         //使能文本重绘色功能
    lv_label_set_recolor(label1, true);                  /*Enable re-coloring by commands in the text*/
                                                         //设置文本对齐模式
    lv_label_set_align(label1, LV_LABEL_ALIGN_CENTER);     /*Center aligned lines*/
                                                         //设置文本内容

    lv_label_set_text(label1, text_temp);
    lv_obj_set_width(label1, 240);
    //设置对齐模式
    lv_obj_align(label1, NULL, LV_ALIGN_CENTER, 0, -50);


    label2 = lv_label_create(lv_scr_act(), NULL);
    sprintf((uint8_t *)text_temp, "  2022年5月15日\n星期日", my_rtc.hour, my_rtc.min, my_rtc.sec);
    lv_obj_add_style(label2, LV_LABEL_PART_MAIN, &font_style_24);
    lv_label_set_long_mode(label2, LV_LABEL_LONG_BREAK); /*Break the long lines*/
                                                         //使能文本重绘色功能
    lv_label_set_recolor(label2, true);                  /*Enable re-coloring by commands in the text*/
                                                         //设置文本对齐模式
    lv_label_set_align(label2, LV_LABEL_ALIGN_CENTER);     /*Center aligned lines*/
                                                         //设置文本内容

    lv_label_set_text(label2, text_temp);
    lv_obj_set_width(label2, 240);
    //设置对齐模式
    lv_obj_align(label2, NULL, LV_ALIGN_CENTER, 0, 50);

    lv_task_t *task = lv_task_create(update_time, 1000, LV_TASK_PRIO_LOW, &test_data);
}