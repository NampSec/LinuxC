/*************************************************
Copyright © yang. 1998-2023. All rights reserved.
File name: practise2.c
Author: yang
Version: 1.0
Description: 嵌入式C专题一练习二
Others:
Log: 2023-04-15 1.0 yang create
*************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
static double calc_triangle_area(double a, double b, double c);
/*
 *@ Description: 由三角形三边获取三角形的面积
 * @param 1:a
 * @param 2:b
 * @param 3:c
 * @return: 三角形的面积
 */
static double calc_triangle_area(double a, double b, double c)
{
    double area = 0;
    double s = 0;
    int flag = 0;
    flag = ((a + b) > c ? (a + c > b ? (b + c > a ? 1:0) : 0) : 0);
    if (!flag)
    {
        fprintf(stderr,"the parameter error,please check\n");
        exit(1);
    }
    s = (1.0 / 2.0) * (a + b + c);
    area = sqrt(s * (s - a) * (s - b) * (s - c));
    return area;
}

int main(void)
{
    int input_num = 0;
    double a, b, c;
    double area = 0;
    printf("pleasure enter the triangle a,b,c\n");
    input_num  = scanf("%lf%lf%lf", &a, &b, &c);
    if(input_num != 3)
    {
        fprintf(stderr,"the triangle parameters error\n");
        exit(1);
    }
    area = calc_triangle_area(a, b, c);
    printf("triangle area: %f\n", area);
    return 0;
}