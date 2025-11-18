/*11. Demonstrates redirection of standard output to a file */

#include <stdio.h>

int main() {
    // Redirect stdout to a file named "redirect_assi11.txt"
    // All printf statements after this will go to this file instead of console
    freopen("redirect_assi11.txt", "w", stdout);

    // Print statements now write to "redirect_assi11.txt"
    printf("This will be written to output file named redirect_assi11.txt\n");
    printf("Hello, World! This text is written with the help of code.\n");
    printf("Hello, Lightning Monster!\n");

    // Close the redirected stdout to save file properly
    fclose(stdout);

    return 0;
}

// Output:
// gcc P11_redirect_output.c -o redirect_output
// ./redirect_output
// cat redirect_assi11.txt