#include <stdio.h>
#include <sys/resource.h>

int main() {
    struct rlimit rl;

    // -------------------- FILE LIMIT (RLIMIT_NOFILE) --------------------
    printf("---- FILE DESCRIPTOR LIMIT ----\n");

    // Get current file descriptor limit
    if (getrlimit(RLIMIT_NOFILE, &rl) == 0) {
        printf("Current Soft Limit : %ld\n", rl.rlim_cur);
        printf("Current Hard Limit : %ld\n", rl.rlim_max);
    }

    // Set new file limit (Example: soft=1024)
    rl.rlim_cur = 1024;
    if (setrlimit(RLIMIT_NOFILE, &rl) == 0) {
        printf("Updated Soft Limit to 1024 successfully!\n");
    } else {
        perror("setrlimit failed (files)");
    }

    // -------------------- MEMORY LIMIT (RLIMIT_STACK) --------------------
    printf("\n---- STACK MEMORY LIMIT ----\n");

    // Get current memory limit
    if (getrlimit(RLIMIT_STACK, &rl) == 0) {
        printf("Current Soft Limit : %ld bytes\n", rl.rlim_cur);
        printf("Current Hard Limit : %ld bytes\n", rl.rlim_max);
    }

    // Set new stack memory limit (Example: 8 MB)
    rl.rlim_cur = 8 * 1024 * 1024;  // 8 MB
    if (setrlimit(RLIMIT_STACK, &rl) == 0) {
        printf("Updated Stack Soft Limit to 8MB successfully!\n");
    } else {
        perror("setrlimit failed (stack)");
    }

    return 0;
}

/*
    Compile & Run:
    gcc Q1_GetSet_ResourceLimits.c
    ./a.out
*/
