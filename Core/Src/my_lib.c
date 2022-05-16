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
#include "rtc.h"
void LCD_SET_LIGHT(int light)
{
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET);
}

void lv_ex_calendar_1(void);
void spinbox_time(void);
void img1_show(void);
void img2_show(void);
void img3_show(void);
void btnm_p_test(void);
void btnm_t_test(void);
void text_show(uint8_t num);
uint8_t Minute = 59;
uint8_t Hour = 8;
uint8_t Second = 2;
extern Times my_rtc;
lv_obj_t *label1, *label2, *label_text;
static lv_obj_t *btnm1, *btnm_p, *btnm_t;
lv_obj_t *calendar;
lv_obj_t *img1, *img2, *img3;
static lv_obj_t *spinbox_time1, *spinbox_time2;
uint8_t text_temp[500] = "", text_temp2[500] = "";
int32_t time_cnt = 0;
// static lv_style_t font_style_35;
// static lv_style_t font_style_45;
// static lv_style_t font_style_60;
static lv_style_t font_style_24;
static lv_style_t font_style_50;
static lv_task_t *Tim_Task; //创建一个实时读取温度的任务。
uint8_t Mode = 0x01;
extern RTC_DateTypeDef GetData;
extern RTC_TimeTypeDef GetTime;
uint8_t now_mode = 1;
uint8_t week_text[7][5] = {"一", "二", "三", "四", "五", "六", "日"};

