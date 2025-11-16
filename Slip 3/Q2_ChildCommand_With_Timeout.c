#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <stdlib.h>

pid_t child_pid;

// Handler for SIGCHLD (child terminated)
void child_handler(int sig) {
    printf("\nChild process finished normally.\n");
}

// Handler for SIGALRM (5 seconds exceeded)
void alarm_handler(int sig) {
    printf("\nChild took too long! Killing child process...\n");
    kill(child_pid, SIGKILL);
}

int main() {
    signal(SIGCHLD, child_handler);  // Handle child completion
    signal(SIGALRM, alarm_handler);  // Handle timeout

    child_pid = fork();

    if (child_pid < 0) {
        printf("Fork failed.\n");
        exit(1);
    }

    // Child process
    if (child_pid == 0) {
        printf("Child running command: sleep 10\n");
        execlp("sleep", "sleep", "10", NULL);   // Example command
        perror("exec failed");
        exit(1);
    }

    // Parent process
    else {
        printf("Parent: Waiting for child for max 5 seconds...\n");
        alarm(5);          // Set 5-second timer
        waitpid(child_pid, NULL, 0);  // Wait for child or kill
        alarm(0);          // Cancel alarm if child finished early
    }

    return 0;
}

/*
    For execution use the following commands:
    gcc Q2_ChildCommand_With_Timeout.c
    ./a.out
*/
