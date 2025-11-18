// Slip 21 Q2: List files and directories in alphabetical order
// COMPILE: gcc -o Q2 Q2.c
// EXAMPLE: ./Q2 => ., .., Q1, Q1.c, Q2, Q2.c
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

typedef struct {
    char name[256];
    int is_dir;
} Entry;

int compare_entries(const void *a, const void *b) {
    Entry *ea = (Entry *)a;
    Entry *eb = (Entry *)b;
    return strcmp(ea->name, eb->name);
}

int main() {
    DIR *dir;
    struct dirent *entry;
    struct stat file_stat;
    Entry *entries = NULL;
    int count = 0, capacity = 20;
    
    dir = opendir(".");
    if (dir == NULL) {
        perror("opendir");
        return 1;
    }
    
    entries = malloc(capacity * sizeof(Entry));
    
    // Read all entries
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] == '.') continue;
        
        if (count >= capacity) {
            capacity *= 2;
            entries = realloc(entries, capacity * sizeof(Entry));
        }
        
        stat(entry->d_name, &file_stat);
        strcpy(entries[count].name, entry->d_name);
        entries[count].is_dir = S_ISDIR(file_stat.st_mode) ? 1 : 0;
        count++;
    }
    
    // Sort entries
    qsort(entries, count, sizeof(Entry), compare_entries);
    
    // Display
    printf("All files and directories (alphabetical):\n");
    printf("========================================\n");
    for (int i = 0; i < count; i++) {
        if (entries[i].is_dir) {
            printf("%s/\n", entries[i].name);
        } else {
            printf("%s\n", entries[i].name);
        }
    }
    
    printf("\nTotal items: %d\n", count);
    
    closedir(dir);
    free(entries);
    return 0;
}
