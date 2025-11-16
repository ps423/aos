/*
 * Q.1) Take multiple files as Command Line Arguments and print their file type and inode number
 * [10 Marks]
 */

#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    struct stat st;
    for (int i = 1; i < argc; i++) {
        if (stat(argv[i], &st) == 0) {
            printf("File: %s - Inode: %lu, Type: ", argv[i], st.st_ino);
            if (S_ISREG(st.st_mode)) printf("Regular File\n");
            else if (S_ISDIR(st.st_mode)) printf("Directory\n");
            else if (S_ISCHR(st.st_mode)) printf("Character Device\n");
            else if (S_ISBLK(st.st_mode)) printf("Block Device\n");
            else if (S_ISFIFO(st.st_mode)) printf("FIFO\n");
            else if (S_ISLNK(st.st_mode)) printf("Symbolic Link\n");
            else if (S_ISSOCK(st.st_mode)) printf("Socket\n");
            else printf("Unknown\n");
        } else {
            perror(argv[i]);
        }
    }
    return 0;
}
