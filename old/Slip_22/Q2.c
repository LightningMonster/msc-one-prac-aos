// Slip 22 Q2: Display file info like ls -l (same as Slip 15 Q2)
// COMPILE: gcc -o Q2 Q2.c
// EXAMPLE: ./Q2 Q1.c => -rw-r--r--  1 user group  1500 Nov 18 10:30 Q1.c
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <stdlib.h>
#include <pwd.h>
#include <grp.h>
#include <string.h>

void print_permissions(mode_t mode) {
    printf( (S_ISDIR(mode)) ? "d" : "-");
    printf( (mode & S_IRUSR) ? "r" : "-");
    printf( (mode & S_IWUSR) ? "w" : "-");
    printf( (mode & S_IXUSR) ? "x" : "-");
    printf( (mode & S_IRGRP) ? "r" : "-");
    printf( (mode & S_IWGRP) ? "w" : "-");
    printf( (mode & S_IXGRP) ? "x" : "-");
    printf( (mode & S_IROTH) ? "r" : "-");
    printf( (mode & S_IWOTH) ? "w" : "-");
    printf( (mode & S_IXOTH) ? "x" : "-");
}

int main(int argc, char *argv[]) {
    struct stat file_stat;
    struct passwd *pwd;
    struct group *grp;
    char time_str[20];
    
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
    
    print_permissions(file_stat.st_mode);
    printf(" %2ld %s %s %8ld ",
           (long)file_stat.st_nlink,
           pwd ? pwd->pw_name : "unknown",
           grp ? grp->gr_name : "unknown",
           (long)file_stat.st_size);
    
    strftime(time_str, sizeof(time_str), "%b %d %H:%M", 
             localtime(&file_stat.st_mtime));
    printf("%s %s\n", time_str, argv[1]);
    
    return 0;
}
