#include <stdio.h>
#include <stdlib.h>

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
    #if 0
    datap = find(tree, 10);
    if (datap == NULL)
        printf("Not found in tree\n");
    else
        print_s(datap);
    #endif
    draw(tree);
    return 0;
}