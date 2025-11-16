#include <stdio.h>
#include <dirent.h>

int main() {
    DIR *dp;
    struct dirent *entry;
    int count = 0;

    dp = opendir(".");
    if (dp == NULL) {
        perror("Unable to open current directory");
        return 1;
    }

    printf("Files in current directory:\n");

    while ((entry = readdir(dp)) != NULL) {
        printf("%s\n", entry->d_name);
        count++;
    }

    printf("\nTotal entries: %d\n", count);

    closedir(dp);
    return 0;
}

/*
    Compile & Run:
    gcc Q1_ListFiles_Count.c
    ./a.out
*/
