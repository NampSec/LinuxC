/*************************************************
Copyright © yang. 1998-2023. All rights reserved.
File name: compute.c
Author: yang
Version: 1.0
Description: 表达式计算器，采用栈进行计算。首先对表达式进行入栈，在针对优先级对两个栈进行计算。
按照优先级来进行计算，栈底的优先级应该是最低的，栈顶的优先级最高。
操作符中括号的优先级最高，乘除法优先级一致，加减法优先级一致。
例如例子中的(3+4)*5,两个栈中分别为 ( + ) * 和 3 4 5
我们可以这样设计，每次遇到一个括号，括号右边的优先级加2，
Others: 该版本错误，遇到(3+4)*5可以正常计算，而对于(3+4)*5+(6+7)会报错
Log: 2023-05-09 1.0 yang create
*************************************************/

#include "stack_arr.h"
#include <stdio.h>
#include <stdlib.h>
int get_prior(int op);
int get_prior(int op)
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
        fprintf(stderr, "Invalid operation, line:%d\n",__LINE__);
        exit(1);
    }
}
//按照顺序进行计算,计算到栈为空或者遇到左括号为止
// 1代表已经不需要计算了
int compute(STACK *num, STACK *op)
{
    datatype n1, n2, temp;
    datatype result = 0;
    if(!is_stack_empty(op)) // 操作符为空时直接返回
    {
        return 1;
    }
    stack_pop(op, &temp);
    stack_pop(num, &n1);
    stack_pop(num, &n2);
    switch (temp)
    {
    case '+':
        result =  n1 + n2;
        break;
    case '-':
        result =  n1 - n2;
        break;
    case '*':
        result =  n1 * n2;
        break;
    case '/':
        result =  n1 / n2;    
        break;
    default:
        fprintf(stderr, "Invalid operation, line:%d\n", __LINE__);
        exit(1);
    }
    stack_push(num , &result);
    return 0;
    // 退栈运算再入栈
}
int main(void)
{
    char expression[] = "(3+4)*5";
    char *p = expression;
    STACK *num = stack_create();
    STACK *op = stack_create();

    if (op == NULL || num == NULL)
        exit(1);
    
    while(*p != '\0')
    {
        datatype temp;
        datatype push_op = *p;
        datatype assic_2_num = *p - '0';
        if (0 <= assic_2_num && assic_2_num <= 9)
        {
            stack_push(num, &assic_2_num);
        }
        else
        {
            if(push_op == '(') // 左括号直接入栈
            {
                stack_push(op, &push_op);
            }
            else if(push_op == ')') //对于右括号直接计算直到匹配到作括号
            {
                do
                {
                    compute(num, op);
                    stack_top(op, &temp);
                }while(temp != '(');
                stack_pop(op, &temp); // 丢弃左括号
            }
            else
            {
                stack_top(op, &temp);
                while(get_prior(push_op) <= get_prior(temp)) // 如果当前操作符优先级低于栈顶优先级，退栈运算再入栈
                {
                    compute(op, num);
                    stack_top(op, &temp);
                }
                stack_push(op, &push_op);
            }
        }
        p++;
    }
    while(compute(num, op));
    printf("the result is %d\n", num->data[0]);
    return 0;
}