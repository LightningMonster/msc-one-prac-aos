// Slip 15 Q1: Create unnamed pipe with messages
// COMPILE: gcc -o Q1 Q1.c
// EXAMPLE: ./Q1 => Pipe messages
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    int pipefd[2];
    pid_t pid;
    char buffer[100];
    char msg1[] = "Hello Friends !!! Good Afternoon ";
    char msg2[] = "Hello!!!  Good Afternoon ";
    
    if (pipe(pipefd) < 0) {
        perror("pipe");
        return 1;
    }
    
    pid = fork();
    
    if (pid < 0) {
        perror("fork");
        return 1;
    } else if (pid == 0) {
        // Child process - write messages to pipe
        close(pipefd[0]);  // Close read end
        
        write(pipefd[1], msg1, strlen(msg1) + 1);
        write(pipefd[1], msg2, strlen(msg2) + 1);
        
        close(pipefd[1]);
        exit(0);
    } else {
        // Parent process - read and display messages
        close(pipefd[1]);  // Close write end
        
        printf("Parent displaying messages from child:\n");
        printf("=====================================\n");
        
        int count = 0;
        while (read(pipefd[0], buffer, sizeof(buffer)) > 0) {
            count++;
            printf("Message %d: %s\n", count, buffer);
        }
        
        close(pipefd[0]);
        wait(NULL);
    }
    
    return 0;
}
