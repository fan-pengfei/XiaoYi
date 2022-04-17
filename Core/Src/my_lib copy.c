#include "my_lib.h"
#include "my_lib2.h"
#include "tim.h"
#include "lcd_init.h"
#include "lcd.h"
#include "stdio.h"
#include "lvgl.h"
#include "lv_port_disp.h"
#include "lv_ex_conf.h"
#include "lv_examples.h"
#include "lv_demo_widgets.h"
#include "usbd_cdc_if.h"
#include "lv_port_indev.h"
extern Times time_tick;
extern lv_group_t *group;
int8_t my_day = 15, my_month = 10;
uint16_t my_year = 2021;
lv_obj_t *calendar;
uint8_t Mode = 0;
uint16_t menu_cnt = 0;
uint16_t menu2_cnt = 0;
uint8_t btnm_state[3] = {0, 0, 0};
uint8_t btnm2_state[3] = {0, 0, 0};
uint8_t test_data = 0;
uint32_t time_cnt = 0;
uint32_t num_cnt = 0;
uint32_t time_cnt_temp = 0;
uint32_t num_cnt_temp = 0;
uint32_t data[3] = {0, 0, 0};
char text_lcd[100];
//弹窗
static lv_obj_t *mbox1;
static lv_obj_t *mbox_mima;
static lv_obj_t *mbox_mima_enter;
static lv_obj_t *label1;
static lv_obj_t *label_menu;
static lv_obj_t *label_Mode1_head;
static lv_obj_t *label_Mode1_content;
static lv_obj_t *label_Mode2_head;
static lv_obj_t *label_Mode2_content;
static lv_obj_t *label_menu_condition;
static lv_obj_t *label_condition_head;
static lv_obj_t *label_condition_content;
static lv_obj_t *label_time_cnt;
static lv_obj_t *label_clock;

static lv_obj_t *ta1;
static lv_obj_t *btnm1;
static lv_obj_t *btnm_condition;
static lv_obj_t *keyboard1;
static lv_obj_t *spinbox_time1;
static lv_obj_t *spinbox_num1;
static lv_obj_t *spinbox_condition[3];
static lv_obj_t *ta2;
static lv_obj_t *keyboard2;
static lv_obj_t *btnm_int;
static lv_obj_t *lable_int;
static lv_obj_t *mbox_naozhong;
static lv_obj_t *mbox_int;
static lv_obj_t *mbox_fail;
static lv_obj_t *mbox_message;
static lv_obj_t *lable_yanzheng;
static void label_mode1(void);
static void label_mode2(void);
static void label_condition(void);
static void label_menu_condition_set(void);
static void mbox_set_mima(void);
static void mbox_set_mima_enter(void);
static void spinbox_time(void);
static void spinbox_num(void);
static void spinbox_condition_set(void);
static void btnm_condition_set(void);
static void label_time_cnt_set(void);
static void label_clock_show(void);
static lv_obj_t *btnm_condition;
static void btnm_int_condition_set(void);
static void mbox_int_test(void);
static void mbox_naozhong_test(void);
static void mbox_fail_test(void);
static void mbox_message_test(void);
static void label_yanzheng_test(void);
static void mbox_white_mima_enter(void);
void mbox_re_test(void);
uint8_t time_temp = 0;
uint8_t flag_wancheng[3];
uint8_t flag_wancheng_[3] = {0, 0, 0};
uint8_t mima_temp[6] = {0};
uint8_t wancheng_flag[3] = {0};
uint8_t flag_right = 0;
extern lv_obj_t *mode2_spinbox_condition[3];
extern lv_obj_t *mode2_btnm_condition;
extern lv_obj_t *mode2_label_menu_condition;
extern lv_obj_t *mode2_btnm_int;
extern lv_obj_t *mode2_lable_int;
extern Times times_temp[3];