uint8_t CaculateWeekDay(int y, int m, int d)
{
    int week;
    if (m == 1 || m == 2)
    {
        m += 12;
        y--;
    }
    week = (d + 2 * m + 3 * (m + 1) / 5 + y + y / 4 - y / 100 + y / 400) % 7;
    return week;
}
static void update_time(lv_task_t *task)
{
    if (Mode == 0x00)
    {
    }
    else if (Mode == 0x01)
    {
        now_mode = 1;
        sprintf((uint8_t *)text_temp, "%02d:%02d:%02d", GetTime.Hours, GetTime.Minutes, GetTime.Seconds);
        lv_label_set_text(label1, text_temp); /* 设置文字 */
        sprintf((uint8_t *)text_temp2, "  20%02d年%02d月%02d日\n星期%s", GetData.Year, GetData.Month, GetData.Date, week_text[CaculateWeekDay(GetData.Year, GetData.Month, GetData.Date)]);
        lv_label_set_text(label2, text_temp2); /* 设置文字 */
    }
    else if (Mode == 0x02)
    {
        // lv_group_add_obj(group, btnm1);
        if (now_mode == 1)
        {
            lv_obj_del(label1);
            lv_obj_del(label2);
            lv_group_remove_obj(btnm1);
        }
        if (now_mode == 3)
        {
            lv_obj_del(spinbox_time1);
            lv_obj_del(spinbox_time2);
            lv_group_remove_obj(btnm1);
        }
        if (now_mode == 4)
        {
            lv_obj_del(btnm_p);
            lv_group_remove_obj(btnm1);
            lv_obj_t *act_obj = lv_scr_act(); // 获取当前活动页
            lv_obj_clean(act_obj);            // 清空此前页面
            btnm_test();
            lv_group_remove_obj(btnm1);
        }
        if (now_mode == 5)
        {
            lv_obj_del(btnm_t);
            lv_obj_del(label_text);
            lv_group_remove_obj(btnm1);
            lv_obj_t *act_obj = lv_scr_act(); // 获取当前活动页
            lv_obj_clean(act_obj);            // 清空此前页面
            btnm_test();
            lv_group_remove_obj(btnm1);
        }
        // lv_group_add_obj(group, btnm1);
        lv_ex_calendar_1();
        lv_group_add_obj(group, calendar);
        now_mode = 2;
        Mode = 0x00;
    }
    else if (Mode == 0x03)
    {
        // lv_group_add_obj(group, btnm1);
        lv_group_remove_obj(calendar);
        lv_group_add_obj(group, btnm1);
        now_mode = 2;
        Mode = 0x00;
    }
    else if (Mode == 0x04)
    {
        // lv_group_add_obj(group, btnm1);
        if (now_mode == 2)
        {
            lv_obj_del(calendar);
        }
        if (now_mode == 3)
        {
            lv_obj_del(spinbox_time1);
            lv_obj_del(spinbox_time2);
        }
        if (now_mode == 4)
        {
            lv_obj_del(btnm_p);
            lv_obj_t *act_obj = lv_scr_act(); // 获取当前活动页
            lv_obj_clean(act_obj);            // 清空此前页面
            btnm_test();
        }
        if (now_mode == 5)
        {
            lv_obj_del(btnm_t);
            lv_obj_del(label_text);
            lv_group_remove_obj(btnm1);
            lv_obj_t *act_obj = lv_scr_act(); // 获取当前活动页
            lv_obj_clean(act_obj);            // 清空此前页面
            btnm_test();
            lv_group_remove_obj(btnm1);
        }
        analog(lv_scr_act());
        lv_group_add_obj(group, btnm1);
        now_mode = 1;
        Mode = 0x01;
    }
    else if (Mode == 0x05)
    {
        // lv_group_add_obj(group, btnm1);
        if (now_mode == 1)
        {
            lv_obj_del(label1);
            lv_obj_del(label2);
            lv_group_remove_obj(btnm1);
        }
        if (now_mode == 2)
        {
            lv_obj_del(calendar);
            lv_group_remove_obj(btnm1);
        }
        if (now_mode == 4)
        {
            lv_obj_del(btnm_p);
            lv_group_remove_obj(btnm1);
            lv_obj_t *act_obj = lv_scr_act(); // 获取当前活动页
            lv_obj_clean(act_obj);            // 清空此前页面
            btnm_test();
            lv_group_remove_obj(btnm1);
        }
        if (now_mode == 5)
        {
            lv_obj_del(btnm_t);
            lv_obj_del(label_text);
            lv_group_remove_obj(btnm1);
            lv_obj_t *act_obj = lv_scr_act(); // 获取当前活动页
            lv_obj_clean(act_obj);            // 清空此前页面
            btnm_test();
            lv_group_remove_obj(btnm1);
        }
        now_mode = 3;
        spinbox_time();
        lv_group_add_obj(group, spinbox_time1);
        Mode = 0x00;
    }
    else if (Mode == 0x06)
    {
        lv_group_remove_obj(spinbox_time1);
        lv_group_add_obj(group, spinbox_time2);
        Mode = 0x00;
    }
    else if (Mode == 0x07)
    {
        lv_group_remove_obj(spinbox_time2);
        lv_group_add_obj(group, btnm1);
        Mode = 0x00;
    }
    else if (Mode == 0x08)
    {
        // lv_group_add_obj(group, btnm1);
        if (now_mode == 1)
        {
            lv_obj_del(label1);
            lv_obj_del(label2);
            lv_group_remove_obj(btnm1);
        }
        if (now_mode == 2)
        {
            lv_obj_del(calendar);
            lv_group_remove_obj(btnm1);
        }
        if (now_mode == 3)
        {
            lv_obj_del(spinbox_time1);
            lv_obj_del(spinbox_time2);
            lv_group_remove_obj(btnm1);
        }
        if (now_mode == 5)
        {
            lv_obj_del(btnm_t);
            lv_obj_del(label_text);
            lv_group_remove_obj(btnm1);
            lv_obj_t *act_obj = lv_scr_act(); // 获取当前活动页
            lv_obj_clean(act_obj);            // 清空此前页面
            btnm_test();
            lv_group_remove_obj(btnm1);
        }
        img1_show();
        btnm_p_test();
        lv_group_add_obj(group, btnm_p);
        now_mode = 4;
        Mode = 0x00;
    }
    else if (Mode == 0x09)
    {
        lv_group_remove_obj(btnm_p);
        lv_group_add_obj(group, btnm1);
        Mode = 0x00;
    }
    else if (Mode == 0x10)
    {
        // lv_group_add_obj(group, btnm1);
        if (now_mode == 1)
        {
            lv_obj_del(label1);
            lv_obj_del(label2);
            lv_group_remove_obj(btnm1);
        }
        if (now_mode == 2)
        {
            lv_obj_del(calendar);
            lv_group_remove_obj(btnm1);
        }
        if (now_mode == 3)
        {
            lv_obj_del(spinbox_time1);
            lv_obj_del(spinbox_time2);
            lv_group_remove_obj(btnm1);
        }
        if (now_mode == 4)
        {
            lv_obj_del(btnm_p);
            lv_group_remove_obj(btnm1);
            lv_obj_t *act_obj = lv_scr_act(); // 获取当前活动页
            lv_obj_clean(act_obj);            // 清空此前页面
            btnm_test();
            lv_group_remove_obj(btnm1);
        }
        text_show(1);
        btnm_t_test();
        lv_group_add_obj(group, btnm_t);
        now_mode = 5;
        Mode = 0x00;
    }
    else if (Mode == 0x11)
    {
        lv_group_remove_obj(btnm_t);
        lv_group_add_obj(group, btnm1);
        Mode = 0x00;
    }
}
LV_FONT_DECLARE(myFont24); // 字体声明,35号字体，数字字母加:.一二三四五六日年月,2M位置开始
LV_FONT_DECLARE(myFont50); // 字体声明,35号字体，数字字母加:.一二三四五六日年月，0kb开始

