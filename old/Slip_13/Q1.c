// Slip 13 Q1: Display file timestamps (same as Slip 11 Q1)
// COMPILE: gcc -o Q1 Q1.c
// EXAMPLE: ./Q1 filename => File times
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    struct stat file_stat;
    
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    
    if (stat(argv[1], &file_stat) < 0) {
        perror("stat");
        return 1;
    }
    
    printf("File: %s\n", argv[1]);
    printf("Last Access Time: %s", ctime(&file_stat.st_atime));
    printf("Last Modified Time: %s", ctime(&file_stat.st_mtime));
    printf("Status Change Time: %s", ctime(&file_stat.st_ctime));
    
    return 0;
}
