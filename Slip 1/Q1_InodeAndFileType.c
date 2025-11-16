/* Take multiple files as Command Line Arguments and print their inode numbers and file types  */

#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    struct stat fileStat;
    
    // At least 1 file needed
    if (argc < 2) {
        printf("Usage: %s <file1> <file2> ...\n", argv[0]);
        return 1;
    }

    // Loop through each file
    for (int i = 1; i < argc; i++) {
        if (stat(argv[i], &fileStat) == -1) {
            perror("Error");
            continue;
        }

        printf("\nFile: %s\n", argv[i]);
        printf("Inode Number: %lu\n", fileStat.st_ino);

        // File type check
        if (S_ISREG(fileStat.st_mode))
            printf("Type: Regular File\n");
        else if (S_ISDIR(fileStat.st_mode))
            printf("Type: Directory\n");
        else if (S_ISLNK(fileStat.st_mode))
            printf("Type: Symbolic Link\n");
        else if (S_ISCHR(fileStat.st_mode))
            printf("Type: Character Device\n");
        else if (S_ISBLK(fileStat.st_mode))
            printf("Type: Block Device\n");
        else if (S_ISFIFO(fileStat.st_mode))
            printf("Type: FIFO/PIPE\n");
        else if (S_ISSOCK(fileStat.st_mode))
            printf("Type: Socket\n");
        else
            printf("Type: Unknown\n");
    }

    return 0;
}

//for output use the following command
// gcc Q1_InodeAndFileType.c 
// ./a.out test.txt test.c test
