// Slip 18 Q2: List only regular files in alphabetical order
// COMPILE: gcc -o Q2 Q2.c
// EXAMPLE: ./Q2 => Q1, Q1.c, Q2, Q2.c
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

typedef struct {
    char name[256];
} FileEntry;

int compare_names(const void *a, const void *b) {
    return strcmp(((FileEntry *)a)->name, ((FileEntry *)b)->name);
}

int main() {
    DIR *dir;
    struct dirent *entry;
    struct stat file_stat;
    FileEntry *files = NULL;
    int count = 0, capacity = 10;
    
    dir = opendir(".");
    if (dir == NULL) {
        perror("opendir");
        return 1;
    }
    
    files = malloc(capacity * sizeof(FileEntry));
    
    // Read all regular files
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] == '.') continue;
        
        if (stat(entry->d_name, &file_stat) == 0 && S_ISREG(file_stat.st_mode)) {
            if (count >= capacity) {
                capacity *= 2;
                files = realloc(files, capacity * sizeof(FileEntry));
            }
            strcpy(files[count].name, entry->d_name);
            count++;
        }
    }
    
    // Sort files
    qsort(files, count, sizeof(FileEntry), compare_names);
    
    // Display
    printf("Regular files (alphabetical):\n");
    printf("=============================\n");
    for (int i = 0; i < count; i++) {
        printf("%s\n", files[i].name);
    }
    
    printf("\nTotal: %d files\n", count);
    
    closedir(dir);
    free(files);
    return 0;
}
