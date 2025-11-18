#include<stdio.h>
#include<sys/stat.h>

int main(int argc, char *argv[]){

    struct stat fileStat;

    if(argc < 2){
        printf("Usage: %s <file1> <file2> ...\n", argv[0]);
        return 1;
    }

    for(int i = 1; i < argc; i++){

        if(stat(argv[i], &fileStat) == -1){
            perror("Error");
            continue;
        }

        printf("\nFile: %s\n", argv[i]);
        printf("Inode Number: %lu\n", fileStat.st_ino);

        if(S_ISREG(fileStat.st_mode))
            printf("Type: Regular File\n");
        else if(S_ISDIR(fileStat.st_mode))
            printf("Type: Directory\n");
        else
            printf("Type: Unknown\n");
    }

    return 0;
}
