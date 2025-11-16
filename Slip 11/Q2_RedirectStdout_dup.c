#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    // Open the file
    int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    // Redirect stdout using dup()
    close(1);   // Close stdout (file descriptor 1)
    if (dup(fd) < 0) {
        perror("dup");
        return 1;
    }

    close(fd);  // fd no longer needed

    // ----------- NOW stdout = output.txt -----------
    printf("Hello, this is redirected output using dup()!\n");
    printf("Successfully redirected using open() and dup().\n");

    return 0;
}

/*
    Compile & Run:
    gcc Q2_RedirectStdout_dup.c
    ./a.out
    Check output.txt
*/
