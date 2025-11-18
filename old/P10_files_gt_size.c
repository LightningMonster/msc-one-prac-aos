/*10. Display all files from current directory whose size is greater than n Bytes */

#include <stdio.h>      // for printf, fprintf, perror
#include <stdlib.h>     // for atoll(), exit codes
#include <dirent.h>     // for opendir(), readdir(), closedir()
#include <sys/stat.h>   // for stat() and S_ISREG()

int main(int argc, char *argv[]) {
    // Check if user provides size argument
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <size_in_bytes>\n", argv[0]);
        return 1;
    }

    long long int min_size = atoll(argv[1]); // Convert argument to integer

    if (min_size <= 0) {                     // Validate size
        fprintf(stderr, "Invalid size. Please provide a positive size in bytes.\n");
        return 2;
    }

    DIR *dir = opendir(".");                 // Open current directory
    if (dir == NULL) {                       // Check if directory opened
        perror("opendir");
        return 3;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) { // Loop through all entries
        struct stat fileStat;

        // Get file information
        if (stat(entry->d_name, &fileStat) == -1) {
            perror("stat");
            continue;
        }

        // Check if it is a regular file and size > min_size
        if (S_ISREG(fileStat.st_mode) && fileStat.st_size > min_size) {
            printf("%s\n", entry->d_name);   // Print filename
        }
    }

    closedir(dir);  // Close directory
    return 0;
}

// Output:
// gcc P10_files_gt_size.c -o files_gt_size
// ./files_gt_size 1000
