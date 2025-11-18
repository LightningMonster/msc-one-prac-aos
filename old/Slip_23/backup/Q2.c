// Slip 23 Q2: Read directory and copy files to backup using fork and exec
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

int main() {
    DIR *dir;
    struct dirent *entry;
    struct stat file_stat;
    pid_t pid;
    
    // Create backup directory
    mkdir("backup", 0755);
    
    dir = opendir(".");
    if (dir == NULL) {
        perror("opendir");
        return 1;
    }
    
    printf("Copying files to backup directory...\n");
    
    int file_count = 0;
    while ((entry = readdir(dir)) != NULL) {
        // Skip directories and special files
        if (entry->d_name[0] == '.' || strcmp(entry->d_name, "backup") == 0)
            continue;
        
        if (stat(entry->d_name, &file_stat) == 0 && S_ISREG(file_stat.st_mode)) {
            pid = fork();
            
            if (pid < 0) {
                perror("fork");
                continue;
            } else if (pid == 0) {
                // Child process - execute cp command
                char dest[256];
                snprintf(dest, sizeof(dest), "backup/%s", entry->d_name);
                
                execlp("cp", "cp", entry->d_name, dest, NULL);
                perror("execlp");
                exit(1);
            } else {
                // Parent waits for child
                wait(NULL);
                printf("Copied: %s -> backup/%s\n", entry->d_name, entry->d_name);
                file_count++;
            }
        }
    }
    
    printf("\nTotal files copied: %d\n", file_count);
    
    closedir(dir);
    return 0;
}