lv_fs_res_t lv_res;
lv_fs_file_t lv_file;
uint32_t length_text = 0;
uint8_t test_data = 0;
void img1_show(void)
{
    img1 = lv_img_create(lv_scr_act(), NULL);
    lv_img_set_src(img1, "F:/P4.bin");
    lv_obj_set_size(img1, 240, 200);
    lv_obj_set_auto_realign(img1, true);
    lv_obj_align(img1, NULL, LV_ALIGN_CENTER, 0, -40);
}
void img2_show(void)
{
    img2 = lv_img_create(lv_scr_act(), NULL);
    lv_img_set_src(img2, "F:/P2.bin");
    lv_obj_set_size(img2, 240, 200);
    lv_obj_set_auto_realign(img2, true);
    lv_obj_align(img2, NULL, LV_ALIGN_CENTER, 0, -40);
}
void img3_show(void)
{
    img3 = lv_img_create(lv_scr_act(), NULL);
    lv_img_set_src(img3, "F:/P3.bin");
    lv_obj_set_size(img3, 240, 200);
    lv_obj_set_auto_realign(img3, true);
    lv_obj_align(img3, NULL, LV_ALIGN_CENTER, 0, -40);
}
uint32_t num_f_text;
void text_show(uint8_t num)
{
    uint8_t temp_text1[15];
    lv_fs_file_t lv_file;
    for (uint8_t i = 0; i < 255; i++)
    {
        text_temp2[i] = 0;
    }
    sprintf((uint8_t *)temp_text1, "F:/T%d.txt", num);
    lv_res = lv_fs_open(&lv_file, temp_text1, LV_FS_MODE_RD);
    lv_fs_read(&lv_file, text_temp2, 200, &num_f_text);
    lv_fs_close(&lv_file);

    lv_style_init(&font_style_24);
    lv_style_set_text_font(&font_style_24, LV_STATE_DEFAULT, &myFont24);

    lv_obj_t *scr = lv_disp_get_scr_act(NULL); /* 获取当前屏幕 */

    label_text = lv_label_create(scr, NULL); /* 创建 label 控件 */
    lv_obj_set_pos(label_text, 0, 0);
    lv_obj_align(label_text, NULL, LV_ALIGN_CENTER, -45, -90); /* 设置控件的对齐方式-相对坐标 */ // 应用效果风格
    lv_obj_add_style(label_text, LV_LABEL_PART_MAIN, &font_style_24);
    lv_label_set_text(label_text, text_temp2); /* 设置文字 */
}

