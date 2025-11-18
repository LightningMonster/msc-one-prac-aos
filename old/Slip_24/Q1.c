// Slip 24 Q1: Send SIGALRM from child to parent (same as Slip 18 Q1)
// COMPILE: gcc -o Q1 Q1.c
// EXAMPLE: ./Q1 => SIGALRM signal demo
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <stdlib.h>

int alarm_fired = 0;

void alarm_handler(int sig) {
    alarm_fired = 1;
    printf("Parent: Alarm is fired!\n");
}

int main() {
    pid_t pid;
    
    signal(SIGALRM, alarm_handler);
    
    pid = fork();
    
    if (pid < 0) {
        perror("fork");
        return 1;
    } else if (pid == 0) {
        // Child process
        printf("Child: PID = %d\n", getpid());
        printf("Child: Sleeping for 3 seconds...\n");
        sleep(3);
        
        printf("Child: Sending SIGALRM to parent (PID %d)\n", getppid());
        kill(getppid(), SIGALRM);
        
        exit(0);
    } else {
        // Parent process
        printf("Parent: PID = %d, waiting for alarm...\n", getpid());
        
        while (!alarm_fired) {
            sleep(1);
        }
        
        wait(NULL);
        printf("Parent: Child terminated\n");
    }
    
    return 0;
}
