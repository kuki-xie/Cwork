//
//  main.c
//  no5
//
//  Created by 谢容海 on 2020/6/11.
//  Copyright © 2020 谢容海. All rights reserved.
//

/**
 9.    简单文件数据库-模拟图书馆管理系统
 涉及知识点：文件读写、内存管理、结构体定义、基本数据结构、高级格式化输入输出
 要求：
 编写一个程序模拟图书管理系统。用户分为管理员和读者两类，分别显示不同文本格式菜单，通过菜单项对应数字进行选择。读者菜单包括借书、还书、查询等功能。管理员菜单包括图书和读者信息录入、修改和删除。图书信息至少应包括：编号、书名、数量，读者信息至少应包括：编号、姓名、所借图书。可根据图书名称或编号进行图书信息查询，可查询某本书现在被哪些读者借走。
 命令行参数如下：
 Libsim –a(-u) xxxx
 第一个参数为可执行程序名称；第二个参数为用户身份，-a表示管理员，-u表示读者；第三个参数为用户名

 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
struct BOOK //定义图书信息数组结构体
{
    int id;//图书id
    char name[30];//书名
    int num;//数量
} BOOKS[1000];

struct READER //定义读者信息数组结构体
{
    int id;//卡号
    char name[30];//读者名
    struct BOOK booklent;//所借书
} READERS[1000]; //定义读者信息数组结构体；
void readerMenu(void);
void stuffMenu(void);

int getReaderId(char s[]);
void getBooklentName(char s[]);

int readerInput(void);
void readerOutput(void);

void reviseReader(void);
void deleteReader(void);
void addReader(void);
int searchId(void);

int getBookId(char s[]);
int getBookNum(char s[]);

void f1(char *s);
void f2(char *s);
int bookInput(void);
void bookOutput(void);
void reviseBook(void);
void addBook(void);
void deleteBook(void);
void searchBook(void);

void borrowBook(void);
void returnBook(void);

//删除前导空格
void f1(char *s)
{
    char *t;
    t = s;
    while (*s == ' ')//遇到空格，不读入
    {
        s++;
    }
    while ((*t++ = *s++))
        ;
}


void f2(char *s)//删除后导空格
{
    int i = 0, k;
    while (s[i] != '\0')//读到末尾
    {
        i++;
    }
    for (k = i - 1; s[k] ==32; k--)
        ;
    
    s[k + 1] = '\0';
}


int bookInput()//图书信息录入
{
    int number = 0;
    FILE *infile = fopen("/Users/xieronghai/Desktop/book.txt", "rb");//读取图书文件
    if (infile)
    {
        char buf[100] = {0};
        int i = 0, k = 0;
        while (fgets(buf, 100, infile))
        {
            BOOKS[i].id = getBookId(buf);//获取图书id
            BOOKS[i].num = getBookNum(buf);//获取图书数量
            k = 0;
            char buff[100] = {0};
            for (int j = 0; j < strlen(buf); j++)
            {
                if ((buf[j] >= 'A' && buf[j] <= 'Z') || (buf[j] >= 'a' && buf[j] <= 'z') || buf[j] == 32)//判断图书
                {
                    buff[k] = buf[j];
                    k++;
                }
            }
            f1(buff);
            f2(buff);//去除书名的无用空格
            for (int q = 0; q < strlen(buff); q++)
            {
                BOOKS[i].name[q] = buff[q];//存储书名
            }
            i++;
            number = BOOKS[i - 1].id;//返回读取书的数量
        }
    }
    else
    {
        printf("打开失败\n");
    }
    fclose(infile);
    return number;
}

//将做过改动的图书信息录入到文本中；
void bookOutput()
{
    char s[100];
    int n, num;
    FILE *outfile = fopen("/Users/xieronghai/Desktop/book.txt", "wb");//打开图书文件
    for (int i = 0; i < 1000; i++)
    {
        
        if (BOOKS[i].num >0)
        {
            for (int j = 0; j < 100; j++)
            {
                s[j] = '\0';//初始化
            }
            n = (int)strlen(BOOKS[i].name);//读取书名长度
            num = BOOKS[i].num;
            s[0] = (BOOKS[i].id / 100) + '0';
            s[1] = (BOOKS[i].id / 10) + '0';
            s[2] = (BOOKS[i].id % 10) + '0';//判断书id
            s[3] = 32;
            s[4] = 32;
            for (int j = 0; j < n; j++)//录入书名
            {
                s[5 + j] = BOOKS[i].name[j];
            }
            s[5 + n] = 32;
            s[6 + n] = 32;//做间隔
            for (int j = 2; j >= 0; j--)
            {
                s[7 + n + j] = num % 10 + '0';
                num = num / 10;
            }
            s[7 + n + 3] = '\n';
            s[7 + n + 4] = '\0';//换行并添加字符串结束标志
            if (outfile)//读到文件末尾
            {
                fputs(s, outfile);
            }
            else
                printf("打开文件失败\n");
        }
    }
    fclose(outfile);
}

//读者信息录入
int readerInput()
{
    int number = 0;
    FILE *inf = fopen("/Users/xieronghai/Desktop/reader.txt", "rb");
    if (inf)
    {
        char buf[100] = {0};
        char str[100];
        int i = 0;
        while (fgets(buf, 100, inf))//每次读出100字节
        {
            READERS[i].id = getBookId(buf);//获得id
            READERS[i].booklent.num = getBookNum(buf);//获得所借图书个数
            strcpy(str, buf);//保证原数据不动
            READERS[i].booklent.id = getReaderId(str);//获得借书人卡号
            strcpy(READERS[i].name, str);
            getBooklentName(buf);//获得借书的书名
            strcpy(READERS[i].booklent.name, buf);
            i++;
            number = READERS[i - 1].id;
        }
    }
    else
    {
        printf("打开文件失败！\n");
    }
    fclose(inf);
    return number;
}

//将做过改动的读者信息录入到文本中；
void readerOutput()
{
    char s[100];
    int rnamelen, rbooknum, rbnamelen;
    FILE *outf = fopen("/Users/xieronghai/Desktop/reader.txt", "wb");
    for (int i = 0; i < 1000; i++)
    {
        if (READERS[i].id != 0)
        {
            for (int j = 0; j < 100; j++)
            {
                s[j] = '\0';
            }
            rnamelen = (int)strlen(READERS[i].name);//借书人姓名length
            rbooknum = READERS[i].booklent.num;//所借书数量
            rbnamelen = (int)strlen(READERS[i].booklent.name);//所借书书名长度
            s[0] = (READERS[i].id / 100) + '0';//输入书id
            s[1] = (READERS[i].id / 10) + '0';
            s[2] = (READERS[i].id % 10) + '0';
            s[3] = 32;
            s[4] = 32;
            for (int j = 0; j < rnamelen; j++)//输入书名
            {
                s[5 + j] = READERS[i].name[j];
            }
            s[5 + rnamelen] = 32;
            s[6 + rnamelen] = 32;
            s[7 + rnamelen] = (READERS[i].booklent.id / 100) + '0';//谁让所借书id
            s[8 + rnamelen] = (READERS[i].booklent.id / 10) + '0';
            s[9 + rnamelen] = (READERS[i].booklent.id % 10) + '0';
            s[10 + rnamelen] = 32;
            s[11 + rnamelen] = 32;
            for (int j = 0; j < rbnamelen; j++)//输入所借书名
            {
                s[12 + rnamelen + j] = READERS[i].booklent.name[j];
            }
            s[12 + rnamelen + rbnamelen] = 32;
            s[13 + rnamelen + rbnamelen] = 32;
            for (int j = 2; j >= 0; j--)//输入所借书数量
            {
                s[14 + rnamelen + rbnamelen + j] = rbooknum % 10 + '0';
                rbooknum = rbooknum / 10;
            }
            s[14 + rbnamelen + rnamelen + 3] = '\n';
            s[14 + rbnamelen + rnamelen + 4] = '\0';
            if (outf)
            {
                fputs(s, outf);
            }
            else
            {
                printf("打开文件失败\n");
            }
        }
    }
    fclose(outf);
}

int getBookId(char s[])
{
    int i = 0, num = 0, a[100], t = 0;
    for(i=0;i<strlen(s);i++){
        while (s[i] >= '0' && s[i] <= '9')
        {
            a[t] = s[i] - '0';//转换为int型
            i++;
            t++;
        }
    }
    for (i = 0; i < t; i++)//转换为实际数字
    {
        num = num + pow(10, t - 1 - i) * a[i];
    }
    return num;
} //得到图书编号

int getBookNum(char s[])
{
    char str[1000] = {0};
    int length = (int)strlen(s);
    int i, num = 0, a[100], t = 0;
    for (int i = 0; i < strlen(s); i++)//倒置
    {
        str[length - 1 - i] = s[i];
    }
    for (i = 0; i < strlen(str); i++)
    {
        while ('0' <= str[i] && str[i] <= '9')
        {
            a[t] = str[i] - '0';
            i++;
            t++;
        }
        if (str[i] == 32)
        {
            break;
        }
    }
    for (i = 0; i < t; i++)//转换为实际数字
    {
        num = num + pow(10, i) * a[i];
    }
    return num;
} //得到每种图书的个数

//获取读者名
int getReaderId(char s[])
{
    int i = 0, k = 0, flag = 0, j = 0, temp = 0, id = 0, t = 0;
    char str[100];
    int num[5];
    for (int i = 0; i < strlen(s); i++)
    {
        while (s[i] > '9' || s[i] < '0')//为英文
        {
            str[k] = s[i];//转接
            k++;//递增
            i++;//递增
            flag = 1;
        }
        if (flag == 1)
        {
            for (int m = i; m < strlen(s); m++)
            {
                while (s[m] >= '0' && s[m] <= '9')
                {
                    num[j] = s[m] - '0';//获取数字
                    j++;
                    m++;
                    t++;
                    temp = 1;
                }
                if (temp == 1)
                    break;
            }
            break;
        }
    }
    f1(str);
    f2(str);
    strcpy(s, str);
    for (i = 0; i < t; i++)//转换为实际id
    {
        id = id + pow(10, t - 1 - i) * num[i];
    }
    return id;
}

//获取借走的书的名字
void getBooklentName(char s[])
{
    int flag = 0, k = 0, i = 0;
    char name[30] = {0};
    for (i = 0; i < strlen(s); i++)
    {
        while (s[i] >= '0' && s[i] <= '9')//读者编号
        {
            i++;
            flag = 1;
        }
        while (s[i] < '0' || s[i] > '9')//判断书名
        {
            i++;
            flag = 2;
        }
        while (s[i] >= '0' && s[i] <= '9')//借的书的编号
        {
            i++;
            flag = 3;
        }
        if (flag == 3)
        {
            while (s[i] < '0' || s[i] > '9')//为英文
            {
                name[k] = s[i];
                k++;
                i++;
                flag = 4;
            }
        }
        if (flag == 4)
        {
            break;
        }
    }
    f1(name);
    f2(name);
    strcpy(s, name);//复制过去
}

//修改读者信息
void reviseReader()
{
    readerInput();
    int choice = 0;
    printf("请输入想要更改的项目\n");
    printf("1.修改借书卡卡号\n");
    printf("2.修改借书人姓名\n");
    printf("3.修改所借书籍\n");
    scanf("%d", &choice);
    switch (choice)
    {
        case 1:
            printf("请输入所修改卡号的借书人姓名");
            char s[30];
            scanf("%s", s);
            for (int i = 0; i < 1000; i++)
            {
                if (strcmp(READERS[i].name, s) == 0)//比对相符
                {
                    printf("请输入新的借书卡卡号");
                    int id;
                    scanf("%d", &id);
                    READERS[i].id = id;//改变id
                    printf("reader.id=%d\n", READERS[i].id);
                    puts(READERS[i].name);
                    printf("booklent.id=%d\n", READERS[i].booklent.id);
                    puts(READERS[i].booklent.name);
                    printf("booklentnum=%d\n", READERS[i].booklent.num);
                }
            }
            break;
        case 2:
            printf("请输入借书卡卡号\n");
            int id;
            scanf("%d", &id);
            for (int i = 0; i < 1000; i++)
            {
                if (READERS[i].id == id)
                {
                    printf("请输入新的借书卡持有人的姓名\n");
                    char name[30];
                    scanf("%s", name);
                    strcpy(READERS[i].name, name);//更改姓名
                    printf("reader.id=%d\n", READERS[i].id);
                    puts(READERS[i].name);
                    printf("booklent.id=%d\n", READERS[i].booklent.id);
                    puts(READERS[i].booklent.name);
                    printf("booklentNum=%d\n", READERS[i].booklent.num);
                }
            }
            break;
        case 3://修改所借书籍
            printf("请输入借书卡卡号\n");
            int readerId;
            scanf("%d", &readerId);
            for (int i = 0; i < 1000; i++)
            {
                if (READERS[i].id == readerId)
                {
                    printf("新输入新的所借书目编号名称及数量\n");
                    int bookId, num;
                    char name[30];
                    scanf("%d", &bookId);
                    scanf("%s", name);
                    scanf("%d", &num);
                    READERS[i].booklent.id = bookId;
                    strcpy(READERS[i].booklent.name, name);
                    READERS[i].booklent.num = num;
                    printf("reader.id=%d\n", READERS[i].id);
                    puts(READERS[i].name);
                    printf("booklent.id=%d\n", READERS[i].booklent.id);
                    puts(READERS[i].booklent.name);
                    printf("booklentNum=%d\n", READERS[i].booklent.num);
                }
            }
            break;
        default:
            printf("输入不合法\n");
            break;
    }
    readerOutput();
}

//读者信息删除
void deleteReader()
{
    readerInput();
    char s1[30] = "have deleted";
    char s2[30] = "no book lent";
    printf("请输入想删除的借书卡卡号\n");
    int id;
    scanf("%d", &id);
    for (int i = 0; i < 1000; i++)
    {
        if (READERS[i].id == id)
        {
            READERS[i].id = 0;
            strcpy(READERS[i].name, s1);
            strcpy(READERS[i].booklent.name, s2);
            READERS[i].booklent.id = 0;//删除id
            READERS[i].booklent.num = 0;//删除数量
        }
    }
    readerOutput();
}

//读者信息增加
void addReader()
{
    int n = readerInput();
    printf("请输入增加的读者姓名\n");
    char s[30] = "no book lent";
    
    scanf("%s", s);
    READERS[n + 1].id = n + 1;
    strcpy(READERS[n + 1].name, s);
    READERS[n + 1].booklent.id = 0;
    strcpy(READERS[n + 1].booklent.name, s);
    READERS[n + 1].booklent.num = 0;
    readerOutput();
}

//查找某本书被谁借走
int searchId()
{
    readerInput();
    printf("请输入所需查找图书编号\n");
    int id, flag = 0;
    scanf("%d", &id);
    for (int i = 0; i < 1000; i++)
    {
        if (READERS[i].booklent.id == id)
        {
            printf("该书已被%d%s借走\n", READERS[i].id, READERS[i].name);
            flag = 1;
            break;
        }
    }
    if (flag == 0)
    {
        printf("该书未被借阅\n");
    }
    return flag;
}

//修改图书信息
void reviseBook()
{
    bookInput();
    int id, num, choice;
    char s[30];
    printf("请选择修改方式\n");
    printf("1.修改编号下的书籍\n");
    printf("2.修改某种数量\n");
    scanf("%d", &choice);
    if (choice == 1)
    {
        printf("请输入想要更改的图书编号\n");
        scanf("%d", &id);
        printf("请输入更改的书名\n");
        scanf("%s", s);
        printf("请输入该种书现有数量\n");
        scanf("%d", &num);
        for (int i = 0; i < 1000; i++)
        {
            if (BOOKS[i].id == id)
            {
                strcpy(BOOKS[i].name, s);
                BOOKS[i].num = num;
                printf("finish\n");
            }
        }
    }
    else if (choice == 2)//修改数量
    {
        printf("请输入想要更改的书名\n");
        scanf("%s", s);
        for (int i = 0; i < 1000; i++)
        {
            if (strcmp(s, BOOKS[i].name) == 0)
            {
                printf("请输入该书现有数量\n");
                scanf("%d", &num);
                BOOKS[i].num = num;
            }
        }
    }
    else
    {
        printf("输入无效\n");
    }
    bookOutput();
}

void addBook()
{
    int n = bookInput();
    printf("请输入增加的书目\n");
    char s[30];
    int k = 0;
    scanf("%s", s);
    BOOKS[n + 1].id = n + 1;//增加id
    strcpy(BOOKS[n + 1].name, s);
    for (int i = 0; i < 1000; i++)
    {
        if (strcmp(BOOKS[i].name, s) == 0)//已存在
        {
            k = 1;
            BOOKS[i].num++;
            BOOKS[n + 1].num = BOOKS[i].num;//同名都统一数量
        }
    }
    if (k == 0)//不存在
    {
        BOOKS[n + 1].num = 1;
    }
    bookOutput();
}

//图书删除
void deleteBook()
{
    bookInput();
    printf("请输入想要删除的图书编号\n");
    int id;
    scanf("%d", &id);
    for (int i = 0; i < 1000; i++)
    {
        if (BOOKS[i].id == id)//找到编号
        {
            for (int j = 0; j < 1000; j++)
            {
                if (strcmp(BOOKS[i].name, BOOKS[j].name) == 0)
                {
                    BOOKS[j].num--;//找其他书
                }
            }
            for (int j = 0; j < 30; j++)
            {
                BOOKS[i].name[j] = '\0';//删除名称
            }
            BOOKS[i].num = 0;//数量归0
        }
    }
    bookOutput();
}

//查找图书
void searchBook()
{
    readerInput();
    bookInput();
    char name[30];
    printf("请输入要查找的图书名称\n");
    scanf("%s", name);
    int flag = 0, temp = 0;
    for (int i = 0; i < 1000; i++)
    {
        if (strcmp(name, BOOKS[i].name) == 0)//找到书
        {
            for (int j = 0; j < 1000; j++)
            {
                temp = 0;
                if (READERS[j].booklent.id == BOOKS[i].id)//书已被借走
                {
                    temp = 1;
                    break;
                }
            }
            if (temp == 0)
            {
                printf("可借阅的图书编号%d\n", BOOKS[i].id);
            }
            flag = 1;
        }
    }
    if (flag == 0)
        printf("该书不存在\n");
    if (temp == 1)
        printf("该种书目已经全部被借走");
}

//借书
void borrowBook()
{
    readerInput();
    bookInput();
    printf("请输入借书卡卡号\n");
    int idcard, flag = 0, temp;
    int i = 0;
    
    scanf("%d", &idcard);
    for (i = 0; i < 1000; i++)
    {
        if (READERS[i].id == idcard)//匹配到卡
        {
            flag = 1;
            if (READERS[i].booklent.id == 0)//是否借过书
            {
                printf("借书卡存在,请输入所借图书编号\n");
                int id;
                scanf("%d", &id);
                temp = searchId();//判断该书是否未被借阅
                if (temp == 0)
                {
                    for (int j = 0; j < 1000; j++)
                    {
                        if (id == BOOKS[j].id)//匹配到要借的书
                        {
                            strcpy(READERS[i].booklent.name, BOOKS[j].name);//复制到借书名称
                            BOOKS[j].num = BOOKS[j].num - 1;//书数量-1
                            READERS[i].booklent.num = BOOKS[j].num;//所借同名书的总数给过去
                            for (int k = 0; k < 1000; k++)
                            {
                                if (strcmp(BOOKS[j].name, BOOKS[k].name) == 0)
                                {
                                    BOOKS[k].num = BOOKS[j].num;//改正同名书的数量
                                }
                            }
                        }
                    }
                    for (int j = 0; j < 1000; j++)
                    {
                        if (strcmp(READERS[i].booklent.name, READERS[j].booklent.name) == 0)
                        {
                            READERS[j].booklent.num = READERS[i].booklent.num;//改正所有借书的数量
                        }
                        if (strcmp(READERS[i].booklent.name, BOOKS[j].name) == 0)
                        {
                            BOOKS[j].num = READERS[i].booklent.num;
                        }
                    }
                    READERS[i].booklent.id = id;
                    printf("借书成功\n");
                    printf("reader.id=%d\n", READERS[i].id);
                    puts(READERS[i].name);
                    printf("booklent.id=%d\n", READERS[i].booklent.id);
                    puts(READERS[i].booklent.name);
                    printf("booklentnum=%d\n", READERS[i].booklent.num);
                }
                else
                {
                    printf("请重写查找未被借阅的图书编号后借书\n");
                }
            }
            else
                printf("清先还书再进行借阅\n");
        }
    }
    if (flag == 0)
    {
        printf("借阅卡不存在\n");
    }
    readerOutput();
    bookOutput();
}

//还书
void returnBook()
{
    readerInput();
    printf("请输入您要还的图书编号\n");
    int id, flag = 0;
    char s[30] = "no book lent";
    scanf("%d", &id);
    for (int i = 0; i < 1000; i++)
    {
        if (READERS[i].booklent.id == id)//匹配到
        {
            for (int j = 0; j < 1000; j++)
            {
                if (strcmp(READERS[i].booklent.name, BOOKS[j].name) == 0)//书库里书匹配到自己所借
                {
                    BOOKS[j].num++;
                }
            }
            READERS[i].booklent.id = 0;//清空借书
            strcpy(READERS[i].booklent.name, s);//清空书名
            READERS[i].booklent.num = 0;//清空书的数量
            printf("还书成功\n");
            flag = 1;
        }
    }
    if (flag == 0)
    {
        printf("无法查询此书\n");
    }
    readerOutput();
    bookOutput();
}

/**
 主函数
 */
