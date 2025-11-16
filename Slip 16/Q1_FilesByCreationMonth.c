#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <stdlib.h>

int main() {
    DIR *dp;
    struct dirent *entry;
    struct stat st;
    int month;

    printf("Enter month number (1-12): ");
    scanf("%d", &month);

    if (month < 1 || month > 12) {
        printf("Invalid month!\n");
        return 1;
    }

    dp = opendir(".");
    if (dp == NULL) {
        perror("Unable to open directory");
        return 1;
    }

    printf("\nFiles created in month %d:\n", month);

    while ((entry = readdir(dp)) != NULL) {
        if (stat(entry->d_name, &st) == -1)
            continue;

        struct tm *t = localtime(&st.st_ctime);

        if ((t->tm_mon + 1) == month) {   // tm_mon = 0-11
            printf("%s\n", entry->d_name);
        }
    }

    closedir(dp);
    return 0;
}

/*
    Compile & Run:
    gcc Q1_FilesByCreationMonth.c
    ./a.out
    Enter month number (1-12): 11
*/
