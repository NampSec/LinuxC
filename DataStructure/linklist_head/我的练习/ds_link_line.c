/*************************************************
Copyright © yang. 1998-2023. All rights reserved.
File name: ds_link_line.c
Author: yang
Version: 1.0
Description: 有头和无头链表的实现，无头节点没有创建这个函数
Others: 一般采用二级指针对有头链表进行创建，以及使用二级指针改变无头链表
Log: 2023-04-28 1.0 yang create
*************************************************/

#include "ds_link_line.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
*@ Description: 有头链表的创建
* @param 1: node二级指针
* @return: 0代表创建成功，1代表创建失败 
*/

int head_link_line_create(node ** me)
{
    (*me) = (node *)malloc(sizeof(node));
    if(*me == NULL)
        return (-1);
    (*me)->next = NULL;
    return 0;
}

/*
*@ Description: 非循环有头/无头链表删除
* @param 1: 指向头节点的指针
* @return: 0
*/

int head_link_line_destroy(node *me)
{
    
    node * p = NULL;
    node *q = NULL;
    p = me;
    q = p->next;
    while(p != NULL)
    {
        free(p);
        p = q;
        if(q != NULL)
            q = q->next;
    }
    return 0;
}
/*
*@ Description: 按照顺序插入，最后插入的在队列的尾部
* @param 1: 指向头节点的指针
* @param 2: 要插入的数据
* @return: 0代表插入成功，-1代表参数非法，-2代表插入失败
*/

int head_link_line_insert_end(node *me , datatype data)
{
    node * p;
    p = head_link_line_tail(me);
    p->next = (node *)malloc(sizeof(node));
    if(p->next == NULL)
        return -2;
    p->next->data = data;
    p->next->next = NULL;
    return 0;

}


/*
*@ Description: 按照顺序插入，最后插入的在队列的头部
* @param 1: 指向头节点的指针
* @param 2: 要插入的数据
* @return: 0代表插入成功，-1代表参数非法，-2代表插入失败
*/

int head_link_line_insert_head(node *me , datatype data)
{
    node * p = me;
    node * q = p->next;
    p->next = (node *)malloc(sizeof(node));
    if(p->next == NULL)
        return -2;
    p->next->data = data;
    p->next->next = q;
    return 0;

}

/*
*@ Description: 按照顺序插入，根据data的exist_status的值来进行排序，未update的放在最前面
* @param 1: 指向头节点的指针
* @param 2: 要插入的数据
* @return: 0代表插入成功，-1代表参数非法，-2代表插入失败
*/

int head_link_line_insert_order(node *me , datatype data)
{
    int response = 0;
    if (data.status == updated)
    {
        response = head_link_line_insert_end(me,data);
    }else
    {
        response = head_link_line_insert_head(me,data);
    }
    return response;
}


/*
*@ Description: 返回指向最后一个节点的指针
* @param 1: 指向头节点的指针
* @return: 指向最后一个节点的指针
*/

static node * head_link_line_tail(node * me)
{
    node *p  = me;
    while (p->next != NULL)
    {
        p = p->next;
    }
    return p;
    
}


