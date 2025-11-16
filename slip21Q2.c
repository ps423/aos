/*
 * Q.2) Write a C program which receives file names as command line arguments and display those filenames in ascending order according to their sizes. (e.g $ a.out a.txt b.txt c.txt, )
 * [20 Marks]
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

typedef struct {
    char *name;
    off_t size;
} FileInfo;

static int cmp_size_asc(const void *a, const void *b) {
    const FileInfo *x = a, *y = b;
    if (x->size < y->size) return -1;
    if (x->size > y->size) return 1;
    return strcmp(x->name, y->name);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <file1> <file2> ...\n", argv[0]);
        return 1;
    }

    int n = argc - 1, i, count = 0;
    FileInfo *arr = calloc(n, sizeof(*arr));
    if (!arr) { perror("Calloc"); return 1; }

    for (i = 1; i < argc; i++) {
        struct stat st;
        if (stat(argv[i], &st) == -1) {
            perror(argv[i]);
            continue;
        }
        arr[count].name = argv[i];
        arr[count].size = st.st_size;
        count++;
    }

    qsort(arr, count, sizeof(*arr), cmp_size_asc);

    puts("Files in ascending order of size:");
    for (i = 0; i < count; i++)
        printf("%s (%ld bytes)\n", arr[i].name, (long)arr[i].size);

    free(arr);
    return 0;
}
