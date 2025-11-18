/*16. Two-way communication between parent and child using pipes */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
    int parent_to_child[2];  // Pipe: parent writes, child reads
    int child_to_parent[2];  // Pipe: child writes, parent reads
    pid_t child_pid;

    // Create the pipes
    if (pipe(parent_to_child) == -1 || pipe(child_to_parent) == -1) {
        perror("Pipe creation failed");
        exit(EXIT_FAILURE);
    }

    // Fork a child process
    child_pid = fork();
    if (child_pid < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0) {
        // CHILD PROCESS
        close(parent_to_child[1]); // Close write end (child reads)
        close(child_to_parent[0]); // Close read end (child writes)

        char received[100];
        ssize_t n = read(parent_to_child[0], received, sizeof(received)-1); // Read from parent
        if (n > 0) received[n] = '\0';  // Null-terminate
        printf("Child received: %s\n", received);

        char message[] = "Message from child to parent";
        write(child_to_parent[1], message, strlen(message)); // Write to parent

        // Close pipes in child
        close(parent_to_child[0]);
        close(child_to_parent[1]);

        exit(EXIT_SUCCESS);
    } else {
        // PARENT PROCESS
        close(parent_to_child[0]); // Close read end (parent writes)
        close(child_to_parent[1]); // Close write end (parent reads)

        char message[] = "Hello from the parent process!";
        write(parent_to_child[1], message, strlen(message)); // Write to child

        char received[100];
        ssize_t n = read(child_to_parent[0], received, sizeof(received)-1); // Read from child
        if (n > 0) received[n] = '\0';  // Null-terminate
        printf("Parent received: %s\n", received);

        // Close pipes in parent
        close(parent_to_child[1]);
        close(child_to_parent[0]);
    }

    return 0;
}

// Output:
// gcc P16_two_way_pipe.c -o two_way_pipe
// ./two_way_pipe