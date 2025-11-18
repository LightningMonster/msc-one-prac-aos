/*5. Write a C program to find whether a given file is present in current directory  or not */

#include <stdio.h>      // for printf
#include <unistd.h>     // for access(), F_OK

int main(int argc, char *argv[])
{
    // Check if filename is passed as argument
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;   // exit with error if no file provided
    }

    // access() with F_OK checks if file exists in current directory
    if (access(argv[1], F_OK) == 0)
        printf("File '%s' exists.\n", argv[1]);
    else
        printf("File '%s' does not exist.\n", argv[1]);

    return 0;   // success
}


//  Output:
//  gcc P5_file_exist.c -o file_exist
//  ./file_exist file1.txt