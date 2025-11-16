#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    pid_t pid;
    int status;

    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }

    // ---------------- CHILD PROCESS ----------------
    if (pid == 0) {
        printf("Child: I am exiting with status 7\n");
        exit(7);   // Exit child with status value 7
    }

    // ---------------- PARENT PROCESS ----------------
    else {
        wait(&status);  // Wait for child to terminate

        if (WIFEXITED(status)) {
            printf("Parent: Child exited normally.\n");
            printf("Parent: Exit status = %d\n", WEXITSTATUS(status));
        } else {
            printf("Parent: Child did not exit normally.\n");
        }
    }

    return 0;
}

/*
    Compile & Run:
    gcc Q1_ChildExitStatus.c
    ./a.out
*/