void test_lv_font(void) // UTF-8编码
{
    lv_obj_t *central = lv_scr_act();
    lv_obj_set_size(central, LV_HOR_RES_MAX, LV_VER_RES_MAX);
    lv_obj_set_pos(central, 0, 0);
    lv_style_init(&font_style_24);
    lv_style_set_text_font(&font_style_24, LV_STATE_DEFAULT, &myFont24);

    lv_style_init(&font_style_50);
    lv_style_set_text_font(&font_style_50, LV_STATE_DEFAULT, &myFont50);

    lv_obj_t *scr = lv_disp_get_scr_act(NULL); /* 获取当前屏幕 */

    lv_obj_t *label1 = lv_label_create(scr, NULL); /* 创建 label 控件 */
    lv_obj_set_pos(label1, 0, 0);
    lv_obj_align(label1, NULL, LV_ALIGN_CENTER, -60, -60); /* 设置控件的对齐方式-相对坐标 */ // 应用效果风格
    lv_obj_add_style(label1, LV_LABEL_PART_MAIN, &font_style_50);
    sprintf((uint8_t *)text_temp, "%02d:%02d:%02d", my_rtc.hour, my_rtc.min, my_rtc.sec);
    lv_label_set_text(label1, text_temp); /* 设置文字 */

    lv_obj_t *label2 = lv_label_create(scr, NULL); /* 创建 label 控件 */
    lv_obj_set_pos(label2, 0, 0);                  /* 设置控件的坐标 */
    sprintf((uint8_t *)text_temp2, "  20%02d年%02d月%02d日\n星期%s", GetData.Year, GetData.Month, GetData.Date, week_text[CaculateWeekDay(GetData.Year, GetData.Month, GetData.Date)]);
    lv_label_set_text(label2, text_temp);                                                  /* 设置文字 */
    lv_obj_align(label2, NULL, LV_ALIGN_CENTER, -30, 0); /* 设置控件的对齐方式-相对坐标 */ // 应用效果风格
    lv_obj_add_style(label2, LV_LABEL_PART_MAIN, &font_style_24);
    // lv_fs_close(&lv_file);

    Tim_Task = lv_task_create(update_time, 10, LV_TASK_PRIO_MID, &test_data);
}

