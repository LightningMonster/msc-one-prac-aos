/* 4. Print the type of file where file name accepted through Command Line */

#include <stdio.h>      // for printf, fprintf, perror
#include <sys/types.h>  // for system types (required by stat)
#include <sys/stat.h>   // for struct stat and S_IS* macros
#include <stdlib.h>     // for exit()

int main(int argc, char *argv[])
{
    // Check if filename is given in command line
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];  // filename from command line
    struct stat file_info;           // struct to hold file details

    // Get file information using stat()
    if (stat(filename, &file_info) == -1) {
        perror("Error getting file information");
        return 1;
    }

    // Check file type using macros
    if (S_ISREG(file_info.st_mode)) {
        printf("%s is a regular file\n", filename);
    } 
    else if (S_ISDIR(file_info.st_mode)) {
        printf("%s is a directory\n", filename);
    } 
    else if (S_ISLNK(file_info.st_mode)) {
        printf("%s is a symbolic link\n", filename);
    } 
    else if (S_ISCHR(file_info.st_mode)) {
        printf("%s is a character device\n", filename);
    } 
    else if (S_ISBLK(file_info.st_mode)) {
        printf("%s is a block device\n", filename);
    } 
    else if (S_ISFIFO(file_info.st_mode)) {
        printf("%s is a FIFO (named pipe)\n", filename);
    } 
    else if (S_ISSOCK(file_info.st_mode)) {
        printf("%s is a socket\n", filename);
    } 
    else {
        printf("Unknown file type\n");
    }

    return 0;   // success
}

//  Output:
//  gcc P4_file_type.c -o file_type
//  ./file_type file1.txt