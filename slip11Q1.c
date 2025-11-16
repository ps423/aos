/*
 * Q.1) Write a C program to get and set the resource limits such as files, memory associated with a process
 * [10 Marks]
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <errno.h>

void print_rlimit(int resource, const char *name) {
    struct rlimit r;
    if (getrlimit(resource, &r) == -1) { perror("getrlimit"); return; }
    printf("%s: soft=", name);
    if (r.rlim_cur == RLIM_INFINITY) printf("infinity");
    else printf("%llu", (unsigned long long)r.rlim_cur);
    printf(", hard=");
    if (r.rlim_max == RLIM_INFINITY) printf("infinity");
    else printf("%llu", (unsigned long long)r.rlim_max);
    printf("\n");
}

int main(void) {
    struct rlimit r;
    
    // Display RLIMIT_NOFILE (max open files)
    print_rlimit(RLIMIT_NOFILE, "RLIMIT_NOFILE");
    
    // Display RLIMIT_AS (virtual memory size)
    print_rlimit(RLIMIT_AS, "RLIMIT_AS");
    
    // Display RLIMIT_DATA (data segment size)
    print_rlimit(RLIMIT_DATA, "RLIMIT_DATA");
    
    return 0;
}
