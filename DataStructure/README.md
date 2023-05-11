```
推荐的书籍：
严尉敏 数据结构
算法导论
编程之美
```

单链表有单向和双向，有头和无头这四种。

树-递归：

递归转非递归，特点是有向无环图。

图可以拆分为树来解决。

```
写程序一定要永远认为和别人一起写程序，只有.h提供给别人，main函数只负责调用和逻辑。
```

# 线性表

``` c++
#ifndef SQLIST_H_	//后加下划线防止名字和内核源码中的宏冲突，内核中经常为前加下划线
#define SQLIST_H_

#define DATASIZE 1024

typedef int datatype;

typedef struct 
{
  datatype data[DATASIZE];
  int last;
}sqlist;

sqlist *sqlist_create();
void sqlist_createone(sqlist **);

// 数据操作
int sqlist_insert(sqlist*, int, datatype*);
int sqlist_delete(sqlist*, int);
int sqlist_find(sqlist*, datatype*);

// 工具方法
int sqlist_isempty(sqlist*);
int sqlist_setempty(sqlist*);
int sqlist_getnum(sqlist*);
void sqlist_show(sqlist*);

int sqlist_destory(sqlist*);

#endif // SQLIST_H_

```

``` c++
#include <stdio.h>
#include <stdlib.h>
#include "sqlist.h"

sqlist *sqlist_create(){
    sqlist *me;
    me = malloc(sizeof(*me));
    if (me == NULL) {
        return NULL;
    }
    me->last = -1;
    return me;
}
void sqlist_createone(sqlist **ptr){
    *ptr = malloc(sizeof(**ptr));
    if (*ptr == NULL) {
        return;
    }

    (*ptr)->last = -1;
    return;
}

int sqlist_destory(sqlist* me){
    free(me);

    return 0;
}

// 数据操作
int sqlist_insert(sqlist* me, int i, datatype* data){
    if (me->last == DATASIZE-1 ) {
        return -1;
    }
    if (i < 0 || i > me->last+1) {
        return -2;
    }

    for (int j = me->last;i <= j;j-- ) {
        me->data[j+1] = me->data[j];
    }
    me->data[i] = *data;
    me->last++;

    return 0;
}

int sqlist_delete(sqlist* me, int i){
    if (i < 0 || i > me->last){
        return -1;
    }
    for (int j = i;j < me->last;j++) {
        *(me->data+j) = *(me->data+j+1);
    }
    me->last--;
    return 0;
}

int sqlist_find(sqlist* me, datatype* data){

    if (sqlist_isempty(me) == 0){
        return -1;
    }
    for (int i = 0;i <= me->last;i++){
        if (*(me->data+i) == *data) {
            return i;
        }
    }

    return - -1;
}

int sqlist_union(sqlist* ptr1, sqlist* ptr2) {
    return 0;
}

// 工具方法
int sqlist_isempty(sqlist* me){
    if (me->last == -1){
        return 0;
    }else{
        return -1;
    }
}

int sqlist_setempty(sqlist* me){
    return 0;
}

int sqlist_getnum(sqlist* me){
    return me->last+1;
}

void sqlist_show(sqlist *me){
    if (me->last == -1) {
        return;
    }

    for (int i = 0;i <= me->last;i++) {
        printf("%d ", *(me->data+i));
    }
    printf("\n");
}


```


``` c++
#include <stdlib.h>
#include <stdio.h>
#include "sqlist.h"

int main() {
    sqlist *list;
    list = sqlist_create();
    // sqlist_createone(&list);
    int err = -1;
    if (list == NULL) {
        perror("list init faild");
        exit(1);
    }

    int arr[] = {21, 34, 54, 98, 56, 1, 3, 5};
    for (int i = 0;i < sizeof(arr)/sizeof(*arr);i++) {
        if ((err = sqlist_insert(list, i, arr+i)) != 0){
            if (err == -1){
                perror("数组为空");
            }else if (err == -2){
                perror("插入失败");
            }else{
                perror("未知错误");
            }
        }
    }

    sqlist_show(list);
    sqlist_delete(list, 1);
    sqlist_show(list);

    printf("顺序表长度: %d\n", sqlist_getnum(list));
    int num = 5;
    printf("%d的位置: %d\n",num ,sqlist_find(list, &num));

    sqlist_destory(list);

    exit(0);
}

```

# 链表

有头和无头节点

