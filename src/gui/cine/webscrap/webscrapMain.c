#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "webscrapMain.h"

void pyAlhondiga(void)
{
    FILE *fp;
    char path[1035];
    char peliculas[100][100];
    int r = 0;

    // Execute the Python command
    fp = popen("python alhondiga.py --titulos", "r");
    if (fp == NULL) {
        printf("Failed to run command\n");
        return;
    }

    // Read the output of the command and store it in the array
    while (fgets(path, sizeof(path), fp) != NULL && r < 100) {
        path[strcspn(path, "\n")] = '\0';  // Remove the newline character
        snprintf(peliculas[r], sizeof(peliculas[r]), "%s", path);
        r++;
    }

    // Close the file pointer
    pclose(fp);

    // Print the stored strings
    for (int i = 0; i < r; i++) {
        printf("Pelicula %d: %s\n", i + 1, peliculas[i]);
    }
}

int cargarNombresPeliculas(char *message)
{
    FILE *fp;
    char path[1035];
    char peliculas[100][100];
    int r = 0;
    char command[1050];

    // Format the command string
    snprintf(command, sizeof(command), "python movies.py %s", message);

    // Execute the command
    fp = popen(command, "r");
    if (fp == NULL) {
        printf("Failed to run command\n");
        return 1;
    }

    // Read the output of the command and store it in the array
    while (fgets(path, sizeof(path), fp) != NULL && r < 100) {
        path[strcspn(path, "\n")] = '\0';  // Remove the newline character
        snprintf(peliculas[r], sizeof(peliculas[r]), "%s", path);
        r++;
    }

    // Close the file pointer
    pclose(fp);

    // Print the stored strings
    for (int i = 0; i < r; i++) {
        printf("Pelicula %d: %s\n", i + 1, peliculas[i]);
    }

    return 0;
}

int main(void)
{
    pyAlhondiga();
    // cargarNombresPeliculas("upcoming");
    return 0;
}