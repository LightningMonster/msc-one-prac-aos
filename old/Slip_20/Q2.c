// Slip 20 Q2: List files larger than n bytes recursively
// COMPILE: gcc -o Q2 Q2.c
// EXAMPLE: ./Q2 1000 => Q1.c (1500), Q2.c (1719), Q1 (16384)
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

void search_files(const char *path, long min_size, int depth) {
    DIR *dir;
    struct dirent *entry;
    struct stat file_stat;
    char full_path[1024];
    
    dir = opendir(path);
    if (dir == NULL) {
        return;
    }
    
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] == '.') continue;
        
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);
        
        if (stat(full_path, &file_stat) == 0) {
            if (S_ISDIR(file_stat.st_mode)) {
                search_files(full_path, min_size, depth + 1);
            } else if (S_ISREG(file_stat.st_mode) && file_stat.st_size > min_size) {
                printf("%s (%ld bytes)\n", full_path, (long)file_stat.st_size);
            }
        }
    }
    
    closedir(dir);
}

int main() {
    long min_size;
    
    printf("Enter minimum file size in bytes: ");
    scanf("%ld", &min_size);
    
    printf("\nFiles larger than %ld bytes:\n", min_size);
    printf("============================\n");
    
    search_files(".", min_size, 0);
    
    return 0;
}
