// Slip 16 Q2: Sort files by size in ascending order
// COMPILE: gcc -o Q2 Q2.c
// EXAMPLE: ./Q2 => Q1.c (950), Q2.c (1719), Q1 (16384)
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

typedef struct {
    char name[100];
    long size;
} FileInfo;

int compare_size(const void *a, const void *b) {
    return ((FileInfo *)a)->size - ((FileInfo *)b)->size;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <file1> <file2> ...\n", argv[0]);
        return 1;
    }
    
    FileInfo *files = malloc((argc - 1) * sizeof(FileInfo));
    struct stat file_stat;
    int count = 0;
    
    // Get file sizes
    for (int i = 1; i < argc; i++) {
        if (stat(argv[i], &file_stat) == 0) {
            strcpy(files[count].name, argv[i]);
            files[count].size = file_stat.st_size;
            count++;
        }
    }
    
    // Sort by size
    qsort(files, count, sizeof(FileInfo), compare_size);
    
    // Display sorted files
    printf("Files sorted by size (ascending):\n");
    printf("==================================\n");
    for (int i = 0; i < count; i++) {
        printf("%-30s %ld bytes\n", files[i].name, files[i].size);
    }
    
    free(files);
    return 0;
}
