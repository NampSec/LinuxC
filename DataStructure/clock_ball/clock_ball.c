#include <stdio.h>
#include "stack_arr.h"
#include "queue_link.h"

#define BALL_COUNT_MAX (27)
struct ball
{
    int ball_index;
};
static int queue_is_empty(queue *sq)
{
    if (sq->head.next == &sq->head)
        return 1;
    else
        return 0;
}
int main(void)
{
    // Initialize the clock ball queue
    queue *queue = queue_create(sizeof(struct ball));
    struct ball ball_template;
    for (int i = 0; i < BALL_COUNT_MAX; i++)
    {
        ball_template.ball_index = i;
        queue_enqueue(queue, &ball_template);
    }
    // Initialize the timer counter stacks
    STACK *stack_min = stack_create();
    STACK *stack_5min = stack_create();
    STACK *stack_hour = stack_create();
    // minite stack: 4 ,5minite stack:11 1hour stack: 11
    while (!queue_is_empty(queue))
    {
        queue_dequeue(queue, &ball_template);
        datatype push_index = ball_template.ball_index;
        if (stack_min->top <= 3)
        {
            stack_push(stack_min, &push_index);
        }
        else if (stack_5min->top <= 10)
        {
            stack_push(stack_5min, &push_index);
        }
        else if  (stack_hour->top <= 10)
        {
            stack_push(stack_hour, &push_index);
        }
        else
        {
            
        }
        
    }
    

    return 0;
}
