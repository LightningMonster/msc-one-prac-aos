/* 6.Write a C program that a string as an argument and return all the files that  
 begins with that name in the current directory. For example > ./a.out foo will  
 return all file names that begins with foo  */

#include <stdio.h>      // for printf, perror
#include <stdlib.h>     // for exit codes
#include <string.h>     // for strncmp, strlen
#include <dirent.h>     // for DIR, struct dirent, opendir, readdir, closedir

int main(int argc, char *argv[]) {
    // Check if prefix argument is provided
    if (argc != 2) {
        printf("Usage: %s <prefix>\n", argv[0]);
        return 1;
    }

    char *prefix = argv[1];    // the prefix string to match

    DIR *dir;                  // pointer to directory stream
    struct dirent *entry;      // struct to hold directory entry (filename info)

    // Open current directory (".")
    dir = opendir(".");
    if (dir == NULL) {
        perror("Error opening directory");  // print error if directory cannot be opened
        return 1;
    }

    printf("Files starting with '%s' in the current directory:\n", prefix);

    // Read each entry (file/folder) in directory
    while ((entry = readdir(dir)) != NULL) {
        // Compare prefix with start of file name
        if (strncmp(prefix, entry->d_name, strlen(prefix)) == 0) {
            printf("%s\n", entry->d_name);   // print if match
        }
    }

    // Close directory after reading all entries
    closedir(dir);

    return 0;   // success
}

// Output:
// gcc P6_prefix_files.c -o prefix_files
// ./prefix_files foo
