#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>

pid_t child_pid;

// ---------- CHILD HANDLERS ----------
void handle_sighup(int sig) {
    printf("Child: I have received SIGHUP signal.\n");
}

void handle_sigint(int sig) {
    printf("Child: I have received SIGINT signal.\n");
}

void handle_sigquit(int sig) {
    printf("Child: My DADDY has Killed me!!!\n");
    exit(0);
}

int main() {
    child_pid = fork();

    if (child_pid < 0) {
        perror("Fork failed");
        return 1;
    }

    // --------------------- CHILD PROCESS ---------------------
    if (child_pid == 0) {
        signal(SIGHUP, handle_sighup);
        signal(SIGINT, handle_sigint);
        signal(SIGQUIT, handle_sigquit);

        while (1) {
            pause();   // Wait for signals
        }
    }

    // --------------------- PARENT PROCESS ---------------------
    else {
        printf("Parent: Sending signals for 30 seconds...\n");

        for (int t = 3; t <= 30; t += 3) {
            sleep(3);

            if (t == 30) {
                printf("\nParent: Sending SIGQUIT to child\n");
                kill(child_pid, SIGQUIT);
            } else {
                printf("Parent: Sending SIGHUP and SIGINT...\n");
                kill(child_pid, SIGHUP);
                kill(child_pid, SIGINT);
            }
        }

        wait(NULL);  // Wait for child to exit
    }

    return 0;
}

/*
    Compile & Run:
    gcc Q2_Child_CatchSignals2.c
    ./a.out
*/
