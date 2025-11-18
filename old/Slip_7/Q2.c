// Slip 7 Q2: Block SIGQUIT for 5 seconds, check pending signals
// COMPILE: gcc -o Q2 Q2.c
// EXAMPLE: ./Q2 => Try Ctrl+\ to test
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

void sigquit_handler(int sig) {
    printf("SIGQUIT received - Terminating program\n");
    exit(0);
}

int main() {
    sigset_t set, oldset, pending;
    int quit_pending = 0;
    
    signal(SIGQUIT, sigquit_handler);
    
    printf("Press Ctrl+\\ to send SIGQUIT\n");
    printf("Blocking SIGQUIT for 5 seconds...\n");
    
    // Create signal set with SIGQUIT
    sigemptyset(&set);
    sigaddset(&set, SIGQUIT);
    
    // Block SIGQUIT
    sigprocmask(SIG_BLOCK, &set, &oldset);
    
    printf("SIGQUIT blocked. You can send Ctrl+\\ now.\n");
    sleep(5);
    
    // Check if SIGQUIT was sent during blocking
    sigpending(&pending);
    
    if (sigismember(&pending, SIGQUIT)) {
        quit_pending = 1;
        printf("SIGQUIT was sent during blocking period\n");
    } else {
        printf("No SIGQUIT during blocking period\n");
    }
    
    // Unblock SIGQUIT
    printf("Unblocking SIGQUIT...\n");
    sigprocmask(SIG_UNBLOCK, &set, NULL);
    
    printf("SIGQUIT unblocked\n");
    
    if (quit_pending) {
        printf("If you sent Ctrl+\\, the program will terminate now\n");
    }
    
    printf("Program ending normally\n");
    return 0;
}
