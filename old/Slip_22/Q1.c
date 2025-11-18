// Slip 22 Q1: Display message n times using setjmp (same as Slip 17 Q1)
// COMPILE: gcc -o Q1 Q1.c
// EXAMPLE: ./Q1 => Message repeated
#include <stdio.h>
#include <setjmp.h>
#include <stdlib.h>

jmp_buf buf;
int counter = 0;
int max_count = 5;

void display_message() {
    counter++;
    printf("Message %d: Hello from setjmp/longjmp!\n", counter);
    
    if (counter < max_count) {
        longjmp(buf, 1);
    }
}

int main() {
    printf("Enter number of times to display message: ");
    scanf("%d", &max_count);
    
    if (setjmp(buf) == 0) {
        printf("Starting display loop\n\n");
    }
    
    display_message();
    
    printf("\nDone!\n");
    return 0;
}
