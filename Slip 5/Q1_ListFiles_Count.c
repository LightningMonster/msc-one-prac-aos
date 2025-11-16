#include <stdio.h>
#include <dirent.h>

int main() {
    DIR *dp;
    struct dirent *entry;
    int count = 0;

    dp = opendir(".");   // Open current directory
    if (dp == NULL) {
        perror("Unable to open directory");
        return 1;
    }

    printf("Files in current directory:\n");

    // Read all entries
    while ((entry = readdir(dp)) != NULL) {
        printf("%s\n", entry->d_name);
        count++;
    }

    printf("\nTotal files/directories: %d\n", count);

    closedir(dp);
    return 0;
}

/*
    For output use the following commands:
    gcc Q1_ListFiles_Count.c
    ./a.out
*/