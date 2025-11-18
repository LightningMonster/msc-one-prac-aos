/*8. Write a C program which receives file names as command line arguments and  
   display those filenames in ascending order according to their sizes. */

#include <stdio.h>      // For printf, etc.
#include <sys/stat.h>   // For stat() system call (to get file info)
#include <stdlib.h>     // For general functions like exit()

// Structure to hold file name and file size
struct FileInfo {
    char *name;   // File name
    long size;    // File size in bytes
};

int main(int argc, char *argv[]) {
    int i, j;

    // Check if at least 1 file is provided
    if (argc < 2) {
        printf("Usage : %s <file1> <file2> ...\n", argv[0]);
        return 1;
    }

    // Array of FileInfo structures for all given files
    struct FileInfo fileInfos[argc - 1];

    // Loop through all command-line files
    for (i = 1; i < argc; i++) {
        fileInfos[i - 1].name = argv[i];   // Save file name
        struct stat fileStat;

        // Get file statistics using stat()
        if (stat(argv[i], &fileStat) == 0 && S_ISREG(fileStat.st_mode)) {
            fileInfos[i - 1].size = fileStat.st_size;  // Save file size if regular file
        } else {
            printf("Skip non-regular file : %s\n", argv[i]);  // If directory or error
            fileInfos[i - 1].size = -1;  // Invalid size
        }
    }

    // Bubble sort files by size (ascending order)
    for (i = 0; i < argc - 1; i++) {
        for (j = 0; j < argc - 1 - i; j++) {
            if (fileInfos[j].size > fileInfos[j + 1].size) {
                struct FileInfo temp = fileInfos[j];
                fileInfos[j] = fileInfos[j + 1];
                fileInfos[j + 1] = temp;
            }
        }
    }

    // Print sorted files with their sizes
    for (i = 0; i < argc - 1; i++) {
        if (fileInfos[i].size >= 0) { // Ignore skipped files
            printf("%s - %ld bytes\n", fileInfos[i].name, fileInfos[i].size);
        }
    }

    return 0;
}


// Output:
// gcc P8_file_sort_size.c -o file_sort_size
// ./file_sort_size a.txt b.txt c.txt