// Slip 5 Q1: Find if file exists in current directory
// COMPILE: gcc -o Q1 Q1.c
// EXAMPLE: ./Q1 Q1.c => File exists, ./Q1 notfound => File not found
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char filename[100];
    
    if (argc < 2) {
        printf("Enter filename to search: ");
        scanf("%s", filename);
    } else {
        strcpy(filename, argv[1]);
    }
    
    // Check if file exists using access()
    if (access(filename, F_OK) == 0) {
        printf("File '%s' exists in current directory\n", filename);
        
        // Check read permission
        if (access(filename, R_OK) == 0)
            printf("File is readable\n");
        
        // Check write permission
        if (access(filename, W_OK) == 0)
            printf("File is writable\n");
        
        // Check execute permission
        if (access(filename, X_OK) == 0)
            printf("File is executable\n");
    } else {
        printf("File '%s' does not exist in current directory\n", filename);
    }
    
    return 0;
}
