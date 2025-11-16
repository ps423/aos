/*
 * Q.2) Implement the following unix/linux command (use fork, pipe and exec system call) ls -l | wc -l
 * [20 Marks]
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    int p[2];
    if (pipe(p) == -1) { perror("pipe"); return 1; }

    pid_t c1 = fork();
    if (c1 == -1) { perror("fork"); return 1; }

    if (c1 == 0) {
        dup2(p[1], STDOUT_FILENO);
        close(p[0]); close(p[1]);
        execlp("ls", "ls", "-l", (char*)NULL);
        perror("execlp ls"); _exit(127);
    }

    pid_t c2 = fork();
    if (c2 == -1) { perror("fork"); return 1; }

    if (c2 == 0) {
        dup2(p[0], STDIN_FILENO);
        close(p[0]); close(p[1]);
        execlp("wc", "wc", "-l", (char*)NULL);
        perror("execlp wc"); _exit(127);
    }

    close(p[0]); close(p[1]);
    waitpid(c1, NULL, 0);
    waitpid(c2, NULL, 0);
    return 0;
}
