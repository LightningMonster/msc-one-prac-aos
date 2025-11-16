#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

pid_t child_pid;

// Handler for SIGCHLD (child finished)
void child_exit_handler(int sig) {
    printf("\n[Parent] Child process has terminated.\n");
}

// Handler for SIGALRM (timeout)
void alarm_handler(int sig) {
    printf("\n[Parent] Child did not finish in 5 seconds. Killing child...\n");
    kill(child_pid, SIGKILL);
}

int main() {
    // Set parent signal handlers
    signal(SIGCHLD, child_exit_handler);
    signal(SIGALRM, alarm_handler);

    child_pid = fork();

    if (child_pid < 0) {
        perror("fork failed");
        return 1;
    }

    // ---------------- CHILD PROCESS ----------------
    if (child_pid == 0) {
        printf("[Child] Running command: sleep 10\n");
        execlp("sleep", "sleep", "10", NULL);   // Example long-running command
        perror("exec failed");
        exit(1);
    }

    // ---------------- PARENT PROCESS ----------------
    else {
        printf("[Parent] Child started. Waiting max 5 seconds...\n");

        alarm(5);                // Activate 5-second timer
        wait(NULL);              // Wait until child ends or parent kills it
        alarm(0);                // Cancel alarm if child already finished
    }

    return 0;
}

/*
    Compile & Run:
    gcc Q2_ChildCommand_WithTimeout.c
    ./a.out
*/
