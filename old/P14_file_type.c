/*14. Identify the type of a given file using stat() system call */

#include <stdio.h>      // for printf, perror
#include <sys/stat.h>   // for stat() and macros like S_ISDIR

int main(int argc, char *argv[]) {
    // Check if file path is provided
    if (argc != 2) {
        printf("Usage: %s <file_path>\n", argv[0]);
        return 1;
    }

    struct stat fileStat;

    // Get file information using stat()
    if (stat(argv[1], &fileStat) < 0) {
        perror("stat"); // Print error if stat fails
        return 1;
    }

    printf("File type: ");

    // Check file type using macros
    if (S_ISDIR(fileStat.st_mode)) {
        printf("Directory\n");
    } else if (S_ISCHR(fileStat.st_mode)) {
        printf("Character Device\n");
    } else if (S_ISBLK(fileStat.st_mode)) {
        printf("Block Device\n");
    } else if (S_ISREG(fileStat.st_mode)) {
        printf("Regular File\n");
    } else if (S_ISFIFO(fileStat.st_mode)) {
        printf("FIFO or Pipe\n");
    } else if (S_ISLNK(fileStat.st_mode)) {
        printf("Symbolic Link\n");
    } else if (S_ISSOCK(fileStat.st_mode)) {
        printf("Socket\n");
    } else {
        printf("Unknown\n");
    }

    return 0;
}

//  Output:
//  gcc P14_file_type.c -o file_type
//  ./file_type file1.txt
//  ./file_type testDir