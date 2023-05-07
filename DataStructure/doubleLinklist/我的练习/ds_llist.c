/*************************************************
Copyright © yang. 1998-2023. All rights reserved.
File name: ds_llist.c
Author: yang
Version: 1.0
Description: 用于实现通用的双向环链库，为初始的版本
Others:
Log: 2023-05-06 1.0 yang create
*************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ds_llist.h"

static node_list * __find_node_by_key(const LLIST *llist, void *key, cmp_op *op);
static void __insert__betweeen__(node_list *node_insert, node_list *node1, node_list *node2);
/*
 *@ Description: 将要插入的node插入到node1和node2之前
 * @param 1: 要插入的node
 * @param 2: node1
 * @param 3: node2
 * @return: void
 */
static void __insert__betweeen__(node_list *node_insert, node_list *node1, node_list *node2)
{
    node1->next = node_insert;
    node2->prev = node_insert;
    node_insert->next = node2;
    node_insert->prev = node1;
}
/*
 *@ Description: 创建双向环链，其中头节点包括了每个node中data的大小
 * @param 1: 所创建环链的每个node中data的大小
 * @return: 双向环链的头指针
 */
LLIST *_llist_create(int size)
{
    if (size <= 0)
        return NULL;
    LLIST *llist = (LLIST *)malloc(sizeof(LLIST));
    if (llist == NULL)
        return NULL;
    llist->size = size;
    llist->head.data = NULL;
    llist->head.next = &llist->head;
    llist->head.prev = &llist->head;
    return llist;
}
/*
 *@ Description: 向双向环链中插入输入，插入方法有前向插入（头节点后插入）和后向插入（头节点之前插入）
 * @param 1: 双向环链的头指针
 * @param 2: 指向要插入数据的指针
 * @param 3: 插入方法：有FORWARD_INSERT和BACKWARD_INSERT这两种方法。
 * @return:
 */

int _llist_insert(LLIST *llist, void *data, int method)
{
    node_list * insert_node = (node_list *)malloc(sizeof(node_list));
    void * data_ptr = malloc(llist->size);
    if(data_ptr == NULL || insert_node == NULL)
        return -1;
    memcpy(data_ptr, data, llist->size);
    insert_node->data = data_ptr;

    if (method == LLIST_FORWARD_INSERT)
    {
        __insert__betweeen__(insert_node, &llist->head,llist->head.next);
    }
    else if (method == LLIST_BACKWARD_INSERT)
    {
        __insert__betweeen__(insert_node, llist->head.prev,&llist->head);
    }
    else
    {
        fprintf(stderr, "the insert method is not supported\n");
        exit(1);
    }
    return 0;
}

/*
*@ Description: 依次销毁释放掉双向环链中的node节点和其中的data
* @param 1: 指向双向环链的头节点
* @return: void
*/
void _llist_destroy(LLIST *llist)
{
    node_list *cur = NULL;
    node_list *next = NULL;
    for (cur = llist->head.next; cur != &llist->head; cur = next)
    {
        next = cur->next;
        free(cur->data);
        free(cur);
    }
    free(llist);
}
/*
*@ Description: 通过Callback回调函数进行比较，回调函数由用户编写
* @param 1: 需要匹配的key值
* @param 2: 需要用户
* @param 3: 指向用户编写的比较函数的指针
* @return: 如果找到了返回指向该node的指针
*/
static node_list * __find_node_by_key(const LLIST *llist, void *key, cmp_op *op)
{
    node_list * cur = llist->head.next;
    for (; cur!= &llist->head; cur = cur->next)
    {
        if(op(cur,key)==0)
            return cur;
    }
    return cur;
}


/*
*@ Description: 根据key和比较回调函数找到node并返回其data指针
* @param 1: 需要匹配的key值
* @param 2: 需要用户
* @param 3: 指向用户编写的比较函数的指针
* @return: 指向匹配到的node的指针
*/
void *_llist_find(const LLIST *llist, void *key, cmp_op *op)
{
    node_list * result_node = __find_node_by_key(llist,key,op);
    if(result_node != &llist->head)
        return result_node;
    return NULL;
}

/*
*@ Description: 
* @param 1: 双向链表的头节点
* @param 2: 需要匹配的key值
* @param 3: 指向用户编写的比较函数的指针
* @return: -1代表未找到，删除失败 0代表删除成功
*/
int _llist_remove(const LLIST *llist, void *key, cmp_op *op)
{
    node_list *remove_node = __find_node_by_key(llist, key, op);
    if(remove_node != &llist->head)
    {
        remove_node->prev->next = remove_node->next;
        remove_node->next->prev = remove_node->prev;
        free(remove_node->data);
        free(remove_node);
        return 0;
    }else
    {
        return -1;
    }
    
}

/*
*@ Description: 删除指定的节点node，向参数data指向的位置写入这些要删除的数据
* @param 1: 需要匹配的key值
* @param 2: 需要用户
* @param 3: 指向用户编写的比较函数的指针
* @param 4: 用户存放要删除数据的data指针
* @return: 0代表删除成功，-1代表删除失败。
*/

int _llist_fetch(const LLIST *llist, void *key, cmp_op *op, void *data)
{
    node_list *remove_node = __find_node_by_key(llist, key, op);
    if(remove_node != &llist->head)
    {
        remove_node->prev->next = remove_node->next;
        remove_node->next->prev = remove_node->prev;
        memcpy(data, remove_node->data, llist->size);
        free(remove_node->data);
        free(remove_node);
        return 0;
    }else
    {
        return -1;
    }
    
}

void _llist_travel(LLIST *llist, void (*fuc)(node_list *data))
{
    node_list * cur = llist->head.next;
    for(;cur != &llist->head; cur = cur->next)
    {
        fuc(cur);
    }
}