带头：插入首节点时只需要修改头节点即可

无头：不知道能否插入首节点，插入时起始位置这个变量要变。且不需要创建，可以直接插入。需要二级指针传参。

某些特殊的情形，不适合有头节点，而适合无头节点，不如说循环的单向链表，约瑟夫算法单向无头循环链表。

循环链表的创建有前向插入插入和后向插入：

```
前向插入：不断地在第一个节点的后面插入节点，并将插入节点的后继节点指向之前第一个节点指向的节点
后向插入：在链表的最后一个节点插入，再指向头节点
```

第二种思路比较好，情形完备，适合哪怕是仅有一个节点这种情况。

## 单向有头 

``` c++
#ifndef LINKLIST_H_
#define LINKLIST_H_

typedef void *datatype;

typedef struct node_st{
  datatype data;
  struct node_st *next;
}list;

list* list_create();
void list_destory(list*);

int list_insert_at(list*, int, datatype);
int list_order_insert(list* me, datatype data, int (*)(datatype,datatype));
int list_delete_at(list*, int, datatype);
int list_delete(list* me,datatype data, int (*)(datatype, datatype));

int list_isempty(list*);
void list_show(list *me, void (*)(datatype));

#endif // LINKLIST_H_


```


``` c++
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "linklist.h"

list* list_create(){
  list *head;
  head = malloc(sizeof(*head));
  if (head == NULL){
    return NULL;
  }

  return head;
}

void list_destory(list* me){
  if (list_isempty(me)){
    return;
  }

  list *node,*next;
  for(node = me->next;next != NULL;node = next){
    next = node->next;
    free(node);
  }
  free(me);

}

int list_insert_at(list* me, int i, datatype data){
  int j = 0;
  list *node = me, *newnode;

  if(i < 0){
    return -EINVAL;
  }
  
  while(j < i && node != NULL){
    node = node->next;
    j++;
  }

  if (node){
    newnode = malloc(sizeof(*newnode));
    if (newnode == NULL){
      return -2;
    }
    newnode->data = data;
    newnode->next = node->next;
    node->next = newnode;
    return 0;

  }else{
    return -3;

  }

}

// 排序插入
int list_order_insert(list* me, datatype data, int (*f)(datatype,datatype)){
  if (me == NULL){
    return EINVAL;
  }

  list *p = me,*q;

  while(p->next && f(p->next->data, data))
    p = p->next;

  q = malloc(sizeof(*q));
  if (q == NULL){
    return -1;
  }

  q->data = data;
  q->next = p->next;
  p->next = q;

  return 0;
}

int list_delete_at(list* me, int i, datatype data){

  if (me == NULL){
    return EINVAL;
  }

  list *node = me;

  for (int j = 1;j < i;j++){
    if (node->next == NULL){
      return -1;
    }
    node = node->next;
  }

  list *tempnode;
  tempnode = node->next;
  node->next = tempnode->next;
  *(void **)data = tempnode->data;
  free(tempnode);
  return 0;

}

int list_delete(list* me,datatype data, int f(datatype, datatype)){
  list *p = me;

  while(p->next && f(p->next->data, data)){
    p = p->next;
  }

  if (!p->next){
    return -1;
  }else{
    list *q;
    q = p->next;
    p->next = q->next;
    free(q);
    return 0;
  }
  return -2;
}

int list_isempty(list* me){
  if (me == NULL){
    return 1;
  }
  return 0;
}

void list_show(list *me, void f(datatype)){
  if (list_isempty(me)){
    return;
  }

  for (list *node = me->next;node != NULL;node = node->next){
    f(node->data);
  }
  printf("\n");
}

```


``` c++
#include "linklist.h"
#include <stdio.h>
#include <stdlib.h>

int a(datatype a, datatype b){
  return *(int *)a < *(int*)b;
}

void b(datatype data){
  printf("%d ", *(int *)data);
}

int main(){
  int arr[] = {3, 4, 66, 76, 334, 12, 32};
  list *l;

  l = list_create();

  for (unsigned long i = 0;i < sizeof(arr)/sizeof(*arr);i++){
    list_order_insert(l, arr+i,a);
  }

  list_show(l, b);

  int *num =  NULL;
  list_delete_at(l, 2, &num);

  printf("%d删除\n", *num);
  list_show(l, b);
  list_destory(l);

  exit(0);

}

```


## 单向无头

