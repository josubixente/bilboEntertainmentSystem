#ifndef FUNCIONESCINE_H
#define FUNCIONESCINE_H

void clear_screen();
int elegirNEntradas(int altura, int anchura);
void elegirAsientos(int nEntradas, char **matrizAsientos, int altura, int anchura);
int comprarEntradas();

#endif // FUNCIONESCINE_H