/*    API    */
#ifndef __API_h__
#define __API_h__
void draw_point(int *fd, int x, int y, int r, int g, int b);
void set_echo_on();
void set_echo_off();
void get_terminal_size(int* width, int* height);
void close_framebuffer(int *fd);
void open_framebuffer(int *fd);

#endif