``` c++
#ifndef LINKLIST_H_
#define LINKLIST_H_

typedef void *datatype;

typedef struct node_st{
  datatype data;
  struct node_st *next;
}list;

list* list_create();
void list_destory(list**);

// 首部插入
int list_insert(list** me, datatype data);
int list_delete(list** me);

int list_isempty(list*);
void list_show(list *me, void (*)(datatype));

#endif // LINKLIST_H_

```



``` c++
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "linklist.h"

list* list_create(){
  list *head;
  head = malloc(sizeof(*head));
  if (head == NULL){
    return NULL;
  }

  return head;
}

void list_destory(list** me){
  if (list_isempty(*me)){
    return;
  }

  list *node,*next;
  for(node = *me;next != NULL;node = next){
    next = node->next;
    free(node);
  }
  free(*me);

}

int list_insert(list** me, datatype data){
  list *newnode;

  newnode = malloc(sizeof(*newnode));
  if (newnode == NULL){
    return ENOMEM;
  }



  newnode->data = data;
  newnode->next = *me;

  *me = newnode;

  return 0;

}

// 首部删除
int list_delete(list** me){
  list *p = *me;

  if (!p){
    return -EEXIST;
  }

  *me = p->next;
  free(p);
  return 0;

}

int list_isempty(list* me){
  if (me == NULL){
    return 1;
  }
  return 0;
}

void list_show(list *me, void f(datatype)){
  if (list_isempty(me)){
    return;
  }

  for (list *node = me;node != NULL;node = node->next){
    f(node->data);
  }
  printf("\n");
}

```


``` c++
#include "linklist.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

void b(datatype data){
  printf("%d ", *(int *)data);
}

int main(){
  int arr[] = {3, 4, 66, 76, 334, 12, 32};
  list *l = NULL;


  for (unsigned long i = 0;i < sizeof(arr)/sizeof(*arr);i++){
    list_insert(&l, arr+i);
  }

  list_show(l, b);

  if ((list_delete(&l)) == -EEXIST){
    exit(1);
  }
  if ((list_delete(&l)) == -EEXIST){
    exit(1);
  }
  if ((list_delete(&l)) == -EEXIST){
    exit(1);
  }

  list_show(l, b);
  list_destory(&l);

  exit(0);

}

```

### 单向链表的应用

``` c++
#include <stdio.h>
#include <stdlib.h>

struct node_st{
  int coef; // 系数
  int exp;  // 指数
  struct node_st *next;
};

struct node_st *poly_create(int a[][2], int size){
  struct node_st *me;
  struct node_st *temp;
  struct node_st *cur;

  me = malloc(sizeof(*me));
  if (me == NULL){
    return NULL;;
  }
  me->next = NULL;
  me->exp = -1;
  cur = me;

  for(int i = 0;i < size;i++){
    temp = malloc(sizeof(*temp));
    // 构建失败的话 要进行内存释放
    if (temp == NULL){
      cur = me;
      struct node_st *q;
      for (int j = 0;j < i;j++){
        q = cur->next;
        free(cur);
        cur = q;
      }
    }
    // 构建新节点
    temp->coef = *(*(a+i));
    temp->exp = *(*(a+i)+1);
    temp->next = NULL;
    // 插入正确的位置
    cur = me;
    while(cur->next && cur->next->exp < temp->exp){
      cur = cur->next;
    }
    temp->next = cur->next;
    cur->next = temp;
  }

  return me;

}

void poly_union(p1, p2){

}

void poly_destory(struct node_st* p){
  free(p);
}

void poly_show(struct node_st *me){
  struct node_st *temp;
  for (temp = me->next;temp != NULL;temp = temp->next){
    printf("%d*X^%d ", temp->coef, temp->exp);
  }
  printf("\n");

}

int main(){
  int a[][2] = {{5,0},{8,8},{2,1},{3,16}};
  int b[][2] = {{6,1},{16,6},{-8,8}};
  struct node_st *p1,*p2;

  p1 = poly_create(a, 4);
  p2 = poly_create(b, 3);

  if (p1 == NULL || p2 == NULL){
    exit(1);
  }

  poly_show(p1);
  poly_show(p2);

  poly_destory(p1);
  poly_destory(p2);

}

```

**约瑟夫算法**

## 双向链表

