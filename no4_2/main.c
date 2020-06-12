//
//  main.c
//  no4_2
//
//  Created by 谢容海 on 2020/6/11.
//  Copyright © 2020 谢容海. All rights reserved.
//

/**
 8.    RLE压缩解压算法
 涉及知识点：文件读写、位操作、内存管理、结构体定义、RLE算法、命令行参数
 要求：
 编写一个程序，可以在命令行输入参数，完成指定文件的压缩解压
 命令行参数如下
 rle file1 –c(-d) file2
 第一个参数为可执行程序名称，第二个参数为原始文件名，第三个参数为压缩或解压缩选项，第四个参数为新文件名

 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int RLE_Compression(char *infile,char *outfile);
int RLE_Decompression(char *infile,char *outfile);
/**
 主函数
 */
int main(int argc,char **argv)
{
    printf("RLE Compression and Decompression\n");
    if (argc!=4) {//Judge the number of arguments
        printf("Please type 4 arguments.\n");
        printf("-c Means Compression and -d Means Decompression.\n");
        exit(0);
    }
    if (strcmp(argv[2], "-c")==0) {//Judge the action is Compression
        printf("Compressing...\n");
        RLE_Compression(argv[1], argv[3]);
    }
    else if(strcmp(argv[2], "-d")==0){//Judge the action is Decompression
        printf("Decompresing...\n");
        RLE_Decompression(argv[1], argv[3]);
    }
    else{
        printf("Unknow command.\n");
    }
    return 0;
}

/**
 解压
 */
int RLE_Decompression(char *infile,char *outfile)
{
    register int count;
    char space[255],temp;
    FILE *inbuf,*outbuf;
    //检验是否能打开
    if ((inbuf=fopen(infile, "rb"))==NULL) {//源文件打开失败
        strcpy(space, "Unable to open");//复制
        strcat(space, infile);//追加到结尾
        puts(space);//输出报错
        return 1;
    }
    if ((outbuf=fopen(outfile, "wb"))==NULL) {//taget文件打开失败
        strcpy(space, "Unable to open");//复制到space
        strcat(space, outfile);//将文件名追加到结尾
        puts(space);//输出
        return 1;
    }
    if (feof(inbuf)) {//读到文件结尾
        return 0;
    }
    
    while (!feof(inbuf)) {
        count=(int)fgetc(inbuf);//字符表示的相同字母个数
        temp=fgetc(inbuf);//所读字母
        for (int i=0; i<count; i++) {
            fputc(temp, outbuf);//被写入对象，被写入的流
        }
    }
    printf("Decopression Success.\n");
    fclose(inbuf);
    fclose(outbuf);
    return 0;
}
/**
 压缩
 */
int RLE_Compression(char *infile,char *outfile)
{
    register int count;
    char space[255],temp,flag;
    FILE *inbuf,*outbuf;
    //检验是否能打开
    if ((inbuf=fopen(infile, "rb"))==NULL) {//文件打开失败
        strcpy(space, "Unable to open");
        strcat(space, infile);
        puts(space);
        return 1;
    }
    if((outbuf=fopen(outfile, "wb"))==NULL)//打开目标文件失败
    {
        strcpy(space, "Unable to open");//复制
        strcat(space, outfile);//追加到末尾
        puts(space);
        return 1;
    }
    
    if (feof(inbuf)) {//读到文件末尾
        return 0;
    }
    
    temp=fgetc(inbuf);//获取第一个字符
    flag=temp;//基准值
    count=1;
    
    while (!feof(inbuf)) {
        temp=fgetc(inbuf);//第一字符做基准值
        if(temp==flag)//下一个字符和前一个相等
        {
            count++;//相同字符数
        }
        else
        {
            fputc(count, outbuf);//将长度放入文件
            fputc(flag, outbuf);//将字符放入
            flag=temp;//改变标尺
            count=1;
        }
    }
    printf("Copression Success.\n");
    fclose(inbuf);
    fclose(outbuf);
    return 0;
}
