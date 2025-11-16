#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    int pfd[2];

    // Create pipe
    if (pipe(pfd) == -1) {
        perror("pipe error");
        return 1;
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork error");
        return 1;
    }

    // ----------------- CHILD : run ls -l -----------------
    if (pid == 0) {
        close(pfd[0]);                // Close read end
        dup2(pfd[1], STDOUT_FILENO);  // Send ls output → pipe
        close(pfd[1]);

        execlp("ls", "ls", "-l", NULL);
        perror("exec ls failed");
        exit(1);
    }

    // ----------------- PARENT : run wc -l ----------------
    else {
        close(pfd[1]);                // Close write end
        dup2(pfd[0], STDIN_FILENO);   // wc input ← pipe
        close(pfd[0]);

        execlp("wc", "wc", "-l", NULL);
        perror("exec wc failed");
        exit(1);
    }

    return 0;
}

/*
    Compile & Run:
    gcc Q2_ls_wc_pipeline.c
    ./a.out
*/
