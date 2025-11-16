#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    int fd[2];

    // Create pipe
    if (pipe(fd) == -1) {
        perror("pipe failed");
        return 1;
    }

    pid_t pid1 = fork();

    if (pid1 < 0) {
        perror("fork failed");
        return 1;
    }

    // ----------------- FIRST CHILD (ls -l) -----------------
    if (pid1 == 0) {
        close(fd[0]);                     // Close read end
        dup2(fd[1], STDOUT_FILENO);       // redirect stdout → pipe
        close(fd[1]);

        execlp("ls", "ls", "-l", NULL);
        perror("exec ls failed");
        exit(1);
    }

    pid_t pid2 = fork();

    if (pid2 < 0) {
        perror("fork failed");
        return 1;
    }

    // ----------------- SECOND CHILD (wc -l) -----------------
    if (pid2 == 0) {
        close(fd[1]);                     // Close write end
        dup2(fd[0], STDIN_FILENO);        // redirect stdin ← pipe
        close(fd[0]);

        execlp("wc", "wc", "-l", NULL);
        perror("exec wc failed");
        exit(1);
    }

    // ----------------- PARENT PROCESS -----------------
    close(fd[0]);
    close(fd[1]);

    wait(NULL);
    wait(NULL);

    return 0;
}

/*
    Compile & Run:
    gcc Q2_ls_wc_pipe.c
    ./a.out
*/

