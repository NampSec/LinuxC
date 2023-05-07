/*************************************************
Copyright © yang. 1998-2023. All rights reserved.
File name: pratise3.c
Author: yang
Version: 1.0
Description: 解二元一次方程组,暂时只适用于有实数解,对于有虚数解等到结构体在继续补充
Others: 
Log: 2023-04-15 1.0 yang create
*************************************************/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
/*
*@ Description: 二元一次方程组求解,只适用于有实数解
* @param 1: a
* @param 2: b
* @param 3: c
* @return: void
*/

static void resolve_equation(double a, double b, double c);

static void resolve_equation(double a, double b, double c){
    double s = pow(b, 2) - 4 * a*c < 0;
    double t1 = 0;
    double t2 = 0;
    if(s < 0)
    {
        fprintf(stderr,"Error:the equation does not has answer\n");
        exit(1);
    }
    t1 = (-b + sqrt(s))/(2.0*a);
    t2 = (-b - sqrt(s))/(2.0*a);
    printf("the answer is: t1 = %lf\tt2 = %lf\n",t1,t2);
}

int main(void)
{
    int input_num = 0;
    double a,b,c;
    printf("please input the a,b,c of the equation\n");
    input_num = scanf("%lf%lf%lf",&a,&b,&c);
    if(input_num != 3)
    {
        fprintf(stderr,"the input format is incorrect\n");
        exit(1);
    }
    resolve_equation(a,b,c);
    return 0;
}

