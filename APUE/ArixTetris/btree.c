#include <stdio.h>
#include <stdlib.h>
// 在实际环境中要加上递归层数的上限，防止栈的溢出，并通过longjmp可以跳回到之前的地址。
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
void travel(struct node_st *root, int method) // 按层 先序 中序 后序 四种方法
{
    if (root == NULL) return;
    switch (method)
    {
    case 1: // 按层遍历,按照队列进行排序后出对顺序即为按层遍历
    
        travel(root->l, 4);
        travel(root->r, 4);
        print_s(&root->data);        
        break;
    case 2: //先序遍历
        print_s(&root->data);
        travel(root->l, 2);
        travel(root->r, 2);
        break;
    case 3: // 中序遍历
        travel(root->l, 3);
        print_s(&root->data);
        travel(root->r, 3);
        break;
    case 4: // 后序遍历
        travel(root->l, 4);
        travel(root->r, 4);
        print_s(&root->data);
        break;
    default:
        fprintf(stderr, "the method is not defined\n");
        exit(1);
        break;
    }

}
void delete(); // 删除某个节点，将其的左节点当作原来的节点
void balance(); // 旋转二叉树并且让其每个子树的左子树和右子树的节点个数差值小于等于一
void destroy(); //在遍历的基础上通过free销毁该树
void update(); // 在find的基础上查找方法修改该树的值
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