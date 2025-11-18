// Slip 6 Q1: Find files that begin with a given string in current directory
// COMPILE: gcc -o Q1 Q1.c
// EXAMPLE: ./Q1 Q => Q1.c, Q2.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

int main(int argc, char *argv[]) {
    DIR *dir;
    struct dirent *entry;
    char prefix[100];
    
    if (argc < 2) {
        printf("Enter file prefix to search: ");
        scanf("%s", prefix);
    } else {
        strcpy(prefix, argv[1]);
    }
    
    dir = opendir(".");
    if (dir == NULL) {
        perror("opendir");
        return 1;
    }
    
    printf("Files beginning with '%s':\n", prefix);
    printf("=============================\n");
    
    int count = 0;
    while ((entry = readdir(dir)) != NULL) {
        if (strncmp(entry->d_name, prefix, strlen(prefix)) == 0) {
            printf("%s\n", entry->d_name);
            count++;
        }
    }
    
    if (count == 0) {
        printf("No files found with prefix '%s'\n", prefix);
    } else {
        printf("\nTotal files found: %d\n", count);
    }
    
    closedir(dir);
    return 0;
}
