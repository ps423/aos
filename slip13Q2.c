/*
 * Q.2) Write a C program that a string as an argument and return all the files that begins with that name in the current directory. For example > ./a.out foo will return all file names that begins with foo
 * [20 Marks]
 */

#include <stdio.h>
#include <dirent.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <prefix>\n", argv[0]);
        return 1;
    }

    DIR *dir = opendir(".");
    struct dirent *entry;
    int len = strlen(argv[1]);

    printf("Files starting with '%s':\n", argv[1]);
    while ((entry = readdir(dir)) != NULL) {
        if (strncmp(entry->d_name, argv[1], len) == 0) {
            printf("%s\n", entry->d_name);
        }
    }
    closedir(dir);
    return 0;
}
