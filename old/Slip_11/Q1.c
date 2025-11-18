// Slip 11 Q1: Display access and modification time of file
// COMPILE: gcc -o Q1 Q1.c
// EXAMPLE: ./Q1 Q1.c => Access: Tue Nov 18 10:30:45, Modify: Tue Nov 18 10:30:40
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
    
    return 0;
}
