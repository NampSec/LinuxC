/*    STACK_LINK    */
#ifndef __STACK_LINK_h__
#define __STACK_LINK_h__
#include "ds_llist_v2.h"
typedef LLIST STACK;



STACK * stack_create(unsigned int size);
void stack_destroy(STACK * stack);
int stack_top(STACK * stack, void *data);
int stack_push(STACK * stack,void *data);
int stack_pop(STACK * stack,void *data);
void stack_travel(STACK * stack,void (*fuc)(void *data));
#endif
