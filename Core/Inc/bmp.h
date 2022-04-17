#ifndef _BMP_H_
#pragma pack(1) //强制1个字节对齐
// BMP的文件头
struct _BMP_HEAD
{
    char type[2];      //图片的类型 "BM"
    unsigned int size; //文件大小
    unsigned short r1; //保留1
    unsigned short r2; //保留2
    unsigned int seek; //数据偏移字节(真实像素点数据)
};

// BMP的参数信息
struct _BMP_INFO
{
    unsigned int size;   //当前结构体大小
    unsigned int w;      //宽度
    unsigned int h;      //高度
    unsigned short flag; //固定为1
    unsigned short bit;  //像素点的位数
    unsigned int r1;     //压缩方式  0
    unsigned int r2;     //水平分辨率
    unsigned int r3;     //垂直分辨率
    unsigned int r4;     //垂直分辨率
    unsigned int r5;     //引用色彩
    unsigned int r6;     //关键色彩
};
void bmp_test(void);
#endif // !_BMP_H_
