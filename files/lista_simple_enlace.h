#ifndef LISTA_SIMPLE_ENLACE_H
#define LISTA_SIMPLE_ENLACE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "nodos.h"


typedef tNodo* tLista;

typedef void (*Mostrar)(const void *);
typedef void (*Accion)(void *, void *);
typedef int (*tCompararFn)(const void *, const void *);
typedef int (*Acumular)(void **, unsigned *, void *, unsigned);
typedef int  (*Cmp)(const void *, const void *);

typedef tNodo* tLista; // La lista sera un puntero a Nodo. Es decir, la lista
// tendra la direccion de memoria de un nodo, no datos. Asi ocupara solo 8 Bytes (tam de puntero).


typedef int (*Cmp)(const void *, const void *);
typedef void (*Mostrar) (const void*);
typedef int (*tCompararFn)(const void*, const void*);
typedef int (*Acumular) (void **, unsigned *, void *, unsigned);
typedef int  (*Cmp)(const void *, const void *);
typedef void  (*Accion)(void *, void *);


void crearLista(tLista *p);
int  vaciarLista(tLista *p);
int  ponerAlFinal(tLista *p, const void *d, unsigned cantBytes);
//int  sacarPrimeroLista(tLista *p, void *d, unsigned cantBytes);

//int  eliminarPorClave(tLista *p, void *d, unsigned tamDato, Cmp cmp);


void recorrerLista(tLista *lista, Accion accion, void *contexto);
int  buscarPorPosicionLista(tLista *lista, void *dest, unsigned tam, int pos);
int  eliminarPorClave(tLista *p, void *d, unsigned tamDato, Cmp cmp);
int vaciarLista(tLista *lista);
int ponerAlFinal(tLista *lista, const void *dato, unsigned tamDato);

int insertarOrdenadoLista(tLista *lista, const void *dato, unsigned tamDato, tCompararFn comparar, int conDup, Acumular acum);
int sacarPrimeroLista(tLista *lista, void *dest, unsigned tamDest);
int sacarUltimoLista(tLista *lista, void *dest, unsigned tamDest);

int insertarAlInicio(tLista *lista, void *d, unsigned tamDato);
int insertarAlFinalLista(tLista *lista, const void *d, unsigned tamDato);
int eliminarPorClaveLista(tLista *lista, void *d, unsigned tamDato, Cmp cmp);
int insertarEnPosLista(tLista *lista, void *d, unsigned tamDato, unsigned pos);

void recorrerLista(tLista *lista, Accion accion, void *contexto);
int buscarPorClaveEnLista(const tLista *lista, const void* clave, void *destDato, unsigned tamDest, tCompararFn comparar);

int actualizarPosLista(tLista *lista, void *d, unsigned tamDato, unsigned pos, Acumular acum);
int buscarPorClaveLista(tLista *lista, void *d, unsigned tamDato, Cmp cmp);

int mostrarLista(const tLista *lista, Mostrar mostrar);
#endif // LISTA_SIMPLE_ENLACE_H
