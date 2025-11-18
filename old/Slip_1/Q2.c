// Slip 1 Q2: Create 'n' child processes and display total cumulative time
// When all children terminate, display total user and kernel mode time
// COMPILE: gcc -o Q2 Q2.c
// EXAMPLE: ./Q2 (Input: 2)
// OUTPUT: Child 1 created, Total time: 1s
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/resource.h>

int main() {
    int n, i;
    pid_t pid;
    int status;
    struct rusage usage;
    
    printf("Enter number of child processes: ");
    scanf("%d", &n);
    
    // Create n child processes
    for (i = 0; i < n; i++) {
        pid = fork();
        
        if (pid < 0) {
            perror("fork");
            return 1;
        } else if (pid == 0) {
            // Child process - do some work
            printf("Child process %d created (PID: %d)\n", i+1, getpid());
            
            // Do some CPU work
            for (int j = 0; j < 100000000; j++) {
                int temp = j * 2;
            }
            
            printf("Child process %d terminating\n", i+1);
            exit(0);
        }
    }
    
    // Parent process waits for all children
    printf("\nParent waiting for all children...\n");
    
    long total_user_time = 0;
    long total_kernel_time = 0;
    
    for (i = 0; i < n; i++) {
        pid = wait3(&status, 0, &usage);
        total_user_time += usage.ru_utime.tv_sec;
        total_kernel_time += usage.ru_stime.tv_sec;
    }
    
    printf("\n===== Total Cumulative Time =====\n");
    printf("Total User Mode Time: %ld seconds\n", total_user_time);
    printf("Total Kernel Mode Time: %ld seconds\n", total_kernel_time);
    printf("Total Time: %ld seconds\n", total_user_time + total_kernel_time);
    
    return 0;
}
