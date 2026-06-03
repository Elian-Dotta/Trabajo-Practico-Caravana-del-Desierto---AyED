#ifndef CONSOLAH
#define CONSOLAH
#include <stdio.h>
#include <stdlib.h>
#include "jugador.h"
#include "estado.h""

typedef struct tLista tLista;

int mostrarMenu();
void mostrarTablero(tLista *);
void mostrarEstadisticas();
void mostrarPedirNombre();
int mostrarPedirMov();
void mostrarHUD(tJugador*, tEstado*);


#endif // CONSOLAH
