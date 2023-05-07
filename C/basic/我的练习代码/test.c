#include "test.h"
#include "ds_line.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
void show_menu(void)
{
    printf("\n********************************");
    printf("\n1. add_entity");
    printf("\n2. show_entity");
    printf("\n3. del_entity");
    printf("\n4. exit");
    printf("\n********************************\n");
    sleep(1);
}
void show_entity(ds_line *line)
{
    for (int i = 0; i <= line->last; i++)
        printf("%d  ", line->data[i]);
    printf("\n");
}

int main(void)
{
    int accept_num = 0;
    int choice = 0;
    datatype value = 0;
    int position = 0;
    ds_line *line = create_line();
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
            destroy_line(line);
            exit(0);
        default:
            break;
        }

    } while (1);

    return 0;
}