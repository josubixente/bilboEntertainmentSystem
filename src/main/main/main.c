#include <stdio.h>
#include <stdlib.h>

int main() {
    // Clear the screen
    system("cls");

    // Change to the root directory of the project
    if (system("cd ../../gui/cine/cineMain") != 0) {
        perror("Error changing directory");
        return 1;
    }

    // Compile the C files
    if (system("gcc  funcionesCine.c main.c -o cine") != 0) {
        perror("Error compiling the C files");
        return 1;
    }

    // Execute the compiled program
    if (system("./cine") != 0) {
        perror("Error executing the compiled program");
        return 1;
    }

    return 0;
}