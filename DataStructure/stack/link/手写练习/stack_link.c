#include "stack_link.h"
#include <stdlib.h>
#include <string.h>
static int cmp_op_stack(void * n1, void * n2);
static int cmp_op_stack(void * n1, void * n2)
{
    return 0;
}

STACK * stack_create(unsigned int size)
{
    STACK * stack = _llist_create(size);
    return stack;
}
void stack_destroy(STACK * stack)
{
    _llist_destroy(stack);
}
int stack_top(STACK * stack, void *data)
{
    void *data_src = NULL;
    data_src = _llist_find(stack, (void*)0, cmp_op_stack);
    memcpy(data, data_src, stack->size);
    return 0;
}
int stack_push(STACK * stack,void *data)
{
    return _llist_insert(stack, data, LLIST_FORWARD_INSERT);
}
int stack_pop(STACK * stack,void *data)
{
    return _llist_fetch(stack, (void *)0,cmp_op_stack,data);
}
void stack_travel(STACK * stack,void (*fuc)(void *data))
{
    _llist_travel(stack, fuc);
}