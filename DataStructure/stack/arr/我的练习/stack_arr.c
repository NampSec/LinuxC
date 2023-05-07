/*************************************************
Copyright © yang. 1998-2023. All rights reserved.
File name: stack_arr.c
Author: yang
Version: 1.0
Description: 用于顺序存储的栈的库
Others: 一般来说用0代表该函数为真，而非零代表函数为假，因为0对应false只有一个值，而true对应非零有很多值。
Log: 2023-05-07 1.0 yang create
*************************************************/

#include "stack_arr.h"
#include <stdlib.h>


/*
*@ Description: 判断栈是否为空
* @param 1: 指向栈的指针
* @return: 0代表栈为空，其他值代表栈不为空
*/
int is_stack_empty(STACK *stack)
{
    return stack->top + 1;
}
/*
*@ Description: 判断栈是否已满
* @param 1: 指向栈的指针
* @return: 0代表已满，其他值代表未满
*/
int is_stack_full(STACK *stack)
{
    return (STACKSIZE -1 - stack->top);
}
STACK * stack_create(void)
{
    STACK *stack = (STACK *)malloc(sizeof(STACK));
    if (stack == NULL)
    {
        return NULL;
    }
    stack->top = -1;
    return stack;
    
}
void stack_destroy(STACK * stack)
{
    free(stack);
}
int stack_top(STACK * stack, datatype *data)
{
    if(!is_stack_empty(stack))
        return -1;
    *data = stack->data[stack->top];
    return 0;
}
int stack_push(STACK * stack,datatype *data)
{
    if(!is_stack_full(stack))
        return -1;
    stack->data[++stack->top] = *data;
    return 0;
}
int stack_pop(STACK * stack,datatype *data)
{
    if(!is_stack_empty(stack))
        return -1;
    *data = stack->data[stack->top--];
    return 0;
}