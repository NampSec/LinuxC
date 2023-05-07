/*    DS_LLIST    */
#ifndef __DS_LLIST_h__
#define __DS_LLIST_h__

typedef struct node_list
{
    struct node_list * prev;
    struct node_list * next;
    char data[0];
}node_list;

typedef struct DS_LLIST
{
    int size;
    node_list  head;
}LLIST;
/* Callback比较函数的原型 */
typedef int cmp_op(void * record, void *data);

#define LLIST_FORWARD_INSERT (1)
#define LLIST_BACKWARD_INSERT (2)


LLIST *_llist_create(int size);

void _llist_destroy(LLIST *llist);

int _llist_insert(LLIST *llist, void *data, int method);

int _llist_remove(const LLIST *llist, void *key, cmp_op *op);

int _llist_fetch(const LLIST *llist, void *key, cmp_op *op, void *data);

void *_llist_find(const LLIST *llist, void *key, cmp_op *op);

void _llist_travel(LLIST *llist, void (*fuc)(node_list *data));

#endif
