// Slip 14 Q2: Display file properties using stat()
// COMPILE: gcc -o Q2 Q2.c
// EXAMPLE: ./Q2 Q1.c => Size: 1500, Mode: 0644, Inode: 12345
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <stdlib.h>
#include <pwd.h>
#include <grp.h>

int main(int argc, char *argv[]) {
    struct stat file_stat;
    struct passwd *pwd;
    struct group *grp;
    
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    
    if (stat(argv[1], &file_stat) < 0) {
        perror("stat");
        return 1;
    }
    
    pwd = getpwuid(file_stat.st_uid);
    grp = getgrgid(file_stat.st_gid);
    
    printf("File: %s\n", argv[1]);
    printf("=========================================\n");
    printf("Inode Number: %ld\n", (long)file_stat.st_ino);
    printf("Hard Links: %ld\n", (long)file_stat.st_nlink);
    printf("File Permissions: %o\n", file_stat.st_mode & 0777);
    printf("File Size: %ld bytes\n", (long)file_stat.st_size);
    printf("User ID: %d (%s)\n", file_stat.st_uid, pwd ? pwd->pw_name : "unknown");
    printf("Group ID: %d (%s)\n", file_stat.st_gid, grp ? grp->gr_name : "unknown");
    printf("Last Access: %s", ctime(&file_stat.st_atime));
    printf("Last Modified: %s", ctime(&file_stat.st_mtime));
    printf("Status Changed: %s", ctime(&file_stat.st_ctime));
    
    return 0;
}
