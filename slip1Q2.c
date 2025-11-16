/*
 * Q.2) Write a C program to send SIGALRM signal by child process to parent process and parent process make a provision to catch the signal and display alarm is fired.(Use Kill, fork, signal and sleep system call)
 * [20 Marks]
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void alarm_handler(int sig) {
    printf("Parent: alarm is fired (caught SIGALRM from child)\n");
}

int main(void) {
    pid_t pid;
    signal(SIGALRM, alarm_handler);

    pid = fork();
    if (pid < 0) { perror("fork"); exit(1); }
    if (pid == 0) {
        sleep(2);
        kill(getppid(), SIGALRM);
        _exit(0);
    } else {
        wait(NULL);
    }
    return 0;
}
