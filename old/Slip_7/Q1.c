// Slip 7 Q1: Read directory contents and display files/subdirectories
// COMPILE: gcc -o Q1 Q1.c
// EXAMPLE: ./Q1 => ., .., Q1.c, Q2.c, Q1, Q2
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>

int main() {
    DIR *dir;
    struct dirent *entry;
    struct stat file_stat;
    int file_count = 0, dir_count = 0;
    
    dir = opendir(".");
    if (dir == NULL) {
        perror("opendir");
        return 1;
    }
    
    printf("Contents of current directory:\n");
    printf("================================\n\n");
    
    printf("%-40s %s\n", "Name", "Type");
    printf("%-40s %s\n", "----", "----");
    
    while ((entry = readdir(dir)) != NULL) {
        // Skip . and ..
        if (entry->d_name[0] == '.') continue;
        
        stat(entry->d_name, &file_stat);
        
        if (S_ISDIR(file_stat.st_mode)) {
            printf("%-40s [DIR]\n", entry->d_name);
            dir_count++;
        } else {
            printf("%-40s [FILE]\n", entry->d_name);
            file_count++;
        }
    }
    
    printf("\n================================\n");
    printf("Total Files: %d\n", file_count);
    printf("Total Directories: %d\n", dir_count);
    printf("Total Items: %d\n", file_count + dir_count);
    
    closedir(dir);
    return 0;
}
