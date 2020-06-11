//
//  main.c
//  no1_2
//
//  Created by 谢容海 on 2020/6/11.
//  Copyright © 2020 谢容海. All rights reserved.
//

/**
 2.    高精度计算
 a)    涉及知识点：数组、流程控制、函数等
 b)要求：用整型数组表示10进制大整数（超过2^32的整数），数组的每个元素存储大整数的一位数字，实现大整数的加减法。

 */
#include <stdio.h>
#include <string.h>
#define M 100 //定义了数量M是100作为数组初始化的数量

int i, j = 0;
int k, n, f = 0;
char s1[M] = {'\0'}, s2[M] = {'\0'}; //整数数组初始化
int len1 = 0, len2 = 0;                 //len1是字符数组s1的长度,len2是字符数组s2的长度
char c = {'\0'};                     //用c来代表加减号
int num_a[M] = {0};                     //数字数组num_a
int num_b[M] = {0};                     //数字数组num_b
int num_c[M] = {0};                     //差值数组

void plus(char s1[], char c, char s2[]); //声明加法
void sub(char s1[], char c, char s2[]);     //声明减法

int main() //主函数
{
    printf("Please type the first number :\n");
    scanf("%s", s1); //输入第一个数字
    getchar();
    printf("Please choose + or - :\n");
    scanf("%c", &c); //选择加减号
    printf("Please type the next number :\n");
    scanf("%s", s2); //输入第二个数
    
    len1 = strlen(s1); //求第一个数的位数
    len2 = strlen(s2); //求第二个的位数
    
    switch (c)
    {
        case '+':
            plus(s1, c, s2);
            break; //调用加法
        case '-':
            sub(s1, c, s2);
            break; //调用减法
        default:
            break;
    }
    printf("\n");
    return 0;
}

void plus(char s1[], char c, char s2[])
{
    for (i = len1 - 1, j = 0; i >= 0; i--) //将数字数组倒数存放，作为第一个加数
    {
        num_a[j] = s1[i] - '0';
        j++;
    }
    
    for (i = len2 - 1, j = 0; i >= 0; i--) //将数字数组倒数存放，作为第二个加数
    {
        num_b[j] = s2[i] - '0';
        j++;
    }
    
    for (i = 0; i <= M; i++) //实现大数的加法
    {
        num_a[i] = num_a[i] + num_b[i];
        if (num_a[i] > 9)
        {
            num_a[i] = num_a[i] - 10;
            num_a[i + 1]++;
        }
    }
    
    for (i = M - 1; i >= 0 && num_a[i] == 0; i--)
        ; //求得最终结果的位数
    printf("The answer is :");
    if (i > 0)
    {
        for (; i >= 0; i--) //最终答案的输出
        {
            printf("%d", num_a[i]);
        }
    }
    else
    {
        printf("0");
    }
}

void sub(char s1[], char c, char s2[])
{
    //k的值是参与运算的数据最大位数
    if (len1 > len2)
        k = len1;
    else
        k = len2;
    num_c[0] = 0;
    
    //n>0表示a大于b,n<0,表示a<b,n=0表示a=b
    if (len1 > len2)
        n = 1;
    else if (len1 == len2)
        n = strcmp(s1, s2);
    else
        n = -1;
    
    //字符数组倒序后位数对齐存在整数数组中
    for (i = len1 - 1, j = 0; i >= 0; i--, j++)
    {
        num_a[j] = s1[i] - '0';
    }
    for (i = len2 - 1, j = 0; i >= 0; i--, j++)
    {
        num_b[j] = s2[i] - '0';
    }
    
    //具体执行减法运算
    for (i = 0; i < k; i++)
    {
        if (n >= 0)
        {
            if (num_a[i] - num_b[i] >= 0) //第一个数I位比第二个数I位大
                num_c[i] = num_a[i] - num_b[i];
            else
            {
                num_c[i] = num_a[i] + 10 - num_b[i]; //第一个数I位比第二个数I位小
                num_a[i + 1]--;                         //第一个数I+1位去1
            }
        }
        else
        {
            if (num_b[i] - num_a[i] >= 0)
                num_c[i] = num_b[i] - num_a[i];
            else
            {
                num_c[i] = num_b[i] + 10 - num_a[i];
                num_b[i + 1]--;
            }
        }
    }
    //最终结果的输出
    for (i = k - 1; i >= 0 && num_c[i] == 0; i--)
        ; //求得最终结果的位数
    printf("The answer is :");
    if (n < 0)
        printf("-");
    if (i > 0)
    {
        for (; i >= 0; i--) //最终答案的输出
        {
            printf("%d", num_c[i]);
        }
    }
    else
    {
        printf("0");
    }
    /*printf("The answer is :\n");
     
     if (n < 0)
     printf("-");
     for (i = k - 1; i >= 0; i--) //从高位到低位输出可能情况(000121)
     {
     if (num_c[i]) //如果num_c[i]非0,则返回f=1(初始值为0)
     f = 1;
     if (f || i == 0) //如果f不为0,或者i等于0，就输出数组中的一位，否则不输出
     printf("%d", num_c[i]);
     }*/
}
