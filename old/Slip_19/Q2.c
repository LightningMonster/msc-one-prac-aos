// Slip 19 Q2: List only subdirectories in alphabetical order
// COMPILE: gcc -o Q2 Q2.c
// EXAMPLE: ./Q2 => . , .., subdir1, subdir2
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

typedef struct {
    char name[256];
} DirEntry;

int compare_names(const void *a, const void *b) {
    return strcmp(((DirEntry *)a)->name, ((DirEntry *)b)->name);
}

int main() {
    DIR *dir;
    struct dirent *entry;
    struct stat file_stat;
    DirEntry *dirs = NULL;
    int count = 0, capacity = 10;
    
    dir = opendir(".");
    if (dir == NULL) {
        perror("opendir");
        return 1;
    }
    
    dirs = malloc(capacity * sizeof(DirEntry));
    
    // Read all subdirectories
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] == '.') continue;
        
        if (stat(entry->d_name, &file_stat) == 0 && S_ISDIR(file_stat.st_mode)) {
            if (count >= capacity) {
                capacity *= 2;
                dirs = realloc(dirs, capacity * sizeof(DirEntry));
            }
            strcpy(dirs[count].name, entry->d_name);
            count++;
        }
    }
    
    // Sort directories
    qsort(dirs, count, sizeof(DirEntry), compare_names);
    
    // Display
    printf("Subdirectories (alphabetical):\n");
    printf("==============================\n");
    for (int i = 0; i < count; i++) {
        printf("%s/\n", dirs[i].name);
    }
    
    printf("\nTotal: %d directories\n", count);
    
    closedir(dir);
    free(dirs);
    return 0;
}
