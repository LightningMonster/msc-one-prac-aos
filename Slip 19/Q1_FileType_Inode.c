#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    struct stat st;

    if (argc < 2) {
        printf("Usage: %s <file1> <file2> ...\n", argv[0]);
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        if (stat(argv[i], &st) == -1) {
            perror(argv[i]);
            continue;
        }

        printf("\nFile: %s\n", argv[i]);
        printf("Inode Number: %lu\n", st.st_ino);

        printf("File Type: ");
        if (S_ISREG(st.st_mode))
            printf("Regular File\n");
        else if (S_ISDIR(st.st_mode))
            printf("Directory\n");
        else if (S_ISCHR(st.st_mode))
            printf("Character Device\n");
        else if (S_ISBLK(st.st_mode))
            printf("Block Device\n");
        else if (S_ISFIFO(st.st_mode))
            printf("FIFO / Pipe\n");
        else if (S_ISLNK(st.st_mode))
            printf("Symbolic Link\n");
        else if (S_ISSOCK(st.st_mode))
            printf("Socket\n");
        else
            printf("Unknown\n");
    }

    return 0;
}

/*
    Compile & Run:
    gcc Q1_FileType_Inode.c
    ./a.out file1.txt prog.c folder 
*/
