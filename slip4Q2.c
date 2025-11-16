/*
 * Q.2) Write a C program which creates a child process and child process catches a signal SIGHUP, SIGINT and SIGQUIT. The Parent process send a SIGHUP or SIGINT signal after every 3 seconds, at the end of 15 second parent send SIGQUIT signal to child and child terminates by displaying message 'My Papa has Killed me!!!'.
 * [20 Marks]
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

void handler(int sig) {
    if (sig == SIGHUP) printf("Child: received SIGHUP\n");
    else if (sig == SIGINT) printf("Child: received SIGINT\n");
    else if (sig == SIGQUIT) {
        printf("My Papa has Killed me!!!\n");
        _exit(0);
    }
}

int main(void) {
    pid_t pid = fork();
    if (pid < 0) { perror("fork"); exit(1); }
    if (pid == 0) {
        signal(SIGHUP, handler);
        signal(SIGINT, handler);
        signal(SIGQUIT, handler);
        while (1) pause();
    } else {
        int t;
        for (t = 3; t <= 15; t += 3) {
            sleep(3);
            if ((t/3) % 2 == 1) kill(pid, SIGHUP);
            else kill(pid, SIGINT);
        }
        kill(pid, SIGQUIT);
        wait(NULL);
    }
    return 0;
}