void LOCK(void)
{
    __HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2, 50);
}
void UNLOCK(void)
{
    __HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2, 250);
}
static void task_cb(lv_task_t *task)
{
    uint8_t i, j;
    if (Mode == 0)
    {
        label_test();
        mbox_test();
        LOCK();
        Mode = 1;
    }
    else if (Mode == 1)
    {
        time_temp = time_tick.min;
    }
    else if (Mode == 2)
    {
        lv_obj_del(mbox1);
        lv_obj_del(label1);
        lv_obj_del(label_menu);
        label_mode1();
        btnm_test();
        Mode = 1;
    }
    else if (Mode == 3)
    {
        lv_obj_del(mbox1);
        lv_obj_del(label1);
        lv_obj_del(label_menu);
        label_mode2();
        mode2_btnm_condition_set();
        mode2_spinbox_condition_set();
        mode2_label_menu_condition_set();
        Mode = 1;
    }
    else if (Mode == 4)
    {
        lv_obj_del(mbox_mima);
        lv_group_add_obj(group, btnm1);
        lv_btnmatrix_set_focused_btn(btnm1, menu_cnt);
        Mode = 1;
    }
    else if (Mode == 5)
    {
        lv_obj_del(mbox_mima);
        lv_obj_del(btnm1);
        lvgl_keyboard_mode_test();
        Mode = 1;
    }
    else if (Mode == 6)
    {
        mbox_set_mima_enter();
        lv_group_remove_obj(keyboard1);
        Mode = 1;
    }
    else if (Mode == 7)
    {
        lv_obj_del(mbox_mima_enter);
        lv_obj_del(ta1);
        lv_obj_del(keyboard1);
        btnm_test();
        Mode = 1;
    }
    else if (Mode == 8)
    {
        lv_obj_del(mbox_mima_enter);
        lv_group_add_obj(group, keyboard1);
        lv_keyboard_set_textarea(keyboard1, ta1);
        Mode = 1;
    }
    else if (Mode == 9)
    {
        lv_obj_del(label_Mode1_head);
        lv_obj_del(label_Mode1_content);
        lv_obj_del(btnm1);
        Mode = 0;
    }
    else if (Mode == 10)
    {
        lv_obj_del(spinbox_time1);
        lv_group_add_obj(group, btnm1);
        lv_btnmatrix_set_focused_btn(btnm1, menu_cnt);
        Mode = 1;
    }
    else if (Mode == 11)
    {
        lv_obj_del(spinbox_num1);
        lv_group_add_obj(group, btnm1);
        lv_btnmatrix_set_focused_btn(btnm1, menu_cnt);
        Mode = 1;
    }
    else if (Mode == 12)
    {
        lv_obj_del(btnm1);
        lv_obj_del(label_Mode1_head);
        lv_obj_del(label_Mode1_content);
        label_condition();
        label_menu_condition_set();
        spinbox_condition_set();
        for (i = 0; i < 3; i++)
        {
            lv_group_remove_obj(spinbox_condition[i]);
        }
        btnm_condition_set();
        Mode = 1;
    }
    else if (Mode == 13)
    {
        for (i = 0; i < 3; i++)
        {
            lv_obj_del(spinbox_condition[i]);
        }
        lv_obj_del(label_condition_head);
        lv_obj_del(btnm_condition);
        lv_obj_del(label_menu_condition);
        label_mode1();
        btnm_test();
        Mode = 1;
    }
    else if (Mode == 13)
    {
        for (i = 0; i < 3; i++)
        {
            lv_obj_del(spinbox_condition[i]);
        }
        lv_obj_del(label_condition_head);
        lv_obj_del(btnm_condition);
        lv_obj_del(label_menu_condition);
        label_mode1();
        btnm_test();
        Mode = 1;
    }
    else if (Mode == 14)
    {
        for (i = 0; i < 3; i++)
        {
            lv_obj_del(spinbox_condition[i]);
        }
        lv_obj_del(label_condition_head);
        lv_obj_del(btnm_condition);
        lv_obj_del(label_menu_condition);
        // label_time_cnt_set();
        // label_clock_show();
        time_tick.hour = 0;
        time_tick.min = 0;
        time_tick.sec = 0;
        btnm_int_condition_set();
        Mode = 23;
    }
    else if (Mode == 15)
    {
        if (time_tick.min - time_temp == time_cnt)
        {
            time_temp = time_tick.min;
            mbox_naozhong_test();
            lv_obj_del(mbox_int);
            HAL_GPIO_WritePin(BEEP_GPIO_Port, BEEP_Pin, GPIO_PIN_SET);
            Mode = 16;
        }
    }
    else if (Mode == 16)
    {
        Mode = 23;
        time_temp = time_tick.min;
    }
    else if (Mode == 17)
    {
        lv_obj_del(btnm_int);
        lv_obj_del(lable_int);
        label_condition();
        label_menu_condition_set();
        spinbox_condition_set();
        for (i = 0; i < 3; i++)
        {
            lv_group_remove_obj(spinbox_condition[i]);
        }
        btnm_condition_set();
        Mode = 23;
    }
    else if (Mode == 18)
    {
        lv_obj_del(mbox_naozhong);
        lv_group_add_obj(group, btnm_int);
        HAL_GPIO_WritePin(BEEP_GPIO_Port, BEEP_Pin, GPIO_PIN_RESET);
        Mode = 23;
    }
    else if (Mode == 19)
    {
        lv_group_remove_obj(btnm_int);
        mbox_fail_test();
        Mode = 23;
    }
    else if (Mode == 20)
    {
        lv_obj_del(mbox_fail);
        lv_group_add_obj(group, btnm_int);
        Mode = 23;
    }
    else if (Mode == 21)
    {
        lv_obj_del(mbox_message);
        lv_group_add_obj(group, btnm_int);
        Mode = 23;
    }
    else if (Mode == 22)
    {
        lv_obj_del(btnm_int);
        lv_obj_del(lable_int);
        label_yanzheng_test();
        lv_ex_textarea_2();
        lvgl_keyboard_mode_test2();
        lv_keyboard_set_textarea(keyboard2, ta2);
        Mode = 23;
    }
    else if (Mode == 23)
    {
        time_temp = time_tick.min;
        if (flag_wancheng_[0] == 0)
        {
            if (HAL_GPIO_ReadPin(BM1_GPIO_Port, BM1_Pin))
            {
                flag_wancheng[0] = 1;
                flag_wancheng_[0] = 1;
                Mode = 22;
            }
        }
        if (flag_wancheng_[1] == 0)
        {
            if (HAL_GPIO_ReadPin(BM2_GPIO_Port, BM2_Pin))
            {
                flag_wancheng[1] = 1;
                flag_wancheng_[1] = 1;
                Mode = 22;
            }
        }
        if (flag_wancheng_[2] == 0)
        {
            if (HAL_GPIO_ReadPin(BM3_GPIO_Port, BM3_Pin))
            {
                flag_wancheng[2] = 1;
                flag_wancheng_[2] = 1;
                Mode = 22;
            }
        }
    }
    else if (Mode == 24)
    {
        mbox_white_mima_enter();
        lv_group_remove_obj(keyboard2);
        Mode = 23;
    }

    else if (Mode == 25)
    {
        lv_obj_del(mbox1);
        lv_group_add_obj(group, keyboard2);
        lv_keyboard_set_textarea(keyboard2, ta2);
        Mode = 23;
    }
    else if (Mode == 26)
    {
        lv_obj_del(mbox1);

        lv_obj_del(keyboard2);
        lv_obj_del(ta2);
        lv_obj_del(lable_yanzheng);
        btnm_int_condition_set();
        Mode = 23;
    }
    else if (Mode == 27)
    {
        mbox_re_test();
        lv_obj_del(mbox_mima_enter);
        Mode = 23;
    }
    else if (Mode == 28)
    {
        mbox_re_test();
        lv_obj_del(mbox_mima_enter);
        Mode = 23;
    }
    else if (Mode == 29)
    {
        lv_obj_del(mbox_mima_enter);
        lv_group_add_obj(group, keyboard2);
        lv_keyboard_set_textarea(keyboard2, ta2);
        Mode = 23;
    }
    else if (Mode == 30)
    {
        lv_obj_del(mode2_label_menu_condition);
        lv_obj_del(mode2_btnm_condition);
        lv_obj_del(label_Mode2_head);
        for (i = 0; i < 3; i++)
        {
            lv_obj_del(mode2_spinbox_condition[i]);
        }
        label_test();
        mbox_test();

        Mode = 1;
    }
    else if (Mode == 31)
    {
        lv_obj_del(mode2_label_menu_condition);
        lv_obj_del(mode2_btnm_condition);
        lv_obj_del(label_Mode2_head);
        mode2_btnm_int_condition_set();
        for (i = 0; i < 3; i++)
        {
            lv_obj_del(mode2_spinbox_condition[i]);
        }
        Mode = 35;
    }
    else if (Mode == 32)
    {
        // lv_obj_del(mode2_btnm_int);
        // lv_obj_del(mode2_lable_int);
        mode2_mbox_test();
        lv_group_remove_obj(mode2_btnm_int);
        Mode = 35;
    }
    else if (Mode == 33)
    {
        lv_obj_del(mode2_btnm_int);
        lv_obj_del(mode2_lable_int);
        label_mode2();
        mode2_btnm_condition_set();
        mode2_spinbox_condition_set();
        mode2_label_menu_condition_set();
        Mode = 35;
    }
    else if (Mode == 34)
    {
        // lv_obj_del(mode2_btnm_int);
        // lv_obj_del(mode2_lable_int);
        lv_obj_del(mode2_mbox);

        lv_group_add_obj(group, mode2_btnm_int);
        Mode = 35;
    }
    else if (Mode == 35)
    {
        if ((time_tick.hour * 60 + time_tick.min) - (times_temp[0].hour * 60 + times_temp[0].min) == mode2_data[0])
        {
            HAL_GPIO_WritePin(BEEP_GPIO_Port, BEEP_Pin, GPIO_PIN_SET);
            flag_ok[0] = 1;
            lv_group_remove_obj(mode2_btnm_int);
            mode2_mbox_test_ok();
            UNLOCK();
            Mode = 1;
        }
        else if ((time_tick.hour * 60 + time_tick.min) - (times_temp[1].hour * 60 + times_temp[0].min) == mode2_data[1])
        {
            HAL_GPIO_WritePin(BEEP_GPIO_Port, BEEP_Pin, GPIO_PIN_SET);
            flag_ok[1] = 1;
            lv_group_remove_obj(mode2_btnm_int);
            mode2_mbox_test_ok();
            UNLOCK();
            Mode = 1;
        }
        else if ((time_tick.hour * 60 + time_tick.min) - (times_temp[2].hour * 60 + times_temp[2].min) == mode2_data[2])
        {
            HAL_GPIO_WritePin(BEEP_GPIO_Port, BEEP_Pin, GPIO_PIN_SET);
            flag_ok[2] = 1;
            lv_group_remove_obj(mode2_btnm_int);
            mode2_mbox_test_ok();
            UNLOCK();
            Mode = 1;
        }
    }
    else if (Mode == 36)
    {
        Mode = 38;
        lv_group_remove_obj(mode2_btnm_int);
        lv_obj_del(mode2_mbox_ok);
        task1();
    }
    else if (Mode == 37)
    {
        Mode = 35;
    }
    else if (Mode == 38)
    {
    }
    else if (Mode == 39)
    {
        lv_group_remove_obj(mode2_btnm_int);
        lv_obj_del(mode2_mbox_ok);
        task2();
        Mode = 38;
    }
    else if (Mode == 40)
    {
        lv_obj_del(mode2_mbox);
        lv_group_add_obj(group, mode2_btnm_int);
        if (flag_ok[0] == 1)
        {
            times_temp[0].hour = 200;
        }
        if (flag_ok[1] == 1)
        {
            times_temp[1].hour = 200;
        }
        if (flag_ok[2] == 1)
        {
            times_temp[2].hour = 200;
        }
        Mode = 35;
    }
    else if (Mode == 41)
    {
        lv_obj_del(spinbox_C);
        task3();
        Mode = 35;
    }
    else if (Mode == 42)
    {
        lv_obj_del(mode2_mbox);
        lv_group_add_obj(group, mode2_btnm_int);
        Mode = 35;
    }
}
void User_task(void)
{
    lv_task_t *task = lv_task_create(task_cb, 10, LV_TASK_PRIO_MID, &test_data);
}
//消息弹窗
const char *str_mima, *str_mima2;
static void mbox_event_handler(lv_obj_t *obj, lv_event_t event)
{
    switch (event)
    {
    case LV_EVENT_KEY:
    {
        const uint32_t *key = lv_event_get_data();
        if (*key == LV_KEY_ENTER)
        {
            lv_msgbox_start_auto_close(mbox1, 0);
            // usb_printf("%d\r\n", lv_msgbox_get_active_btn(mbox1));
            if (lv_msgbox_get_active_btn(mbox1) == 0)
            {
                Mode = 2;
            }
            else
            {
                Mode = 3;
            }
        }
    }
    break;
    default:
        break;
    }
}
void mbox_test(void)
{
    static const char *btn_str[] = {"Mode 1", "Mode 2", ""};
    mbox1 = lv_msgbox_create(lv_scr_act(), NULL);
    lv_obj_set_size(mbox1, 170, 80);
    lv_obj_align(mbox1, NULL, LV_ALIGN_CENTER, 0, 15);
    lv_msgbox_set_text(mbox1, "Select Box");
    lv_msgbox_add_btns(mbox1, btn_str);
    lv_msgbox_set_recolor(mbox1, true);
    // lv_msgbox_set_anim_time(mbox1, 1000);
    lv_group_add_obj(group, mbox1);
    lv_obj_set_event_cb(mbox1, mbox_event_handler);
}

