// Slip 19 Q1: Map file in memory and display in reverse
// COMPILE: gcc -o Q1 Q1.c
// EXAMPLE: ./Q1 filename => Reversed content
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int fd;
    struct stat sb;
    char *file_mmap;
    
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    
    fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        perror("open");
        return 1;
    }
    
    if (fstat(fd, &sb) < 0) {
        perror("fstat");
        close(fd);
        return 1;
    }
    
    file_mmap = mmap(NULL, sb.st_size, PROT_READ, MAP_SHARED, fd, 0);
    if (file_mmap == MAP_FAILED) {
        perror("mmap");
        close(fd);
        return 1;
    }
    
    printf("File content in reverse:\n");
    printf("========================\n");
    
    for (int i = sb.st_size - 1; i >= 0; i--) {
        printf("%c", file_mmap[i]);
    }
    printf("\n");
    
    munmap(file_mmap, sb.st_size);
    close(fd);
    
    return 0;
}
