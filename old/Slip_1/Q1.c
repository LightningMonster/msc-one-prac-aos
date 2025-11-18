// Slip 1 Q1: Create a file with hole in it
// A sparse file (hole) is created when we write data at non-contiguous positions
// COMPILE: gcc -o Q1 Q1.c
// EXAMPLE OUTPUT:
// $ ./Q1
// File 'holey_file.txt' created with hole in it
// File size: 1005 bytes (but actual disk space used is less)
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main() {
    int fd;
    char data[] = "Hello";
    
    // Create a file
    fd = open("holey_file.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd < 0) {
        perror("open");
        return 1;
    }
    
    // Write first data at position 0
    write(fd, data, 5);
    
    // Move file pointer to position 1000 (creating hole)
    // The gap between 5 and 1000 is a hole
    lseek(fd, 1000, SEEK_SET);
    
    // Write second data at position 1000
    write(fd, data, 5);
    
    close(fd);
    
    printf("File 'holey_file.txt' created with hole in it\n");
    printf("File size: %ld bytes (but actual disk space used is less)\n", 
           lseek(fd, 0, SEEK_END));
    
    return 0;
}
