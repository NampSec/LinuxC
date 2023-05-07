/*    DS_LINK_LINE    */
#ifndef __DS_LINK_LINE_h__
#define __DS_LINK_LINE_h__

#define FILENAME_MAX (1024)
typedef enum {
  updated = 0,
  need_update,
} update_status;

typedef struct 
{
    update_status status;
    char filename[FILENAME_MAX];
} datatype;

typedef struct node
{
    datatype data;
    struct node * next;
} node;

int head_link_line_insert_head(node *me , datatype data);
int head_link_line_insert_end(node *me , datatype data);
int head_link_line_insert_order(node *me , datatype data);
static node * head_link_line_tail(node * me);
int head_link_line_create(node ** me);
int head_link_line_destroy(node *me);

#endif
