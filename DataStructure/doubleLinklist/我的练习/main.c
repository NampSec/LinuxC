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