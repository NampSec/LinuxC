/*    QUEUE_LINK    */
#ifndef __QUEUE_LINK_h__
#define __QUEUE_LINK_h__
#include "ds_llist_v2.h"

typedef LLIST queue;

queue *queue_create(unsigned int size);
void queue_destroy(queue *sq);

int queue_enqueue(queue *sq, void *data);
int queue_dequeue(queue *sq, void *data);

void queue_clear(queue *sq);
void queue_travel(queue *sq, void (*fuction)(void *data));



#endif
