/*
 * Q.1) Write a C Program that demonstrates redirection of standard output to a file
 * [10 Marks]
 */

#include <stdio.h>

int main(void) {
    if (!freopen("output.txt", "w", stdout)) {
        perror("freopen");
        return 1;
    }
    printf("This line goes into output.txt\n");
    printf("So does this one.\n");
    return 0;
}
