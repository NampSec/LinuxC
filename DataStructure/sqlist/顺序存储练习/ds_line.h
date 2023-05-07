/*    DS_LINE    */
#ifndef __DS_LINE_h__
#define __DS_LINE_h__

#define MAX_DS_LINE_SIZE (1024)
typedef int datatype;
typedef struct
{
    datatype data[MAX_DS_LINE_SIZE];
    int last;
} ds_line;

ds_line *create_line(void);

int destroy_line(ds_line *line);

int insert_line(ds_line *line, int position, datatype value);

int find_line(ds_line *line, datatype value);

int change_line(ds_line *line, int position, datatype value);

int delete_line(ds_line *line, int position);


#endif
