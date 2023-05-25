/*************************************************
Copyright © yang. 1998-2023. All rights reserved.
File name: btree.c
Author: yang
Version: 1.0
Description: 二叉树的实现demo
Others: 
Log: 2023-05-11 1.0 yang create
*************************************************/

#include "queue_link.h"
#include <stdio.h>
#include <stdlib.h>
queue *layer_queue;
#define NAMESIZE (32)

struct score_st
{
    int id;
    char name[NAMESIZE];
    int math;
    int chinese;
};

struct node_st
{
    struct score_st data;
    struct node_st *l, *r;
};
void print_s(struct score_st *data);


void insert(struct node_st **root, struct score_st *data)
{
    if (*root == NULL)
    {
        struct node_st *tmp = (struct node_st *)malloc(sizeof(struct node_st));
        tmp->l = NULL;
        tmp->r = NULL;
        tmp->data = *data;
        *root = tmp;
        return;
    }
    if ((*root)->data.id < (*data).id)
        insert(&(*root)->r, data);
    else
        insert(&(*root)->l, data);
}

struct score_st *find(struct node_st *root, int id)
{
    if (root == NULL) // 没有找到
        return NULL;
    if (root->data.id == id) // 成功找到
        return &root->data;
    if (root->data.id < id)
        find(root->r, id);
    else
        find(root->l, id);
}

void travel(struct node_st *root, int method) // 四种遍历方法，按层遍历，先序遍历，中序遍历，后序遍历
{
    if( root == NULL ) return;
    switch (method)
    {
    case 1: // 按层遍历，先用先序遍历入队，只入队左右两个树，再出队递归;
        print_s(&root->data);
        if ( root->l != NULL)
            queue_enqueue(layer_queue, (void*)&root->l);
        if ( root->r != NULL)
            queue_enqueue(layer_queue, (void*)&root->r);
        if(layer_queue->head.next == &layer_queue->head)
            return;
        struct node_st *temp ;
        queue_dequeue(layer_queue, &temp);
        travel(temp, 1);
        break;
    case 2: // 先序遍历
        print_s(&root->data);
        travel(root->l, 2);
        travel(root->r, 2);
        break;
    case 3: // 中序遍历
        travel(root->l, 3);
        print_s(&root->data);
        travel(root->r, 3);
        break;
    case 4: //后序遍历
        travel(root->l, 4);
        travel(root->r, 4);
        print_s(&root->data);
        break;
    default:
        fprintf(stderr, " the method is not defined \n");
        exit(1);
        break;
    }
}


void delete_tree()
{
    return ;
}
struct node_st *get_left_leaf(struct node_st *root)
{
    struct node_st * cur = root;
    while(cur->l != NULL)
    {
        cur = cur->l;
    }
    return cur;
}
struct node_st *get_right_leaf(struct node_st *root)
{
    struct node_st * cur = root;
    while(cur->r != NULL)
    {
        cur = cur->r;
    }
    return cur;
}
int get_tree_size(struct node_st *root) // 计算该树下所有节点的个数
{
    if ( root == NULL ) return 0;
    return get_tree_size(root->l) + get_tree_size(root->r) + 1;
}
void tree_turn_left(struct node_st **root)
{
    struct node_st *temp = (*root)->l;
    get_right_leaf((*root)->l)->r = (*root);
    (*root)->l = NULL;
    (*root) = temp;
}
void tree_turn_right(struct node_st **root)
{
    struct node_st *temp = (*root)->r;
    get_left_leaf((*root)->r)->l = (*root);
    (*root)->r = NULL;
    (*root) = temp;
}
void balance_tree(struct node_st ** root) // 平衡左右子树，当左右子树相差不超过1时，此时平衡, 由于对无头节点的树会进行修改需要二级指针
{
    int subtract = get_tree_size((*root)->l) - get_tree_size((*root)->r);
    while( subtract > 1 ||  subtract < -1)
    {
        if(subtract > 1)
        {
            tree_turn_left(root);
        }else
        {
            tree_turn_right(root);
        }
        subtract = get_tree_size((*root)->l) - get_tree_size((*root)->r);
    }
}

/*
*@ Description: 画出树的图形，该函数本质是一个中序遍历的函数，可以看这个函数的结构符合树的中序遍历结构。
* @param 1: 要画的节点
* @param 2: 该节点的深度
* @return: void
*/
void _draw(struct node_st *root, int level)
{
    if(root == NULL)
        return;
    _draw(root->r, level + 1); // 先画右子树
    for (int i = 0; i < level; i++)
    {
        printf("    ");
    }
    printf("%d\n", root->data.id);   //再画根子树
    _draw(root->l, level + 1);    //再画左子树
}
void draw(struct node_st *root)
{
    _draw(root, 0);
}
void print_s(struct score_st *data)
{
    printf("student id: %d math: %d chinese: %d name: %s\n", data->id, data->math, data->chinese, data->name);
}

int main(void)
{
    struct node_st *tree = NULL;
    struct score_st tmp;
    struct score_st *datap;
    int arr[] = {3, 6, 7, 8, 2, 4};
    for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
    {
        tmp.id = arr[i];
        snprintf(tmp.name, NAMESIZE, "student:%d", arr[i]);
        tmp.math = rand() % 100;
        tmp.chinese = rand() % 100;
        insert(&tree, &tmp);
    }
    layer_queue = queue_create(sizeof(struct node_st *));
    if(layer_queue == NULL) exit(1); // 创建队列便于travel函数使用
    draw(tree);
    balance_tree(&tree);
    draw(tree);

    #if 0
    datap = find(tree, 10);
    if (datap == NULL)
        printf("Not found in tree\n");
    else
        print_s(datap);
    #endif
    return 0;
}
