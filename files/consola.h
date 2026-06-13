#ifndef CONSOLA_H_
#define CONSOLA_H_

#include <stdio.h>
#include <stdlib.h>


#include "tablero.h"
#include "estado.h"
#include "jugador.h"
#include "log.h"


void dibujarEscena(tTablero *tablero, tJugador *jugador, tEstado *estado, tLog *log);

void mostrarTitulo();
void mostrarSeparador();

void mostrar(const char *msj);

void mostrarHUD(tJugador*, tEstado*); // HAY QUE AGREGAR COMO PARAMETRO LAS VARIABLES A IMPRIMIR, HAY QUE DEFINIR TAMBIEN LAS VARIABLES A IMPRIMIR.

void limpiarBuffer(void);


//void mostrarTablero(void *casilla);

#endif // CONSOLA_H_
