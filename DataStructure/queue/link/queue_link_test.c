#include "queue_link.h"
#include <stdlib.h>
#include <stdio.h>
#define NAMESIZE (32)
struct student_info {
    char name[NAMESIZE];
    int chinese;
    int english;
};
void print_info(void *data)
{
    struct student_info *info = (struct student_info *)data;
    printf("student name: %s english: %d chinese :%d\n", info->name, info->english, info->chinese);
}

int main(void)
{
    struct student_info info;
    queue *qu = queue_create(sizeof(struct student_info));
    if (qu == NULL)
        exit(1);
    for(int i = 0; i < 7; i++) 
    {
        info.chinese = rand() % 100;
        info.english = rand() % 100;
        snprintf(info.name, NAMESIZE, "student:%d", i);
        queue_enqueue(qu, &info);
    }
    // printf("before dequeueing\n");
    // for(int i = 0; i < 7; i++) 
    // {
    //     queue_dequeue(qu, &info);
    //     print_info(&info);
    // }
    // printf("after dequeueing\n");
    printf("before clear\n");
    queue_travel(qu, print_info);

    queue_clear(qu);
    printf("after clear\n");

    queue_travel(qu, print_info);
    queue_destroy(qu);

    return 0;
}