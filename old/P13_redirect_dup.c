/*13. Redirect standard output to a file using dup2 and open system calls */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    // Open file for writing (create if doesn't exist, truncate if exists)
    int fd = open("redirect_assi13.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Failed to open file");
        return 1;
    }

    // Save current stdout
    int saved_stdout = dup(STDOUT_FILENO);

    // Redirect stdout to file
    if (dup2(fd, STDOUT_FILENO) == -1) {
        perror("dup2 failed");
        close(fd);
        return 1;
    }
    close(fd); // original fd not needed

    // Disable buffering to ensure printf writes immediately
    setvbuf(stdout, NULL, _IONBF, 0);

    // This will go to the file
    printf("This will be written to redirect_assi13.txt\n");

    // Restore stdout
    if (dup2(saved_stdout, STDOUT_FILENO) == -1) {
        perror("Failed to restore stdout");
        return 1;
    }
    close(saved_stdout);

    // This will go to the terminal
    printf("This will be displayed on the terminal\n");

    return 0;
}


// Output:
// gcc P13_redirect_dup.c -o redirect_dup
// ./redirect_dup
// cat redirect_assi13.txt