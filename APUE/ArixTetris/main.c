#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include "api.h"
#include "game.h"
#include "queue.h"
unsigned int x_res, y_res;
point game_frame;
point nextblock_frame;
point score_frame;

unsigned int diamond, next_diamond;
point cur_diamond_pos;

void my_handler(int signum)
{
    // Do something here, such as drawing a point on the framebuffer
    update_screen();
    update_nextblock();
    // Schedule the next alarm after 1 second
    alarm(1);
}

int main()
{
    int ch;
    unsigned int turn_diamond;
    point temp = {0, 0, NULL};
    int fd;
    int flag = 1;
    set_echo_off();
    game_initialized();
    signal(SIGALRM, my_handler); // Set up the signal handler for SIGALRM

    // Schedule the first alarm after 1 second
    alarm(1);

    // Wait indefinitely for signals to arrive
    while (flag)
    {
        system("stty -icanon");
        ch = getchar();
        switch (ch)
        {
        case ' ':
            turn_diamond = matrix_turn_right(diamond);
            convert_blockpoint_respoint(&cur_diamond_pos, &temp);
            open_framebuffer(&fd);
            draw_rect(&fd, temp.x, temp.y - BLOCK_RES_SIZE * (DIAMOND_MATRIX_SIZE), temp.x + BLOCK_RES_SIZE * DIAMOND_MATRIX_SIZE, temp.y, BACKGROUND_COLOR);
            close_framebuffer(&fd);
            refresh_diamond(temp.x, temp.y, 0xffff, turn_diamond, 0, 0);
            diamond = turn_diamond;
            break;
        case 'a':
        case 'A':
            break;
        case 'd':
        case 'D':
            break;
        case 's':
        case 'S':
            while (update_screen());
            break;
        case 'q':
        case 'Q':
            flag = 0;
            break;
        default:
            break;
        }
        
    }
    set_echo_on();
    return 0;
}
