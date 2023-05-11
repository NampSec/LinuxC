/*************************************************
Copyright © yang. 1998-2023. All rights reserved.
File name: compute_v2.c
Author: yang
Version: 2.0
Description: 2.0版本的计算器
Others: 
Log: 2023-05-10 2.0 yang create
*************************************************/
#include "stack_arr.h"
#include <stdlib.h>
#include <stdio.h>
static void compute(STACK *num, datatype * op)
{
    datatype n1, n2, n;
    stack_pop(num, &n2);
    stack_pop(num, &n1);
    switch (*op)
    {
    case '+':
        n = n1 + n2;
        break;
    case '-':
        n = n1 - n2;
        break;
    case '*':
        n = n1 * n2;
        break;
    case '/':
        n = n1 / n2;
        break;
    default:
        exit(1);
    }
    stack_push(num, &n);
}
void deal_bracket(STACK *num, STACK *op)
{
    datatype old_op;
    stack_top(op, &old_op);
    while(old_op != '(')
    {
        stack_pop(op, &old_op);
        compute(num, &old_op);
        stack_top(op, &old_op);
    }
    stack_pop(op, &old_op); // 去掉左边括号
}
static int get_pri(int op)
{
    switch (op)
    {
    case '(':
        return 0;
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    default:
        exit(1);
    }
}
static void deal_op(STACK *num, STACK *sop, int op)
{
    datatype old_op;
    if(!is_stack_empty(sop) || op == '(') // 如果运算符栈为空或者为括号，直接入栈
    {
        stack_push(sop, &op);
        return;
    }
    stack_top(sop, &old_op);
    if( get_pri(op) > get_pri(old_op))
    {
        stack_push(sop, &op);
        return ;
    }
    while( get_pri(op) <= get_pri(old_op) )
    {
        stack_pop(sop, &old_op);
        compute(num, &old_op);
        if(!is_stack_empty(sop))
            break;
        stack_top(sop, &old_op);
    }
    stack_push(sop, &op);

}
int main(void)
{
    STACK *num = stack_create();
    STACK *op = stack_create();
    if (num == NULL || op == NULL)
        exit(1);

    char str[] = "(11+3)*2-5+10-(3+5)*2";
    int i = 0;
    int value = 0;
    int flag = 0;
    datatype pop_value;
    while (str[i] != '\0') 
    {
        if (str[i] >= '0' && str[i] <= '9')
        {
            value = value * 10 + (str[i] - '0');
            flag = 1;
            /* code */
        }
        else // is a op
        {
            if(flag)
            {
                stack_push(num, &value);
                flag = 0;
                value = 0;
            }
            if(str[i] == ')')
            {
                deal_bracket(num, op);
            }
            else
            {
                deal_op(num, op , str[i]);
            }

        }
        i++;
    }
    
    if(flag)
        stack_push(num, &value);
    while (is_stack_empty(op))
    {
        stack_pop(op, &pop_value);
        compute(num, &pop_value);
    }
    
    printf("the result is %d\n", num->data[0]);
    stack_destroy(num);
    stack_destroy(op);
    return 0;
}