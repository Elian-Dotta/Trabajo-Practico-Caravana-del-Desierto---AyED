#ifndef LISTA_DOBLE_ENLACE_CIRCULAR_H
#define LISTA_DOBLE_ENLACE_CIRCULAR_H

#include <string.h>
#include <stdlib.h>
#include "nodos.h"

typedef tNodoDE* tListaDE;


//  - LA LISTA DOBLEMENTE ENLAZADA SIEMPRE QUEDA APUNTANDO AL ULTIMO ELEMENTO QUE PROCESO, SEA AÑADIRLO, ACTUALIZARLO O ELIMINARLO(EN ESTE CASO QUEDA AL LADO DEL ELIMINADO)
//  - DEBE HABER UNA FUNCION DE ACTUALIZAR POSICION DE LISTA YA QUE NO VAMOS A ELIMINAR LAS CASILLAS, SOLO ACTUALIZAR SU CONTENIDO
//  - EL ACCESO A LA ESTRUCTURA NODO DEBE QUEDAR UNICAMENTE A DISPOSICION DEL TDA, SINO ROMPEMOS ENCAPSULAMIENTO
// EL ACCESO AL DATO VA A SER SIEMPRE POR UNA FUNCION DE ACUMULAR O MOSTRAR O COMPARACION, COMO PUNTERO A FUNCION ENVIADO A LA PRIMITIVA
// LAS FUNCIONES PRIMITIVAS VAN A SER HECHAS A BENEFICIO DE LA LOGICA DEL JUEGO PERO IGUAL NO VAN A SABER QUE EXISTE EL JUEGO EN SI
// EL JUEGO TAMPOCO VA A SABER DE LA EXISTENCIA DE LOS NODOS EN SI
// TABLERO NO PUEDE METERSE A LA CASILLA Y CASILLA NO PUEDE METERSE EN EL TABLERO
// TABLERO DEBE LLAMAR A FUNCIONES DE CASILLA POR MEDIO DE LISTADE, CASILLA VAN A SER FUNCIONES PARA MANEJAR LA CASILLA
// Y CASILLA VA A LLAMAR A FUNCIONES DE LISTASE

// CONVENCION: *pl es un cursor que apunta al ultimo nodo procesado.
//  - Lista vacia: *pl == NULL
//  - Circular: ningun sig/ant es NULL. ultimo->sig == primero, primero->ant == ultimo
//  - Toda primitiva que procesa un nodo deja *pl apuntando a ese nodo


typedef int  (*Acumular)(void **, unsigned *, void *, unsigned);
typedef void (*Mostrar)(const void *);
typedef void (*Accion)(void *, void *);
typedef int  (*Cmp)(const void *, const void *);

//typedef void (*Accion)(tNodoDE **, tEstado*);

typedef void (*Accion)(void *, void*);


int  insertarAlFinalDeListaDE(tListaDE *pl, void *d, unsigned tamInfo);
// int  actualizarPosListaDE(tListaDE *pl, void *d, unsigned tamInfo, unsigned pos, Acumular acum);
// ESTA FUNCION FUNCIONARIA SI LA LISTADE QUEDARIA APUNTANDO AL INICIO
// PERO NO FUNCIONA ASI, LA PLANTIE ANTES DE SABER COMO FUNCIONABA LA DE. MEJOR UTILIZAR ACTUALIZAR POR ID Y POR POS RELATIVA
// COMO REEMPLAZO SE PUEDE JUSTO LUEGO DE AÑADIR UNA CASILLA A LA LISTA UTILIZAR ACTUALIZAR POR POS RELATIVA

void crearListaDE(tListaDE *lista);
int  vaciarListaDE(tListaDE *lista);
int  listaVaciaDE(tListaDE *lista);


int buscarPorClaveListaDE(tListaDE *lista, const void* clave, unsigned tam, Cmp cmp);
//int buscarPorClaveListaDE(tListaDE *lista, const void* clave, unsigned tam, Cmp cmp, Accion accion, void* contexto);


int buscarPorClaveListaDE(tListaDE *lista, const void* clave, unsigned tam, Cmp cmp, Accion accion, void* estado);

// ESTA FUNCION PODRIA DEVOLVER LA POSICION PERO DENUEVO, ES CIRCULAR Y DE ASI QUE QUEDA APUNTANDO AL ULTIMO ELEMENTO PROCESADO
// A LO MEJOR PODEMOS ACTUALIZAR UNA POSICION DEL TABLERO POR ID DE ELEMENTO, ESO ES UNA BUSQUEDA Y UNA ACTUALIZACION EN LA MISMA PRIMITIVA
// SINO UNA FUNCION QUE DEJE EL PUNTERO DE LA LISTA EN LA POSICION A ACTUALIZAR POR ID, Y LUEGO OTRA QUE ACTUALICE POSICION ACTUAL

int  actualizarPorClaveListaDE(tListaDE *pl, void *d, unsigned tamInfo, Cmp cmp, Acumular acum);                  // PARA ACTUALIZAR POR ID
int  actualizarPosRelativaListaDE(tListaDE *pl, void *d, unsigned tamInfo, int pos, Acumular acum);  // PARA ACTUALIZAR RELATIVO A LA ULTIMA POSICION DE PUNTERO

void crearListaDE(tListaDE *pl);
int  listaVaciaDE(const tListaDE *pl);

int  insertarAlFinalDeListaDE(tListaDE *pl, const void *d, unsigned tamInfo);
int  vaciarListaDE(tListaDE *pl);

void mostrarListaDE(tListaDE *pl, Mostrar mostrar);
void recorrerListaDE(tListaDE *pl, Accion accion, void *contexto);

int  buscarPorClaveListaDE(tListaDE *pl, const void *clave, unsigned tam, Cmp cmp);
int  actualizarPosRelativaListaDE(tListaDE *pl, void *d, unsigned tamInfo, int pos, Acumular acum);

#endif // LISTA_DOBLE_ENLACE_CIRCULAR_H
