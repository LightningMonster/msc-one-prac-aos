// Slip 9 Q2: Two-way pipe communication (same as Slip 3 Q2)
// COMPILE: gcc -o Q2 Q2.c
// EXAMPLE: ./Q2 => Pipe messaging
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    int pipe1[2], pipe2[2];
    pid_t pid;
    char buffer[100];
    
    // Create pipes
    pipe(pipe1);  // Parent writes, Child reads
    pipe(pipe2);  // Child writes, Parent reads
    
    pid = fork();
    
    if (pid < 0) {
        perror("fork");
        return 1;
    } else if (pid == 0) {
        // Child process
        close(pipe1[1]);  // Close write end of pipe1
        close(pipe2[0]);  // Close read end of pipe2
        
        // Read message from parent
        read(pipe1[0], buffer, sizeof(buffer));
        printf("Child received: %s\n", buffer);
        
        // Send reply to parent
        strcpy(buffer, "Hello Parent!");
        write(pipe2[1], buffer, strlen(buffer) + 1);
        
        close(pipe1[0]);
        close(pipe2[1]);
        exit(0);
    } else {
        // Parent process
        close(pipe1[0]);  // Close read end of pipe1
        close(pipe2[1]);  // Close write end of pipe2
        
        // Send message to child
        strcpy(buffer, "Hello Child!");
        write(pipe1[1], buffer, strlen(buffer) + 1);
        
        // Read reply from child
        read(pipe2[0], buffer, sizeof(buffer));
        printf("Parent received: %s\n", buffer);
        
        close(pipe1[1]);
        close(pipe2[0]);
        wait(NULL);
    }
    
    return 0;
}
