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

#define MSJ_LISTA_MAPA_VACIO "EL TABLERO NO FUE GENERADO"
#define TAM_BUFFER 30

typedef tListaDE tTablero;

int  crearTablero(tTablero* tablero, tConfig config);
int  generarTablero(tTablero* tablero, int *contElem, int cantPos);
int  distribuirElementos(tTablero* tablero, int *contElem, tConfig config);
int  moverElementoPorId(tTablero* tablero, int id, int mov);
int  generarMovBandido(tTablero* tablero, tCola *mov);
int  actualizarEstadoDelJugador(tTablero* tablero, int posJug, tEstado *estado);

void mostrarTablero(tTablero* tablero); // muestra la lista
int  cmpInt(const void *a, const void *b);
tTablero posicionarTablero(tTablero* tablero, int idElemPosicion);
#endif // TABLERO_H_
