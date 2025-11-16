/*
 * Q.1) Write a C program to find file properties such as inode number, number of hard link, File permissions, File size, File access and modification time and so on of a given file using stat() system call.
 * [10 Marks]
 */

#include <stdio.h>
#include <sys/stat.h>
#include <time.h>

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

    printf("File: %s\n", argv[1]);
    printf("Inode: %lu\n", st.st_ino);
    printf("Links: %ld\n", st.st_nlink);
    printf("Size: %ld bytes\n", st.st_size);
    printf("Permissions: %o\n", st.st_mode & 0777);
    printf("Last Access: %s", ctime(&st.st_atime));
    printf("Last Modification: %s", ctime(&st.st_mtime));
    return 0;
}
