#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>

int main() {
    DIR *dp;
    struct dirent *entry;
    struct stat st;
    long limit;

    printf("Enter minimum file size (in bytes): ");
    scanf("%ld", &limit);

    dp = opendir(".");
    if (dp == NULL) {
        perror("Cannot open current directory");
        return 1;
    }

    printf("\nFiles larger than %ld bytes:\n", limit);

    while ((entry = readdir(dp)) != NULL) {
        // Get file info
        if (stat(entry->d_name, &st) == -1)
            continue;

        // Only consider regular files
        if (S_ISREG(st.st_mode) && st.st_size > limit) {
            printf("%s  ->  %ld bytes\n", entry->d_name, st.st_size);
        }
    }

    closedir(dp);
    return 0;
}

/*
    Compile & Run:
    gcc Q1_Files_SizeGreaterThanN.c
    ./a.out
    Enter minimum file size (in bytes): 200
*/
