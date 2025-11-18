#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int fd[2];

    if (pipe(fd) == -1) {
        perror("pipe failed");
        exit(1);
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }

    if (pid == 0) {
        // Child process: executes "ls -l"
        close(fd[0]);                 // Close unused read end
        dup2(fd[1], STDOUT_FILENO);   // Redirect stdout to pipe
        close(fd[1]);                 // Close duplicated write end

        execlp("ls", "ls", "-l", NULL); // Execute ls -l
        perror("execlp ls failed");
        exit(1);
    } else {
        // Parent process: executes "wc -l"
        close(fd[1]);                 // Close unused write end
        dup2(fd[0], STDIN_FILENO);    // Redirect stdin to pipe
        close(fd[0]);                 // Close duplicated read end

        execlp("wc", "wc", "-l", NULL); // Execute wc -l
        perror("execlp wc failed");
        exit(1);
    }

    return 0;
}

// Output:
// gcc P17_ls_wc_pipe.c -o ls_wc_pipe
// ./ls_wc_pipe