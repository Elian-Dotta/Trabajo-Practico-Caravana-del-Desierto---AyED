#ifndef LISTA_DOBLE_ENLACE_CIRCULAR_H
#define LISTA_DOBLE_ENLACE_CIRCULAR_H

#include <string.h>
#include <stdlib.h>
#include "nodos.h"

typedef tNodoDE* tListaDE;

// CONVENCION: *pl es un cursor que apunta al ultimo nodo procesado.
//  - Lista vacia: *pl == NULL
//  - Circular: ningun sig/ant es NULL. ultimo->sig == primero, primero->ant == ultimo
//  - Toda primitiva que procesa un nodo deja *pl apuntando a ese nodo

typedef int  (*Acumular)(void **, unsigned *, void *, unsigned);
typedef void (*Mostrar)(const void *);
typedef void (*Accion)(void *, void *);
typedef int  (*Cmp)(const void *, const void *);

void crearListaDE(tListaDE *pl);
int  listaVaciaDE(const tListaDE *pl);

int  insertarAlFinalDeListaDE(tListaDE *pl, const void *d, unsigned tamInfo);
int  vaciarListaDE(tListaDE *pl);

void mostrarListaDE(tListaDE *pl, Mostrar mostrar);
void recorrerListaDE(tListaDE *pl, Accion accion, void *contexto);

int  buscarPorClaveListaDE(tListaDE *pl, const void *clave, unsigned tam, Cmp cmp);
int  actualizarPosRelativaListaDE(tListaDE *pl, void *d, unsigned tamInfo, int pos, Acumular acum);

#endif // LISTA_DOBLE_ENLACE_CIRCULAR_H
