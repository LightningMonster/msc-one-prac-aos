#include <stdio.h>
#include <dirent.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    char *target = argv[1];
    DIR *dp;
    struct dirent *entry;
    int found = 0;

    dp = opendir(".");
    if (dp == NULL) {
        perror("Unable to open directory");
        return 1;
    }

    while ((entry = readdir(dp)) != NULL) {
        if (strcmp(entry->d_name, target) == 0) {
            found = 1;
            break;
        }
    }

    closedir(dp);

    if (found)
        printf("File '%s' is PRESENT in current directory.\n", target);
    else
        printf("File '%s' is NOT FOUND in current directory.\n", target);

    return 0;
}

/*
    Compile & Run:
    gcc Q1_CheckFileInDirectory.c
    ./a.out test.txt
*/
