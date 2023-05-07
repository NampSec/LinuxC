/*************************************************
Copyright © yang. 1998-2023. All rights reserved.
File name: practise4.c
Author: yang
Version: 1.0
Description: 流程控制专题练习一
A以每年百分之10的单利息投资100美元,B以每年百分之5的复利息投资100美元,问什么时候B会超过A.并显示此时A,B的各自资产总额.
单利息:本金不会累加.
复利息:本金会不断累加得到的利息.
Others: 
Log: 2023-04-15 1.0 yang create
*************************************************/
#include <stdio.h>
#include <stdlib.h>

#define A_GROWTH_RATE (0.1)
#define B_GROWTH_RATE (0.05)

int main(void)
{
    float a_money = 100;
    float b_money = 100;
    int i = 0;
    do
    {
        a_money += 100 * (A_GROWTH_RATE);
        b_money *= (1 + B_GROWTH_RATE);
        i++;

    }while (b_money <= a_money);
    printf("a_money = %f,b_money = %f\n", a_money,b_money);
    printf("the year is %d\n",i);

    return 0;
}