static void mbox_re_event_handler(lv_obj_t *obj, lv_event_t event)
{
    switch (event)
    {
    case LV_EVENT_KEY:
    {
        const uint32_t *key = lv_event_get_data();
        if (*key == LV_KEY_ENTER)
        {
            lv_msgbox_start_auto_close(mbox1, 0);
            // usb_printf("%d\r\n", lv_msgbox_get_active_btn(mbox1));
            // if (lv_msgbox_get_active_btn(mbox1) == 0)
            // {
            //     Mode = 2;
            // }
            // else
            // {
            //     Mode = 3;
            // }
            if (flag_right == 1)
            {
                Mode = 25;
                flag_right = 0;
            }
            else
            {
                Mode = 26;
            }
        }
    }
    break;
    default:
        break;
    }
}

void mbox_re_test(void)
{
    static const char *btn_str[] = {"OK", "", ""};
    mbox1 = lv_msgbox_create(lv_scr_act(), NULL);
    lv_obj_set_size(mbox1, 170, 80);
    lv_obj_align(mbox1, NULL, LV_ALIGN_CENTER, 0, 15);
    if (flag_right == 1)
    {
        lv_msgbox_set_text(mbox1, "Wrong");
    }
    else
    {
        lv_msgbox_set_text(mbox1, "Right");
    }
    lv_msgbox_add_btns(mbox1, btn_str);
    lv_msgbox_set_recolor(mbox1, true);
    // lv_msgbox_set_anim_time(mbox1, 1000);
    lv_group_add_obj(group, mbox1);
    lv_obj_set_event_cb(mbox1, mbox_re_event_handler);
}
static void mbox_mima_event_handler(lv_obj_t *obj, lv_event_t event)
{
    switch (event)
    {
    case LV_EVENT_KEY:
    {
        const uint32_t *key = lv_event_get_data();
        if (*key == LV_KEY_ENTER)
        {
            lv_msgbox_start_auto_close(mbox_mima, 0);
            // usb_printf("%d\r\n", lv_msgbox_get_active_btn(mbox_mima));
            if (lv_msgbox_get_active_btn(mbox_mima) == 0)
            {
                Mode = 5;
            }
            else
            {
                Mode = 4;
            }
        }
    }
    break;
    default:
        break;
    }
}
//消息弹窗
static void mbox_set_mima(void)
{
    static const char *btn_str1[] = {"Yes", "Cancle", ""};
    mbox_mima = lv_msgbox_create(lv_scr_act(), NULL);
    lv_obj_set_size(mbox_mima, 170, 80);
    lv_obj_align(mbox_mima, NULL, LV_ALIGN_CENTER, 0, 15);
    lv_msgbox_set_text(mbox_mima, "Set Password");
    lv_msgbox_add_btns(mbox_mima, btn_str1);
    lv_msgbox_set_recolor(mbox_mima, true);
    // lv_msgbox_set_anim_time(mbox1, 1000);
    lv_group_add_obj(group, mbox_mima);
    lv_obj_set_event_cb(mbox_mima, mbox_mima_event_handler);
}
static void mbox_mima_enter_event_handler(lv_obj_t *obj, lv_event_t event)
{
    uint8_t i = 0, flag = 0;
    switch (event)
    {
    case LV_EVENT_KEY:
    {
        const uint32_t *key = lv_event_get_data();
        if (*key == LV_KEY_ENTER)
        {
            lv_msgbox_start_auto_close(mbox_mima_enter, 0);
            if (lv_msgbox_get_active_btn(mbox_mima_enter) == 0)
            {
                str_mima = lv_textarea_get_text(ta1);
                for (i = 0; i < 6; i++)
                {
                    mima_temp[i] = str_mima[i];
                }
                usb_printf("1:%s\r\n", str_mima);
                Mode = 7;
            }
            else
            {
                Mode = 8;
            }
        }
    }
    break;
    default:
        break;
    }
}

static void mbox_mima_white_event_handler(lv_obj_t *obj, lv_event_t event)
{
    uint8_t i = 0;
    switch (event)
    {
    case LV_EVENT_KEY:
    {
        const uint32_t *key = lv_event_get_data();
        if (*key == LV_KEY_ENTER)
        {
            lv_msgbox_start_auto_close(mbox_mima_enter, 0);
            if (lv_msgbox_get_active_btn(mbox_mima_enter) == 0)
            {
                str_mima2 = lv_textarea_get_text(ta2);

                // usb_printf("2:%s,%d\r\n", str_mima2, flag);
                for (i = 0; i < 6; i++)
                {
                    if (mima_temp[i] != str_mima2[i])
                    {
                        flag_right = 1;
                    }
                }
                usb_printf("2:%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,flag:%d\r\n", mima_temp[0], mima_temp[1], mima_temp[2], mima_temp[3], mima_temp[4], mima_temp[5], str_mima2[0], str_mima2[1], str_mima2[2], str_mima2[3], str_mima2[4], str_mima2[5], flag_right);
                if (flag_right == 1)
                {
                    Mode = 27;
                    for (i = 0; i < 3; i++)
                    {
                        wancheng_flag[i] = flag_wancheng[i];
                    }
                }
                else
                {
                    Mode = 28;
                }
            }
            else
            {
                Mode = 29;
            }
        }
    }
    break;
    default:
        break;
    }
}
//消息弹窗
static void mbox_set_mima_enter(void)
{
    static const char *btn_str1[] = {"Enter", "Retype", ""};
    mbox_mima_enter = lv_msgbox_create(lv_scr_act(), NULL);
    lv_obj_set_size(mbox_mima_enter, 170, 80);
    lv_obj_align(mbox_mima_enter, NULL, LV_ALIGN_CENTER, 0, 15);
    lv_msgbox_set_text(mbox_mima_enter, "Sure To Save");
    lv_msgbox_add_btns(mbox_mima_enter, btn_str1);
    lv_msgbox_set_recolor(mbox_mima_enter, true);
    // lv_msgbox_set_anim_time(mbox1, 1000);
    lv_group_add_obj(group, mbox_mima_enter);
    lv_obj_set_event_cb(mbox_mima_enter, mbox_mima_enter_event_handler);
}

