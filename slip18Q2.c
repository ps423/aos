/*
 * Q.2) Write a C program to create an unnamed pipe. The child process will write following three messages to pipe and parent process display it. Message1 = 'Hello World' Message2 = 'Hello SPPU' Message3 = 'Linux is Funny'
 * [20 Marks]
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(void) {
    int fd[2];
    pid_t pid;
    char buf[256];
    
    if (pipe(fd) == -1) { perror("pipe"); exit(1); }

    pid = fork();
    if (pid < 0) { perror("fork"); exit(1); }

    if (pid == 0) {
        close(fd[0]);
        const char *m1 = "Hello World\n";
        const char *m2 = "Hello SPPU\n";
        const char *m3 = "Linux is Funny\n";
        write(fd[1], m1, strlen(m1));
        write(fd[1], m2, strlen(m2));
        write(fd[1], m3, strlen(m3));
        close(fd[1]);
        exit(0);
    } else {
        close(fd[1]);
        ssize_t n;
        while ((n = read(fd[0], buf, sizeof(buf)-1)) > 0) {
            buf[n] = '\0';
            printf("%s", buf);
        }
        close(fd[0]);
        wait(NULL);
    }
    return 0;
}
