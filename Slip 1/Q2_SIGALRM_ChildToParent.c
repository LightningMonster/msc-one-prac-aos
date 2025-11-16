#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>

// Signal handler function for SIGALRM
void alarm_handler(int sig) {
    printf("\nAlarm is fired! (SIGALRM received)\n");
}

int main() {
    pid_t pid;

    // Register signal handler in parent process
    signal(SIGALRM, alarm_handler);

    pid = fork();

    if (pid < 0) {
        printf("Fork failed.\n");
        return 1;
    }

    // Child Process
    if (pid == 0) {
        sleep(3); // Wait before sending signal
        kill(getppid(), SIGALRM); // Send SIGALRM to parent
    }
    // Parent Process
    else {
        printf("Parent waiting for SIGALRM...\n");
        pause();  // Wait for signal
    }

    return 0;
}

/*
    // For output use the following commands:
    // gcc Q2_SIGALRM_ChildToParent.c
    // ./a.out
*/
