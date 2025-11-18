// Slip 25 Q1: Get and set resource limits (same as Slip 20 Q1)
// COMPILE: gcc -o Q1 Q1.c
// EXAMPLE: ./Q1 => Resource limits
#include <stdio.h>
#include <sys/resource.h>
#include <stdlib.h>

int main() {
    struct rlimit limit;
    
    printf("Current Resource Limits:\n");
    printf("========================\n\n");
    
    // File size limit
    getrlimit(RLIMIT_FSIZE, &limit);
    printf("File Size Limit:\n");
    printf("  Soft: %ld bytes\n", limit.rlim_cur);
    printf("  Hard: %ld bytes\n\n", limit.rlim_max);
    
    // Memory limit
    getrlimit(RLIMIT_AS, &limit);
    printf("Virtual Memory Limit:\n");
    printf("  Soft: %ld bytes\n", limit.rlim_cur);
    printf("  Hard: %ld bytes\n\n", limit.rlim_max);
    
    // Open files limit
    getrlimit(RLIMIT_NOFILE, &limit);
    printf("Open Files Limit:\n");
    printf("  Soft: %ld\n", limit.rlim_cur);
    printf("  Hard: %ld\n\n", limit.rlim_max);
    
    // CPU time limit
    getrlimit(RLIMIT_CPU, &limit);
    printf("CPU Time Limit:\n");
    printf("  Soft: %ld seconds\n", limit.rlim_cur);
    printf("  Hard: %ld seconds\n", limit.rlim_max);
    
    return 0;
}
