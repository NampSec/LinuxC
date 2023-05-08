/*    QUEUE_ARR    */
#ifndef __QUEUE_ARR_h__
#define __QUEUE_ARR_h__
#define QUEUE_MAX_SIZE (10)
typedef int datatype;
typedef struct
{
    int head;
    int tail;
    datatype data[QUEUE_MAX_SIZE];
}queue;
queue *queue_create(void);
int is_queue_empty(queue *sq);
int is_queue_full(queue *sq);
int queue_enqueue(queue *sq, datatype *data);
int queue_dequeue(queue *sq, datatype *data);
int queue_travel(queue *sq);
void queue_destroy(queue *sq);
void queue_clear(queue *sq);
#endif
