// Slip 21 Q1: Demonstrate atexit() function
// COMPILE: gcc -o Q1 Q1.c
// EXAMPLE: ./Q1 => Handler 1, Handler 2, Handler 3, Main exits
#include <stdio.h>
#include <stdlib.h>

void exit_function1() {
    printf("Exit function 1 called\n");
}

void exit_function2() {
    printf("Exit function 2 called\n");
}

void exit_function3() {
    printf("Exit function 3 called\n");
}

int main() {
    printf("Registering exit handlers...\n");
    
    atexit(exit_function1);
    atexit(exit_function2);
    atexit(exit_function3);
    
    printf("Main function executing\n");
    printf("Main function completed\n");
    
    printf("Program exiting (handlers will be called in reverse order)\n");
    
    return 0;
}
