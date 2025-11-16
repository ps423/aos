/*
 * Q.1) Take multiple files as Command Line Arguments and print their inode numbers and file types
 * [10 Marks]
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    struct stat st;
    int i;

    if (argc < 2) {
        printf("Usage: %s <file> [file...]\n", argv[0]);
        return 1;
    }

    for (i = 1; i < argc; i++) {
        if (lstat(argv[i], &st) == -1) {
            perror(argv[i]);
            continue;
        }

        printf("File: %s\n", argv[i]);
        printf("Inode: %lu\n", (unsigned long)st.st_ino);

        if (S_ISREG(st.st_mode))
            printf("Type: regular file\n\n");
        else if (S_ISDIR(st.st_mode))
            printf("Type: directory\n\n");
        else if (S_ISLNK(st.st_mode))
            printf("Type: symbolic link\n\n");
        else if (S_ISCHR(st.st_mode))
            printf("Type: character device\n\n");
        else if (S_ISBLK(st.st_mode))
            printf("Type: block device\n\n");
        else if (S_ISFIFO(st.st_mode))
            printf("Type: FIFO/pipe\n\n");
        else if (S_ISSOCK(st.st_mode))
            printf("Type: socket\n\n");
        else
            printf("Type: unknown\n\n");
    }

    return 0;
}
