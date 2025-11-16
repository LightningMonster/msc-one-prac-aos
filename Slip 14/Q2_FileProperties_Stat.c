#include <stdio.h>
#include <sys/stat.h>
#include <time.h>

int main(int argc, char *argv[]) {
    struct stat st;

    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    // Get file details
    if (stat(argv[1], &st) == -1) {
        perror("stat error");
        return 1;
    }

    printf("\nFile: %s\n", argv[1]);

    printf("Inode Number: %lu\n", st.st_ino);
    printf("Number of Hard Links: %lu\n", st.st_nlink);
    printf("File Size: %ld bytes\n", st.st_size);

    // Permissions
    printf("Permissions: ");
    printf((st.st_mode & S_IRUSR) ? "r" : "-");
    printf((st.st_mode & S_IWUSR) ? "w" : "-");
    printf((st.st_mode & S_IXUSR) ? "x" : "-");
    printf((st.st_mode & S_IRGRP) ? "r" : "-");
    printf((st.st_mode & S_IWGRP) ? "w" : "-");
    printf((st.st_mode & S_IXGRP) ? "x" : "-");
    printf((st.st_mode & S_IROTH) ? "r" : "-");
    printf((st.st_mode & S_IWOTH) ? "w" : "-");
    printf((st.st_mode & S_IXOTH) ? "x" : "-");
    printf("\n");

    // Access and Modification time
    printf("Last Access Time: %s", ctime(&st.st_atime));
    printf("Last Modification Time: %s", ctime(&st.st_mtime));

    return 0;
}

/*
    Compile & Run:
    gcc Q2_FileProperties_Stat.c
    ./a.out test.txt
*/
