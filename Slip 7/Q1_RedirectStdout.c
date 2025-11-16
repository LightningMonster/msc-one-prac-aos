#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int fd;

    // Open file (create if not exists, truncate if exists)
    fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (fd < 0) {
        perror("File open failed");
        return 1;
    }

    // Redirect stdout to the file
    dup2(fd, STDOUT_FILENO);

    close(fd);  // No longer needed

    // Anything printed using printf will now go into output.txt
    printf("This text is redirected to output.txt\n");
    printf("Hello SPPU!\n");

    return 0;
}

/*
    Compile & Run:
    gcc Q1_RedirectStdout.c
    ./a.out
    Check output.txt
*/
