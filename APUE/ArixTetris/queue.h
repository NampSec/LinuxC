#ifndef __QUEUEN_h__
#define __QUEUEN_h__
typedef struct point
{
    unsigned int x;
    unsigned int y;
    struct point *next;
}point;

void add_point(point **qu, int x, int y);
void destroy_queue(point *qu);
void print_queue(point *qu);



#endif
