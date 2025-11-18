/* 2.Take multiple files as Command Line Arguments and print their inode number*/

#include <stdio.h>      // for printf, perror, fprintf
#include <stdlib.h>     // for exit codes
#include <fcntl.h>      // for open() flags
#include <sys/types.h>  // for types like ino_t
#include <sys/stat.h>   // for struct stat and fstat()

// Function to get inode number of a file using file descriptor
int get_inode(int fd) {
    struct stat buf;          // structure to hold file information
    int ret;

    ret = fstat(fd, &buf);    // get file info from fd into buf
    if (ret < 0) {            // check for error
        perror("fstat");
        // return -1;         // could return error code if needed
    }

    return buf.st_ino;        // return inode number of the file
}

int main(int argc, char *argv[]) {
    int fd, inode;

    // Check if user provided at least one file name
    if (argc < 2) {
        fprintf(stderr, "usage: %s <file1> <file2> ...\n", argv[0]);
        return 1;   // exit with error
    }

    // Loop through all command line arguments (files)
    for (int i = 1; i < argc; i++) {
        fd = open(argv[i], O_RDONLY);   // open each file in read-only mode
        if (fd < 0) {                   // check if file open failed
            perror("open");
            continue;                   // skip to next file
        }

        inode = get_inode(fd);          // get inode of current file
        printf("File: %s, Inode: %d\n", argv[i], inode);

        close(fd);                      // close file descriptor
    }

    return 0;   // successful execution

// Output:
//  gcc P2_print_inode.c -o inode_check
//  ./inode_check file1.txt file2.txt file3.txt