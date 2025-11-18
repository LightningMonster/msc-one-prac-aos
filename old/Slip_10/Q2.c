// Slip 10 Q2: Suspend and resume processes using signals
// COMPILE: gcc -o Q2 Q2.c
// EXAMPLE: ./Q2 => SIGSTOP/SIGCONT demo
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

int suspended = 0;

void suspend_handler(int sig) {
    suspended = 1;
    printf("\nProcess suspended. Press Ctrl+Z again or 'fg' command to resume...\n");
}

void resume_handler(int sig) {
    suspended = 0;
    printf("Process resumed\n");
}

int main() {
    signal(SIGTSTP, suspend_handler);  // Ctrl+Z
    signal(SIGCONT, resume_handler);   // Continue
    
    printf("Process running. Press Ctrl+Z to suspend, Ctrl+C to exit\n");
    printf("=========================================================\n");
    
    int count = 0;
    while (1) {
        if (!suspended) {
            printf("Count: %d\n", count++);
            sleep(1);
        } else {
            sleep(1);  // While suspended, just sleep
        }
    }
    
    return 0;
}
