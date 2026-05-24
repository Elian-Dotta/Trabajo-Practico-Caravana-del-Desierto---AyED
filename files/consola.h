#ifndef CONSOLA_H_
#define CONSOLA_H_

#include "tablero.h"
#include "estado.h"
#include "jugador.h"

void dibujarEscena(tTablero *tablero, tJugador *jugador, tEstado *estado);

void mostrarTitulo();
void mostrarSeparador();
void mostrarHud(tJugador* jugador, tEstado *estado); // HAY QUE AGREGAR COMO PARAMETRO LAS VARIABLES A IMPRIMIR, HAY QUE DEFINIR TAMBIEN LAS VARIABLES A IMPRIMIR.

void mostrar(const char *msj, FILE *output);



//void mostrarTablero(void *casilla);

#endif // CONSOLA_H_
