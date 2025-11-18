/* Unnamed pipe: Child writes messages, parent reads and displays them */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h> // Include wait()

int main() {
    int fd[2];
    pid_t pid;
    char buff[100]; // Buffer for reading

    char *msg1 = "Hello World.";
    char *msg2 = "Hello SPPU.";
    char *msg3 = "Linux is Funny.";

    if (pipe(fd) < 0) {
        perror("pipe failed");
        exit(1);
    }

    pid = fork();
    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }

    if (pid == 0) {
        // CHILD: write messages to pipe
        close(fd[0]); // Close read end
        write(fd[1], msg1, strlen(msg1));
        write(fd[1], msg2, strlen(msg2));
        write(fd[1], msg3, strlen(msg3));
        close(fd[1]);
        exit(0);
    } else {
        // PARENT: read messages from pipe
        close(fd[1]); // Close write end
        ssize_t n;
        while ((n = read(fd[0], buff, sizeof(buff)-1)) > 0) {
            buff[n] = '\0';
            printf("%s\n", buff);
        }
        close(fd[0]);
        wait(NULL); // Wait for child
    }

    return 0;
}


// Output:
// gcc P19_unnamed_pipe.c -o unnamed_pipe
// ./unnamed_pipe