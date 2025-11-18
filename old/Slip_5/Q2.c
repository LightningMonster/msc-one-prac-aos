// Slip 5 Q2: Implement "ls -l | wc -l" using fork, pipe, exec with signal blocking
// COMPILE: gcc -o Q2 Q2.c
// EXAMPLE: ./Q2 => Line count output
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>

int main() {
    int pipefd[2];
    pid_t pid1, pid2;
    sigset_t set;
    
    // Block Ctrl+C (SIGINT) and Ctrl+\ (SIGQUIT)
    sigemptyset(&set);
    sigaddset(&set, SIGINT);
    sigaddset(&set, SIGQUIT);
    sigprocmask(SIG_BLOCK, &set, NULL);
    
    printf("Running: ls -l | wc -l\n");
    
    // Create pipe
    pipe(pipefd);
    
    // First child process - execute "ls -l"
    pid1 = fork();
    if (pid1 == 0) {
        close(pipefd[0]);  // Close read end
        dup2(pipefd[1], STDOUT_FILENO);  // Redirect stdout to pipe
        close(pipefd[1]);
        execlp("ls", "ls", "-l", NULL);
        perror("execlp ls");
        exit(1);
    }
    
    // Second child process - execute "wc -l"
    pid2 = fork();
    if (pid2 == 0) {
        close(pipefd[1]);  // Close write end
        dup2(pipefd[0], STDIN_FILENO);  // Redirect stdin from pipe
        close(pipefd[0]);
        execlp("wc", "wc", "-l", NULL);
        perror("execlp wc");
        exit(1);
    }
    
    // Parent closes both ends and waits
    close(pipefd[0]);
    close(pipefd[1]);
    
    wait(NULL);
    wait(NULL);
    
    // Unblock signals
    sigprocmask(SIG_UNBLOCK, &set, NULL);
    
    printf("\nCommand execution completed\n");
    return 0;
}
