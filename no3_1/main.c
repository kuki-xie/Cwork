//
//  main.c
//  no3_1
//
//  Created by 谢容海 on 2020/6/11.
//  Copyright © 2020 谢容海. All rights reserved.
//

#include <stdio.h>

int main(int argc, const char * argv[]) {
    // insert code here...
    char str[50];//设定temp数组用来读取fp1
    long n;//str的长度
    int i,j,flag,count;
    FILE *file1,*file2,*tagtetfile;//三个文件指针
    if((file1=fopen("/Users/xieronghai/Desktop/test.c", "r"))==NULL)
    {//打开test.c文件
        printf("test.c open error\n");
        exit(0);
    }
    if((file2=fopen("/Users/xieronghai/Desktop/new.c","w"))==NULL)
    {//打开new.c文件
        printf("new.c open error\n");
        exit(0);
    }
    while (!feof(file1)) {//当未读到文件结尾
        flag=1;//用来判断是否读入文件fp2
        fgets(str, 50, file1);//将文件读成String数组
        n=strlen(str);
        for (i=0; i<n;i++) {
            if (str[i]=='/'&&str[i-1]=='/') {//当遇到//这样的例子时，将已读入的文件写入
                str[i-1]='\n';//换行
                str[i]='\0';
                fputs(str, file2);//读入文件fp2
                flag=0;
                break;
            }
            else if(str[i-1]=='/'&&str[i]=='*')
            {//当读到/*这样的例子时*/
                str[i-1]='\n';
                str[i]='\0';//把已读入的字符串写入fp2
                fputs(str, file2);
                flag=0;
                break;
            }
            else if (str[i-1]=='*'&&str[i]=='/') {///*前半部分读入后，处理后半部分
                for (j=0; j<n-i; j++) {
                    str[j]=str[j+1+i];//直接开始读*/后的内容
                }
                str[j]='\0';//并将末尾置为'\0'
                fputs(str, file2);
                flag=0;
                break;
            }
        }
        if (flag) {//如果里面没有注释，也放进去
            fputs(str, file2);
        }
    }
    
    if(fclose(file1))
    {//当fp1关闭失败时
        printf("Can't close the test.c\n");
        exit(0);
    }
    else if(fclose(file2))
    {//当fp2关闭失败时
        printf("Can't close the new.c\n");
        exit(0);
    }
    //加入行号
    file2=fopen("/Users/xieronghai/Desktop/new.c", "r");
    tagtetfile=fopen("/Users/xieronghai/Desktop/to.c", "w");
    count=1;//数行号
    while(fgets(str, 50, file2)!=NULL)
    {
        fprintf(tagtetfile, "[%3d]",count);//添加行号,按照格式
        fputs(str, tagtetfile);
        count++;
    }
    fclose(file2);
    fclose(tagtetfile);
    return 0;
}
