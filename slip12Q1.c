/*
 * Q.1) Write a C program that print the exit status of a terminated child process
 * [10 Marks]
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
    pid_t pid = fork();
    if (pid == 0) {
        // child: exit with code 7 (for demo)
        sleep(1);
        _exit(7);
    } else if (pid > 0) {
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)) {
            printf("Child exited normally with status = %d\n", WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("Child killed by signal %d\n", WTERMSIG(status));
        } else {
            printf("Child terminated with unknown status\n");
        }
    } else { perror("fork"); }
    return 0;
}
