#ifndef LISTA_SIMPLE_ENLACE_H
#define LISTA_SIMPLE_ENLACE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "nodos.h"

typedef tNodo* tLista;

typedef void (*Mostrar) (const void*);
typedef void (*Accion) (const *, const *);
typedef int (*tCompararFn)(const void*, const void*);
typedef int (*Acumular) (void **, unsigned *, void *, unsigned);
typedef int  (*Cmp)(const void *, const void *);
typedef void  (*Accion)(void *, void *);

void crearLista(tLista *lista);
int listaVacia(const tLista *lista);
int listaLlena(const tLista *lista, unsigned tamDato); //No se requiere el dato en principio, ver si borrar

int vaciarLista(tLista *lista);
int ponerAlFinal(tLista *lista, const void *dato, unsigned tamDato);

int insertarOrdenadoLista(tLista *lista, const void *dato, unsigned tamDato, tCompararFn comparar, int conDup, Acumular acum);
int sacarPrimeroLista(tLista *lista, void *dest, unsigned tamDest);
int sacarUltimoLista(tLista *lista, void *dest, unsigned tamDest);

int insertarAlInicio(tLista *lista, void *d, unsigned tamDato);
int insertarAlFinalLista(tLista *lista, const void *d, unsigned tamDato);
int eliminarPorClaveLista(tLista *lista, void *d, unsigned tamDato, Cmp cmp);
int buscarPorClaveLista(tLista *lista, void *d, unsigned tamDato, Cmp cmp);
int insertarEnPosLista(tLista *lista, void *d, unsigned tamDato, unsigned pos);

void recorrerLista(tLista *lista, Accion accion, void *contexto);
int desenlazarNodoPorClave(tLista *lista, tNodo **destNodo, const void *clave, int (*comparar)(const void*, const void*));
int enlazarNodoOrdenado(tLista *lista, tNodo *nodo, int (*comparar)(const void*, const void*));
void mostrarLista(const tLista *lista, Mostrar mostrar);
void recorrerLista(void **pl, Accion accion,void* estado);

#endif // LISTA_SIMPLE_ENLACE_H
