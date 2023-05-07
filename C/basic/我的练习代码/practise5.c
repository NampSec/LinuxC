/*************************************************
Copyright © yang. 1998-2023. All rights reserved.
File name: practise5.c
Author: yang
Version: 1.0
Description: 流程控制专题练习
1.从终端读入数据直到输入0为止,计算输入偶数的个数及其平均值.计算奇数的个数以及其平均值.
2.从终端读入字符,对其中的元音字符进行统计
3.fibonacci数列的前40项,不能使用数组
4.输出九九乘法表
5.百钱买鸡:公鸡5元,母鸡3元,三只小鸡1元,问能买到的各个鸡的个数
6.求出1000以内的水仙花的个数:例如153 = 1 + 125 + 27
7.求出1000以内的质数
8.在终端上实现以下输出:
    ABCDEF
    BCDEF
    CDEF
    DEF
    EF
    F
9.终端输出钻石
  *
 * *
* * *
 * *
  *
10.终端输入N个数,以字符q/Q终止,输出总和
11.从半径1开始,输出园的面积,直到园的面积大于100为止
Others:
Log: 2023-04-15 1.0 yang create
*************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
 *@ Description: 1.从终端读入数据直到输入0为止,计算输入偶数的个数及其平均值.计算奇数的个数以及其平均值.
 * @return: void
 */
static void practise_1(void)
{
    int input_value = 0;
    int scanf_accept_num = 0;
    int sum_odd = 0;
    int sum_even = 0;
    int num_of_odd = 0;
    int num_of_even = 0;
    do
    {

        scanf_accept_num = scanf("%d", &input_value);
        if (scanf_accept_num != 1)
        {
            fprintf(stderr, "the input value must be integer\n");
            exit(1);
        }
        if (input_value != 0)
        {
            if (input_value % 2 == 0)
            {
                num_of_even++;
                sum_even += input_value;
            }
            else if (input_value % 2 == 1)
            {
                num_of_odd++;
                sum_odd += input_value;
            }
            else
            {
                fprintf(stderr, "unknown error\n");
                exit(1);
            }
        }
        else
        {
            // the input is 0,just skip it do nothing
        }

    } while (input_value != 0);
    printf("the number of even numbers is %d ,and average of it is %f\n", num_of_even, (float)sum_even / (float)num_of_even);
    printf("the number of odd numbers is %d ,and average of it is %f\n", num_of_odd, (float)sum_odd / (float)num_of_odd);
}

/*
 *@ Description: 2.从终端读入字符,对其中的元音字符进行统计
 * @return: void
 * @other: 为了防止gets/scanf导致的一些溢出和空格截断,此处采用动态内存分配getline
 */
static void practise_2(void)
{
    char *line = NULL;
    char *temp = NULL;
    size_t allocate_size = 0;
    int nread = 0;
    int nvowel = 0;
    if ((nread = getline(&line, &allocate_size, stdin)) != -1)
    {
        temp = line;
        while (*temp != '\0')
        {
            temp++;
            switch (*temp)
            {
            case 'a':
            case 'e':
            case 'i':
            case 'o':
            case 'u':
            case 'A':
            case 'E':
            case 'I':
            case 'O':
            case 'U':
                nvowel++;
                break;
            default:
                break;
            }
        }
        free(line);
    }
    else
    {
        fprintf(stderr, "getline failed\n");
        exit(1);
    }
    printf("the number of vowel characters is %d\n", nvowel);
}

/*
 *@ Description: fibonacci数列的前40项,不能使用数组
 * @return: void
 */
static void practise_3(void)
{
    int i = 0;
    int previous_1 = 1, previous_2 = 1;
    int next = 0;
    printf("%d  %d  ", previous_1, previous_2);
    for (i = 0; i < 40 - 2; i++)
    {
        next = previous_1 + previous_2;
        previous_1 = previous_2;
        previous_2 = next;
        printf("%d  ", next);
    }
    printf("\n");
}

/*
 *@ Description: 输出九九乘法表
 * @return: void
 */
static void practise_4(void)
{
    int col = 1, row = 1;
    for (row = 1; row <= 9; row++)
    {
        for (col = 1; col <= row; col++)
        {
            printf("%d  ", row * col);
        }
        printf("\n");
    }
}

