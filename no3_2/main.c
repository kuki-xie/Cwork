//
//  main.c
//  no3_2
//
//  Created by 谢容海 on 2020/6/11.
//  Copyright © 2020 谢容海. All rights reserved.
//

#include<stdio.h>
#include<stdlib.h>
#include<sys/malloc.h>
#include<math.h>

typedef unsigned short int WORD;
typedef unsigned int DWORD;
typedef unsigned char BYTE;

typedef struct tagBITMAPFILEHEADR
{
    WORD bfType;//位图文件的类型，必须为BM(0-1)字节
    DWORD bfSize;//位图文件的大小，以字节为单位（2-5）字节
    WORD bfReserved1;//位图文件保留字，必须为0（6-7）字节
    WORD bfReserved2;//位图文件保留字，必须为0（8-9）字节
    DWORD bfOffBits;//位图数据的起始位置（10-13）字节，以相对于文件头的偏移量表示，以字节为单位
} BITMAPFILEHEADR;

typedef struct tagBITMAPINFOHEAER
{
    DWORD biSize;//本结构所占用字节数（14-17字节）
    DWORD biWidth;//位图的宽度，以像素为单位（18-21字节）
    DWORD biHeight;//位图的高度，以像素为单位（22-25字节）
    WORD biPlanes;//目标设备的级别，必须为1（26-27字节）
    WORD biBitCount;//每个像素所需的位数，必须是1（双色）(28-29字节），4（16色），8（256色）或24（真彩色）之一
    DWORD biCompression;//位图压缩类型，必须是0（不压缩），（30-33字节）1（BI_RLE8压缩类型）或2（BI_RLE4压缩类型）之一
    DWORD biSizeImage;//位图的大小，以字节为单位（34-37字节）
    DWORD biXPelsPerMeter;//位图水平分辨率，每米像素数（38-41字节）
    DWORD biYPelsPerMeter;//位图垂直分辨率，每米像素数（42-45字节）
    DWORD biClrUsed;//位图实际使用的颜色表中的颜色数（46-49字节）设为0的话，则说明使用所有调色板项 即2 biBitCount种颜色
    DWORD biClrImportant;//位图显示过程中重要的颜色数（50-53字节）
} BITMAPINFOHEAER;

typedef struct tagRGBQUAD
{
    BYTE rgbBlue;//蓝色的亮度(值范围为0-255）
    BYTE rgbGreen;//绿色的亮度（值范围为0-255）
    BYTE rgbRed;//红色的亮度（值范围为0-255）
    BYTE rgbReserved;//保留字，必须为0
}RGBQUAD;

int main(int argc,char **argv)
{
    /*printf("%d个参数\n",argc);
     for(int i=0;i<argc;i++)
     {
     printf("%s\n",argv[i]);
     }*/
    FILE *org=fopen(argv[2], "rb");//要读入的BMP文件
    if(org==0)
        return 0;
    BITMAPFILEHEADR header;//BMP文件头
    fread(&header, 14, 1, org);
    BITMAPINFOHEAER info;//BMP信息头
    fread(&info, 40, 1, org);
    
    int width=info.biWidth;//图像宽度
    int height=info.biHeight;//图像高度
    
    printf("宽：%d 高：%d\n",info.biWidth,info.biHeight);
    printf("每个像素所需的位数：%d\n",info.biBitCount);
    printf("位图压缩类型：%d\n",info.biCompression);
    printf("位图的总颜色数：%d\n",info.biClrUsed);
    
    int lineByte=(8*width/8+3)/4*4;//计算位图每行所占的字节数
    RGBQUAD *ColorTable;
    ColorTable=new RGBQUAD[256];//设置颜色映射表
    fread(ColorTable, 4, 256, org);
    
    BYTE *orgBuf,*tagBuf;
    orgBuf=new BYTE[lineByte*height];//读入图像数据
    fread(orgBuf, lineByte*height, 1, org);
    fclose(org);
    
    //统计概率
    double st[256]={0};//每一个灰度在整个图像中像素个数的占比
    int ss[256]={0};
    int t;
    for (int i=0; i<height; i++) {
        for (int j=0; j<width; j++) {
            t=*(orgBuf+i*lineByte+j);//当前点
            st[t]++;//统计原始图像各灰度级的像素数目
        }
    }
    
    //计算累加直方图并完成映射
    st[0]=st[0]/(width*height);
    ss[0]=round(double((256-1)*st[0]));//根据公式求取像素映射关系
    for (int i=1; i<256; i++) {
        st[i]=st[i]/(width*height);//图像中灰度为i的像素的出现概率，归一化到[0, 1]
        st[i]=st[i]+st[i-1];//计算直方图概率累计值
        ss[i]=int(round(double((256-1)*st[i])));//最大灰度-最小灰度，计算均衡化之后的灰度值，完成灰度值映射
        printf("st[%d]=%f,ss[%d]=%d\n",i,st[i],i,ss[i]);
    }
    
    //新图像的像素填充
    tagBuf=new BYTE[lineByte*height];//灰度映射
    for (int i=0; i<height; i++) {
        for (int j=0; j<width; j++) {
            t=*(orgBuf+i*lineByte+j);//当前点
            *(tagBuf+i*lineByte+j)=ss[t];//映射回原来像素的坐标的像素值
        }
    }
    printf("Success!\n");
    
    FILE *tag=fopen(argv[3], "wb");//要复制的BMP文件
    if (tag==0) {
        return 0;
    }
    fwrite(&header, 14, 1, tag);
    fwrite(&info, 40, 1, tag);
    fwrite(ColorTable, 4, 256, tag);
    fwrite(tagBuf, lineByte*height, 1, tag);
    fclose(tag);
    
    return 0;
}
