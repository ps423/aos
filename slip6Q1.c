/*
 * Q.1) Display all the files from current directory which are created in particular month
 * [10 Marks]
 */

#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>

int main(void) {
    int month;
    printf("Enter month (1-12): ");
    if (scanf("%d", &month) != 1 || month < 1 || month > 12) {
        fprintf(stderr, "Invalid month.\n");
        return 1;
    }

    DIR *d = opendir("."); 
    if (!d) { perror("opendir"); return 1; }

    struct dirent *e; 
    while ((e = readdir(d)) != NULL) {
        struct stat st;
        if (lstat(e->d_name, &st) == -1) continue;
        if (!S_ISREG(st.st_mode) && !S_ISLNK(st.st_mode)) continue;
        struct tm *tm = localtime(&st.st_mtime);
        if (tm && (tm->tm_mon + 1) == month)
            printf("%s\n", e->d_name);
    }
    closedir(d);
    return 0;
}