/*
 *@ Description: 百钱买鸡:公鸡5元,母鸡3元,三只小鸡1元,问能买到的各个鸡的个数
 * @return: void
 */
#define COCK_PRICE (5)
#define HEN_PRICE (3)
#define NUM_CHICKEN_PER_YUAN (3)

static void practise_5(void)
{
    int x = 0, y = 0, z = 0;
    int remain_money;
    for (int x = 0;; x++)
    {
        if (100 - x * COCK_PRICE < 0)
        {
            break;
        }
        for (y = 0;; y++)
        {
            remain_money = (100 - x * COCK_PRICE - y * HEN_PRICE);
            if (remain_money >= 0)
            {
                z = remain_money * NUM_CHICKEN_PER_YUAN;
                if (x + y + z == 100)
                {
                    printf("COCK: %d  HEN: %d  CHICKEN: %d\n", x, y, z);
                }
            }
            else
            {
                break;
            }
        }
    }
}

/*
 *@ Description: 求出1000以内的水仙花的个数:例如153 = 1 + 125 + 27
 * @return: void
 */
static void practise_6(void)
{
    int num = 0;
    int x, y, z;
    for (num = 0; num < 1000; num++)
    {
        x = num / 100;
        y = (num - x * 100) / 10;
        z = num - x * 100 - y * 10;
        if (num == x * x * x + y * y * y + z * z * z)
        {
            printf("THE WATER FLOWER NUMBER IS :%d\n", num);
        }
    }
}

/*
 *@ Description: 求出1000以内的质数
 * @return: void
 */
static void practise_7(void)
{
    int num = 1;
    while (num < 1000)
    {

        int flag = 1;
        // 判断某个数是否为质数，只需要判断其的一半或者sqrt（num）即可
        for (int i = 2; i < num / 2; i++)
        {
            if (num % i == 0)
            {
                flag = 0;
            }
        }
        if (flag == 1)
        {
            printf("%d\n", num);
        }
        num++;
    }
}

/*
*@ Description:
在终端上实现以下输出:
    ABCDEF
    BCDEF
    CDEF
    DEF
    EF
    F
* @return:void
*/
#define STRINGSIZE (120)
#include <string.h>
static void practise_8(void)
{
    char string[STRINGSIZE] = "ABCDEF";
    int slen = strlen(string);
    int i = 0;
    while (i < slen)
    {
        printf("%s\n", string + i);
        i++;
    }
}

/*
*@ Description:
终端输出钻石
   *
  * *
 * * *
* * * * //
 * * *
  * *
   *
* @return: void
*/
static void practise_9(void)
{
    // row : 钻石排列的最中间行的’*‘个数
    int row = 0;
    int scanf_accept_num = 0;
    scanf_accept_num = scanf("%d", &row);
    if ((scanf_accept_num != 1) || (row % 2 == 0))
    {
        fprintf(stderr, "the input value must be an odd integer\n");
        exit(1);
    }
    for (int i = 1; i <= row * 2 - 1; i++)
    {
        // 先打印row - i - 1个空格
        int i_copy = i;
        if (i_copy > row)
        {
            i_copy = 2 * row - i;
        }
        for (int j = 0; j < row - i_copy; j++)
        {
            putchar(' ');
        }
        // 在打印i个’ *‘
        for (int j = 0; j < i_copy; j++)
        {
            putchar('*');
            putchar(' ');
        }
        putchar('\n');
    }
}

/*
 *@ Description: 终端输入N个数,以字符q/Q终止,输出总和
 * @return: void
 */
static void practise_10(void)
{
    int num = 0;
    int scanf_accept_num = 0;
    while (1)
    {
        scanf_accept_num = scanf("%d", &num);
        printf("%d\n", num);
        if ((scanf_accept_num != 1))
        {
            fprintf(stderr, "the input value must be an integer\n");
            exit(1);
        }
        #if 0
        if(getchar() == 'q' || getchar() == 'Q')
        {
            fprintf(stderr, "input exit\n");
            exit(1);
        }
        #endif
    }
}

int main(void)
{
    // practise_1();
    practise_10();
    return 0;
}