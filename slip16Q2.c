/*
 * Q.2) Write a C program which create a child process which catch a signal sighup, sight and sigquit. The Parent process send a sighup or sight signal after every 3 seconds, at the end of 30 second parent send sigquit signal to child and child terminates my displaying message 'My DADDY has Killed me!!!'.
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
        printf("My DADDY has Killed me!!!\n");
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
        // send signal every 3 sec for 30 sec (i.e., 10 times), alternate SIGHUP/SIGINT
        for (int i = 1; i <= 10; ++i) {
            sleep(3);
            if (i % 2 == 1) kill(pid, SIGHUP);
            else kill(pid, SIGINT);
        }
        // after 30 seconds, send SIGQUIT
        kill(pid, SIGQUIT);
        wait(NULL);
    }
    return 0;
}
