// Slip 8 Q1: Read directory and display only regular files
// COMPILE: gcc -o Q1 Q1.c
// EXAMPLE: ./Q1 => Q1.c, Q2.c, Q1, Q2
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>

int main() {
    DIR *dir;
    struct dirent *entry;
    struct stat file_stat;
    int file_count = 0;
    
    dir = opendir(".");
    if (dir == NULL) {
        perror("opendir");
        return 1;
    }
    
    printf("Regular files in current directory:\n");
    printf("====================================\n");
    
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] == '.') continue;
        
        stat(entry->d_name, &file_stat);
        
        if (S_ISREG(file_stat.st_mode)) {
            printf("%s\n", entry->d_name);
            file_count++;
        }
    }
    
    printf("====================================\n");
    printf("Total regular files: %d\n", file_count);
    
    closedir(dir);
    return 0;
}
