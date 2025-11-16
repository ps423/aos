/*
 * Q.2) Write a C program which creates a child process to run linux/ unix command or any user defined program. The parent process set the signal handler for death of child signal and Alarm signal. If a child process does not complete its execution in 5 second then parent process kills child process.
 * [20 Marks]
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

pid_t child = -1;

void sigchild_handler(int sig) {
    int status;
    pid_t p = waitpid(child, &status, WNOHANG);
    if (p == child) {
        if (WIFEXITED(status)) printf("Child exited with code %d\n", WEXITSTATUS(status));
        else if (WIFSIGNALED(status)) printf("Child killed by signal %d\n", WTERMSIG(status));
    }
}

void sigalrm_handler(int sig) {
    if (child > 0) {
        printf("Timeout: killing child %d\n", child);
        kill(child, SIGKILL);
    }
}

int main(int argc, char *argv[]) {
    char *cmd = "sleep";
    char *arg = "10";
    if (argc >= 2) cmd = argv[1];
    if (argc >= 3) arg = argv[2];

    signal(SIGCHLD, sigchild_handler);
    signal(SIGALRM, sigalrm_handler);

    child = fork();
    if (child < 0) { perror("fork"); exit(1); }
    if (child == 0) {
        execlp(cmd, cmd, arg, (char *)NULL);
        perror("execlp"); _exit(1);
    } else {
        alarm(5);
        while (1) {
            pause();
            int status;
            pid_t r = waitpid(child, &status, WNOHANG);
            if (r == child) break;
        }
        printf("Parent exiting\n");
    }
    return 0;
}
