/*************************************************
Copyright © yang. 1998-2023. All rights reserved.
File name: queue_arr.c
Author: yang
Version: 1.0
Description: 一个通用的队列库，其中队列的头节点不能存放数据，判断队列为空：head == tail 判断队列为满的条件：(head + 1) % QUEUE_SIZE == tail
Others: 
Log: 2023-05-08 1.0 yang create
*************************************************/
#include "queue_arr.h"
#include <stdlib.h>
#include <stdio.h>
queue *queue_create(void)
{
    queue *sq = (queue *)malloc(sizeof(queue));
    if(sq == NULL)
        return NULL;
    sq->head = 0;
    sq->tail = 0;
    return sq;
}
int is_queue_empty(queue *sq)
{
    return sq->tail - sq->head;
}
int is_queue_full(queue *sq)
{
    return ((sq->tail + 1) % QUEUE_MAX_SIZE) - sq->head;

}
int queue_enqueue(queue *sq, datatype *data)
{
    if(!is_queue_full(sq))
        return -1;
    sq->tail = (sq->tail + 1) % QUEUE_MAX_SIZE;
    sq->data[sq->tail] = *data;
    return 0;
}
int queue_dequeue(queue *sq, datatype *data)
{
    if(!is_queue_empty(sq))
        return -1;
    sq->head = (sq->head + 1) % QUEUE_MAX_SIZE;
    *data = sq->data[sq->head];
    return 0;
}
int queue_travel(queue *sq)
{
    if(!is_queue_empty(sq))
        return -1;
    int i = (sq->head + 1) % QUEUE_MAX_SIZE;
    while(i != sq->tail)
    {
        printf("sq->data[%d]\n", sq->data[i]);
        i = (i + 1) % QUEUE_MAX_SIZE;
    }
    printf("sq->data[%d]\n", sq->data[i]);
    return 0;
}
void queue_destroy(queue *sq)
{
    free(sq);
}
void queue_clear(queue *sq)
{
    sq->head = sq->tail;
}