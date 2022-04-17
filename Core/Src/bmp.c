#include "bmp.h"
#include "spi.h"
#include "w25qxx.h"
#include "lcd.h"
#include "ff.h"
extern FATFS fs;
extern FIL file1,file2;                      /* 文件对象 */
extern FIL *pf,*pf1,*pf2;                       //将FIL结构体对象设置为全局变量！！！！！！！！！！！！
extern FRESULT f_res;                 /* 文件操作结果 */
extern UINT fnum;                     /* 文件成功读写数量 */
extern BYTE ReadBuffer[240 * 20 * 3]; /* 读缓冲区 */
extern BYTE WriteBuffer[];
extern BYTE work[4096];
extern UINT bw;
UINT bw1,bw2;
struct _BMP_HEAD bmp_head;
struct _BMP_INFO bmp_info;

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
        LCD_ShowPicture_bmp(0, 20 * i, 240,20, ReadBuffer);
    }
    f_res = f_close(&file2);
    HAL_Delay(1000);
}
