/*
 * Q.2) Write a C program to create n child processes. When all n child processes terminates, Display total cumulative time children spent in user and kernel mode
 * [20 Marks]
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/resource.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n_children>\n", argv[0]);
        return 1;
    }
    int n = atoi(argv[1]);
    if (n <= 0) { fprintf(stderr, "n must be > 0\n"); return 1; }

    for (int i = 0; i < n; i++) {
        pid_t pid = fork();
        if (pid == -1) { perror("fork"); return 1; }
        if (pid == 0) {
            volatile unsigned long long x = 0;
            for (unsigned long long k = 0; k < 10000000ULL; k++) x += k;
            _exit(0);
        }
    }

    for (int i = 0; i < n; i++) wait(NULL);

    struct rusage ru;
    if (getrusage(RUSAGE_CHILDREN, &ru) == -1) { perror("getrusage"); return 1; }

    double ut = ru.ru_utime.tv_sec + ru.ru_utime.tv_usec/1e6;
    double st = ru.ru_stime.tv_sec + ru.ru_stime.tv_usec/1e6;
    printf("Children total user time : %.6f s\n", ut);
    printf("Children total kernel time: %.6f s\n", st);
    return 0;
}
