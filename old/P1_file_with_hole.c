// 1. Create a file with hole in it.

#include <stdio.h>      // for perror, printf
#include <stdlib.h>     // for exit codes
#include <fcntl.h>      // for open() flags like O_WRONLY, O_CREAT, O_TRUNC
#include <unistd.h>     // for write(), lseek(), close()
#include <string.h>     // for strlen()

int main()
{
    // Open file for writing, create if not exists, truncate if exists, permissions 0666
    int fd = open("file_with_hole_text", O_WRONLY | O_CREAT | O_TRUNC, 0666);

    // If open failed, fd = -1 (not 1), print error and exit
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    // First data to write at the beginning of file
    const char *data1 = "this is the beginning of the file";
    write(fd, data1, strlen(data1));   // Write data1 to file

    // Define hole size (in bytes)
    off_t hole_size = 1024;

    // Move file pointer forward by hole_size, without writing data
    // This creates a "hole" (sparse area filled with implicit zeros)
    lseek(fd, hole_size, SEEK_CUR);

    // Second data to write after the hole
    const char *data2 = "this is the end of the file";
    write(fd, data2, strlen(data2));   // Write data2 after hole

    // Close file descriptor
    close(fd);

    return 0;   // Successful execution
}


//Output:
// gcc P1_file_with_hole.c -o file_with_hole
// ./file_with_hole