#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include "api.h"
void my_handler(int signum)
{
    // Do something here, such as drawing a point on the framebuffer
    update_screen();
    // Schedule the next alarm after 1 second
    alarm(1);
}

int main()
{
    int fd;
    open_framebuffer(&fd);

    signal(SIGALRM, my_handler); // Set up the signal handler for SIGALRM

    // Schedule the first alarm after 1 second
    alarm(1);

    // Wait indefinitely for signals to arrive
    while (1)
    {
        pause();
    }

    close_framebuffer(&fd);

    return 0;
}
