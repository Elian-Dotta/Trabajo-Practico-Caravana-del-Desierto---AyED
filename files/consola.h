#ifndef CONSOLA_H_
#define CONSOLA_H_

#include <stdio.h>
#include <stdlib.h>

#include "estado.h"
#include "jugador.h"
#include "log.h"
#include "tablero.h"

void dibujarEscena(tTablero *tablero, tJugador *jugador, tEstado *estado, tLog *log);

void dibujarFinDePartida(tTablero *tablero, tJugador *jugador, tLog *log);

void mostrarTitulo();

void mostrarSeparador();

void mostrar(const char *msj);

void mostrarHUD(tJugador*, tEstado*); // HAY QUE AGREGAR COMO PARAMETRO LAS VARIABLES A IMPRIMIR, HAY QUE DEFINIR TAMBIEN LAS VARIABLES A IMPRIMIR.

void mostrarEstadisticas(tJugador *j);

void limpiarBuffer(void);

void limpiarPantalla();


#endif // CONSOLA_H_
