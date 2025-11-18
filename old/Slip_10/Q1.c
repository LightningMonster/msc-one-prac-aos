// Slip 10 Q1: Identify file type using stat()
// COMPILE: gcc -o Q1 Q1.c
// EXAMPLE: ./Q1 Q1.c => Regular File, ./Q1 /dev/null => Character Device
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    struct stat file_stat;
    char file_type[50];
    
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    
    if (stat(argv[1], &file_stat) < 0) {
        perror("stat");
        return 1;
    }
    
    // Determine file type
    if (S_ISREG(file_stat.st_mode))
        strcpy(file_type, "Regular File");
    else if (S_ISDIR(file_stat.st_mode))
        strcpy(file_type, "Directory");
    else if (S_ISCHR(file_stat.st_mode))
        strcpy(file_type, "Character Device");
    else if (S_ISBLK(file_stat.st_mode))
        strcpy(file_type, "Block Device");
    else if (S_ISFIFO(file_stat.st_mode))
        strcpy(file_type, "FIFO/Named Pipe");
    else if (S_ISLNK(file_stat.st_mode))
        strcpy(file_type, "Symbolic Link");
    else if (S_ISSOCK(file_stat.st_mode))
        strcpy(file_type, "Socket");
    else
        strcpy(file_type, "Unknown");
    
    printf("File: %s\n", argv[1]);
    printf("Type: %s\n", file_type);
    printf("Mode: %o\n", file_stat.st_mode);
    
    return 0;
}
