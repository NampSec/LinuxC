#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include "api.h"
#include "game.h"
#include "queue.h"
unsigned int x_res, y_res;
point game_frame;
point nextblock_frame;
point score_frame;
void my_handler(int signum)
{
    // Do something here, such as drawing a point on the framebuffer
    update_screen();
    // Schedule the next alarm after 1 second
    alarm(1);
}

int main()
{
    set_echo_off();
    game_initialized();
    signal(SIGALRM, my_handler); // Set up the signal handler for SIGALRM

    // Schedule the first alarm after 1 second
    alarm(1);

    // Wait indefinitely for signals to arrive
    while (1)
    {
        
        pause();
    }
    set_echo_on();
    return 0;
}
