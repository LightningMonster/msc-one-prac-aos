// Slip 25 Q2: Create files with different permissions using umask and chmod
// COMPILE: gcc -o Q2 Q2.c
// EXAMPLE: ./Q2 => Created file1 (644), file2 (600), file3 (755)
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int main() {
    int fd;
    mode_t old_umask;
    
    printf("Creating files with different permissions...\n\n");
    
    // First file - default permissions (rw-rw-rw-)
    // No umask applied
    fd = open("file1.txt", O_CREAT | O_WRONLY, 0666);
    if (fd >= 0) {
        printf("Created file1.txt with permissions 0666\n");
        close(fd);
    }
    
    // Second file - apply umask
    old_umask = umask(0022);  // rw-r--r-- (removes write for group and others)
    fd = open("file2.txt", O_CREAT | O_WRONLY, 0666);
    if (fd >= 0) {
        printf("Created file2.txt with umask(0022)\n");
        close(fd);
    }
    umask(old_umask);  // Restore old umask
    
    // Third file - set group-id and remove group execute
    fd = open("file1.txt", O_WRONLY);
    if (fd >= 0) {
        // Set group-id bit and remove group execute
        chmod("file1.txt", S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH | S_ISGID);
        printf("Modified file1.txt: turned on group-id, removed group execute\n");
        close(fd);
    }
    
    // Fourth file - set read permission for all
    chmod("file2.txt", S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    printf("Modified file2.txt: set read permission for all\n");
    
    // Display file permissions
    struct stat sb;
    printf("\nFile Permissions:\n");
    printf("=================\n");
    
    if (stat("file1.txt", &sb) == 0) {
        printf("file1.txt: %04o\n", sb.st_mode & 0777);
    }
    
    if (stat("file2.txt", &sb) == 0) {
        printf("file2.txt: %04o\n", sb.st_mode & 0777);
    }
    
    return 0;
}
