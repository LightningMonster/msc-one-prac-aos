#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>

int main() {
    int fd[2];

    // -------- Block SIGINT (Ctrl-C) and SIGQUIT (Ctrl-\) --------
    sigset_t blockset;
    sigemptyset(&blockset);
    sigaddset(&blockset, SIGINT);
    sigaddset(&blockset, SIGQUIT);

    // Block for the entire process (parent + children)
    sigprocmask(SIG_BLOCK, &blockset, NULL);

    // Create pipe
    if (pipe(fd) == -1) {
        perror("pipe failed");
        return 1;
    }

    // ---------------- FIRST CHILD (exec: ls -l) ----------------
    pid_t pid1 = fork();

    if (pid1 < 0) {
        perror("fork failed");
        return 1;
    }

    if (pid1 == 0) {
        sigprocmask(SIG_UNBLOCK, &blockset, NULL);  // optional

        close(fd[0]);                 // close read end
        dup2(fd[1], STDOUT_FILENO);   // redirect stdout → pipe
        close(fd[1]);

        execlp("ls", "ls", "-l", NULL);
        perror("exec ls failed");
        exit(1);
    }

    // ---------------- SECOND CHILD (exec: wc -l) ----------------
    pid_t pid2 = fork();

    if (pid2 < 0) {
        perror("fork failed");
        return 1;
    }

    if (pid2 == 0) {
        sigprocmask(SIG_UNBLOCK, &blockset, NULL);  // optional

        close(fd[1]);                 // close write end
        dup2(fd[0], STDIN_FILENO);    // redirect stdin ← pipe
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

    // Unblock after pipeline completes
    sigprocmask(SIG_UNBLOCK, &blockset, NULL);

    return 0;
}

/*
    Compile & Run:
    gcc Q2_ls_wc_BlockSignals.c
    ./a.out
*/
