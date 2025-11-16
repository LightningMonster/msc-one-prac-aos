#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int fd, saved_stdout;

    // Open file "output.txt"
    fd = open("output.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);

    if (fd < 0) {
        perror("open failed");
        return 1;
    }

    // Save current stdout
    saved_stdout = dup(STDOUT_FILENO);

    // Redirect stdout → output.txt
    close(STDOUT_FILENO);
    dup(fd);   // Duplicate 'fd' into the lowest free FD (which is 1 = stdout)

    close(fd); // No longer needed

    printf("This output goes to output.txt using dup()!\n");
    printf("Slip 8 Q1 completed.\n");

    // Restore original stdout (not required but good practice)
    dup2(saved_stdout, STDOUT_FILENO);
    close(saved_stdout);

    printf("Stdout restored to terminal.\n");

    return 0;
}

/*
    Compile & Run:
    gcc Q1_Redirect_Output_dup.c
    ./a.out
    Check output.txt
*/
