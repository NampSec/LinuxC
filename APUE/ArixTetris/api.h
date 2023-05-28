/*    API    */
#ifndef __API_h__
#define __API_h__
void draw_point(int *fd, int x, int y, unsigned int color);
void set_echo_on();
void set_echo_off();
void get_terminal_size(int* width, int* height);
void close_framebuffer(int *fd);
void open_framebuffer(int *fd);
void draw_line(int *fd, int x, int y,int x2, int y2, unsigned int color);
void draw_rect(int *fd, int x, int y, int x2, int y2, unsigned int color);
void clear_screen(int *fd, unsigned int color);
#endif