### 
``` c++
#ifndef LLIST_H__
#define LLIST_H__
enum{
    F = 1,
    B = 2,
};

//普通节点
struct llist_node_st{
    void *data;
    struct llist_node_st *prev;
    struct llist_node_st *next;
};
//头节点
typedef struct {
    int size;
    struct llist_node_st head;
} LLIST; //LLIST就是一个双向链表的头节点类型，对于链表的操作都是用head来进行的

//传入 每个数据节点的数据类型大小
LLIST *llist_careate(int size);
//传入 一个已经创好的链表的头节点，插入的数据，插入的模式
int llist_insert(LLIST *,const void *data,int mode);
//传入
void *llist_find(LLIST *head,const void* ,int (*func)(const void*,const void*));
//
int llist_delete(LLIST *head,const void* ,int (*func)(const void*,const void*));
//
int llist_fetch(LLIST *head,const void* ,int (*func)(const void*,const void*),void *);
//传入 一个已经创建好的链表头节点
void llist_travel(LLIST* head,void (*func)(const void*));
void llist_destroy(LLIST *);

#endif

```


``` c++
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "llist.h"


//传入 每个数据节点的数据类型大小
LLIST *llist_careate(int size){
    LLIST *new;
    new = malloc(sizeof(*new));
    if (new == NULL){
        return NULL;
    }

    new->size = size;
    new->head.data = NULL;
    new->head.prev = &new->head;
    new->head.next = &new->head;
    
    return new;
}
//传入 一个已经创好的链表的头节点，插入的数据，插入的模式
int llist_insert(LLIST *head,const void *data,int mode){
    struct llist_node_st *newnode;
    newnode = malloc(sizeof(*newnode));
    if (newnode == NULL)
      return -1;

    newnode->data = malloc(head->size);
    if (newnode->data == NULL){
        return -2;
    }
    memcpy(newnode->data,data,head->size);

    switch (mode) {
        case F:
            newnode->prev = &head->head;
            newnode->next = head->head.next;
            break;
        case B:
            newnode->prev = head->head.prev;
            newnode->next = &head->head;
            break;
        default:
            return -3;
    }

    newnode->prev->next = newnode;
    newnode->next->prev = newnode;

    return 0;

}
//传入 一个已经创建好的链表头节点,一个辅助遍历函数
void llist_travel(LLIST* head,void (*func)(const void *)){
    struct llist_node_st *cur,*next;
    for (cur = head->head.next;cur != &head->head;cur = next) {
        func(cur->data);
        next = cur->next;
    }
}

//辅助函数
static struct llist_node_st *find_(LLIST *head,const void *key,int (*func)(const void *,const void *)){
    struct llist_node_st *cur;
    for (cur = head->head.next;cur != &head->head;cur = cur->next){
        if (func(key,cur->data) == 0){
            return cur;
        }
    }
    return &head->head;
}

void *llist_find(LLIST *head,const void* key,int (*func)(const void*,const void*)){
    return find_(head,key,func)->data;
}

//
int llist_delete(LLIST *head,const void* key,int (*func)(const void*,const void*)){
    struct llist_node_st *node;
    node = find_(head,key,func);
    if (node == &head->head){
        return -1;
    }else {
        node->prev->next = node->next;
        node->next->prev = node->prev;
        free(node->data);
        free(node);
        return 0;
    }
}
//
int llist_fetch(LLIST *head,const void* key,int (*func)(const void*,const void*),void *data){
    struct llist_node_st *node;
    node = find_(head,key,func);
    if (node == &head->head){
        return -1;
    }else {
        node->prev->next = node->next;
        node->next->prev = node->prev;
        data = node->data;
        free(node->data);
        free(node);
        return 0;
    }
}

void llist_destroy(LLIST *head) {
    struct llist_node_st *cur,*next;

    for (cur = head->head.next;cur != &head->head;cur = next) {
        next = cur->next;
        free(cur->data);
        free(cur);
    }
    free(head);
}

```


``` c++
#include <stdio.h>
#include <stdlib.h>

#include "llist.h"


void print_llist(const void *data){
    int res =  *(int *)data;
    printf("%d ",res);
}

int cmp(const void *a,const void *b){
    return *(int *)a < *(int *)b;
}

int main()
{
    LLIST *headler;
    headler = llist_careate(sizeof(int));
    if (headler == NULL) {
        exit(1);
    }
    
    for (int i = 0;i < 10;i++){
        if (llist_insert(headler,&i,F) < 0){
            llist_destroy(headler);
            exit(1);
        }
    }

    llist_travel(headler,print_llist);
    printf("\n");
    int key = 7;
    void * temp = llist_find(headler,&key,cmp);
    if (temp == NULL){
        printf("查无此项\n");
    }else {
        printf("%d\n",*(int *)temp);
    }

    llist_delete(headler,&key,cmp);
    llist_travel(headler,print_llist);
    printf("\n");

    llist_destroy(headler);

    exit(0);
}


```


