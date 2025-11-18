/*15.Parent writes to unnamed pipe, child reads from it */

#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd[2];               // fd[0] for reading, fd[1] for writing
    if (pipe(fd) == -1) {    // create unnamed pipe
        perror("pipe");
        return 1;
    }

    pid_t child_pid = fork(); // create child process

    if (child_pid == -1) {   // check for fork error
        perror("fork");
        return 1;
    }

    if (child_pid == 0) {    // Child process
        close(fd[1]);        // Close write end in child

        char buffer[100];
        ssize_t n = read(fd[0], buffer, sizeof(buffer)-1); // read from pipe
        if (n > 0) buffer[n] = '\0'; // null-terminate string

        printf("Child: Received message: %s\n", buffer);
        close(fd[0]);        // Close read end
    } else {                  // Parent process
        close(fd[0]);        // Close read end in parent

        char message[] = "Hello, child!";
        write(fd[1], message, strlen(message)); // write to pipe
        printf("Parent: Sent message to child.\n");
        close(fd[1]);        // Close write end
    }

    return 0;
}

// Output:
// gcc P15_pipe_example.c -o pipe_example
// ./pipe_example
