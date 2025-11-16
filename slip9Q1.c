/*
 * Q.1) Generate parent process to write unnamed pipe and will read from it
 * [10 Marks]
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
        close(p[1]);
        char buf[256];
        ssize_t n = read(p[0], buf, sizeof(buf)-1);
        if (n >= 0) {
            buf[n] = '\0';
            printf("Child got: %s\n", buf);
        }
        close(p[0]);
        return 0;
    } else {
        close(p[0]);
        const char *msg = "Hello from parent via pipe";
        write(p[1], msg, strlen(msg));
        close(p[1]);
        wait(NULL);
    }
    return 0;
}
