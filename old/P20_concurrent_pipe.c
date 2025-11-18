/*20.  Write a program that illustrates how 
to execute two commands concurrently with a pipe.  */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int pipe_fd[2];

    if (pipe(pipe_fd) == -1) {
        perror("Pipe creation failed");
        exit(EXIT_FAILURE);
    }

    pid_t pid1 = fork();
    if (pid1 < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid1 == 0) {
        // First child: executes "ls"
        close(pipe_fd[0]);            // Close read end
        dup2(pipe_fd[1], STDOUT_FILENO); // Redirect stdout to pipe
        close(pipe_fd[1]);

        execlp("ls", "ls", NULL);     // Execute ls
        perror("execlp ls failed");
        exit(EXIT_FAILURE);
    }

    pid_t pid2 = fork();
    if (pid2 < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid2 == 0) {
        // Second child: executes "grep World"
        close(pipe_fd[1]);            // Close write end
        dup2(pipe_fd[0], STDIN_FILENO);  // Redirect stdin to pipe
        close(pipe_fd[0]);

        execlp("grep", "grep", "World", NULL); // Execute grep
        perror("execlp grep failed");
        exit(EXIT_FAILURE);
    }

    // Parent closes both ends and waits for children
    close(pipe_fd[0]);
    close(pipe_fd[1]);

    wait(NULL);
    wait(NULL);

    return 0;
}

// Output:
// gcc P20_concurrent_pipe.c -o concurrent_pipe
// ./concurrent_pipe
