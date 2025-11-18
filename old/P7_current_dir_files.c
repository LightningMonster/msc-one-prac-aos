/* 7. Read the current directory and display the name of the files, 
   and the number of files in the current directory. 
   (Hint: Current Directory is represented by .(dot)) */

#include <stdio.h>   // Standard I/O functions (printf, perror)
#include <stdlib.h>  // Standard library (exit codes)
#include <dirent.h>  // For directory handling functions (opendir, readdir, closedir)

int main() {
    DIR *dir;                // Pointer to directory stream
    struct dirent *entry;    // Structure pointer to hold directory entries
    int fileCount = 0;       // Counter to count number of files

    // Open the current directory (represented by ".")
    dir = opendir(".");
    if (dir == NULL) {                      // If directory cannot be opened
        perror("Error opening directory");  // Print error message
        return 1;                           // Exit with failure code
    }

    printf("Files in the current directory:\n");

    // Read each entry in the directory one by one
    while ((entry = readdir(dir)) != NULL) {
        // Check if the entry is a regular file (not directory, link, etc.)
        if (entry->d_type == DT_REG) {
            printf("%s\n", entry->d_name);  // Print the file name
            fileCount++;                    // Increment file count
        }
    }

    // Close the directory after use
    closedir(dir);

    // Print the total number of files found
    printf("\nTotal number of files in the current directory: %d\n", fileCount);

    return 0;   // Successful program termination
}

// Output:
// gcc P7_current_dir_files.c -o current_dir_files
// ./current_dir_files