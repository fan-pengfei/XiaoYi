#include "bmp.h"
#include "spi.h"
#include "w25qxx.h"
#include "lcd.h"
#include "ff.h"
#include "stdio.h"
extern FATFS fs;
extern FIL file1, file2;              /* 文件对象 */
extern FIL *pf, *pf1, *pf2;           //将FIL结构体对象设置为全局变量！！！！！！！！！！！！
extern FRESULT f_res;                 /* 文件操作结果 */
extern UINT fnum;                     /* 文件成功读写数量 */
extern BYTE ReadBuffer[240 * 20 * 3]; /* 读缓冲区 */
extern BYTE WriteBuffer[];
extern BYTE work[4096];
extern UINT bw;
UINT bw1, bw2;
struct _BMP_HEAD bmp_head;
struct _BMP_INFO bmp_info;
void show_bmp(unsigned int x, unsigned int y, unsigned int num) //适用于24色位图
{
    uint8_t temp_text[10];
    uint8_t num_buf = 0;
    uint8_t i, j;
    sprintf((char *)temp_text, "%d.bmp", num);
    f_res = f_open(&file1, temp_text, FA_READ);
    f_res = f_read(&file1, &bmp_head, sizeof(struct _BMP_HEAD), &bw);
    f_res = f_read(&file1, &bmp_info, sizeof(struct _BMP_INFO), &bw);
    f_lseek(&file1, bmp_head.seek);
    if (bmp_info.h < 20)
    {
        f_read(&file1, &ReadBuffer, bmp_info.w * bmp_info.h * 3, &bw);
        LCD_ShowPicture_bmp(x, y, bmp_info.w, bmp_info.h, ReadBuffer);
    }
    else
    {
        num_buf = bmp_info.h / 20;
        for (i = 0; i < num_buf; i++)
        {
            // f_lseek(&file, bmp_head.seek + i * bmp_info.w * 20 * 3);
            f_read(&file1, &ReadBuffer, bmp_info.w * 20 * 3, &bw);
            LCD_ShowPicture_bmp(x, y + 20 * i, bmp_info.w, 20, ReadBuffer);
        }
        f_read(&file1, &ReadBuffer, (bmp_info.w * bmp_info.h * 3) - (bmp_info.w * 20 * num_buf), &bw);
        LCD_ShowPicture_bmp(x, y + 20 * num_buf, bmp_info.w, bmp_info.h - 20 * num_buf, ReadBuffer);
    }
    f_res = f_close(&file1);
}
void bmp_test(void)
{

    int cnt;
    int i = 0;
    f_res = f_open(&file1, "1.bmp", FA_READ);
    f_res = f_read(&file1, &bmp_head, sizeof(struct _BMP_HEAD), &bw1);
    f_res = f_read(&file1, &bmp_info, sizeof(struct _BMP_INFO), &bw1);
    f_lseek(&file1, bmp_head.seek);
    for (i = 0; i < 12; i++)
    {

        f_res = f_read(&file1, &ReadBuffer, 240 * 20 * 3, &bw1);
        LCD_ShowPicture_bmp(0, 20 * i, 240, 20, ReadBuffer);
    }
    f_res = f_close(&file1);
    HAL_Delay(1000);
    f_res = f_open(&file2, "2.bmp", FA_READ);
    f_res = f_read(&file2, &bmp_head, sizeof(struct _BMP_HEAD), &bw2);
    f_res = f_read(&file2, &bmp_info, sizeof(struct _BMP_INFO), &bw2);
    f_lseek(&file2, bmp_head.seek);
    for (i = 0; i < 12; i++)
    {
        f_res = f_read(&file2, &ReadBuffer, 240 * 20 * 3, &bw2);
        LCD_ShowPicture_bmp(0, 20 * i, 240, 20, ReadBuffer);
    }
    f_res = f_close(&file2);
    HAL_Delay(1000);
    f_res = f_open(&file2, "3.bmp", FA_READ);
    f_res = f_read(&file2, &bmp_head, sizeof(struct _BMP_HEAD), &bw2);
    f_res = f_read(&file2, &bmp_info, sizeof(struct _BMP_INFO), &bw2);
    f_lseek(&file2, bmp_head.seek);
    for (i = 0; i < 12; i++)
    {
        f_res = f_read(&file2, &ReadBuffer, 240 * 20 * 3, &bw2);
        LCD_ShowPicture_bmp(0, 20 * i, 240, 20, ReadBuffer);
    }
    f_res = f_close(&file2);
    HAL_Delay(1000);
}
