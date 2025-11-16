/*
 * Q.1) Read the current directory and display the name of the files, no of files in current directory
 * [10 Marks]
 */

#include <stdio.h>
#include <dirent.h>

int main() {
    DIR *dir = opendir(".");
    struct dirent *entry;
    int count = 0;

    if (!dir) {
        perror("opendir");
        return 1;
    }

    printf("Files in current directory:\n");
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
        count++;
    }

    closedir(dir);
    printf("Total number of entries: %d\n", count);
    return 0;
}
