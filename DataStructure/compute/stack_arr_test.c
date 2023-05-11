#include "stack_arr.h"
#include <stdlib.h>
#include <stdio.h>
int main(void)
{
    STACK *stack = NULL;
    datatype data = 0;
    stack = stack_create();
    if (stack == NULL)
        exit(1);
    while (!stack_push(stack, &data))
    {
        data++;
    }
    while(!stack_pop(stack, &data))
    {
        printf("stack is %d\n",data);
    }
    stack_destroy(stack);
}
