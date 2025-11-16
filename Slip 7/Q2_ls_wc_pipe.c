#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    int fd[2];
    pipe(fd);

    pid_t pid = fork();

    if (pid < 0) {
        printf("Fork failed.\n");
        return 1;
    }

    // ------------- CHILD PROCESS: executes ls -l -------------
    if (pid == 0) {
        close(fd[0]);           // Close read end
        dup2(fd[1], STDOUT_FILENO);  // Redirect output to pipe
        close(fd[1]);

        execlp("ls", "ls", "-l", NULL);
        perror("exec ls failed");
        exit(1);
    }

    // ------------- PARENT PROCESS: executes wc -l -------------
    else {
        close(fd[1]);           // Close write end
        dup2(fd[0], STDIN_FILENO);   // Read input from pipe
        close(fd[0]);

        execlp("wc", "wc", "-l", NULL);
        perror("exec wc failed");
        exit(1);
    }

    return 0;
}

/*
    Compile and Run:
    gcc Q2_ls_wc_pipe.c
    ./a.out
*/

