/*
 * Q.2) Generate parent process to write unnamed pipe and will write into it. Also generate child process which will read from pipe
 * [20 Marks]
 */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(void) {
    int p[2];
    if (pipe(p) == -1) { perror("pipe"); return 1; }

    pid_t pid = fork();
    if (pid == -1) { perror("fork"); return 1; }

    if (pid == 0) {
        close(p[0]);
        const char *msg = "Hello from parent via pipe";
        write(p[1], msg, strlen(msg));
        close(p[1]);
        return 0;
    } else {
        close(p[1]);
        char buf[256];
        ssize_t n = read(p[0], buf, sizeof(buf)-1);
        if (n >= 0) {
            buf[n] = '\0';
            printf("Parent got: %s\n", buf);
        }
        close(p[0]);
        wait(NULL);
    }
    return 0;
}