lib2
``` c++
/*************************************************
Copyright © yang. 1998-2023. All rights reserved.
File name: ds_llist.c
Author: yang
Version: 2.0
Description: 用于实现通用的双向环链库，为改进版本，node中的data不再是一个void *指针，而是数据本身。
Others:
Log: 2023-05-06 2.0 yang create
*************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ds_llist_v2.h"


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
    node_list * insert_node = (node_list *)malloc(sizeof(node_list) + llist->size);
    if(insert_node == NULL)
        return -1;
    memcpy(insert_node->data, data, llist->size);

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

```


``` c++
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

```


``` c++
main.c文件略
```


lib3 
``` c++
/*************************************************
Copyright © yang. 1998-2023. All rights reserved.
File name: ds_llist.c
Author: yang
Version: 3.0
Description: 用于实现通用的双向环链库，为改进版本，node中的data不再是一个void *指针，而是数据本身。且实现了类似于C++的类。
Others:
Log: 2023-05-06 3.0 yang create
*************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ds_llist_v3.h"

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
    llist->head.next = &llist->head;
    llist->head.prev = &llist->head;
    llist->insert = _llist_insert;
    llist->remove = _llist_remove;
    llist->fetch = _llist_fetch;
    llist->find = _llist_find;
    llist->travel = _llist_travel;
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
    node_list * insert_node = (node_list *)malloc(sizeof(node_list) + llist->size);
    if(insert_node == NULL)
        return -1;
    memcpy(insert_node->data, data, llist->size);

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

```


``` c++
/*    DS_LLIST    */
#ifndef __DS_LLIST_h__
#define __DS_LLIST_h__

typedef int cmp_op(void * record, void *data);

typedef struct node_list
{
    struct node_list * prev;
    struct node_list * next;
    char data[0];
}node_list;

typedef struct LLIST
{
    int size;
    int (*insert)(struct LLIST *llist, void *data, int method);
    int (*remove)(const struct LLIST *llist, void *key, cmp_op *op);
    int (*fetch)(const struct  LLIST *llist, void *key, cmp_op *op, void *data);
    void *(*find)(const struct LLIST *llist, void *key, cmp_op *op);
    void (*travel)(struct LLIST *llist, void (*fuc)(node_list *data));
    node_list  head;

}LLIST;
/* Callback比较函数的原型 */

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

```


``` c++
#include "ds_llist_v3.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILESIZE (1024)
struct file_info
{
    char filename[FILESIZE];
    int size;
};

void printf_file_info(node_list *record)
{
    struct file_info *info = (struct file_info *)record->data;
    printf("filenames: %s\n", info->filename);
    printf("size: %d\n", info->size);
}
int filename_cmp(void *record, void *data)
{
    node_list *node = (node_list *)record;
    struct file_info *info = (struct file_info *)node->data;
    char *filename = (char *)data;
    return strcmp(info->filename, filename);
}

int main(void)
{
    LLIST *link_list = _llist_create(sizeof(struct file_info));
    struct file_info info;
    int err = 0;
    for (int i = 0; i < 7; i++)
    {
        info.size = rand() % 100;
        snprintf(info.filename, FILESIZE, "file%d.txt", i);

        err = link_list->insert(link_list, &info, LLIST_FORWARD_INSERT);
        if (err != 0)
            printf("insert failed\n");
    }
    link_list->travel(link_list, printf_file_info);
    node_list *result_node = NULL;
    result_node = (node_list *)link_list->find(link_list, (void *)"file1.txt", filename_cmp);
    if (result_node != NULL)
    {
        printf_file_info(result_node);
    }
    else
    {
        printf("not found \n");
    }
    link_list->fetch(link_list, (void *)"file1.txt", filename_cmp,&info);

    result_node = (node_list *)link_list->find(link_list, (void *)"file1.txt", filename_cmp);
    if (result_node != NULL)
    {
        printf_file_info(result_node);
    }
    else
    {
        printf("not found \n");
    }
    printf("fetched filename: %s ,size %d\n", info.filename,info.size);

    _llist_destroy(link_list);
    return 0;
}
```


