/*18. Create n child processes and display cumulative user and kernel time */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/resource.h>

int main() {
    int i;
    int n = 5;  // Number of child processes to create
    struct rusage rusage_child;  // To store resource usage of children
    struct timeval user_time, kernel_time;

    // Create n child processes
    for (i = 0; i < n; i++) {
        pid_t child_pid = fork();

        if (child_pid == -1) {  // Error handling
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (child_pid == 0) {  // CHILD PROCESS
            printf("Child %d is running...\n", i + 1);
            sleep(2);  // Simulate some work
            exit(EXIT_SUCCESS);  // Child exits
        }
        // Parent continues to create next child
    }

    int status;
    int remaining = n;

    // Wait for all child processes to terminate
    while (remaining > 0) {
        pid_t terminated_pid = wait(&status); // Wait for any child
        if (terminated_pid > 0 && WIFEXITED(status)) {
            remaining--;
        }
    }

    // Get cumulative resource usage of all terminated children
    if (getrusage(RUSAGE_CHILDREN, &rusage_child) == -1) {
        perror("getrusage failed");
        exit(EXIT_FAILURE);
    }

    user_time = rusage_child.ru_utime;   // User CPU time
    kernel_time = rusage_child.ru_stime; // System (kernel) CPU time

    printf("Total User Time: %ld.%06ld seconds\n", user_time.tv_sec, user_time.tv_usec);
    printf("Total Kernel Time: %ld.%06ld seconds\n", kernel_time.tv_sec, kernel_time.tv_usec);

    return 0;
}

// Output:
// gcc P18_child_time.c -o child_time
// ./child_time