#ifndef TABLERO_H_
#define TABLERO_H_

// SE ENCARGA DE CREAR, MODIFICAR, MOSTRAR Y DESTRUIR EL TABLERO DE JUEGO

#include <stdlib.h>
#include <time.h>
#include <stdlib.h>
#include <time.h>
#include "casilla.h"
#include "config.h"
#include "lista_doble_enlace_circular.h"
#include "lista_simple_enlace.h"

#define MSJ_LISTA_MAPA_VACIO "EL MAPA NO FUE GENERADO"
#define TAM_BUFFER 30

typedef tListaDE tTablero;

int  crearTablero(tTablero* tablero, tConfig config, tLista *bandidosInteligentes);
int  generarTablero(tTablero* tablero, int *contElem, int cantPos);
int  distribuirElementos(tTablero* tablero, int *contElem, tConfig config, *tLista bandidosInteligentes);
int  moverElementoPorId(tTablero* tablero, int id, int mov);
int  generarMovBandido(tTablero* tablero, tCola *mov);

void actualizarEstadoDelJugador(tTablero* tablero, int posJug, tEstado *estado, tLista *bandinteligentes);

void mostrarTablero(tTablero* tablero); // muestra la lista
int  cmpInt(const void *a, const void *b);

// Definidas:

void mostrarMapa(const tListaDE *lista, void(*mostrar)(const void *));
int borrarMapa(tListaDE *lista);

#endif // TABLERO_H_