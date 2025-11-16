#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int fd;

    // Open file output.txt (create if not exists, empty if exists)
    fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("open failed");
        return 1;
    }

    // Redirect stdout to output.txt
    if (dup2(fd, STDOUT_FILENO) < 0) {
        perror("dup2 failed");
        return 1;
    }

    close(fd);  // fd not needed after dup2()

    // All output goes into output.txt now
    printf("This text is redirected into output.txt\n");
    printf("Standard output redirection example completed.\n");

    return 0;
}

/*
    Compile & Run:
    gcc Q1_RedirectStdout.c
    ./a.out
    Check output.txt
*/
