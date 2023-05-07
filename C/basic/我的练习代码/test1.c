#include "ds_link_line.h"
#include "test1.h"
#include <stdio.h>
#include <stdlib.h>
#include "win32_read_dir.h"
void show_menu(void)
{
    printf("\n********************************");
    printf("\n1. add_entity");
    printf("\n2. show_entity");
    printf("\n3. del_entity");
    printf("\n4. exit");
    printf("\n********************************\n");
}

void show_entity(node * me)
{
    node * p = me->next;
    while (p != NULL)
    {
        printf("filename: %s status: %d \n",p->data.filename,p->data.status);
        p = p->next;
    }
    
}


int main(void)
{
    read_dir("E:\\workspace\\*.*");
#if 0
    node *link_head;
    int accept_num = 0;
    int choice = 0;
    if(head_link_line_create(&link_head))
    {
        fprintf(stderr, "Error:head_link_line_create() failed %d\n", __LINE__);        
        exit(1);
    }
do
    {
        show_menu();
        if ((accept_num = scanf("%d", &choice)) != 1)
        {
            fprintf(stderr, "scanf failed\n");
            exit(1);
        }
        switch (choice)
        {
        case 1:
            printf("\n 请输入你想插入的数字和位置\n");
            if ((accept_num = scanf("%d%d", &value, &position)) != 2)
            {
                fprintf(stderr, "scanf failed, line : %d\n", __LINE__);
                exit(1);
            }
            insert_line(line, position, value);
            break;
        case 2:
            show_entity(line);
            break;
        case 3:
            printf("\n 请输入你想删除的位置\n");
            if ((accept_num = scanf("%d", &position)) != 1)
            {
                fprintf(stderr, "scanf failed, line : %d\n", __LINE__);
                exit(1);
            }
            delete_line(line, position);
            break;
        case 4:
            head_link_line_destroy(link_head);
            exit(0);
        default:
            break;
        }
    
#endif

    return 0;
}

