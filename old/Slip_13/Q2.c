// Slip 13 Q2: Variable behavior with setjmp and longjmp
// COMPILE: gcc -o Q2 Q2.c
// EXAMPLE: ./Q2 => Variable values after longjmp
#include <stdio.h>
#include <setjmp.h>
#include <stdlib.h>

jmp_buf buf;

void test_variables() {
    auto int auto_var = 1;           // Automatic variable
    static int static_var = 2;       // Static variable
    register int register_var = 3;   // Register variable
    volatile int volatile_var = 4;   // Volatile variable
    
    printf("Before longjmp:\n");
    printf("auto_var = %d, static_var = %d, register_var = %d, volatile_var = %d\n",
           auto_var, static_var, register_var, volatile_var);
    
    auto_var = 10;
    static_var = 20;
    register_var = 30;
    volatile_var = 40;
    
    printf("Modified:\n");
    printf("auto_var = %d, static_var = %d, register_var = %d, volatile_var = %d\n",
           auto_var, static_var, register_var, volatile_var);
    
    longjmp(buf, 1);
}

int main() {
    auto int auto_var = 1;
    static int static_var = 2;
    register int register_var = 3;
    volatile int volatile_var = 4;
    
    if (setjmp(buf) == 0) {
        printf("First call to setjmp\n");
        printf("Calling test_variables()...\n\n");
        test_variables();
    } else {
        printf("\nAfter longjmp:\n");
        printf("auto_var = %d (unchanged)\n", auto_var);
        printf("static_var = %d (changed)\n", static_var);
        printf("register_var = %d (may be unchanged)\n", register_var);
        printf("volatile_var = %d (reloaded)\n", volatile_var);
    }
    
    return 0;
}
