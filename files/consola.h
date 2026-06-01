#ifndef CONSOLA_H_
#define CONSOLA_H_

#include "tablero.h"
#include "estado.h"
#include "jugador.h"

void dibujarEscena(tTablero *tablero, tJugador *jugador, tEstado *estado);

void mostrarTitulo();
void mostrarSeparador();
void mostrarHud(tJugador* jugador, tEstado *estado);

void mostrar(const char *msj);

#endif // CONSOLA_H_