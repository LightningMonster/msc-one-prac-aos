#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

pid_t child_pid;

// Handler for SIGCHLD (when child finishes)
void child_handler(int sig) {
    printf("\n[Parent] Child process has terminated.\n");
}

// Handler for SIGALRM (5-second timeout)
void alarm_handler(int sig) {
    printf("\n[Parent] Child did not finish in 5 seconds. Killing child...\n");
    kill(child_pid, SIGKILL);
}

int main() {

    // Register signal handlers
    signal(SIGCHLD, child_handler);
    signal(SIGALRM, alarm_handler);

    child_pid = fork();

    if (child_pid < 0) {
        perror("fork failed");
        return 1;
    }

    // -------------------- CHILD PROCESS --------------------
    if (child_pid == 0) {
        printf("[Child] Running command: sleep 10\n");
        execlp("sleep", "sleep", "10", NULL);   // Example long command
        perror("exec failed");
        exit(1);
    }

    // -------------------- PARENT PROCESS --------------------
    else {
        printf("[Parent] Waiting 5 seconds for child...\n");

        alarm(5);    // Start 5-second timer
        
        wait(NULL);  // Wait for child to finish OR be killed

        alarm(0);    // Cancel alarm if child finished early
    }

    return 0;
}

/*
    Compile & Run:
    gcc Q2_Child_Command_WithTimeout.c
    ./a.out
*/
