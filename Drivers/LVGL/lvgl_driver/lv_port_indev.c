#include "lvgl.h"
#include "lv_port_disp.h"
#include "lv_ex_conf.h"
#include "lv_examples.h"
#include "lv_demo_widgets.h"
#include "lv_port_indev.h"
#include "main.h"
static void keypad_init(void);
static bool keypad_read(lv_indev_drv_t *indev_drv, lv_indev_data_t *data);
static uint32_t keypad_get_key(void);
lv_indev_t *indev_keypad;
lv_group_t *group;

void lv_port_indev_init(void)
{
    lv_indev_drv_t indev_drv;
    /*------------------
     * Keypad
     * -----------------*/

    /*Initialize your keypad or keyboard if you have*/
    keypad_init();

    /*Register a keypad input device*/
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_KEYPAD;
    indev_drv.read_cb = keypad_read;
    indev_keypad = lv_indev_drv_register(&indev_drv);
    group = lv_group_create();
    lv_indev_set_group(indev_keypad, group);
}
static void keypad_init(void)
{
    /*Your code comes here*/
}

/* Will be called by the library to read the mouse */
static bool keypad_read(lv_indev_drv_t *indev_drv, lv_indev_data_t *data)
{
    static uint32_t last_key = 0;
    /*Get the current x and y coordinates*/
    /*Get whether the a key is pressed and save the pressed key*/
    uint32_t act_key = keypad_get_key();
    if (act_key != 0)
    {
        data->state = LV_INDEV_STATE_PR;
        /*Translate the keys to LVGL control characters according to your key definitions*/
        switch (act_key)
        {
        case 2:
            act_key = LV_KEY_LEFT;
            break;
        case 1:
            act_key = LV_KEY_RIGHT;
            break;
        case 4:
            act_key = LV_KEY_ENTER;
            break;
        case 3:
            act_key = LV_KEY_UP;
            break;
        }
        last_key = act_key;
    }
    else
    {
        data->state = LV_INDEV_STATE_REL;
    }
    data->key = last_key;
    /*Return `false` because we are not buffering and no more data to read*/
    return false;
}

/*Get the currently being pressed key.  0 if no key is pressed*/
static uint32_t keypad_get_key(void)
{
    if (HAL_GPIO_ReadPin(K1_GPIO_Port, K1_Pin) == 0)
    {
        return 1;
    }
    if (HAL_GPIO_ReadPin(K2_GPIO_Port, K2_Pin) == 0)
    {
        return 2;
    }
    if (HAL_GPIO_ReadPin(K3_GPIO_Port, K3_Pin) == 0)
    {
        return 3;
    }
    if (HAL_GPIO_ReadPin(K4_GPIO_Port, K4_Pin) == 0)
    {
        return 4;
    }
    /*Your code comes here*/
    return false;
}
