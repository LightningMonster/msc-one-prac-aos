// Slip 3 Q1: Print inode numbers of files
// COMPILE: gcc -o Q1 Q1.c
// EXAMPLE: ./Q1 Q1.c Q1 => file1: 12345, file2: 12346
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    struct stat file_stat;
    int i;
    
    if (argc < 2) {
        printf("Usage: %s <file1> <file2> ...\n", argv[0]);
        return 1;
    }
    
    printf("%-30s %s\n", "Filename", "Inode Number");
    printf("%-30s %s\n", "----------", "------------");
    
    for (i = 1; i < argc; i++) {
        if (stat(argv[i], &file_stat) < 0) {
            printf("%-30s Error: File not found\n", argv[i]);
        } else {
            printf("%-30s %ld\n", argv[i], (long)file_stat.st_ino);
        }
    }
    
    return 0;
}
