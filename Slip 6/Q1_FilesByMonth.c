#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
int main(int argc, char *argv[]) {
    DIR *dp;
    struct dirent *entry;
    struct stat fileStat;

    if (argc != 2) {
        printf("Usage: %s <month number 1-12>\n", argv[0]);
        return 1;
    }

    int month = atoi(argv[1]);  // Month input

    dp = opendir(".");
    if (dp == NULL) {
        perror("Unable to open directory");
        return 1;
    }

    printf("Files created in month %d:\n", month);

    while ((entry = readdir(dp)) != NULL) {
        if (stat(entry->d_name, &fileStat) == -1)
            continue;

        struct tm *timeinfo = localtime(&fileStat.st_ctime);

        if (timeinfo->tm_mon + 1 == month) {  
            printf("%s\n", entry->d_name);
        }
    }

    closedir(dp);
    return 0;
}

/*
    Compile and Run:
    gcc Q1_FilesByMonth.c
    ./a.out 11
*/
