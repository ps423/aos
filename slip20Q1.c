/*
 * Q.1) Write a C program that illustrates suspending and resuming processes using signals
 * [10 Marks]
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

int main(void) {
    pid_t pid = fork();
    if (pid < 0) { perror("fork"); exit(1); }

    if (pid == 0) {
        // child: print numbers in a loop
        for (int i = 1; ; ++i) {
            printf("Child: i=%d\n", i);
            fflush(stdout);
            sleep(1);
        }
    } else {
        // parent: let child run 3 sec, then suspend, then resume
        sleep(3);
        printf("Parent: sending SIGSTOP to child\n");
        kill(pid, SIGSTOP);    // suspend child
        sleep(3);
        printf("Parent: sending SIGCONT to child\n");
        kill(pid, SIGCONT);    // resume child
        sleep(3);
        printf("Parent: killing child and exiting\n");
        kill(pid, SIGKILL);
        wait(NULL);
    }
    return 0;
}
