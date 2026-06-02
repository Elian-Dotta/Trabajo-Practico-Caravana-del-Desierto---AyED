#ifndef CONSOLAH
#define CONSOLAH
#include <stdio.h>
#include <stdlib.h>

typedef struct tLista tLista;

int mostrarMenu();
void mostrarTablero(tLista *);
void mostrarEstadisticas();
void mostrarPedirNombre();
int mostrarPedirMov();
void mostrarHUD(tJugador*, tEstado*);


#endif // CONSOLAH