static void mbox_white_mima_enter(void)
{
    static const char *btn_str1[] = {"Enter", "Retype", ""};
    mbox_mima_enter = lv_msgbox_create(lv_scr_act(), NULL);
    lv_obj_set_size(mbox_mima_enter, 170, 80);
    lv_obj_align(mbox_mima_enter, NULL, LV_ALIGN_CENTER, 0, 15);
    lv_msgbox_set_text(mbox_mima_enter, "Sure To Save");
    lv_msgbox_add_btns(mbox_mima_enter, btn_str1);
    lv_msgbox_set_recolor(mbox_mima_enter, true);
    // lv_msgbox_set_anim_time(mbox1, 1000);
    lv_group_add_obj(group, mbox_mima_enter);
    lv_obj_set_event_cb(mbox_mima_enter, mbox_mima_white_event_handler);
}
void label_test(void)
{
    static lv_style_t font_style1;
    lv_style_init(&font_style1);
    lv_style_set_text_font(&font_style1, LV_STATE_DEFAULT, &lv_font_montserrat_24);

    //创建标签对象
    label_menu = lv_label_create(lv_scr_act(), NULL);
    lv_obj_add_style(label_menu, LV_LABEL_PART_MAIN, &font_style1);

    //设置长文本模式
    lv_label_set_long_mode(label_menu, LV_LABEL_LONG_BREAK); /*Break the long lines*/
                                                             //使能文本重绘色功能
    lv_label_set_recolor(label_menu, true);                  /*Enable re-coloring by commands in the text*/
                                                             //设置文本对齐模式
    lv_label_set_align(label_menu, LV_LABEL_ALIGN_CENTER);   /*Center aligned lines*/
                                                             //设置文本内容
    lv_label_set_text(label_menu, "MENU");
    //设置宽度
    lv_obj_set_width(label_menu, 220);
    //设置对齐模式
    lv_obj_align(label_menu, NULL, LV_ALIGN_CENTER, 0, -100);

    //创建标签对象
    label1 = lv_label_create(lv_scr_act(), NULL);

    //设置长文本模式
    lv_label_set_long_mode(label1, LV_LABEL_LONG_BREAK); /*Break the long lines*/
                                                         //使能文本重绘色功能
    lv_label_set_recolor(label1, true);                  /*Enable re-coloring by commands in the text*/
                                                         //设置文本对齐模式
    lv_label_set_align(label1, LV_LABEL_ALIGN_LEFT);     /*Center aligned lines*/
                                                         //设置文本内容
    lv_label_set_text(label1, "Please select the following modes: \n1. Reward and punishment mode. \n2. Timing mode.");
    //设置宽度
    lv_obj_set_width(label1, 220);
    //设置对齐模式
    lv_obj_align(label1, NULL, LV_ALIGN_CENTER, 0, -50);
}
static void label_mode1(void)
{
    static lv_style_t font_style1;
    lv_style_init(&font_style1);
    lv_style_set_text_font(&font_style1, LV_STATE_DEFAULT, &lv_font_montserrat_24);

    //创建标签对象
    label_Mode1_head = lv_label_create(lv_scr_act(), NULL);
    lv_obj_add_style(label_Mode1_head, LV_LABEL_PART_MAIN, &font_style1);

    //设置长文本模式
    lv_label_set_long_mode(label_Mode1_head, LV_LABEL_LONG_BREAK); /*Break the long lines*/
                                                                   //使能文本重绘色功能
    lv_label_set_recolor(label_Mode1_head, true);                  /*Enable re-coloring by commands in the text*/
                                                                   //设置文本对齐模式
    lv_label_set_align(label_Mode1_head, LV_LABEL_ALIGN_CENTER);   /*Center aligned lines*/
                                                                   //设置文本内容
    lv_label_set_text(label_Mode1_head, "Reward Mode");
    //设置宽度
    lv_obj_set_width(label_Mode1_head, 220);
    //设置对齐模式
    lv_obj_align(label_Mode1_head, NULL, LV_ALIGN_CENTER, 0, -110);

    label_Mode1_content = lv_label_create(lv_scr_act(), NULL);
    //设置长文本模式
    lv_label_set_long_mode(label_Mode1_content, LV_LABEL_LONG_BREAK); /*Break the long lines*/
                                                                      //使能文本重绘色功能
    lv_label_set_recolor(label_Mode1_content, true);                  /*Enable re-coloring by commands in the text*/
                                                                      //设置文本对齐模式
    lv_label_set_align(label_Mode1_content, LV_LABEL_ALIGN_CENTER);   /*Center aligned lines*/
                                                                      //设置文本内容
    lv_label_set_text(label_Mode1_content, "Please set the time and interval if you support short access halfway.");
    //设置宽度
    lv_obj_set_width(label_Mode1_content, 220);
    //设置对齐模式
    lv_obj_align(label_Mode1_content, NULL, LV_ALIGN_CENTER, 0, -70);
}
static void label_mode2(void)
{
    static lv_style_t font_style1;
    lv_style_init(&font_style1);
    lv_style_set_text_font(&font_style1, LV_STATE_DEFAULT, &lv_font_montserrat_24);

    //创建标签对象
    label_Mode2_head = lv_label_create(lv_scr_act(), NULL);
    lv_obj_add_style(label_Mode2_head, LV_LABEL_PART_MAIN, &font_style1);
    //设置长文本模式
    lv_label_set_long_mode(label_Mode2_head, LV_LABEL_LONG_BREAK); /*Break the long lines*/
                                                                   //使能文本重绘色功能
    lv_label_set_recolor(label_Mode2_head, true);                  /*Enable re-coloring by commands in the text*/
                                                                   //设置文本对齐模式
    lv_label_set_align(label_Mode2_head, LV_LABEL_ALIGN_CENTER);   /*Center aligned lines*/
                                                                   //设置文本内容

    lv_label_set_text(label_Mode2_head, "Timing Mode");
    //设置宽度
    lv_obj_set_width(label_Mode2_head, 220);
    //设置对齐模式
    lv_obj_align(label_Mode2_head, NULL, LV_ALIGN_CENTER, 0, -100);
}
static void label_menu_condition_set(void)
{
    //创建标签对象
    label_menu_condition = lv_label_create(lv_scr_act(), NULL);
    //设置长文本模式
    lv_label_set_long_mode(label_menu_condition, LV_LABEL_LONG_BREAK); /*Break the long lines*/
                                                                       //使能文本重绘色功能
    lv_label_set_recolor(label_menu_condition, true);                  /*Enable re-coloring by commands in the text*/
                                                                       //设置文本对齐模式
    lv_label_set_align(label_menu_condition, LV_LABEL_ALIGN_CENTER);   /*Center aligned lines*/
                                                                       //设置文本内容

    lv_label_set_text(label_menu_condition, "  Menu              Time        ");
    //设置宽度
    lv_obj_set_width(label_menu_condition, 240);
    //设置对齐模式
    lv_obj_align(label_menu_condition, NULL, LV_ALIGN_CENTER, 0, -65);
}
static void label_condition(void)
{
    static lv_style_t font_style1;
    lv_style_init(&font_style1);
    lv_style_set_text_font(&font_style1, LV_STATE_DEFAULT, &lv_font_montserrat_24);

    //创建标签对象
    label_condition_head = lv_label_create(lv_scr_act(), NULL);
    lv_obj_add_style(label_condition_head, LV_LABEL_PART_MAIN, &font_style1);
    //设置长文本模式
    lv_label_set_long_mode(label_condition_head, LV_LABEL_LONG_BREAK); /*Break the long lines*/
                                                                       //使能文本重绘色功能
    lv_label_set_recolor(label_condition_head, true);                  /*Enable re-coloring by commands in the text*/
                                                                       //设置文本对齐模式
    lv_label_set_align(label_condition_head, LV_LABEL_ALIGN_CENTER);   /*Center aligned lines*/
                                                                       //设置文本内容

    lv_label_set_text(label_condition_head, "Condition Set");
    //设置宽度
    lv_obj_set_width(label_condition_head, 220);
    //设置对齐模式
    lv_obj_align(label_condition_head, NULL, LV_ALIGN_CENTER, 0, -100);

    // label_condition_content = lv_label_create(lv_scr_act(), NULL);
    // //设置长文本模式
    // lv_label_set_long_mode(label_condition_content, LV_LABEL_LONG_BREAK); /*Break the long lines*/
    //                                                                   //使能文本重绘色功能
    // lv_label_set_recolor(label_condition_content, true);                  /*Enable re-coloring by commands in the text*/
    //                                                                   //设置文本对齐模式
    // lv_label_set_align(label_condition_content, LV_LABEL_ALIGN_CENTER);   /*Center aligned lines*/
    //                                                                   //设置文本内容
    // lv_label_set_text(label_condition_content, "");
    // //设置宽度
    // lv_obj_set_width(label_condition_content, 220);
    // //设置对齐模式
    // lv_obj_align(label_condition_content, NULL, LV_ALIGN_CENTER, 0, -45);
}
static void label_time_cnt_set(void)
{
    static lv_style_t font_style1;
    lv_style_init(&font_style1);
    lv_style_set_text_font(&font_style1, LV_STATE_DEFAULT, &lv_font_montserrat_24);

    //创建标签对象
    label_time_cnt = lv_label_create(lv_scr_act(), NULL);
    lv_obj_add_style(label_time_cnt, LV_LABEL_PART_MAIN, &font_style1);
    //设置长文本模式
    lv_label_set_long_mode(label_time_cnt, LV_LABEL_LONG_BREAK); /*Break the long lines*/
                                                                 //使能文本重绘色功能
    lv_label_set_recolor(label_time_cnt, true);                  /*Enable re-coloring by commands in the text*/
                                                                 //设置文本对齐模式
    lv_label_set_align(label_time_cnt, LV_LABEL_ALIGN_CENTER);   /*Center aligned lines*/
                                                                 //设置文本内容

    lv_label_set_text(label_time_cnt, "On The Clock");
    //设置宽度
    lv_obj_set_width(label_time_cnt, 220);
    //设置对齐模式
    lv_obj_align(label_time_cnt, NULL, LV_ALIGN_CENTER, 0, -100);
}
static void label_clock_show(void)
{
    //创建标签对象
    label_time_cnt = lv_label_create(lv_scr_act(), NULL);
    //设置长文本模式
    lv_label_set_long_mode(label_time_cnt, LV_LABEL_LONG_BREAK); /*Break the long lines*/
                                                                 //使能文本重绘色功能
    lv_label_set_recolor(label_time_cnt, true);                  /*Enable re-coloring by commands in the text*/
                                                                 //设置文本对齐模式
    lv_label_set_align(label_time_cnt, LV_LABEL_ALIGN_CENTER);   /*Center aligned lines*/
                                                                 //设置文本内容

    //设置宽度
    lv_obj_set_width(label_time_cnt, 220);
    //设置对齐模式
    lv_obj_align(label_time_cnt, NULL, LV_ALIGN_CENTER, 0, 0);
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
            menu_cnt = lv_btnmatrix_get_active_btn(btnm1);
            if (menu_cnt == 4)
            {
                Mode = 9;
            }
            else if (menu_cnt == 0)
            {
                mbox_set_mima();
                lv_group_remove_obj(btnm1); //没办法，只能放这里了
            }
            else if (menu_cnt == 1)
            {
                spinbox_time();
                lv_group_remove_obj(btnm1); //没办法，只能放这里了
            }
            else if (menu_cnt == 2)
            {
                spinbox_num();
                lv_group_remove_obj(btnm1); //没办法，只能放这里了
            }
            else if (menu_cnt == 3)
            {
                Mode = 12;
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
    static const char *btnm_text[] = {
        "Set Password", "\n",
        "Maximum Time", "\n",
        "Maximum Number", "\n",
        "Condition Set", "\n",
        "Cancle", ""};
    btnm1 = lv_btnmatrix_create(lv_scr_act(), NULL);
    // lv_obj_invalidate_area(btnm1,test);
    lv_btnmatrix_set_map(btnm1, btnm_text);
    lv_obj_set_size(btnm1, 200, 160); //可以设置窗口大小
    lv_obj_align(btnm1, NULL, LV_ALIGN_CENTER, 0, 35);
    lv_group_add_obj(group, btnm1);
    lv_obj_set_event_cb(btnm1, btm_event_handler);
}
static void btm_condition_event_handler(lv_obj_t *obj, lv_event_t event)
{
    switch (event)
    {
    case LV_EVENT_KEY:
    {
        const uint32_t *key = lv_event_get_data();
        if (*key == LV_KEY_ENTER)
        {
            menu2_cnt = lv_btnmatrix_get_active_btn(btnm_condition);
            if (menu2_cnt == 0)
            {
                btnm2_state[0] = !btnm2_state[0];
                if (btnm2_state[0] == 0)
                {
                    lv_btnmatrix_clear_btn_ctrl(btnm_condition, 0, LV_BTNMATRIX_CTRL_CHECK_STATE);
                }
                else
                {
                    lv_btnmatrix_set_btn_ctrl(btnm_condition, 0, LV_BTNMATRIX_CTRL_CHECK_STATE);
                    lv_group_add_obj(group, spinbox_condition[0]);
                    lv_group_remove_obj(btnm_condition);
                }
            }
            else if (menu2_cnt == 1)
            {
                btnm2_state[1] = !btnm2_state[1];
                if (btnm2_state[1] == 0)
                {
                    lv_btnmatrix_clear_btn_ctrl(btnm_condition, 1, LV_BTNMATRIX_CTRL_CHECK_STATE);
                }
                else
                {
                    lv_btnmatrix_set_btn_ctrl(btnm_condition, 1, LV_BTNMATRIX_CTRL_CHECK_STATE);
                    lv_group_add_obj(group, spinbox_condition[1]);
                    lv_group_remove_obj(btnm_condition);
                }
            }
            else if (menu2_cnt == 2)
            {
                btnm2_state[2] = !btnm2_state[2];
                if (btnm2_state[2] == 0)
                {
                    lv_btnmatrix_clear_btn_ctrl(btnm_condition, 2, LV_BTNMATRIX_CTRL_CHECK_STATE);
                }
                else
                {
                    lv_btnmatrix_set_btn_ctrl(btnm_condition, 2, LV_BTNMATRIX_CTRL_CHECK_STATE);
                    lv_group_add_obj(group, spinbox_condition[2]);
                    lv_group_remove_obj(btnm_condition);
                }
            }
            else if (menu2_cnt == 3)
            {
                Mode = 14;
            }
            else if (menu2_cnt == 4)
            {
                Mode = 13;
            }
        }
    }
    break;
    default:
        break;
    }
}
void btnm_condition_set(void)
{
    static const char *btnm_text[] = {
        "Condition1", "\n",
        "Condition2", "\n",
        "Condition3", "\n",
        "Enter", "\n",
        "Cancle", ""};
    btnm_condition = lv_btnmatrix_create(lv_scr_act(), NULL);
    // lv_obj_invalidate_area(btnm1,test);
    lv_btnmatrix_set_map(btnm_condition, btnm_text);
    lv_obj_set_size(btnm_condition, 100, 170); //可以设置窗口大小
    if (btnm2_state[0] == 0)
    {
        lv_btnmatrix_clear_btn_ctrl(btnm_condition, 0, LV_BTNMATRIX_CTRL_CHECK_STATE);
    }
    else
    {
        lv_btnmatrix_set_btn_ctrl(btnm_condition, 0, LV_BTNMATRIX_CTRL_CHECK_STATE);
    }
    if (btnm2_state[1] == 0)
    {
        lv_btnmatrix_clear_btn_ctrl(btnm_condition, 1, LV_BTNMATRIX_CTRL_CHECK_STATE);
    }
    else
    {
        lv_btnmatrix_set_btn_ctrl(btnm_condition, 1, LV_BTNMATRIX_CTRL_CHECK_STATE);
    }
    if (btnm2_state[2] == 0)
    {
        lv_btnmatrix_clear_btn_ctrl(btnm_condition, 2, LV_BTNMATRIX_CTRL_CHECK_STATE);
    }
    else
    {
        lv_btnmatrix_set_btn_ctrl(btnm_condition, 2, LV_BTNMATRIX_CTRL_CHECK_STATE);
    }
    lv_obj_align(btnm_condition, NULL, LV_ALIGN_CENTER, -70, 30);
    lv_group_add_obj(group, btnm_condition);
    lv_obj_set_event_cb(btnm_condition, btm_condition_event_handler);
}
static void spinbox_condition_event_handler(lv_obj_t *obj, lv_event_t event)
{
    switch (event)
    {
    case LV_EVENT_KEY:
    {
        const uint32_t *key = lv_event_get_data();
        if (*key == LV_KEY_ENTER)
        {
            if (obj == spinbox_condition[0])
            {
                lv_group_add_obj(group, btnm_condition);
                lv_group_remove_obj(spinbox_condition[0]);
                lv_btnmatrix_set_focused_btn(btnm_condition, menu2_cnt);
                data[0] = lv_spinbox_get_value(spinbox_condition[0]);
            }
            else if (obj == spinbox_condition[1])
            {
                lv_group_add_obj(group, btnm_condition);
                lv_group_remove_obj(spinbox_condition[1]);
                lv_btnmatrix_set_focused_btn(btnm_condition, menu2_cnt);
                data[1] = lv_spinbox_get_value(spinbox_condition[1]);
            }
            else if (obj == spinbox_condition[2])
            {
                lv_group_add_obj(group, btnm_condition);
                lv_group_remove_obj(spinbox_condition[2]);
                lv_btnmatrix_set_focused_btn(btnm_condition, menu2_cnt);
                data[2] = lv_spinbox_get_value(spinbox_condition[2]);
            }
        }
    }
    break;
    default:
        break;
    }
}
void spinbox_condition_set(void)
{
    int i, j;
    static lv_style_t font_style1;
    lv_style_init(&font_style1);
    lv_style_set_text_font(&font_style1, LV_STATE_DEFAULT, &lv_font_montserrat_14);

    //创建标签对象
    spinbox_condition[0] = lv_spinbox_create(lv_scr_act(), NULL);
    lv_obj_add_style(spinbox_condition[0], LV_LABEL_PART_MAIN, &font_style1);
    lv_spinbox_set_range(spinbox_condition[0], 0, 99999);
    lv_spinbox_set_value(spinbox_condition[0], time_cnt);
    lv_spinbox_set_digit_format(spinbox_condition[0], 5, 0);
    lv_spinbox_step_prev(spinbox_condition[0]);
    lv_obj_set_width(spinbox_condition[0], 60);
    lv_obj_align(spinbox_condition[0], NULL, LV_ALIGN_CENTER, 40, -35);
    lv_group_add_obj(group, spinbox_condition[0]);
    lv_obj_set_event_cb(spinbox_condition[0], spinbox_condition_event_handler);

    //创建标签对象
    spinbox_condition[1] = lv_spinbox_create(lv_scr_act(), NULL);
    lv_obj_add_style(spinbox_condition[1], LV_LABEL_PART_MAIN, &font_style1);
    lv_spinbox_set_range(spinbox_condition[1], 0, 99999);
    lv_spinbox_set_value(spinbox_condition[1], time_cnt);
    lv_spinbox_set_digit_format(spinbox_condition[1], 5, 0);
    lv_spinbox_step_prev(spinbox_condition[1]);
    lv_obj_set_width(spinbox_condition[1], 60);
    lv_obj_align(spinbox_condition[1], NULL, LV_ALIGN_CENTER, 40, -1);
    lv_group_add_obj(group, spinbox_condition[1]);
    lv_obj_set_event_cb(spinbox_condition[1], spinbox_condition_event_handler);
    //创建标签对象
    spinbox_condition[2] = lv_spinbox_create(lv_scr_act(), NULL);
    lv_obj_add_style(spinbox_condition[2], LV_LABEL_PART_MAIN, &font_style1);
    lv_spinbox_set_range(spinbox_condition[2], 0, 99999);
    lv_spinbox_set_value(spinbox_condition[2], time_cnt);
    lv_spinbox_set_digit_format(spinbox_condition[0], 5, 0);
    lv_spinbox_step_prev(spinbox_condition[2]);
    lv_obj_set_width(spinbox_condition[2], 60);
    lv_obj_align(spinbox_condition[2], NULL, LV_ALIGN_CENTER, 40, 29);
    lv_group_add_obj(group, spinbox_condition[2]);
    lv_obj_set_event_cb(spinbox_condition[2], spinbox_condition_event_handler);
    for (i = 0; i < 3; i++)
    {
        lv_spinbox_set_value(spinbox_condition[i], data[i]);
    }
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
            time_cnt = lv_spinbox_get_value(spinbox_time1);
            time_cnt_temp = time_cnt;
            Mode = 10;
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
    lv_spinbox_set_range(spinbox_time1, 0, 99999);
    lv_spinbox_set_value(spinbox_time1, time_cnt);
    lv_spinbox_set_digit_format(spinbox_time1, 5, 0);
    lv_spinbox_step_prev(spinbox_time1);
    lv_obj_set_width(spinbox_time1, 100);
    lv_obj_align(spinbox_time1, NULL, LV_ALIGN_CENTER, 0, 0);
    lv_group_add_obj(group, spinbox_time1);
    lv_obj_set_event_cb(spinbox_time1, spinbox_time_event_handler);
}
static void spinbox_num_event_handler(lv_obj_t *obj, lv_event_t event)
{
    switch (event)
    {
    case LV_EVENT_KEY:
    {
        const uint32_t *key = lv_event_get_data();
        if (*key == LV_KEY_ENTER)
        {
            num_cnt = lv_spinbox_get_value(spinbox_num1);
            num_cnt_temp = num_cnt;
            Mode = 11;
        }
    }
    break;
    default:
        break;
    }
}
void spinbox_num(void)
{
    static lv_style_t font_style1;
    lv_style_init(&font_style1);
    lv_style_set_text_font(&font_style1, LV_STATE_DEFAULT, &lv_font_montserrat_24);

    //创建标签对象
    spinbox_num1 = lv_spinbox_create(lv_scr_act(), NULL);
    lv_obj_add_style(spinbox_num1, LV_LABEL_PART_MAIN, &font_style1);

    lv_spinbox_set_range(spinbox_num1, 0, 99999);
    lv_spinbox_set_value(spinbox_num1, num_cnt);
    lv_spinbox_set_digit_format(spinbox_num1, 5, 0);
    lv_spinbox_step_prev(spinbox_num1);
    lv_obj_set_width(spinbox_num1, 100);
    lv_obj_align(spinbox_num1, NULL, LV_ALIGN_CENTER, 0, 0);
    lv_group_add_obj(group, spinbox_num1);
    lv_obj_set_event_cb(spinbox_num1, spinbox_num_event_handler);
}
static void text_event_handler(lv_obj_t *obj, lv_event_t event)
{
}
void lv_ex_textarea_1(void)
{
    ta1 = lv_textarea_create(lv_scr_act(), NULL);
    lv_obj_set_size(ta1, 220, 20);
    lv_obj_align(ta1, NULL, LV_ALIGN_CENTER, 0, -20);
    lv_textarea_set_text(ta1, ""); /*Set an initial text*/
                                   // lv_group_add_obj(group, ta1);
    lv_obj_set_event_cb(ta1, text_event_handler);
}
static void keyboard_event_handler(lv_obj_t *obj, lv_event_t event)
{
    lv_keyboard_def_event_cb(keyboard1, event);
    if ((event == LV_EVENT_CANCEL) || (event == LV_EVENT_APPLY))
    {
        lv_keyboard_set_textarea(keyboard1, NULL);
        // usb_printf("%s\r\n", str_mima);
        Mode = 6;
    }
}
void lvgl_keyboard_mode_test(void)
{
    lv_ex_textarea_1();
    keyboard1 = lv_keyboard_create(lv_scr_act(), NULL);
    lv_obj_set_size(keyboard1, 240, 100);
    lv_obj_align(keyboard1, NULL, LV_ALIGN_CENTER, 0, 70);
    lv_keyboard_set_mode(keyboard1, LV_KEYBOARD_MODE_NUM);
    lv_group_add_obj(group, keyboard1);
    lv_obj_set_event_cb(keyboard1, keyboard_event_handler);
    lv_keyboard_set_textarea(keyboard1, ta1);
}

void lv_ex_textarea_2(void)
{
    ta2 = lv_textarea_create(lv_scr_act(), NULL);
    lv_obj_set_size(ta2, 220, 20);
    lv_obj_align(ta2, NULL, LV_ALIGN_CENTER, 0, -20);
    lv_textarea_set_text(ta2, ""); /*Set an initial text*/
                                   // lv_group_add_obj(group, ta1);
    lv_obj_set_event_cb(ta2, text_event_handler);
}
static void keyboard2_event_handler(lv_obj_t *obj, lv_event_t event)
{
    uint8_t i = 0;
    uint8_t flag = 0;
    lv_keyboard_def_event_cb(keyboard2, event);
    if ((event == LV_EVENT_CANCEL) || (event == LV_EVENT_APPLY))
    {
        lv_keyboard_set_textarea(keyboard2, NULL);
        // usb_printf("%s\r\n", str_mima2);
        Mode = 24;
        // lv_keyboard_set_textarea(keyboard2, NULL);
        // str_mima2 = lv_textarea_get_text(ta2);
        // usb_printf("2:%s\r\n", str_mima2);
        // for (i = 0; i < strlen(str_mima2); i++)
        // {
        //     if (str_mima[i] != str_mima2[i])
        //     {
        //         flag = 1;
        //     }
        // }
        // if (flag = 1)
        // {
        //     Mode = 24;
        // }
        // else
        // {
        //     Mode = 24;
        // }
    }
}
void lvgl_keyboard_mode_test2(void)
{
    lv_ex_textarea_2();
    keyboard2 = lv_keyboard_create(lv_scr_act(), NULL);
    lv_obj_set_size(keyboard2, 240, 100);
    lv_obj_align(keyboard2, NULL, LV_ALIGN_CENTER, 0, 70);
    lv_keyboard_set_mode(keyboard2, LV_KEYBOARD_MODE_NUM);
    lv_group_add_obj(group, keyboard2);
    lv_obj_set_event_cb(keyboard2, keyboard2_event_handler);
    lv_keyboard_set_textarea(keyboard2, ta2);
}

static void btm_int_event_handler(lv_obj_t *obj, lv_event_t event)
{
    uint8_t i = 0;
    switch (event)
    {
    case LV_EVENT_KEY:
    {
        const uint32_t *key = lv_event_get_data();
        if (*key == LV_KEY_ENTER)
        {
            if (lv_btnmatrix_get_active_btn(btnm_int) == 0)
            {
                if (num_cnt_temp <= 0)
                {
                    Mode = 19;
                }
                else
                {
                    num_cnt_temp--;
                    mbox_int_test();
                    lv_group_remove_obj(btnm_int);
                    time_temp = time_tick.min;
                    UNLOCK();
                    // lv_group_add_obj(group, mbox_fail);
                    Mode = 15;
                }
            }
            else if (lv_btnmatrix_get_active_btn(btnm_int) == 1)
            {
                lv_group_remove_obj(btnm_int);
                mbox_message_test();
            }
            else if (lv_btnmatrix_get_active_btn(btnm_int) == 2)
            {
                Mode = 17;
            }
        }
    }
    break;
    default:
        break;
    }
}
static void btnm_int_condition_set(void)
{
    if (ta2 != NULL)
    {
        lv_obj_del(ta2);
    }

    static const char *btnm_text[] = {
        "Take Out", "\n",
        "Check", "\n",
        "Cancle", ""};
    btnm_int = lv_btnmatrix_create(lv_scr_act(), NULL);
    static lv_style_t font_style1;
    lv_style_init(&font_style1);
    lv_style_set_text_font(&font_style1, LV_STATE_DEFAULT, &lv_font_montserrat_24);

    //创建标签对象
    lable_int = lv_label_create(lv_scr_act(), NULL);
    lv_obj_add_style(lable_int, LV_LABEL_PART_MAIN, &font_style1);
    lv_label_set_long_mode(lable_int, LV_LABEL_LONG_BREAK);
    lv_label_set_recolor(lable_int, true);
    lv_label_set_align(lable_int, LV_LABEL_ALIGN_CENTER);
    lv_label_set_text(lable_int, "Running");
    lv_obj_set_width(lable_int, 220);
    lv_obj_align(lable_int, NULL, LV_ALIGN_CENTER, 0, -110);

    lv_btnmatrix_set_map(btnm_int, btnm_text);
    lv_obj_set_size(btnm_int, 100, 150); //可以设置窗口大小
    lv_obj_align(btnm_int, NULL, LV_ALIGN_CENTER, 0, 30);
    lv_group_add_obj(group, btnm_int);
    lv_obj_set_event_cb(btnm_int, btm_int_event_handler);
}
void mbox_int_test(void)
{
    static const char *btn_str[] = {"", "", ""};
    uint8_t text[100];
    mbox_int = lv_msgbox_create(lv_scr_act(), NULL);
    lv_obj_set_size(mbox_int, 170, 80);
    lv_obj_align(mbox_int, NULL, LV_ALIGN_CENTER, 0, 0);
    sprintf((char *)text, "Countdown %d minutes.", time_cnt);
    lv_msgbox_set_text(mbox_int, text);
    lv_msgbox_add_btns(mbox_int, btn_str);
    lv_msgbox_set_recolor(mbox_int, true);
}
static void mbox_event_naozhong_handler(lv_obj_t *obj, lv_event_t event)
{
    switch (event)
    {
    case LV_EVENT_KEY:
    {
        const uint32_t *key = lv_event_get_data();
        if (*key == LV_KEY_ENTER)
        {
            time_temp = time_tick.min;
            LOCK();
            Mode = 18;
        }
    }
    break;
    default:
        break;
    }
}
static void mbox_naozhong_test(void)
{
    static const char *btn_str[] = {"LOCK", "", ""};
    uint8_t text[100];
    mbox_naozhong = lv_msgbox_create(lv_scr_act(), NULL);
    lv_obj_set_size(mbox_naozhong, 170, 80);
    lv_obj_align(mbox_naozhong, NULL, LV_ALIGN_CENTER, 0, 0);
    sprintf((char *)text, "Please put it back and lock it.");
    lv_msgbox_set_text(mbox_naozhong, text);
    lv_msgbox_add_btns(mbox_naozhong, btn_str);
    lv_msgbox_set_recolor(mbox_naozhong, true);
    lv_group_add_obj(group, mbox_naozhong);
    lv_obj_set_event_cb(mbox_naozhong, mbox_event_naozhong_handler);
}
static void mbox_event_fail_handler(lv_obj_t *obj, lv_event_t event)
{
    switch (event)
    {
    case LV_EVENT_KEY:
    {
        const uint32_t *key = lv_event_get_data();
        if (*key == LV_KEY_ENTER)
        {
            Mode = 20;
        }
    }
    break;
    default:
        break;
    }
}
static void mbox_fail_test(void)
{
    static const char *btn_str[] = {"CLOSE", "", ""};
    uint8_t text[100];
    mbox_fail = lv_msgbox_create(lv_scr_act(), NULL);
    lv_obj_set_size(mbox_fail, 170, 80);
    lv_obj_align(mbox_fail, NULL, LV_ALIGN_CENTER, 0, -30);
    sprintf((char *)text, "The number of times taken out has reached the upper limit and cannot be unlocked.");
    lv_msgbox_set_text(mbox_fail, text);
    lv_msgbox_add_btns(mbox_fail, btn_str);

    lv_msgbox_set_recolor(mbox_fail, true);
    lv_group_add_obj(group, mbox_fail);
    lv_obj_set_event_cb(mbox_fail, mbox_event_fail_handler);
}
static void mbox_event_message_handler(lv_obj_t *obj, lv_event_t event)
{
    switch (event)
    {
    case LV_EVENT_KEY:
    {
        const uint32_t *key = lv_event_get_data();
        if (*key == LV_KEY_ENTER)
        {
            Mode = 21;
        }
    }
    break;
    default:
        break;
    }
}
static void mbox_message_test(void)
{
    static const char *btn_str[] = {"CLOSE", "", ""};
    uint8_t text[100];
    mbox_message = lv_msgbox_create(lv_scr_act(), NULL);
    lv_obj_set_size(mbox_message, 170, 80);
    lv_obj_align(mbox_message, NULL, LV_ALIGN_CENTER, 0, -30);
    if (4 * flag_wancheng_[0] + flag_wancheng_[1] * 2 + flag_wancheng_[2] == 0)
    {
        sprintf((char *)text, "1. %d minute left.\n2. %d minute left.\n3. %d minute left.",
                data[0] - (time_tick.hour * 60 + time_tick.min), data[1] - (time_tick.hour * 60 + time_tick.min), data[2] - (time_tick.hour * 60 + time_tick.min));
    }
    else if (4 * flag_wancheng_[0] + flag_wancheng_[1] * 2 + flag_wancheng_[2] == 1)
    {
        sprintf((char *)text, "1. %d minute left.\n2. %d minute left.\n3. Completed.",
                data[0] - (time_tick.hour * 60 + time_tick.min), data[1] - (time_tick.hour * 60 + time_tick.min));
    }
    else if (4 * flag_wancheng_[0] + flag_wancheng_[1] * 2 + flag_wancheng_[2] == 2)
    {
        sprintf((char *)text, "1. %d minute left.\n2. Completed.\n3. %d minute left.",
                data[0] - (time_tick.hour * 60 + time_tick.min), data[2] - (time_tick.hour * 60 + time_tick.min));
    }
    else if (4 * flag_wancheng_[0] + flag_wancheng_[1] * 2 + flag_wancheng_[2] == 3)
    {
        sprintf((char *)text, "1. %d minute left.\n2.Completed.\n3.Completed.",
                data[0] - (time_tick.hour * 60 + time_tick.min));
    }
    else if (4 * flag_wancheng_[0] + flag_wancheng_[1] * 2 + flag_wancheng_[2] == 4)
    {
        sprintf((char *)text, "1.Completed.\n2. %d minute left.\n3. %d minute left.",
                data[1] - (time_tick.hour * 60 + time_tick.min), data[2] - (time_tick.hour * 60 + time_tick.min));
    }
    else if (4 * flag_wancheng_[0] + flag_wancheng_[1] * 2 + flag_wancheng_[2] == 5)
    {
        sprintf((char *)text, "1.Completed.\n2. %d minute left.\n3.Completed.",
                data[1] - (time_tick.hour * 60 + time_tick.min));
    }
    else if (4 * flag_wancheng_[0] + flag_wancheng_[1] * 2 + flag_wancheng_[2] == 6)
    {
        sprintf((char *)text, "1. Completed.\n2.Completed.\n3. %d minute left.",
                data[2] - (time_tick.hour * 60 + time_tick.min));
    }
    else if (4 * flag_wancheng_[0] + flag_wancheng_[1] * 2 + flag_wancheng_[2] == 7)
    {
        sprintf((char *)text, "1.Completed.\n2.Completed.\n3. Completed.");
    }
    lv_msgbox_set_text(mbox_message, text);
    lv_msgbox_add_btns(mbox_message, btn_str);
    lv_msgbox_set_recolor(mbox_message, true);
    lv_group_add_obj(group, mbox_message);
    lv_obj_set_event_cb(mbox_message, mbox_event_message_handler);
}
static void label_yanzheng_test(void)
{
    static lv_style_t font_style1;
    lv_style_init(&font_style1);
    lv_style_set_text_font(&font_style1, LV_STATE_DEFAULT, &lv_font_montserrat_24);

    //创建标签对象
    lable_yanzheng = lv_label_create(lv_scr_act(), NULL);
    lv_obj_add_style(lable_yanzheng, LV_LABEL_PART_MAIN, &font_style1);
    //设置长文本模式
    lv_label_set_long_mode(lable_yanzheng, LV_LABEL_LONG_BREAK); /*Break the long lines*/
                                                                 //使能文本重绘色功能
    lv_label_set_recolor(lable_yanzheng, true);                  /*Enable re-coloring by commands in the text*/
                                                                 //设置文本对齐模式
    lv_label_set_align(lable_yanzheng, LV_LABEL_ALIGN_CENTER);   /*Center aligned lines*/
                                                                 //设置文本内容

    lv_label_set_text(lable_yanzheng, "Enter Password");
    //设置宽度
    lv_obj_set_width(lable_yanzheng, 220);
    //设置对齐模式
    lv_obj_align(lable_yanzheng, NULL, LV_ALIGN_CENTER, 0, -100);
}