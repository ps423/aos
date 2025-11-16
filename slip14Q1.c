/*
 * Q.1) Display all the files from current directory whose size is greater that n Bytes Where n is accept from user.
 * [10 Marks]
 */

#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>

int main(void) {
    long n;
    printf("Enter size threshold (bytes): ");
    if (scanf("%ld", &n) != 1 || n < 0) {
        fprintf(stderr, "Invalid size.\n");
        return 1;
    }

    DIR *d = opendir("."); 
    if (!d) { perror("opendir"); return 1; }

    struct dirent *e;
    while ((e = readdir(d)) != NULL) {
        struct stat st;
        if (lstat(e->d_name, &st) == -1) continue;
        if (S_ISREG(st.st_mode) && st.st_size > n)
            printf("%s (%ld bytes)\n", e->d_name, (long)st.st_size);
    }
    closedir(d);
    return 0;
}
