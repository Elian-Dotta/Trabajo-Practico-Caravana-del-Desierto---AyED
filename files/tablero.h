#ifndef TABLERO_H_
#define TABLERO_H_

// SE ENCARGA DE CREAR, MODIFICAR, MOSTRAR Y DESTRUIR EL TABLERO DE JUEGO

#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <time.h>
#include "casilla.h"
#include "cola.h"
#include "estado.h"

#include "config.h"

int  crearTablero(tLista* tablero, tConfig config);
int  distruibuirElementos(tLista* tablero, tConfig config); // Puede no ser necesaria


int  agregarElemento();



typedef tListaDE tTablero;

int  crearTablero(tTablero* tablero, tConfig config);
int  generarTablero(tTablero* tablero, int *contElem, int cantPos);
int  distribuirElementos(tTablero* tablero, int *contElem, tConfig config);
int  moverElementoPorId(tTablero* tablero, int id, int mov);
int  generarMovBandido(tTablero* tablero, tCola *mov);
void actualizarEstadoDelJugador(tTablero* tablero, int posJug, tEstado *estado, ModificarEstado modEstado, tLista *bandinteligentes);


void mostrarTablero(tTablero* tablero); // muestra la lista
int  cmpInt(const void *a, const void *b);
int  cmpElem (const void* a, const void* b);
// Definidas:

void mostrarMapa(const tListaDE *lista, void(*mostrar)(const void *));
int borrarMapa(tListaDE *lista);
>>>>>>> Stashed changes

#endif // TABLERO_H_
