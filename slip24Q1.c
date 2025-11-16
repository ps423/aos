/*
 * Q.1) Print the type of file and inode number where file name accepted through Command Line
 * [10 Marks]
 */

#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    struct stat st;
    if (stat(argv[1], &st) == -1) {
        perror("stat");
        return 1;
    }

    printf("File Type: ");
    if (S_ISREG(st.st_mode)) printf("Regular File\n");
    else if (S_ISDIR(st.st_mode)) printf("Directory\n");
    else if (S_ISCHR(st.st_mode)) printf("Character Device\n");
    else if (S_ISBLK(st.st_mode)) printf("Block Device\n");
    else if (S_ISFIFO(st.st_mode)) printf("FIFO\n");
    else if (S_ISLNK(st.st_mode)) printf("Symbolic Link\n");
    else if (S_ISSOCK(st.st_mode)) printf("Socket\n");
    else printf("Unknown\n");

    printf("Inode: %lu\n", st.st_ino);
    return 0;
}
