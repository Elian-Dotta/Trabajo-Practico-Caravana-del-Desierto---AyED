#ifndef LISTA_DOBLE_ENLACE_CIRCULAR_H
#define LISTA_DOBLE_ENLACE_CIRCULAR_H

#include <string.h>
#include <stdlib.h>
#include "nodos.h"

typedef tNodoDE* tListaDE;

typedef int  (*Acumular)(void **, unsigned *, void *, unsigned);
typedef void (*Mostrar)(const void *);
typedef void (*Accion)(void *, void *);
typedef int  (*Cmp)(const void *, const void *);


int  insertarAlFinalDeListaDE(tListaDE *pl, const void *d, unsigned tamInfo);

void crearListaDE(tListaDE *lista);
int  vaciarListaDE(tListaDE *lista);

int  buscarPorClaveListaDE(tListaDE *lista, const void* clave, unsigned tam, Cmp cmp);

int  actualizarPorClaveListaDE(tListaDE *pl, void *d, unsigned tamInfo, Cmp cmp, Acumular acum);                  // PARA ACTUALIZAR POR ID
int  actualizarPosRelativaListaDE(tListaDE *pl, void *d, unsigned tamInfo, int pos, Acumular acum);  // PARA ACTUALIZAR RELATIVO A LA ULTIMA POSICION DE PUNTERO

void recorrerListaDE(tListaDE *pl, Accion accion, void *contexto);
void mostrarListaDE(tListaDE *pl, Mostrar mostrar);

tNodoDE* buscarNodoPorClaveEnListaDE(const tListaDE *lista, const void* clave, Cmp comparar);

#endif // LISTA_DOBLE_ENLACE_CIRCULAR_H
