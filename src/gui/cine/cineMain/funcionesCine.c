#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcionesCine.h"

void clear_screen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// elegir numero de entradas
int elegirNEntradas(int altura, int anchura) {
    int nEntradas;
    printf("Cuantas entradas quieres comprar?: ");
    scanf("%d", &nEntradas);
    while (nEntradas > altura * anchura) {
        printf("No hay suficientes asientos disponibles. Intenta de nuevo: ");
        scanf("%d", &nEntradas);
    }
    return nEntradas;
}

void elegirAsientos(int nEntradas, char **matrizAsientos, int altura, int anchura) {
    printf("------------------------------------------------------------------------------------------------------------------------\n");
    printf("                                                              pantalla\n");
    printf("------------------------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < altura; i++) {
        for (int j = 0; j < anchura; j++) {
            matrizAsientos[i][j] = '0';
        }
    }
    for (int i = 0; i < altura; i++) {
        printf("%d  ", i + 1);
        for (int j = 0; j < anchura; j++) {
            if (i == 0) {
                if (j > 9) {
                    printf("%d ", j);
                } else {
                    printf("%d  ", j);
                }
            } else {
                printf("%c  ", matrizAsientos[i][j]);
            }
        }
        printf("\n");
    }
    for (int i = 0; i < nEntradas; i++) {
        int fila, columna;
        printf("Elige numero de fila: \n");
        scanf("%d", &fila);
        printf("Elige numero de columna: \n");
        scanf("%d", &columna);

        if (fila >= 0 && fila < altura && columna >= 0 && columna < anchura) {
            if (matrizAsientos[fila][columna] == '0') {
                matrizAsientos[fila][columna] = 'x';
                printf("Asiento [%d, %d] reservado.\n", fila, columna);
            } else {
                printf("El asiento [%d, %d] ya está ocupado. Elige otro asiento.\n", fila, columna);
                i--;  // Decrement i to retry the current seat selection
            }
        } else {
            printf("Asiento [%d, %d] fuera de rango. Elige otro asiento.\n", fila, columna);
            i--;  // Decrement i to retry the current seat selection
        }
    }
}


int comprarEntradas() {
    char e = 'e';
    int pelicula;
    int nentradas;
    int altura = 5;
    int anchura = 40;
    char **matrizAsientos;

    // Allocate and initialize matrizAsientos
    matrizAsientos = (char **)calloc(altura, sizeof(char *));
    for (int i = 0; i < altura; i++) {
        matrizAsientos[i] = (char *)calloc(anchura, sizeof(char));
    }

    // Allocate and initialize entradas
    char **entradas = (char **)calloc(100, sizeof(char *));
    for (int i = 0; i < 100; i++) {
        entradas[i] = (char *)calloc(100, sizeof(char));
    }

    while(e != '0') {
        pelicula = '1';
        strcpy(entradas[0], "Han Solo");
        strcpy(entradas[1], "Indiana Jones");
        strcpy(entradas[2], "Rick Deckard");
        strcpy(entradas[3], "Jack Ryan");
        strcpy(entradas[4], "game of thrones");
        strcpy(entradas[5], "garfield");
        printf("Elige una pelicula\n");
        printf("===================================\n");
        for (int i = 0; i < 100; i++) {
            if (strlen(entradas[i]) == 0) {
                break;
            }
            printf("(%d): --> %s <-- \n", i, entradas[i]);
        }
        pelicula = getchar() - '0';
        if (pelicula >= 0 && pelicula < 4) {
            nentradas = elegirNEntradas(altura, anchura);
            elegirAsientos(nentradas, matrizAsientos, altura, anchura);
            printf("Ticket de compra\n");
            printf("Pelicula: %s\n", entradas[pelicula]);
            printf("Asientos: %i \n", nentradas);
            printf("pulse e para seguir comprando y cualquier otra cosa para salir :\n");
            char g;
            scanf("%d", &g);
            if (g != 'e') {
                e = '0';
            }
        } else {
            printf("No has elegido ninguna pelicula\n");
            clear_screen();
        }
    }

    printf("Has elegido %s\n", entradas[pelicula]);

    // Free allocated memory
    for (int i = 0; i < altura; i++) {
        free(matrizAsientos[i]);
    }
    free(matrizAsientos);

    for (int i = 0; i < 100; i++) {
        free(entradas[i]);
    }
    free(entradas);

    return 0;
}