#include <stdio.h>
#include <sys/stat.h>
#include <time.h>

int main(int argc, char *argv[]) {
    struct stat fileStat;

    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    // Get file properties
    if (stat(argv[1], &fileStat) == -1) {
        perror("Error");
        return 1;
    }

    printf("\nFile: %s\n", argv[1]);
    printf("Inode Number: %lu\n", fileStat.st_ino);
    printf("Number of Hard Links: %lu\n", fileStat.st_nlink);
    printf("File Size: %ld bytes\n", fileStat.st_size);

    // File Permissions
    printf("Permissions: ");
    printf((fileStat.st_mode & S_IRUSR) ? "r" : "-");
    printf((fileStat.st_mode & S_IWUSR) ? "w" : "-");
    printf((fileStat.st_mode & S_IXUSR) ? "x" : "-");
    printf((fileStat.st_mode & S_IRGRP) ? "r" : "-");
    printf((fileStat.st_mode & S_IWGRP) ? "w" : "-");
    printf((fileStat.st_mode & S_IXGRP) ? "x" : "-");
    printf((fileStat.st_mode & S_IROTH) ? "r" : "-");
    printf((fileStat.st_mode & S_IWOTH) ? "w" : "-");
    printf((fileStat.st_mode & S_IXOTH) ? "x" : "-");
    printf("\n");

    // Access and Modification Time
    printf("Last Access Time: %s", ctime(&fileStat.st_atime));
    printf("Last Modification Time: %s", ctime(&fileStat.st_mtime));

    return 0;
}

/*
    For output use the following commands:
    gcc Q1_FileProperties.c
    ./a.out test.txt
*/
