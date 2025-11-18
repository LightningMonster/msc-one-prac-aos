// Slip 12 Q2: Child catches SIGHUP, SIGINT, SIGQUIT (same as Slip 6 Q2)
// COMPILE: gcc -o Q2 Q2.c
// EXAMPLE: ./Q2 => Signal handling
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <time.h>

int sighup_count = 0;
int sigint_count = 0;
int quit_signal = 0;

void child_sighup(int sig) {
    sighup_count++;
    printf("Child: SIGHUP received (%d times)\n", sighup_count);
}

void child_sigint(int sig) {
    sigint_count++;
    printf("Child: SIGINT received (%d times)\n", sigint_count);
}

void child_sigquit(int sig) {
    quit_signal = 1;
    printf("Child: My Papa has Killed me!!!\n");
}

int main() {
    pid_t pid;
    int elapsed = 0;
    
    pid = fork();
    
    if (pid < 0) {
        perror("fork");
        return 1;
    } else if (pid == 0) {
        // Child process
        signal(SIGHUP, child_sighup);
        signal(SIGINT, child_sigint);
        signal(SIGQUIT, child_sigquit);
        
        printf("Child: PID = %d, waiting for signals...\n", getpid());
        
        while (!quit_signal) {
            sleep(1);
        }
        
        exit(0);
    } else {
        // Parent process
        printf("Parent: Child PID = %d\n", pid);
        
        // Send signals every 3 seconds for 15 seconds
        for (elapsed = 0; elapsed < 15; elapsed += 3) {
            sleep(3);
            
            if (elapsed < 12) {
                if (elapsed % 6 == 0) {
                    printf("Parent: Sending SIGHUP\n");
                    kill(pid, SIGHUP);
                } else {
                    printf("Parent: Sending SIGINT\n");
                    kill(pid, SIGINT);
                }
            }
        }
        
        printf("Parent: Sending SIGQUIT at 15 seconds\n");
        kill(pid, SIGQUIT);
        
        wait(NULL);
        printf("Parent: Child terminated\n");
    }
    
    return 0;
}
