#include <stdio.h>
#include <dirent.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <prefix>\n", argv[0]);
        return 1;
    }

    char *prefix = argv[1];
    int len = strlen(prefix);

    DIR *dp = opendir(".");
    if (dp == NULL) {
        perror("Unable to open directory");
        return 1;
    }

    struct dirent *entry;

    printf("Files starting with \"%s\":\n", prefix);

    while ((entry = readdir(dp)) != NULL) {
        if (strncmp(entry->d_name, prefix, len) == 0) {
            printf("%s\n", entry->d_name);
        }
    }

    closedir(dp);
    return 0;
}

/*
    Compile & Run:
    gcc Q2_FilesStartingWith.c
    ./a.out Q
    ./a.out Q1
*/