void analog(lv_obj_t *win)
{
    lv_obj_t *central = lv_scr_act();

    lv_obj_set_size(central, LV_HOR_RES_MAX, LV_VER_RES_MAX);
    lv_obj_set_pos(central, 0, 0);

    static lv_style_t font_style_50;
    lv_style_init(&font_style_50);
    lv_style_set_text_font(&font_style_50, LV_STATE_DEFAULT, &myFont50);

    static lv_style_t font_style_24;
    lv_style_init(&font_style_24);
    lv_style_set_text_font(&font_style_24, LV_STATE_DEFAULT, &myFont24);

    label1 = lv_label_create(lv_scr_act(), NULL);

    sprintf((uint8_t *)text_temp, "%02d:%02d:%02d", GetTime.Hours, GetTime.Minutes, GetTime.Seconds);
    lv_obj_add_style(label1, LV_LABEL_PART_MAIN, &font_style_50);
    lv_label_set_long_mode(label1, LV_LABEL_LONG_BREAK); /*Break the long lines*/
                                                         //使能文本重绘色功能
    lv_label_set_recolor(label1, true);                  /*Enable re-coloring by commands in the text*/
                                                         //设置文本对齐模式
    lv_label_set_align(label1, LV_LABEL_ALIGN_CENTER);   /*Center aligned lines*/
                                                         //设置文本内容

    lv_label_set_text(label1, text_temp);
    lv_obj_set_width(label1, 240);
    //设置对齐模式
    lv_obj_align(label1, NULL, LV_ALIGN_CENTER, 0, -50);

    label2 = lv_label_create(lv_scr_act(), NULL);
    sprintf((uint8_t *)text_temp2, "  20%02d年%02d月%02d日\n星期%s", GetData.Year, GetData.Month, GetData.Date, week_text[CaculateWeekDay(GetData.Year, GetData.Month, GetData.Date)]);
    lv_obj_add_style(label2, LV_LABEL_PART_MAIN, &font_style_24);
    lv_label_set_long_mode(label2, LV_LABEL_LONG_BREAK); /*Break the long lines*/
                                                         //使能文本重绘色功能
    lv_label_set_recolor(label2, true);                  /*Enable re-coloring by commands in the text*/
                                                         //设置文本对齐模式
    lv_label_set_align(label2, LV_LABEL_ALIGN_CENTER);   /*Center aligned lines*/
                                                         //设置文本内容

    lv_label_set_text(label2, text_temp2);
    lv_obj_set_width(label2, 240);
    //设置对齐模式
    lv_obj_align(label2, NULL, LV_ALIGN_CENTER, 0, 50);

    lv_task_t *task = lv_task_create(update_time, 1000, LV_TASK_PRIO_LOW, &test_data);
}
static void btm_t_event_handler(lv_obj_t *obj, lv_event_t event)
{
    switch (event)
    {
    case LV_EVENT_KEY:
    {
        const uint32_t *key = lv_event_get_data();
        if (*key != LV_KEY_ENTER)
        {
            if (lv_btnmatrix_get_active_btn(btnm_t) == 0)
            {
                lv_obj_del(label_text);
                text_show(1);
            }
            if (lv_btnmatrix_get_active_btn(btnm_t) == 1)
            {
                lv_obj_del(label_text);
                text_show(2);
            }
            if (lv_btnmatrix_get_active_btn(btnm_t) == 2)
            {
                lv_obj_del(label_text);
                text_show(3);
            }
        }
        else
        {
            Mode = 0x11;
        }
    }
    break;
    default:
        break;
    }
}
void btnm_t_test(void)
{
    static const char *btnm_text[] = {
        "1",
        "2",
        "3", ""};
    btnm_t = lv_btnmatrix_create(lv_scr_act(), NULL);
    // lv_obj_invalidate_area(btnm1,test);
    lv_btnmatrix_set_map(btnm_t, btnm_text);
    lv_obj_set_size(btnm_t, 100, 20); //可以设置窗口大小
    lv_obj_align(btnm_t, NULL, LV_ALIGN_CENTER, 0, 75);
    lv_group_add_obj(group, btnm_t);
    lv_obj_set_event_cb(btnm_t, btm_t_event_handler);
}
static void btm_p_event_handler(lv_obj_t *obj, lv_event_t event)
{
    switch (event)
    {
    case LV_EVENT_KEY:
    {
        const uint32_t *key = lv_event_get_data();
        if (*key != LV_KEY_ENTER)
        {
            if (lv_btnmatrix_get_active_btn(btnm_p) == 1)
            {
                img2_show();
            }
            if (lv_btnmatrix_get_active_btn(btnm_p) == 0)
            {
                img1_show();
            }
            if (lv_btnmatrix_get_active_btn(btnm_p) == 2)
            {
                img3_show();
            }
        }
        else
        {
            if (lv_btnmatrix_get_active_btn(btnm_p) == 1)
            {
                lv_obj_del(img1);
            }
            if (lv_btnmatrix_get_active_btn(btnm_p) == 0)
            {
                lv_obj_del(img2);
            }
            if (lv_btnmatrix_get_active_btn(btnm_p) == 2)
            {
                lv_obj_del(img3);
            }
            Mode = 0x09;
        }
    }
    break;
    default:
        break;
    }
}
void btnm_p_test(void)
{
    static const char *btnm_text[] = {
        "1",
        "2",
        "3", ""};
    btnm_p = lv_btnmatrix_create(lv_scr_act(), NULL);
    // lv_obj_invalidate_area(btnm1,test);
    lv_btnmatrix_set_map(btnm_p, btnm_text);
    lv_obj_set_size(btnm_p, 100, 20); //可以设置窗口大小
    lv_obj_align(btnm_p, NULL, LV_ALIGN_CENTER, 0, 75);
    lv_group_add_obj(group, btnm_p);
    lv_obj_set_event_cb(btnm_p, btm_p_event_handler);
}
static void btm_event_handler(lv_obj_t *obj, lv_event_t event)
{
    switch (event)
    {
    case LV_EVENT_KEY:
    {
        const uint32_t *key = lv_event_get_data();
        if (*key == LV_KEY_ENTER)
        {
            if (now_mode != 1)
            {
                if (lv_btnmatrix_get_active_btn(btnm1) == 0)
                {
                    Mode = 0x04;
                }
            }
            if (now_mode != 2)
            {
                if (lv_btnmatrix_get_active_btn(btnm1) == 1)
                {
                    Mode = 0x02;
                }
            }
            if (now_mode != 3)
            {
                if (lv_btnmatrix_get_active_btn(btnm1) == 2)
                {
                    Mode = 0x05;
                }
            }
            if (now_mode != 4)
            {
                if (lv_btnmatrix_get_active_btn(btnm1) == 3)
                {
                    Mode = 0x08;
                }
            }
            if (now_mode != 5)
            {
                if (lv_btnmatrix_get_active_btn(btnm1) == 4)
                {
                    Mode = 0x10;
                }
            }
        }
    }
    break;
    default:
        break;
    }
}
void btnm_test(void)
{
    lv_obj_t *central = lv_scr_act();
    lv_obj_set_size(central, LV_HOR_RES_MAX, LV_VER_RES_MAX);
    lv_obj_set_pos(central, 0, 0);
    static const char *btnm_text[] = {
        "1",
        "2",
        "3",
        "4",
        "5", ""};
    btnm1 = lv_btnmatrix_create(lv_scr_act(), NULL);
    // lv_obj_invalidate_area(btnm1,test);
    lv_btnmatrix_set_map(btnm1, btnm_text);
    lv_obj_set_size(btnm1, 200, 30); //可以设置窗口大小
    lv_obj_align(btnm1, NULL, LV_ALIGN_CENTER, 0, 100);
    lv_group_add_obj(group, btnm1);
    lv_obj_set_event_cb(btnm1, btm_event_handler);
}

