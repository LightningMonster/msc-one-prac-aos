#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>

struct FileInfo {
    char filename[256];
    long size;
};

// Compare function for qsort
int compare(const void *a, const void *b) {
    struct FileInfo *f1 = (struct FileInfo *)a;
    struct FileInfo *f2 = (struct FileInfo *)b;

    return (f1->size - f2->size);   // Ascending order
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s file1 file2 file3 ...\n", argv[0]);
        return 1;
    }

    struct FileInfo files[100];
    struct stat st;
    int count = 0;

    // Read filenames and sizes
    for (int i = 1; i < argc; i++) {
        if (stat(argv[i], &st) == -1) {
            perror(argv[i]);
            continue;
        }

        strcpy(files[count].filename, argv[i]);
        files[count].size = st.st_size;
        count++;
    }

    // Sort by size
    qsort(files, count, sizeof(struct FileInfo), compare);

    // Print sorted list
    printf("\nFiles in ascending order of size:\n");
    for (int i = 0; i < count; i++) {
        printf("%s -> %ld bytes\n", files[i].filename, files[i].size);
    }

    return 0;
}

/*
    Compile & Run:
    gcc Q2_SortFilesBySize.c
    ./a.out a.txt b.txt c.txt
*/
