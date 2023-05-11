/*    STACK_ARR    */
#ifndef __STACK_ARR_h__
#define __STACK_ARR_h__

#define STACKSIZE (10)
typedef int datatype;

typedef struct  
{
    datatype data[STACKSIZE];
    int top;
}STACK;
STACK * stack_create(void);
int is_stack_empty(STACK *stack);
int is_stack_full(STACK *stack);
void stack_destroy(STACK * stack);
int stack_top(STACK * stack, datatype *data);
int stack_push(STACK * stack,datatype *data);
int stack_pop(STACK * stack,datatype *data);

#endif
