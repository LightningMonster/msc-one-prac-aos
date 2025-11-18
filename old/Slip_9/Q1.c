// Slip 9 Q1: Display subdirectories only
// COMPILE: gcc -o Q1 Q1.c
// EXAMPLE: ./Q1 => ., ..
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>

int main() {
    DIR *dir;
    struct dirent *entry;
    struct stat file_stat;
    int dir_count = 0;
    
    dir = opendir(".");
    if (dir == NULL) {
        perror("opendir");
        return 1;
    }
    
    printf("Subdirectories in current directory:\n");
    printf("====================================\n");
    
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] == '.') continue;
        
        stat(entry->d_name, &file_stat);
        
        if (S_ISDIR(file_stat.st_mode)) {
            printf("%s/\n", entry->d_name);
            dir_count++;
        }
    }
    
    printf("====================================\n");
    printf("Total subdirectories: %d\n", dir_count);
    
    closedir(dir);
    return 0;
}
