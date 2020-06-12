//
//  main.c
//  no2_1
//
//  Created by 谢容海 on 2020/6/11.
//  Copyright © 2020 谢容海. All rights reserved.
//

/**
 3.    简单数据结构-堆栈模拟
 a)    涉及知识点：内存管理、结构体定义、基本数据结构
 b)    要求：
 编写一个程序模拟堆栈，要求能够模拟、入栈、出栈、返回栈顶元素等基本操作。栈中元素可用整数代替。不能使
 用C++模板库预定义的类型。程序运行中可输入多组入栈、出栈操作，每次操作后展示栈中元素。
 */
#include <stdio.h>
#include <stdlib.h>
#define M 50 //设栈中元素个数为50
#define T 1
#define F 0

typedef struct//定义结构体
{
    int elem[M];
    int top;
} SeqStack;

/*===============各个子函数的定义===============*/
int init(SeqStack *stack);                 //初始化顺序栈
void push(SeqStack *stack, int n);         //顺序栈进栈运算
void pop(SeqStack *stack);                 //顺序栈出栈运算
int getTop(SeqStack *stack, int *value); //读取栈顶元素
void show(SeqStack *value);                 //展示栈中当前元素

int main()
{
    int n;
    SeqStack *stack;
    stack = (SeqStack *)malloc(sizeof(SeqStack)); //初始化，分配空间
    int a;
    int *value = &a;
    int choice;
    while (1)
    {
        printf("==============请输入你的选择=================\n");
        printf("              选择 1:栈初始化\n");
        printf("              选择 2:入栈\n");
        printf("              选择 3:出栈\n");
        printf("              选择 4:读取栈顶元素\n");
        printf("              选择 0:退出\n\n");
        scanf("%d", &choice);
        switch (choice)
        {
            case 1:
                (init(stack) == 1) ? printf("初始化成功\n") : printf("初始化失败\n");
                show(stack);
                break;
            case 2:
                printf("请输入您想输入元素的个数\n");
                scanf("%d", &n);
                push(stack, n);//压栈
                show(stack);
                break;
            case 4:
                pop(stack);//弹栈
                show(stack);
                break;
            case 0:
                (getTop(stack, value) == 1) ? printf("栈顶元素是:  %d\n", *value) : printf("这是个空栈！！！\n");//返回栈顶元素
                show(stack);
                break;
            default:
                printf("错误！\n");
                exit(0);
                break;
        }
    }
    return 0;
}
/*===================各个子函数的实现=====================*/
int init(SeqStack *stack) //初始化顺序栈
{
    if (stack != NULL)
    {
        stack->top = -1; //stack指针指向top成员，置为空栈
        return T;
    }
    else
        return F;
}

void push(SeqStack *stack, int n) //进栈，将元素压入栈中
{
    int i, n2;
    if (((stack->top) + n) <= M - 1) //压入栈中的元素不能超过栈的最大存储
    {
        printf("请依次输入栈元素:\n");
        for (i = 0; i < n; i++)
        {
            scanf("%d", &n2);
            stack->top++;//栈元素数量增加
            stack->elem[stack->top] = n2;
        }
        printf("栈空间不足\n");
    }
    else
    {
        printf("栈空间不足\n");
    }
}

void pop(SeqStack *stack)//获取栈顶元素
{
    int a;
    if(stack->top==-1)
    {
        printf("栈为空！！\n");//栈为空操作失败
    }
    else{
        a=stack->elem[stack->top];//取出栈顶元素
        stack->top--;
        printf("栈顶元素%d出栈成功.\n",a);//出栈成功
    }
}

int getTop(SeqStack *stack,int *value)//获取栈顶元素
{
    if(stack->top==-1)
    {
        return F;//栈为空，操作失败
    }
    else
    {
        *value=stack->elem[stack->top];//读取栈顶元素成功
        return T;
    }
}

void show(SeqStack *stack)//展示栈中元素
{
    int i;
    if(stack->top==-1)
    {
        printf("目前栈为空\n");
    }
    else
    {
        printf("目前从栈底到栈顶元素依次为:\n");
        for(i=0;i<=stack->top;i++)
        {
            printf("%d ",stack->elem[i]);
        }
        printf("\n");
    }
}
