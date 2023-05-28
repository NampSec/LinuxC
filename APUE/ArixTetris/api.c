#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <stdlib.h>
#include "api.h"
int static __abs(int x);

int static __abs(int x)
{
    return x > -x ? x : -x;
}

void open_framebuffer(int *fd)
{
    // Open the framebuffer device

    *fd = open("/dev/fb0", O_RDWR);

    if (*fd == -1)
    {
        fprintf(stderr, "open_framebuffer failed\n");
        exit(1);
    }
}
void close_framebuffer(int *fd)
{
    close(*fd);
}
void draw_point(int *fd, int x, int y, unsigned int color)
{

    // Get the fixed screen information
    struct fb_fix_screeninfo fix_info;

    if (ioctl(*fd, FBIOGET_FSCREENINFO, &fix_info) == -1)
    {
        close(*fd);
        return;
    }

    // Get the variable screen information
    struct fb_var_screeninfo var_info;

    if (ioctl(*fd, FBIOGET_VSCREENINFO, &var_info) == -1)
    {
        close(*fd);
        return;
    }

    // Map the framebuffer memory into user space
    char *fb_mem = (char *)mmap(0, fix_info.smem_len, PROT_READ | PROT_WRITE, MAP_SHARED, *fd, 0);

    if (fb_mem == (char *)-1)
    {
        close(*fd);
        return;
    }
    // Draw a point at (x, y)
    int bpp = var_info.bits_per_pixel / 8; // Bytes per pixel

    long location = (x + var_info.xoffset) * bpp +
                    (y + var_info.yoffset) * fix_info.line_length;

    *(fb_mem + location) = color & 0xff;             // Blue
    *(fb_mem + location + 1) = (color >> 8) & 0xff;  // Green
    *(fb_mem + location + 2) = (color >> 16) & 0xff; // Red

    // Unmap the framebuffer memory and close the device
    munmap(fb_mem, fix_info.smem_len);
}

void clear_screen(int *fd, unsigned int color)
{
    // Get the fixed screen information
    struct fb_fix_screeninfo fix_info;

    if (ioctl(*fd, FBIOGET_FSCREENINFO, &fix_info) == -1)
    {
        close(*fd);
        return;
    }

    // Get the variable screen information
    struct fb_var_screeninfo var_info;

    if (ioctl(*fd, FBIOGET_VSCREENINFO, &var_info) == -1)
    {
        close(*fd);
        return;
    }

    // Map the framebuffer memory into user space
    char *fb_mem = (char *)mmap(0, fix_info.smem_len, PROT_READ | PROT_WRITE, MAP_SHARED, *fd, 0);

    if (fb_mem == (char *)-1)
    {
        close(*fd);
        return;
    }

    // Draw a point at (x, y)
    int bpp = var_info.bits_per_pixel / 8; // Bytes per pixel
    long location;
    unsigned int px, py;
    for (px = 0; px < var_info.xres; px++)
    {
        for (py = 0; py < var_info.yres; py++)
        {
            location = (px + var_info.xoffset) * bpp +
                       (py + var_info.yoffset) * fix_info.line_length;
            *(fb_mem + location) = color & 0xff;             // Blue
            *(fb_mem + location + 1) = (color >> 8) & 0xff;  // Green
            *(fb_mem + location + 2) = (color >> 16) & 0xff; // Red
        }
    }
    // Unmap the framebuffer memory and close the device
    munmap(fb_mem, fix_info.smem_len);
}
void draw_line(int *fd, int x, int y, int x2, int y2, unsigned int color)
{

    // Get the fixed screen information
    struct fb_fix_screeninfo fix_info;

    if (ioctl(*fd, FBIOGET_FSCREENINFO, &fix_info) == -1)
    {
        close(*fd);
        return;
    }

    // Get the variable screen information
    struct fb_var_screeninfo var_info;

    if (ioctl(*fd, FBIOGET_VSCREENINFO, &var_info) == -1)
    {
        close(*fd);
        return;
    }

    // Map the framebuffer memory into user space
    char *fb_mem = (char *)mmap(0, fix_info.smem_len, PROT_READ | PROT_WRITE, MAP_SHARED, *fd, 0);

    if (fb_mem == (char *)-1)
    {
        close(*fd);
        return;
    }

    // Draw a point at (x, y)
    int bpp = var_info.bits_per_pixel / 8; // Bytes per pixel
    long location;
    int px, py;
    int max_delta = __abs(x2 - x) > __abs(y2 - y) ? __abs(x2 - x) : __abs(y2 - y);
    for (int i = 0; i <= max_delta; i++)
    {
        px = x + (double)i / (double)max_delta * (x2 - x);
        py = y + (double)i / (double)max_delta * (y2 - y);
        location = (px + var_info.xoffset) * bpp +
                   (py + var_info.yoffset) * fix_info.line_length;
        *(fb_mem + location) = color & 0xff;             // Blue
        *(fb_mem + location + 1) = (color >> 8) & 0xff;  // Green
        *(fb_mem + location + 2) = (color >> 16) & 0xff; // Red
    }
    // Unmap the framebuffer memory and close the device
    munmap(fb_mem, fix_info.smem_len);
}

void set_echo_on()
{
    // Get the terminal attributes
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);

    // Turn on echo
    term.c_lflag |= ECHO;

    // Set the new attributes
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void set_echo_off()
{
    // Get the terminal attributes
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);

    // Turn off echo
    term.c_lflag &= ~ECHO;

    // Set the new attributes
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void get_terminal_size(int *width, int *height)
{
    struct winsize ws;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
    *width = ws.ws_col;
    *height = ws.ws_row;
}

// 这个一定要求x2 >= x1, y2 >= y1
void draw_rect(int *fd, int x, int y, int x2, int y2, unsigned int color)
{

    // Get the fixed screen information
    struct fb_fix_screeninfo fix_info;

    if (ioctl(*fd, FBIOGET_FSCREENINFO, &fix_info) == -1)
    {
        close(*fd);
        return;
    }

    // Get the variable screen information
    struct fb_var_screeninfo var_info;

    if (ioctl(*fd, FBIOGET_VSCREENINFO, &var_info) == -1)
    {
        close(*fd);
        return;
    }

    // Map the framebuffer memory into user space
    char *fb_mem = (char *)mmap(0, fix_info.smem_len, PROT_READ | PROT_WRITE, MAP_SHARED, *fd, 0);

    if (fb_mem == (char *)-1)
    {
        close(*fd);
        return;
    }

    // Draw a point at (x, y)
    int bpp = var_info.bits_per_pixel / 8; // Bytes per pixel
    long location;
    int px, py;
    for (px = x, py = y; py <= y2; py++)
    {
        for (px = x; px <= x2; px++)
        {
            location = (px + var_info.xoffset) * bpp +
                       (py + var_info.yoffset) * fix_info.line_length;
            *(fb_mem + location) = color & 0xff;             // Blue
            *(fb_mem + location + 1) = (color >> 8) & 0xff;  // Green
            *(fb_mem + location + 2) = (color >> 16) & 0xff; // Red
        }
    }
    // Unmap the framebuffer memory and close the device
    munmap(fb_mem, fix_info.smem_len);
}
