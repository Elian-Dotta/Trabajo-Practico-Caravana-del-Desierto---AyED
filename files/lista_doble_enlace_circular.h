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

int  insertarAlFinalDeListaDE(tListaDE *pl, void *d, unsigned tamInfo);
// int  actualizarPosListaDE(tListaDE *pl, void *d, unsigned tamInfo, unsigned pos, Acumular acum);
// ESTA FUNCION FUNCIONARIA SI LA LISTADE QUEDARIA APUNTANDO AL INICIO
// PERO NO FUNCIONA ASI, LA PLANTIE ANTES DE SABER COMO FUNCIONABA LA DE. MEJOR UTILIZAR ACTUALIZAR POR ID Y POR POS RELATIVA
// COMO REEMPLAZO SE PUEDE JUSTO LUEGO DE A UNA CASILLA A LA LISTA UTILIZAR ACTUALIZAR POR POS RELATIVA
void mostrarListaDE(tListaDE *pl, Mostrar mostrar);

void crearListaDE(tListaDE *lista);
int  vaciarListaDE(tListaDE *lista);
int  listaVaciaDE(tListaDE *lista);

int buscarPorClaveListaDE(tListaDE *lista, const void* clave, unsigned tam, Cmp cmp);
//int buscarPorClaveListaDE(tListaDE *lista, const void* clave, unsigned tam, Cmp cmp, Accion accion, void* contexto);


// ESTA FUNCION PODRIA DEVOLVER LA POSICION PERO DENUEVO, ES CIRCULAR Y DE ASI QUE QUEDA APUNTANDO AL ULTIMO ELEMENTO PROCESADO
// A LO MEJOR PODEMOS ACTUALIZAR UNA POSICION DEL TABLERO POR ID DE ELEMENTO, ESO ES UNA BUSQUEDA Y UNA ACTUALIZACION EN LA MISMA PRIMITIVA
// SINO UNA FUNCION QUE DEJE EL PUNTERO DE LA LISTA EN LA POSICION A ACTUALIZAR POR ID, Y LUEGO OTRA QUE ACTUALICE POSICION ACTUAL

int  actualizarPorClaveListaDE(tListaDE *pl, void *d, unsigned tamInfo, Cmp cmp, Acumular acum);                  // PARA ACTUALIZAR POR ID
int  actualizarPosRelativaListaDE(tListaDE *pl, void *d, unsigned tamInfo, int pos, Acumular acum);  // PARA ACTUALIZAR RELATIVO A LA ULTIMA POSICION DE PUNTERO

void recorrerListaDE(tListaDE *pl, Accion accion, void *contexto);

int  buscarPorClaveListaDE(tListaDE *pl, const void *clave, unsigned tam, Cmp cmp);
int  actualizarPosRelativaListaDE(tListaDE *pl, void *d, unsigned tamInfo, int pos, Acumular acum);

#endif // LISTA_DOBLE_ENLACE_CIRCULAR_H
