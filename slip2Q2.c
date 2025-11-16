/*
 * Q.2) Write a C program that catches the ctrl-c (SIGINT) signal for the first time and display the appropriate message and exits on pressing ctrl-c again.
 * [20 Marks]
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handler(int sig) {
    static int count = 0;
    count++;
    if (count == 1) {
        printf("\nSIGINT caught first time - press Ctrl-C again to exit.\n");
        signal(SIGINT, SIG_DFL);
    }
}

int main(void) {
    signal(SIGINT, handler);
    printf("Running... press Ctrl-C.\n");
    while (1) pause();
    return 0;
}
