// Slip 14 Q1: Child creates unnamed pipe and parent reads from it
// COMPILE: gcc -o Q1 Q1.c
// EXAMPLE: ./Q1 => Pipe messaging
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    int pipefd[2];
    pid_t pid;
    char buffer[100];
    
    if (pipe(pipefd) < 0) {
        perror("pipe");
        return 1;
    }
    
    pid = fork();
    
    if (pid < 0) {
        perror("fork");
        return 1;
    } else if (pid == 0) {
        // Child process - write to pipe
        close(pipefd[0]);  // Close read end
        
        char msg1[] = "Hello from Child";
        char msg2[] = "Pipe communication successful";
        
        write(pipefd[1], msg1, strlen(msg1) + 1);
        write(pipefd[1], msg2, strlen(msg2) + 1);
        
        close(pipefd[1]);
        exit(0);
    } else {
        // Parent process - read from pipe
        close(pipefd[1]);  // Close write end
        
        printf("Parent reading from pipe:\n");
        while (read(pipefd[0], buffer, sizeof(buffer)) > 0) {
            printf("Received: %s\n", buffer);
        }
        
        close(pipefd[0]);
        wait(NULL);
    }
    
    return 0;
}
