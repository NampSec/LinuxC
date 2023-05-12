#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void my_handler(int signum) {
    // Do something here, such as drawing a point on the framebuffer

    // Schedule the next alarm after 1 second
    alarm(1);
}

int main() {
    signal(SIGALRM, my_handler); // Set up the signal handler for SIGALRM

    // Schedule the first alarm after 1 second
    alarm(1);

    // Wait indefinitely for signals to arrive
    while (1) {
        pause();
    }

    return 0;
}
