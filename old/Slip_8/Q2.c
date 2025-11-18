// Slip 8 Q2: Child process with timeout (same as Slip 2 Q2)
// COMPILE: gcc -o Q2 Q2.c
// EXAMPLE: ./Q2 => Timeout demo
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <stdlib.h>

int child_dead = 0;
int alarm_fired = 0;

void child_handler(int sig) {
    child_dead = 1;
    printf("Parent: Child process died\n");
}

void alarm_handler(int sig) {
    alarm_fired = 1;
    printf("Parent: Alarm fired! 5 seconds exceeded\n");
}

int main(int argc, char *argv[]) {
    pid_t pid;
    int status;
    
    if (argc < 2) {
        printf("Usage: %s <command> [args...]\n", argv[0]);
        return 1;
    }
    
    pid = fork();
    
    if (pid < 0) {
        perror("fork");
        return 1;
    } else if (pid == 0) {
        // Child process - execute command
        execvp(argv[1], &argv[1]);
        perror("execvp");
        exit(1);
    } else {
        // Parent process - set signal handlers
        signal(SIGCHLD, child_handler);
        signal(SIGALRM, alarm_handler);
        
        // Set alarm for 5 seconds
        alarm(5);
        
        // Wait for child
        waitpid(pid, &status, 0);
        
        if (alarm_fired && !WIFEXITED(status)) {
            printf("Parent: Child did not complete in 5 seconds, killing it\n");
            kill(pid, SIGKILL);
            wait(&status);
        } else {
            printf("Parent: Child completed within 5 seconds\n");
        }
    }
    
    return 0;
}
