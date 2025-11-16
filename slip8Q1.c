/*
 * Q.1) Write a C program that redirects standard output to a file output.txt. (use of dup and open system call).
 * [10 Marks]
 */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(void) {
    int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) { perror("open"); return 1; }

    if (dup2(fd, STDOUT_FILENO) == -1) { perror("dup2"); return 1; }
    close(fd);

    printf("Hello via dup2!\n");
    return 0;
}
