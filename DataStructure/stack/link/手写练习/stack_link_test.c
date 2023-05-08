#include "stack_link.h"
#include <stdlib.h>
#include <stdio.h>
#define NAMESIZE (32)
struct student_info {
    char name[NAMESIZE];
    int english;
    int chinese;
};

void print_info(void *data)
{
    struct student_info * info = (struct student_info *)data;
    printf("Student:%s english:%d chinese:%d\n", info->name, info->english, info->chinese);
}

int main(void)
{
    STACK * stack = NULL;
    struct student_info student;
    stack = stack_create(sizeof(struct student_info));
    for (int i = 0; i < 7; i++)
    {
        snprintf(student.name, NAMESIZE, "student_%d", i);
        student.chinese = rand()%100;
        student.english = rand()%100;
        stack_push(stack, &student);
    }
    stack_travel(stack, print_info);
    for (int i = 0; i < 7; i++)
    {
        stack_pop(stack, &student);
        printf("pop data:\n");
        print_info(&student);
    }
    stack_destroy(stack);
}