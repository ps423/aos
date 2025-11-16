/*
 * Q.2) Write a C program to implement the following unix/linux command (use fork, pipe and exec system call). Your program should block the signal Ctrl-C and Ctrl-\ signal during the execution. ls -l | wc -l
 * [20 Marks]
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void block_sigint_sigquit(void) {
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGINT);
    sigaddset(&set, SIGQUIT);
    if (sigprocmask(SIG_BLOCK, &set, NULL) == -1) { perror("sigprocmask"); exit(1); }
}

int main(void) {
    int fd[2];
    pid_t c1, c2;
    block_sigint_sigquit();

    if (pipe(fd) == -1) { perror("pipe"); exit(1); }

    c1 = fork();
    if (c1 == 0) {
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]); close(fd[1]);
        execlp("ls", "ls", "-l", (char*)NULL);
        perror("execlp ls"); _exit(1);
    }

    c2 = fork();
    if (c2 == 0) {
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]); close(fd[1]);
        execlp("wc", "wc", "-l", (char*)NULL);
        perror("execlp wc"); _exit(1);
    }

    close(fd[0]); close(fd[1]);
    waitpid(c1, NULL, 0);
    waitpid(c2, NULL, 0);
    return 0;
}
