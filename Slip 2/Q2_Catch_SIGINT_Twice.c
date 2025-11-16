#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

int count = 0;

// Signal handler function
void sigint_handler(int sig) {
    count++;

    if (count == 1) {
        printf("\nCTRL-C pressed once! Press again to exit.\n");
    } else {
        printf("\nCTRL-C pressed twice! Exiting...\n");
        exit(0);
    }
}

int main() {
    // Register signal handler
    signal(SIGINT, sigint_handler);

    printf("Program running... Press CTRL-C.\n");

    while (1) {
        pause();  // Wait for signal
    }

    return 0;
}

/*
    For output use the following commands:
    gcc Q2_Catch_SIGINT_Twice.c
    ./a.out
*/
