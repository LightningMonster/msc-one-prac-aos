#include <stdio.h>
#include <dirent.h>
#include <string.h>

int main(int argc, char *argv[]) {
    DIR *dp;
    struct dirent *entry;

    if (argc < 2) {
        printf("Usage: %s <file1> <file2> ...\n", argv[0]);
        return 1;
    }

    // Open current directory
    dp = opendir(".");
    if (dp == NULL) {
        perror("Unable to open directory");
        return 1;
    }

    // For each file passed through command line
    for (int i = 1; i < argc; i++) {
        int found = 0;

        rewinddir(dp);  // Reset directory pointer

        while ((entry = readdir(dp)) != NULL) {
            if (strcmp(entry->d_name, argv[i]) == 0) {
                found = 1;
                break;
            }
        }

        if (found)
            printf("File '%s' is PRESENT in current directory.\n", argv[i]);
        else
            printf("File '%s' is NOT FOUND in current directory.\n", argv[i]);
    }

    closedir(dp);
    return 0;
}

/*
    For output use the following commands:
    gcc Q1_CheckFilesInDirectory.c
    ./a.out file1.txt myprog.c notes.pdf
*/
