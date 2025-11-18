// Slip 12 Q1: Redirect stdout to a file
// COMPILE: gcc -o Q1 Q1.c
// EXAMPLE: ./Q1 => Output redirected to output.txt (check file)
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main() {
    int fd;
    
    // Open file for writing
    fd = open("output.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd < 0) {
        perror("open");
        return 1;
    }
    
    // Redirect stdout to file
    dup2(fd, STDOUT_FILENO);
    close(fd);
    
    printf("This is line 1\n");
    printf("This is line 2\n");
    printf("This is line 3\n");
    
    printf("Output redirected to output.txt\n");
    
    return 0;
}
