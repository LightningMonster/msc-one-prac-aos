#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int fd;

    // Open file "output.txt" (create if not exists)
    fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("open failed");
        return 1;
    }

    // Redirect stdout to file using dup2()
    if (dup2(fd, STDOUT_FILENO) < 0) {
        perror("dup2 failed");
        return 1;
    }

    close(fd);  // No longer needed

    // All printf() output now goes to output.txt
    printf("This text is redirected to output.txt\n");
    printf("Standard output redirection demo completed.\n");

    return 0;
}

/*
    Compile & Run:
    gcc Q1_RedirectStdout.c
    ./a.out
    Check output.txt
*/
