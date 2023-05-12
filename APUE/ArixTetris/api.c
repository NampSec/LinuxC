#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>

void draw_point(int x, int y, int r, int g, int b) {
    // Open the framebuffer device
    int fd = open("/dev/fb0", O_RDWR);

    if (fd == -1) {
        return;
    }

    // Get the fixed screen information
    struct fb_fix_screeninfo fix_info;

    if (ioctl(fd, FBIOGET_FSCREENINFO, &fix_info) == -1) {
        close(fd);
        return;
    }

    // Get the variable screen information
    struct fb_var_screeninfo var_info;

    if (ioctl(fd, FBIOGET_VSCREENINFO, &var_info) == -1) {
        close(fd);
        return;
    }

    // Map the framebuffer memory into user space
    char* fb_mem = (char*)mmap(0, fix_info.smem_len, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    if (fb_mem == (char*)-1) {
        close(fd);
        return;
    }

    // Draw a point at (x, y)
    int bpp = var_info.bits_per_pixel / 8; // Bytes per pixel

    long location = (x + var_info.xoffset) * bpp +
                    (y + var_info.yoffset) * fix_info.line_length;

    *(fb_mem + location) = b; // Blue
    *(fb_mem + location + 1) = g; // Green
    *(fb_mem + location + 2) = r; // Red

    // Unmap the framebuffer memory and close the device
    munmap(fb_mem, fix_info.smem_len);
    close(fd);
}



void set_echo_on() {
    // Get the terminal attributes
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);

    // Turn on echo
    term.c_lflag |= ECHO;

    // Set the new attributes
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void set_echo_off() {
    // Get the terminal attributes
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);

    // Turn off echo
    term.c_lflag &= ~ECHO;

    // Set the new attributes
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}


void get_terminal_size(int* width, int* height) {
    struct winsize ws;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
    *width = ws.ws_col;
    *height = ws.ws_row;
}


