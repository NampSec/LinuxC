#include "queue_arr.h"
#include <stdlib.h>
#include <stdio.h>
int main(void)
{
    queue *sq;
    datatype dat = 0;

    sq = queue_create();
    if(sq == NULL)
        exit(1);
    while(!queue_enqueue(sq, &dat))
    {
        dat = rand()%100;
    }
    queue_travel(sq);
    queue_clear(sq);
    printf("After clear the queue\n");
    queue_travel(sq);
    queue_destroy(sq);

}