#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    int fd[2];
    pid_t pid;

    if (pipe(fd) == -1) {
        perror("pipe failed");
        return 1;
    }

    pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    }

    // ----------------- CHILD PROCESS -----------------
    if (pid == 0) {
        close(fd[0]);  // Close read end

        char *msg1 = "Hello World";
        char *msg2 = "Hello SPPU";
        char *msg3 = "Linux is Funny";

        write(fd[1], msg1, strlen(msg1) + 1);
        write(fd[1], msg2, strlen(msg2) + 1);
        write(fd[1], msg3, strlen(msg3) + 1);

        close(fd[1]);
        return 0;
    }

    // ----------------- PARENT PROCESS ----------------
    else {
        close(fd[1]);  // Close write end

        char buffer[100];
        int bytes;

        printf("Parent reading messages from pipe:\n");

        // Read message-by-message (until pipe closes)
        while ((bytes = read(fd[0], buffer, sizeof(buffer))) > 0) {
            int i = 0;

            // Print each null-terminated string in the buffer
            while (i < bytes) {
                printf("%s\n", &buffer[i]);
                i += strlen(&buffer[i]) + 1;
            }
        }

        close(fd[0]);
        wait(NULL);
    }

    return 0;
}

/*
    // gcc Q2_UnnamedPipe_Messages.c
    // ./a.out
*/
