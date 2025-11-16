#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int fd;

    // Open output.txt for writing
    fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("open failed");
        return 1;
    }

    // Close STDOUT (file descriptor 1)
    close(STDOUT_FILENO);

    // Duplicate fd → it will take the lowest free FD (which is 1 = stdout)
    if (dup(fd) < 0) {
        perror("dup failed");
        return 1;
    }

    close(fd);  // No longer needed

    // -------- ALL PRINTF GOES TO output.txt --------
    printf("This content is written using dup() and open().\n");
    printf("Slip 25 Q2 completed successfully.\n");

    return 0;
}

/*
    Compile & Run:
    gcc Q2_RedirectStdout_dup.c
    ./a.out
    Check output.txt
*/