lib4 
``` c++
/*************************************************
Copyright © yang. 1998-2023. All rights reserved.
File name: ds_llist.c
Author: yang
Version: 2.0
Description: 用于实现通用的双向环链库，为改进版本，node中的data不再是一个void *指针，而是数据本身。
Others:
Log: 2023-05-06 2.0 yang create
*************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ds_llist_v4.h"

typedef struct node_list
{
    struct  node_list * prev;
    struct  node_list * next;
    char data[0];
}node_list;

struct DS_LLIST 
{
    int size;
    node_list  head;
};

static struct node_list * __find_node_by_key(const LLIST  *llist, void *key, cmp_op *op);
static void __insert__betweeen__(node_list *node_insert, struct node_list *node1, struct node_list *node2);
/*
 *@ Description: 将要插入的node插入到node1和node2之前
 * @param 1: 要插入的node
 * @param 2: node1
 * @param 3: node2
 * @return: void
 */
static void __insert__betweeen__(struct node_list *node_insert, struct node_list *node1, struct node_list *node2)
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
LLIST  *_llist_create(int size)
{
    if (size <= 0)
        return NULL;
    struct DS_LLIST  *llist = (struct DS_LLIST  *)malloc(sizeof(struct DS_LLIST));
    if (llist == NULL)
        return NULL;
    llist->size = size;
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

int _llist_insert(LLIST  *ll, void *data, int method)
{
    struct DS_LLIST *llist = (struct DS_LLIST *)ll;
    struct node_list * insert_node = (struct node_list *)malloc(sizeof(struct node_list) + llist->size);
    if(insert_node == NULL)
        return -1;
    memcpy(insert_node->data, data, llist->size);

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
void _llist_destroy(LLIST  *ll)
{
    struct DS_LLIST *llist = (struct DS_LLIST *)ll;
    struct node_list *cur = NULL;
    struct node_list *next = NULL;
    for (cur = llist->head.next; cur != &llist->head; cur = next)
    {
        next = cur->next;
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
static struct node_list * __find_node_by_key(const LLIST  *ll, void *key, cmp_op *op)
{
    struct DS_LLIST *llist = (struct DS_LLIST *)ll;
    struct node_list * cur = llist->head.next;
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
void *_llist_find(const LLIST  *ll, void *key, cmp_op *op)
{
    struct DS_LLIST *llist = (struct DS_LLIST *)ll;
    struct node_list * result_node = __find_node_by_key(llist,key,op);
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
int _llist_remove(const LLIST  *ll, void *key, cmp_op *op)
{
    struct DS_LLIST *llist = (struct DS_LLIST *)ll;
    struct node_list *remove_node = __find_node_by_key(llist, key, op);
    if(remove_node != &llist->head)
    {
        remove_node->prev->next = remove_node->next;
        remove_node->next->prev = remove_node->prev;
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

int _llist_fetch(const LLIST  *ll, void *key, cmp_op *op, void *data)
{
    struct DS_LLIST *llist = (struct DS_LLIST *)ll;
    struct node_list *remove_node = __find_node_by_key(llist, key, op);
    if(remove_node != &llist->head)
    {
        remove_node->prev->next = remove_node->next;
        remove_node->next->prev = remove_node->prev;
        memcpy(data, remove_node->data, llist->size);
        free(remove_node);
        return 0;
    }else
    {
        return -1;
    }
    
}

void _llist_travel(LLIST *ll, void (*fuc)(const void *data))
{
    struct DS_LLIST *llist = (struct DS_LLIST *)ll;
    struct node_list * cur = llist->head.next;
    for(;cur != &llist->head; cur = cur->next)
    {
        fuc(cur);
    }
}

```


``` c++
/*    DS_LLIST    */
#ifndef __DS_LLIST_h__
#define __DS_LLIST_h__

typedef void LLIST;

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

void _llist_travel(LLIST *llist, void (*fuc)(const void *data));

#endif

```


``` c++
main.c略
```

### 内核双向链表赏析

`内核版本：4.14.314`

`文件路径：.\include\linux\list.h`

#### 双向链表的创建

```c++
#define LIST_HEAD_INIT(name) { &(name), &(name) }

#define LIST_HEAD(name) \
	struct list_head name = LIST_HEAD_INIT(name)
```

