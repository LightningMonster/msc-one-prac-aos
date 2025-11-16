#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }

    // ---------------- CHILD PROCESS ----------------
    if (pid == 0) {
        int i = 1;
        while (1) {
            printf("Child running... (%d)\n", i++);
            sleep(1);
        }
    }

    // ---------------- PARENT PROCESS ----------------
    else {
        sleep(3);
        printf("\nParent: Sending SIGSTOP (suspend child)\n");
        kill(pid, SIGSTOP);     // suspend child

        sleep(3);
        printf("\nParent: Sending SIGCONT (resume child)\n");
        kill(pid, SIGCONT);     // resume child

        sleep(3);
        printf("\nParent: Sending SIGKILL to terminate child\n");
        kill(pid, SIGKILL);

        wait(NULL);
    }

    return 0;
}

/*
    Compile & Run:
    gcc Q1_SuspendResumeProcess.c
    ./a.out
*/
