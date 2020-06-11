//
//  main.c
//  no1_1
//
//  Created by 谢容海 on 2020/6/11.
//  Copyright © 2020 谢容海. All rights reserved.
//

#include <stdio.h>
#include <string.h>
int main()
{
    char s[200] = {0}; /*定义一个长度为200的字符串*/
    int l = 0, i = 0;  /* l为输入2进制字符串长度*/
    
    printf("请输入想转换的2进制数字\n");
    gets(s); /*用户输入字符串*/
    while (s[i++])
        l++; /*用while循环计算字符串长度*/
    
    int sum = 0, m = 1; /*sum储存2进制转换为十进制的结果*/
    for (i = 0; i < l; i++)
    {
        /*输入的是字符，需要减去'0'来得到对应的数值*/
        sum += (s[l - i - 1] - '0') * m;
        m *= 2; /*因为随着位数变高，权值依次翻倍，所以每加一次,m从低位依次乘2依次到最高位*/
    }
    printf("转换为10进制的结果为:\n");
    printf("%d\n", sum); /*2进制转换为10进制的结果*/
    return 0;
}
