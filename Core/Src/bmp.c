#include "bmp.h"
#include "spi.h"
#include "w25qxx.h"
#include "lcd.h"
#include "ff.h"
extern FATFS fs;
extern FIL file;                      /* 文件对象 */
extern FIL *pf;                       //将FIL结构体对象设置为全局变量！！！！！！！！！！！！
extern FRESULT f_res;                 /* 文件操作结果 */
extern UINT fnum;                     /* 文件成功读写数量 */
extern BYTE ReadBuffer[240 * 20 * 3]; /* 读缓冲区 */
extern BYTE WriteBuffer[];
extern BYTE work[4096];
extern UINT bw;
struct _BMP_HEAD bmp_head;
struct _BMP_INFO bmp_info;

void bmp_test(void)
{
    int cnt;
    int i = 0;
    f_res = f_open(&file, "1.bmp", FA_READ);
    f_res = f_read(&file, &bmp_head, sizeof(struct _BMP_HEAD), &bw);
    f_res = f_read(&file, &bmp_info, sizeof(struct _BMP_INFO), &bw);
    f_lseek(&file, bmp_head.seek);
    for (i = 0; i < 12; i++)
    {
        f_res = f_read(&file, &ReadBuffer, 240 * 20 * 3, &bw);
        LCD_ShowPicture_bmp(0, 20 * i, 240, 20, ReadBuffer);
    }
    f_res = f_close(&file);
    HAL_Delay(1000);
    f_res = f_open(&file, "2.bmp", FA_READ);
    f_res = f_read(&file, &bmp_head, sizeof(struct _BMP_HEAD), &bw);
    f_res = f_read(&file, &bmp_info, sizeof(struct _BMP_INFO), &bw);
    f_lseek(&file, bmp_head.seek);
    for (i = 0; i < 12; i++)
    {
        f_res = f_read(&file, &ReadBuffer, 240 * 20 * 3, &bw);
        LCD_ShowPicture_bmp(0, 20 * i, 240, 20, ReadBuffer);
    }
    f_res = f_close(&file);
    HAL_Delay(1000);
}
