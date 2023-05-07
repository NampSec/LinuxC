#include "ds_line.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static int is_ds_line_empty(ds_line *line);

/*
 *@ Description: 使用malloc分配一个dsline，并且返回指向其的指针
 * @return: ds_line的指针
 */
ds_line *create_line(void)
{
    ds_line *line = (ds_line *)malloc(sizeof(ds_line));
    if (line == NULL)
    {
        fprintf(stderr, "create_line failed\n");
        exit(1);
    }
    line->last = -1;
    return line;
}

/*
 *@ Description: 使用free销毁该指针，成功后返回0
 * @return: 0代表销毁成功，1代表失败
 */
int destroy_line(ds_line *line)
{
    free(line);
    return 0;
}

/*
 *@ Description: 向顺序存储的队列中插入一个值，所有值都要后移动
 * @param 1: 指向ds_line的指针
 * @param 2: position代表位置
 * @param 3: value代表要插入的值
 * @return: 插入成功返回0，参数错误返回-1，已满返回-2
 */
int insert_line(ds_line *line, int position, datatype value)
{
    if (line->last == (MAX_DS_LINE_SIZE - 1))
        return -2;
    if (position >= MAX_DS_LINE_SIZE || position < 0)
        return -1;
    for (int i = line->last; i >= position; i--)
    {
        line->data[i + 1] = line->data[i];
    }
    line->data[position] = value;
    line->last += 1;
    return 0;
}

/*
 *@ Description: 向顺序存储的队列删除某个位置，所以序列要前移
 * @param 1: 指向ds_line的指针
 * @param 2: 删除的位置
 * @return: 插入成功返回0，参数错误返回-1，已满返回-2
 */
int delete_line(ds_line *line, int position)
{
    if (line->last == (MAX_DS_LINE_SIZE - 1))
        return -2;
    if (position >= MAX_DS_LINE_SIZE || position < 0)
        return -1;
    for (int i = position; i < line->last; i++)
    {
        line->data[i] = line->data[i + 1];
    }
    line->last -= 1;
    return 0;
}

/*
 *@ Description:返回value 所在的Index
 * @param 1: ds_line的指针
 * @param 2: 要查找的value
 * @return: value所在的index,-1代表未查找到
 */
int find_line(ds_line *line, datatype value)
{
    if (is_ds_line_empty(line))
        return -1;
    for (int i = 0; i <= line->last; i++)
    {
        if (line->data[i] == value)
            return i;
    }
    return -1;
}

/*
 *@ Description: 将line的index处修改为value
 * @param 1: ds_line指针
 * @param 2: Index
 * @param 3: value
 * @return: -1代表position超出0-MAX_DS_LINE_SIZE - 1，-2代表超出了line->last
 */

int change_line(ds_line *line, int position, datatype value)
{
    if (position >= MAX_DS_LINE_SIZE || position < 0)
        return -1;
    if (position > line->last)
        return -2;
    line->data[position] = value;
    return 0;
}

static int is_ds_line_empty(ds_line *line)
{
    if (line->last == -1)
        return true;
    return false;
}
