/*************************************************
Copyright © yang. 1998-2023. All rights reserved.
File name: clock_ball.c
Author: yang
Version: 1.0
Description: 这个版本的球钟用了链表形式的队列，而不是顺序存储的队列
Others: 
Log: 2023-05-11 1.0 yang create
*************************************************/


#include <stdio.h>
#include "stack_arr.h"
#include "queue_link.h"

#define BALL_COUNT_MAX (27)
struct ball
{
    int ball_index;
};
static int check_queue_sequence(queue *sq)
{
    node_list *node = sq->head.next;
    struct ball *b1, *b2;
    while(node->next != &sq->head)
    {
        b1 = (struct ball *)node->data;
        b2 = (struct ball *)node->next->data;
        if(b2->ball_index < b1->ball_index)
        {
            return 0;
        }
        node = node->next;
    }
    return 1;
}
int main(void)
{
    int time = 0;
    // Initialize the clock ball queue
    queue *queue = queue_create(sizeof(struct ball));
    struct ball ball_template;
    for (int i = 1; i <= BALL_COUNT_MAX; i++)
    {
        ball_template.ball_index = i;
        queue_enqueue(queue, &ball_template);
    }
    // Initialize the timer counter stacks
    STACK *stack_min = stack_create();
    STACK *stack_5min = stack_create();
    STACK *stack_hour = stack_create();
    // minite stack: 4 ,5minite stack:11 1hour stack: 11
    while (1)
    {
        struct ball ball_temp;
        queue_dequeue(queue, &ball_temp);
        datatype push_index = ball_temp.ball_index;
        datatype pop_template;
        time++;
        if (stack_min->top != 3)
        {
            stack_push(stack_min, &push_index);
        }
        else
        {
            while (is_stack_empty(stack_min))
            {
                stack_pop(stack_min, &pop_template);
                ball_template.ball_index = pop_template;
                queue_enqueue(queue, &ball_template);
            }
            if (stack_5min->top != 10)
            {
                stack_push(stack_5min, &push_index);
            }
            else
            {
                while (is_stack_empty(stack_5min))
                {
                    stack_pop(stack_5min, &pop_template);
                    ball_template.ball_index = pop_template;
                    queue_enqueue(queue, &ball_template);
                }
                if  (stack_hour->top != 10)
                {
                    stack_push(stack_hour, &push_index);
                }
                else
                {
                    while (is_stack_empty(stack_hour))
                    {
                        stack_pop(stack_hour, &pop_template);
                        ball_template.ball_index = pop_template;
                        queue_enqueue(queue, &ball_template);
                    }
                    queue_enqueue(queue, &ball_temp); // 每12个小时队列中满了27个球
                    if(check_queue_sequence(queue)) // 队列满了27个后检查队列程序
                        break;
                }
            }
        }
    }
    printf("the time is %d\n", time);
    return 0;
}
