#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>

int main() {
    int fd[2];

    // Block Ctrl-C (SIGINT) and Ctrl-\ (SIGQUIT)
    sigset_t blockSet;
    sigemptyset(&blockSet);
    sigaddset(&blockSet, SIGINT);
    sigaddset(&blockSet, SIGQUIT);

    // Block these signals for the process
    sigprocmask(SIG_BLOCK, &blockSet, NULL);

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

    // ---------------- FIRST CHILD (exec ls -l) ----------------
    if (pid1 == 0) {
        // Unblock signals for child if required (optional)
        sigprocmask(SIG_UNBLOCK, &blockSet, NULL);

        close(fd[0]);                    // Close read end
        dup2(fd[1], STDOUT_FILENO);     // redirect stdout → pipe
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

    // ---------------- SECOND CHILD (exec wc -l) ----------------
    if (pid2 == 0) {
        sigprocmask(SIG_UNBLOCK, &blockSet, NULL);

        close(fd[1]);                    // Close write end
        dup2(fd[0], STDIN_FILENO);      // redirect stdin ← pipe
        close(fd[0]);

        execlp("wc", "wc", "-l", NULL);
        perror("exec wc failed");
        exit(1);
    }

    // ---------------- PARENT PROCESS ----------------
    close(fd[0]);
    close(fd[1]);

    wait(NULL);
    wait(NULL);

    printf("Signals SIGINT and SIGQUIT were blocked during execution.\n");

    // Unblock signals after execution
    sigprocmask(SIG_UNBLOCK, &blockSet, NULL);

    return 0;
}

/*
    Compile & Run:
    gcc Q2_ls_wc_blockSignals.c
    ./a.out
*/
