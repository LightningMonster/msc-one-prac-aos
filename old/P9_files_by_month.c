/*9. Display all the files from current directory which are created in particular month */

#include <stdio.h>      // For printf, fprintf
#include <stdlib.h>     // For atoi(), exit codes
#include <string.h>     // For string functions
#include <dirent.h>     // For opendir(), readdir()
#include <sys/stat.h>   // For stat() to get file properties
#include <time.h>       // For time-related functions

// Array of month names (not used directly but useful for readability)
const char *month_names[] = {
    "January", "February", "March", "April", "May", "June",
    "July", "August", "September", "October", "November", "December"
};

int main(int argc, char *argv[]) {
    // Ensure correct usage: program requires 1 argument (month number)
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <month_number>\n", argv[0]);
        return 1;
    }

    // Convert month number (string) to integer
    int target_month = atoi(argv[1]);
   
    // Validate month number
    if (target_month < 1 || target_month > 12) {
        fprintf(stderr, "Invalid month number. Please provide a number between 1 and 12.\n");
        return 2;
    }

    // Open the current directory
    DIR *dir = opendir(".");
    if (dir == NULL) {
        perror("opendir");   // Print error if directory can't be opened
        return 3;
    }

    struct dirent *entry;
    // Loop through all entries in the directory
    while ((entry = readdir(dir)) != NULL) {
        struct stat fileStat;

        // Get file properties
        if (stat(entry->d_name, &fileStat) == -1) {
            perror("stat");
            continue;
        }

        // Extract last modification time of the file
        struct tm file_time;
        localtime_r(&fileStat.st_mtime, &file_time);

        // Compare file month with target month
        if (file_time.tm_mon + 1 == target_month) {
            char formatted_time[100];
            // Format time as "Mon YYYY" (e.g., "Sep 2025")
            strftime(formatted_time, sizeof(formatted_time), "%b %Y", &file_time);

            // Print filename and its last modified month
            printf("%s (%s)\n", entry->d_name, formatted_time);
        }
    }

    // Close the directory
    closedir(dir);

    return 0;
}

// Output:
// gcc P9_files_by_month.c -o files_by_month
// ./files_by_month 9