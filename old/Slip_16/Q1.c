// Slip 16 Q1: Redirect stdout to file using dup and open
// COMPILE: gcc -o Q1 Q1.c
// EXAMPLE: ./Q1 => Creates output.txt
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main() {
    int fd;
    int saved_stdout;
    
    // Save original stdout
    saved_stdout = dup(STDOUT_FILENO);
    
    // Open file
    fd = open("output.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd < 0) {
        perror("open");
        return 1;
    }
    
    // Redirect stdout to file
    dup2(fd, STDOUT_FILENO);
    close(fd);
    
    printf("This line goes to output.txt\n");
    printf("This line also goes to output.txt\n");
    
    // Restore stdout
    dup2(saved_stdout, STDOUT_FILENO);
    close(saved_stdout);
    
    printf("This line goes to console (stdout restored)\n");
    
    return 0;
}
