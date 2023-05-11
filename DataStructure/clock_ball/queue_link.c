#include "queue_link.h"
static int queue_cmp(void *a, void *b)
{
    return 0;
}

queue * queue_create(unsigned int size)
{
    queue *sq = _llist_create(size);
    return sq;
}
void queue_destroy(queue *sq)
{
    _llist_destroy(sq);
}

int queue_enqueue(queue *sq, void *data)
{
    return _llist_insert(sq, data, LLIST_BACKWARD_INSERT);
}
int queue_dequeue(queue *sq, void *data)
{
    return _llist_fetch(sq, (void *)0, queue_cmp, data);
}

void queue_clear(queue *sq)
{
    while (sq->head.next != &sq->head)
    {
        _llist_remove(sq, (void *)0, queue_cmp);
    }
    
}
void queue_travel(queue *sq, void (*fuction)(void *data))
{
    _llist_travel(sq, fuction);
    
}