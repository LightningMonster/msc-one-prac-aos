#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

pid_t child_pid;

// -------- CHILD HANDLERS --------
void handle_sighup(int sig) {
    printf("Child: I have received SIGHUP signal.\n");
}

void handle_sigint(int sig) {
    printf("Child: I have received SIGINT signal.\n");
}

void handle_sigquit(int sig) {
    printf("Child: My Papa has Killed me!!!\n");
    exit(0);
}

int main() {
    child_pid = fork();

    if (child_pid < 0) {
        printf("Fork Failed.\n");
        return 1;
    }

    // ----------------- CHILD PROCESS -----------------
    if (child_pid == 0) {
        // Set handlers for SIGHUP, SIGINT, SIGQUIT
        signal(SIGHUP, handle_sighup);
        signal(SIGINT, handle_sigint);
        signal(SIGQUIT, handle_sigquit);

        while (1) {
            pause();   // Wait for signals
        }
    }

    // ----------------- PARENT PROCESS -----------------
    else {
        for (int t = 3; t <= 15; t += 3) {
            sleep(3);

            if (t == 15) {
                printf("Parent: Sending SIGQUIT to child...\n");
                kill(child_pid, SIGQUIT);
            } else {
                printf("Parent: Sending SIGHUP and SIGINT...\n");
                kill(child_pid, SIGHUP);
                kill(child_pid, SIGINT);
            }
        }
    }

    return 0;
}

/*
    For output use the following commands:
    gcc Q2_Child_CatchSignals.c
    ./a.out
*/
