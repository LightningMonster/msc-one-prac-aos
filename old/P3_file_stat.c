/* 3.Write a C program to find file properties such as inode number, number of hard link, File permissions, File size, File access and modification time and so on of a given file using stat() system call.*/

#include <stdio.h>      // for printf, scanf
#include <unistd.h>     // for access(), R_OK, W_OK, X_OK
#include <sys/stat.h>   // for struct stat and stat()
#include <time.h>       // for struct tm, gmtime()

// Function to display file properties
void printFileProperties(struct stat stats);

int main()
{
    char path[100];          // to store file name input
    struct stat stats;       // struct to store file info

    printf("Enter source filename : ");
    scanf("%s", path);       // take file name from user

    // stat() fills 'stats' with file information
    if (stat(path, &stats) == 0)
    {
        printFileProperties(stats);   // if success, print properties
    }
    else
    {
        // if stat() fails, file may not exist or permission issue
        printf("Unable to get file properties.\n");
        printf("Please check whether '%s' file exists.\n", path);
    }

    return 0;
}

void printFileProperties(struct stat stats)
{
    struct tm dt;

    // File access permissions
    printf("\nFile access: ");
    if (stats.st_mode & R_OK)     // check read permission
        printf("read ");
    if (stats.st_mode & W_OK)     // check write permission
        printf("write ");
    if (stats.st_mode & X_OK)     // check execute permission
        printf("execute");

    // File size in bytes
    printf("\nFile size: %ld bytes", stats.st_size);

    // File inode number
    printf("\nInode number: %ld", stats.st_ino);

    // Number of hard links
    printf("\nNumber of hard links: %ld", stats.st_nlink);

    // File creation/change time (ctime)
    dt = *(gmtime(&stats.st_ctime));   // convert to human-readable format (UTC)
    printf("\nCreated on: %02d-%02d-%d %02d:%02d:%02d",
           dt.tm_mday, dt.tm_mon + 1, dt.tm_year + 1900,
           dt.tm_hour, dt.tm_min, dt.tm_sec);

    // Last modification time (mtime)
    dt = *(gmtime(&stats.st_mtime));
    printf("\nModified on: %02d-%02d-%d %02d:%02d:%02d",
           dt.tm_mday, dt.tm_mon + 1, dt.tm_year + 1900,
           dt.tm_hour, dt.tm_min, dt.tm_sec);

    // Last access time (atime)
    dt = *(gmtime(&stats.st_atime));
    printf("\nLast accessed on: %02d-%02d-%d %02d:%02d:%02d\n",
           dt.tm_mday, dt.tm_mon + 1, dt.tm_year + 1900,
           dt.tm_hour, dt.tm_min, dt.tm_sec);
}

// Output:
//  gcc P3_file_stat.c -o file_stat
//  ./file_stat
//  Enter source filename : file1.txt