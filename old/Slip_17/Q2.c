// Slip 17 Q2: List files created in a particular month
// COMPILE: gcc -o Q2 Q2.c
// EXAMPLE: ./Q2 11 => Q1.c, Q2.c, Q1, Q2 (created in November)
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>

int main() {
    DIR *dir;
    struct dirent *entry;
    struct stat file_stat;
    int target_month, target_year;
    struct tm *tm_info;
    
    printf("Enter target month (1-12): ");
    scanf("%d", &target_month);
    printf("Enter target year: ");
    scanf("%d", &target_year);
    
    dir = opendir(".");
    if (dir == NULL) {
        perror("opendir");
        return 1;
    }
    
    printf("\nFiles created in %d/%d:\n", target_month, target_year);
    printf("============================\n");
    
    int count = 0;
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] == '.') continue;
        
        if (stat(entry->d_name, &file_stat) == 0) {
            tm_info = localtime(&file_stat.st_mtime);
            
            if (tm_info->tm_mon + 1 == target_month && 
                tm_info->tm_year + 1900 == target_year) {
                printf("%s - %s", entry->d_name, ctime(&file_stat.st_mtime));
                count++;
            }
        }
    }
    
    if (count == 0) {
        printf("No files found\n");
    } else {
        printf("\nTotal files: %d\n", count);
    }
    
    closedir(dir);
    return 0;
}