#### 双向链表节点的添加

```
/**
 * list_add - add a new entry
 * @new: new entry to be added
 * @head: list head to add it after
 *
 * Insert a new entry after the specified head.
 * This is good for implementing stacks.
 */
static inline void list_add(struct list_head *new, struct list_head *head)
{
	__list_add(new, head, head->next);
}


/**
 * list_add_tail - add a new entry
 * @new: new entry to be added
 * @head: list head to add it before
 *
 * Insert a new entry before the specified head.
 * This is useful for implementing queues.
 */
static inline void list_add_tail(struct list_head *new, struct list_head *head)
{
	__list_add(new, head->prev, head);
}
```

其中__list_add函数如下

```c++
/*
 * Insert a new entry between two known consecutive entries.
 *
 * This is only for internal list manipulation where we know
 * the prev/next entries already!
 */
static inline void __list_add(struct list_head *new,
			      struct list_head *prev,
			      struct list_head *next)
{
	if (!__list_add_valid(new, prev, next)) //这个__list_add_valid永远是true，除非开启CONFIG_DEBUG_LIST
		return;

	next->prev = new;
	new->next = next;
	new->prev = prev;
	WRITE_ONCE(prev->next, new);
}
//WRITE_ONCE()用于原子操作，防止竞争条件多个进程操作prevv->next,这里为8个字节的赋值，其实意义不太大，如果数据长度很长，大于u64(8个字节)，就会采用buildin_memcpy并互斥，防止其他程序访问。如下面的__write_once_size所示。
/*
这个宏定义的核心思想是利用联合体的成员变量共用同一块内存的特性，将要赋给 x 的值写入到联合体的字符数组中，再通过调用一个函数将该字符数组的内容写入到 x 变量中。这样做的好处是可以确保在多线程环境下对 x 变量的写入是原子操作，避免了竞争条件的发生。
*/
#define WRITE_ONCE(x, val) \
({							\
	union { typeof(x) __val; char __c[1]; } __u =	\
		{ .__val = (__force typeof(x)) (val) }; \
	__write_once_size(&(x), __u.__c, sizeof(x));	\
	__u.__val;					\
})

static __always_inline void __write_once_size(volatile void *p, void *res, int size)
{
 switch (size) {
 case 1: *(volatile __u8 *)p = *(__u8 *)res; break;
 case 2: *(volatile __u16 *)p = *(__u16 *)res; break;
 case 4: *(volatile __u32 *)p = *(__u32 *)res; break;
 case 8: *(volatile __u64 *)p = *(__u64 *)res; break;
 default:
  barrier();
  __builtin_memcpy((void *)p, (const void *)res, size);
  barrier();
 }
}
```

#### 双向链表的遍历

```c++
/**
 * list_for_each	-	iterate over a list
 * @pos:	the &struct list_head to use as a loop cursor.
 * @head:	the head for your list.
 */
#define list_for_each(pos, head) \
	for (pos = (head)->next; pos != (head); pos = pos->next)
```

#### 获取节点所在的结构体的指针

```c++
/**
 * list_entry - get the struct for this entry
 * @ptr:	the &struct list_head pointer.
 * @type:	the type of the struct this is embedded in.
 * @member:	the name of the list_head within the struct.
 */
#define list_entry(ptr, type, member) \
	container_of(ptr, type, member)
#define container_of(ptr, type, member) ({				\
	void *__mptr = (void *)(ptr);					\
	((type *)(__mptr - offsetof(type, member))); })
#define offsetof(TYPE, MEMBER)	((size_t)&((TYPE *)0)->MEMBER)
```



# 栈和队列

## 栈
``` c++
顺序存储
```


``` c++
链式存储二次封装
```


``` c++

```


## 队列
``` c++
顺序存储的队列
```


``` c++
link队列
```


``` c++

```

栈和队列的引用

简单的计算器规划好优先级就能进行扩展

# 树

## 二叉树

二叉树的几个概念

深度

度

叶子节点。。。

左子树2*n 右子树2*n+1

总结点：2^n-1

``` c++
// 顺序存储的二叉树
```




``` c++

```


``` c++

```



## 平衡二叉树

``` c++

```


``` c++

```


``` c++

```



## 树转广义表

``` c++

```


``` c++

```


``` c++

```


## 二叉搜索树

``` c++

```


``` c++

```


``` c++

```



