#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    int fd[2];

    if (pipe(fd) == -1) {
        perror("Pipe creation failed");
        return 1;
    }

    pid_t pid1 = fork();
    if (pid1 < 0) {
        perror("Fork failed");
        return 1;
    }

    // ---------------- FIRST CHILD: executes first command ----------------
    if (pid1 == 0) {
        close(fd[0]);                 // Close read end
        dup2(fd[1], STDOUT_FILENO);   // Write output → pipe
        close(fd[1]);

        execlp("ls", "ls", "-l", NULL);   // Example command 1
        perror("exec ls failed");
        exit(1);
    }

    pid_t pid2 = fork();
    if (pid2 < 0) {
        perror("Fork failed");
        return 1;
    }

    // ---------------- SECOND CHILD: executes second command ----------------
    if (pid2 == 0) {
        close(fd[1]);                 // Close write end
        dup2(fd[0], STDIN_FILENO);    // Read input ← pipe
        close(fd[0]);

        execlp("wc", "wc", "-l", NULL);   // Example command 2
        perror("exec wc failed");
        exit(1);
    }

    // ---------------- PARENT PROCESS ----------------
    close(fd[0]);
    close(fd[1]);

    // Wait for both children
    wait(NULL);
    wait(NULL);

    return 0;
}

/*
    Compile & Run:
    gcc Q1_ConcurrentCommandsPipe.c
    ./a.out
*/
