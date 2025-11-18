/*12. List all subdirectories from current directory in alphabetical order */

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>

// Function to filter only directories
static int filter_dirs(const struct dirent *entry) {
    struct stat st;
    if (stat(entry->d_name, &st) == 0) {
        if (S_ISDIR(st.st_mode)) {
            // Skip . and .. directories
            if (strcmp(entry->d_name, ".") != 0 && 
                strcmp(entry->d_name, "..") != 0) {
                return 1;
            }
        }
    }
    return 0;
}

// Comparison function for sorting
static int compare(const struct dirent **a, const struct dirent **b) {
    return strcasecmp((*a)->d_name, (*b)->d_name);
}

int main(void) {
    struct dirent **namelist;
    int n;

    printf("Subdirectories in current folder:\n");
    printf("--------------------------------\n");

    // Scan directory with filtering and sorting
    n = scandir(".", &namelist, filter_dirs, compare);
    
    if (n < 0) {
        perror("scandir");
        return 1;
    }

    // Print and free the list
    for (int i = 0; i < n; i++) {
        printf("%s\n", namelist[i]->d_name);
        free(namelist[i]);
    }
    free(namelist);

    return 0;
}
    
// Output:
// gcc P12_list_subdirs.c -o list_subdirs
// ./list_subdirs