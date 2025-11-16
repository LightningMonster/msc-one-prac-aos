#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/resource.h>

int main() {
    int n;
    printf("Enter number of child processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        if (fork() == 0) {
            // Child work
            for (long j = 0; j < 50000000; j++); // Dummy load
            return 0;
        }
    }

    // Parent gathers usage of each child
    struct rusage usage;
    double total_user = 0, total_sys = 0;

    for (int i = 0; i < n; i++) {
        wait4(-1, NULL, 0, &usage);
        total_user += usage.ru_utime.tv_sec + usage.ru_utime.tv_usec / 1000000.0;
        total_sys += usage.ru_stime.tv_sec + usage.ru_stime.tv_usec / 1000000.0;
    }

    printf("\nTotal User Time: %.6f seconds\n", total_user);
    printf("Total Kernel Time: %.6f seconds\n", total_sys);

    return 0;
}

/*
    Compile & Run:
    gcc Q2_NChild_UserKernelTime.c
    ./a.out

    Enter number of child processes: 3
*/
