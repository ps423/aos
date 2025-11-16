/*
 * Q.2) Write a C program to Identify the type (Directory, character device, Block device, Regular file, FIFO or pipe, symbolic link or socket) of given file using stat() system call.
 * [20 Marks]
 */

#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    struct stat fileStat;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    if (stat(argv[1], &fileStat) == -1) {
        perror("stat");
        return 1;
    }

    if (S_ISREG(fileStat.st_mode))
        printf("%s is a Regular File\n", argv[1]);
    else if (S_ISDIR(fileStat.st_mode))
        printf("%s is a Directory\n", argv[1]);
    else if (S_ISCHR(fileStat.st_mode))
        printf("%s is a Character Device\n", argv[1]);
    else if (S_ISBLK(fileStat.st_mode))
        printf("%s is a Block Device\n", argv[1]);
    else if (S_ISFIFO(fileStat.st_mode))
        printf("%s is a FIFO (named pipe)\n", argv[1]);
    else if (S_ISLNK(fileStat.st_mode))
        printf("%s is a Symbolic Link\n", argv[1]);
    else if (S_ISSOCK(fileStat.st_mode))
        printf("%s is a Socket\n", argv[1]);
    else
        printf("%s is of Unknown type\n", argv[1]);

    return 0;
}
