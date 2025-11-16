/*
 * Q.1) Write a program that illustrates how to execute two commands concurrently with a pipe.
 * [10 Marks]
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    int fd[2];
    pid_t p1, p2;
    
    if (pipe(fd) == -1) { perror("pipe"); exit(1); }

    p1 = fork();
    if (p1 == 0) {
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]); close(fd[1]);
        execlp("ls", "ls", "-l", (char *)NULL);
        perror("execlp ls"); exit(1);
    }

    p2 = fork();
    if (p2 == 0) {
        dup2(fd[0], STDIN_FILENO);
        close(fd[1]); close(fd[0]);
        execlp("wc", "wc", "-l", (char *)NULL);
        perror("execlp wc"); exit(1);
    }

    close(fd[0]); close(fd[1]);
    waitpid(p1, NULL, 0);
    waitpid(p2, NULL, 0);
    return 0;
}