static void event_handler(lv_obj_t *obj, lv_event_t event)
{
    switch (event)
    {
    case LV_EVENT_KEY:
    {
        const uint32_t *key = lv_event_get_data();
        if (*key == LV_KEY_ENTER)
        {

            Mode = 0x03;
        }
    }
    break;
    default:
        break;
    }
}
void lv_ex_calendar_1(void)
{
    calendar = lv_calendar_create(lv_scr_act(), NULL);
    lv_obj_set_size(calendar, 240, 200);
    lv_obj_align(calendar, NULL, LV_ALIGN_IN_TOP_MID, 0, 0);
    lv_group_add_obj(group, calendar);
    lv_obj_set_event_cb(calendar, event_handler);

    /*Make the date number smaller to be sure they fit into their area*/
    lv_obj_set_style_local_text_font(calendar, LV_CALENDAR_PART_DATE, LV_STATE_DEFAULT, lv_theme_get_font_small());

    /*Set today's date*/
    lv_calendar_date_t today;
    today.year = 2000 + GetData.Year;
    today.month = GetData.Month;
    today.day = GetData.Date;

    lv_calendar_set_today_date(calendar, &today);
    lv_calendar_set_showed_date(calendar, &today);

    /*Highlight a few days*/
    static lv_calendar_date_t highlighted_days[3]; /*Only its pointer will be saved so should be static*/
    highlighted_days[0].year = 2022;
    highlighted_days[0].month = 6;
    highlighted_days[0].day = 7;

    highlighted_days[1].year = 2022;
    highlighted_days[1].month = 6;
    highlighted_days[1].day = 11;

    highlighted_days[2].year = 2022;
    highlighted_days[2].month = 10;
    highlighted_days[2].day = 1;

    lv_calendar_set_highlighted_dates(calendar, highlighted_days, 3);
}
int bcd_decimal_code(int bcd)
{
    return (bcd + (bcd / 10) * 6);
}
int decimal_bcd_code(int decimal)
{
    return (decimal - (decimal >> 4) * 6);
}
static void spinbox_time_event_handler(lv_obj_t *obj, lv_event_t event)
{
    switch (event)
    {
    case LV_EVENT_KEY:
    {
        const uint32_t *key = lv_event_get_data();
        if (*key == LV_KEY_ENTER)
        {
            rtc_set_time(bcd_decimal_code(GetData.Year), bcd_decimal_code(GetData.Month), bcd_decimal_code(GetData.Date), bcd_decimal_code(lv_spinbox_get_value(spinbox_time1) / 10000), bcd_decimal_code((lv_spinbox_get_value(spinbox_time1) % 10000) / 100), bcd_decimal_code(lv_spinbox_get_value(spinbox_time1) % 100));
            Mode = 0x06;
        }
    }
    break;
    default:
        break;
    }
}
static void spinbox_time_event_handler2(lv_obj_t *obj, lv_event_t event)
{
    switch (event)
    {
    case LV_EVENT_KEY:
    {
        const uint32_t *key = lv_event_get_data();
        if (*key == LV_KEY_ENTER)
        {
            rtc_set_time(bcd_decimal_code(lv_spinbox_get_value(spinbox_time2) / 10000), bcd_decimal_code((lv_spinbox_get_value(spinbox_time2) % 10000) / 100), bcd_decimal_code(lv_spinbox_get_value(spinbox_time2) % 100), bcd_decimal_code(GetTime.Hours), bcd_decimal_code(GetTime.Minutes), bcd_decimal_code(GetTime.Seconds));
            Mode = 0x07;
        }
    }
    break;
    default:
        break;
    }
}
void spinbox_time(void)
{
    static lv_style_t font_style1;
    lv_style_init(&font_style1);
    lv_style_set_text_font(&font_style1, LV_STATE_DEFAULT, &lv_font_montserrat_24);

    //创建标签对象
    spinbox_time1 = lv_spinbox_create(lv_scr_act(), NULL);
    lv_obj_add_style(spinbox_time1, LV_LABEL_PART_MAIN, &font_style1);
    lv_spinbox_set_range(spinbox_time1, 0, 240000);
    lv_spinbox_set_value(spinbox_time1, GetTime.Hours * 10000 + GetTime.Minutes * 100 + GetTime.Seconds);
    lv_spinbox_set_digit_format(spinbox_time1, 6, 0);
    lv_spinbox_step_prev(spinbox_time1);
    lv_obj_set_width(spinbox_time1, 120);
    lv_spinbox_set_rollover(spinbox_time1, true);

    lv_obj_align(spinbox_time1, NULL, LV_ALIGN_CENTER, 0, -50);
    lv_group_add_obj(group, spinbox_time1);
    lv_obj_set_event_cb(spinbox_time1, spinbox_time_event_handler);

    //创建标签对象
    spinbox_time2 = lv_spinbox_create(lv_scr_act(), NULL);
    lv_obj_add_style(spinbox_time2, LV_LABEL_PART_MAIN, &font_style1);
    lv_spinbox_set_range(spinbox_time2, 0, 991231);
    lv_spinbox_set_value(spinbox_time2, GetData.Year * 10000 + GetData.Month * 100 + GetData.Date);
    lv_spinbox_set_digit_format(spinbox_time2, 6, 0);
    lv_spinbox_step_prev(spinbox_time2);
    lv_obj_set_width(spinbox_time2, 120);
    lv_spinbox_set_rollover(spinbox_time2, true);

    lv_obj_align(spinbox_time2, NULL, LV_ALIGN_CENTER, 0, 50);
    lv_group_add_obj(group, spinbox_time2);
    lv_obj_set_event_cb(spinbox_time2, spinbox_time_event_handler2);
}
