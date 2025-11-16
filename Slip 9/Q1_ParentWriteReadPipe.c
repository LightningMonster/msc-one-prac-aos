#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>   // <-- Required for wait()

int main() {
    int fd[2];
    pid_t pid;

    if (pipe(fd) == -1) {
        perror("Pipe creation failed");
        return 1;
    }

    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }

    // -------------------- CHILD PROCESS --------------------
    if (pid == 0) {
        close(fd[1]);   // Close write end

        char buffer[100];
        read(fd[0], buffer, sizeof(buffer));   // Read message from pipe

        printf("Child received: %s\n", buffer);

        close(fd[0]);
    }

    // -------------------- PARENT PROCESS --------------------
    else {
        close(fd[0]);   // Close read end

        char msg[] = "Hello from Parent through PIPE!";
        write(fd[1], msg, strlen(msg) + 1);

        close(fd[1]);

        wait(NULL);  // Wait for child to finish
    }

    return 0;
}

/*
    Compile & Run:
    gcc Q1_ParentWriteReadPipe.c
    ./a.out
*/
