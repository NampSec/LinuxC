/*************************************************
Copyright © yang. 1998-2023. All rights reserved.
File name: queue.c
Author: yang
Version: 1.0
Description: 本文件作为一个简单的循队列，仅仅实现创建队列，插入点，和销毁队列这三种功能
Others: 
Log: 2023-05-26 1.0 yang create
*************************************************/

#include "queue.h"
#include <stdlib.h>
#include <stdio.h>

void add_point(point **qu, int x, int y)
{
    point *p = NULL;
    point *cur = NULL;
    p = (point *)malloc(sizeof(point));
    if (p == NULL)  return; // malloc failed
    p->next = NULL;
    p->x = x;
    p->y = y;
    if (*qu == NULL) // 如果为NULL，用二级指针改变头节点
    {
        *qu = p;
        return ;
    }
    cur = (*qu);
    while(cur->next != NULL)
    {
        cur = cur->next;
    }
    cur->next = p;
}
void destroy_queue(point *qu)
{
    point *cur = qu, *next;
    if(cur == NULL) return;
    while(cur->next != NULL)
    {
        next = cur->next;
        free(cur);
        cur = next;
    }
    free(cur);
}
void print_queue(point *qu)
{
    point *cur = qu, *next;
    if(cur == NULL) return;
    while(cur->next != NULL)
    {
        next = cur->next;
        printf("x: %d, y: %d\n", cur->x, cur->y);
        cur = next;
    }
    printf("x: %d, y: %d\n", cur->x, cur->y);
}