int main(int argc, char **argv)
{
    printf("Please input the 1.filename 2.-a: staff / -u: reader 3.Name.\n");
    if (argc != 3)//判断参数数量
    {
        printf("Please input the 1.filename 2.-a: staff / -u: reader 3.Name Again.\n");
        exit(0);
    }
    if ((strcmp(argv[1], "-a")) == 0)//接管理员
    {
        stuffMenu();
    }
    else if (strcmp(argv[1], "-u") == 0)//接读者菜单
    {
        readerMenu();
    }
    return 0;
}

void readerMenu()//读者菜单
{
    int choice = 0;
    
    while (1)
    {
        printf("欢迎使用自助系统\n");
        printf("      1.借书\n");
        printf("      2.还书\n");
        printf("      3.查询\n");
        printf("      0.退出\n");
        scanf("%d", &choice);
        switch (choice)
        {
            case 1:
                borrowBook();
                break;
            case 2:
                returnBook();
                break;
            case 3:
                searchBook();
                break;
            case 0:
                exit(0);
                break;
            default:
                break;
        }
    }
}
void stuffMenu()//管理员菜单
{
    int choice = 0;
    
    while (1)
    {
        printf("欢迎使用信息录入系统\n");
        printf("       1.录入读者信息\n");
        printf("       2.修改读者信息\n");
        printf("       3.删除读者信息\n");
        printf("       4.录入图书信息\n");
        printf("       5.修改图书信息\n");
        printf("       6.删除图书信息\n");
        printf("       7.查询图书借阅信息\n");
        printf("       0.退出\n");
        scanf("%d", &choice);
        
        switch (choice)
        {
            case 1:
                addReader();
                break;
            case 2:
                reviseReader();
                break;
            case 3:
                deleteReader();
                break;
            case 4:
                addBook();
                break;
            case 5:
                reviseBook();
                break;
            case 6:
                deleteBook();
                break;
            case 7:
                searchId();
                break;
            case 0:
                exit(0);
                break;
            default:
                break;
        }
    }
}
