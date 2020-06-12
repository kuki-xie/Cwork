//
//  main.c
//  no2_2
//
//  Created by 谢容海 on 2020/6/11.
//  Copyright © 2020 谢容海. All rights reserved.
//

/**
 4.    复杂数据结构-动态链表
a)    涉及知识点：内存管理、结构体定义、指针运用、函数
b)    要求：
链表是一种重要的数据结构，需要动态的进行存储分配，要求通过函数分别实现动态链表的建立、结点的插入、结点的删除以及链表的输出。
*/
#include<stdio.h>
#include<stdlib.h>
//定义结构体
typedef struct node
{
    int data;//int类型的data
    struct node*next;//结构体本度身类型的指针next;
}*list ,node;//声明一个struct node结构体类型的结构体变量;声明一个struct node结构体类型的指针变量

list init()//链表初始化
{
    list head=(list)malloc(sizeof(node));//头结点申请地址
    if (!head) {
        printf("动态内寸分配失败！\n");
        exit(0);
    }
    head->next=NULL;//next下一个结构体变量地址和data当前这个结构体变量的数据
    printf("链表初始化成功\n");
    return head;
}
//头插法建立链表
void create(list l,int a[],int n)
{
    int i;
    list p,q;//两个指针
    q=l;
    for(i=0;i<n;i++)
    {
        p=(list)malloc(sizeof(node));//创建新结点p
        p->data=a[i];//新结点数值域存储a[i]
        p->next=q->next;//使p,q下一个结点位置相同
        q->next=p;//把p结点插入到q结点后
        q=p;//使q成为最后一个节点
    }
    printf("链表建立成功！\n");
}

void print(list head)//输出
{
    list p=head->next;//p为头结点下一个结点
    printf("打印链表:\n");
    while (p)
    {
        printf("%d",p->data);
        p=p->next;//p指向下一个结点
    }
    printf("\n");
}

int insert(list head,int data1,int data2)
{
    list p=head->next,q;
    while(p)
    {
        if(p->data==data1)
        {
            q=(list)malloc(sizeof(node));//创建新结点
            q->data=data2;
            q->next=p->next;//使p,q下一个结点位置相同
            p->next=q;//q结点插到q之后
            return 1;
        }
        p=p->next;//p指向下一个结点
    }
    return 0;
}

//链表删除
int delete(list head,int data)
{
    list p=head,q;
    while(p->next)//依次往后读
    {
        if(p->next->data==data)//找到相符
        {
            q=p->next;//q指针指向p后方
            p->next=q->next;//p,q指针下一结点位置相同
            free(q);
            return 1;
        }
        p=p->next;//p向后
    }
    return 0;
}

int destory(list head)
{
    if(head)
    {
        list p=head->next,q;
        while(p)
        {
            q=p->next;//q指向p后
            free(q);
            p=q;//p成为后一个结点
        }
        free(head);
        return 1;
    }
    return 0;
}

//求链表长度
int listLength(list head)
{
    int i=0;
    list p=head->next;
    while(p)
    {
        i++;
        p=p->next;
    }
    return i;
}

//判断链表是否为空
int isEmpty(list head)
{
    if (head->next) {
        head->next=NULL;
        return 1;
    }
    return 0;
}

int main()
{
    list head=init();//链表初始化
    int length;
    if (isEmpty(head)) {//判断是否为空
        length=listLength(head);
        printf("当前链表为空表，长度为%d\n",length);
    }
    
    int n,a[100],i;
    printf("请输入数字n:\n");
    scanf("%d",&n);
    printf("请输入%d个数字建立链表:\n",n);
    for (i=0; i<n; i++) {
        scanf("%d",&a[i]);
    }
    
    create(head, a, n);//创建链表
    print(head);//输出链表
    
    int insertNum,newNode;
    printf("请输入要插入的位置的结点和插入的结点:\n");
    scanf("%d %d",&insertNum,&newNode);
    //插入结点
    if(insert(head, insertNum, newNode))
    {
        printf("插入成功!\n");
        print(head);
    }
    else{
        printf("插入失败！\n");
    }
    int deleteNum;
    printf("请输入要删除的结点:\n");
    scanf("%d",&deleteNum);
    //删除结点
    if(delete(head, deleteNum))//根据返回值判断是否成功
    {
        printf("删除成功！\n");
        print(head);
    }
    else
    {
        printf("删除失败！\n");
    }
    //销毁链表，结束
    if(destory(head)){
        printf("链表销毁成功！\n");
    }
    return 0;
}
