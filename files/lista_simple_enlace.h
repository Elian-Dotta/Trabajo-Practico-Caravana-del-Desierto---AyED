#ifndef LISTA_SIMPLE_ENLACE_H
#define LISTA_SIMPLE_ENLACE_H

#include <stdio.h>
#include <string.h> // Para funciones MEM
#include <stdlib.h> // Para uso de memoria dinamica y null
#include "nodos.h"

typedef tNodo* tLista; // La lista sera un puntero a Nodo. Es decir, la lista
// tendrá la dirección de memoria de un nodo, no datos. Así ocupara solo 8 Bytes (tam de puntero).

typedef void (*Mostrar) (const void*);
typedef int (*tCompararFn)(const void*, const void*);
typedef int (*Acumular) (void **, unsigned *, void *, unsigned);
typedef int  (*Cmp)(const void *, const void *);
//typedef void  (*Accion)(const void *, const void *);

void crearLista(tLista *lista);
int listaVacia(const tLista *lista);
int listaLlena(const tLista *lista, unsigned tamDato); //No se requiere el dato en principio, ver si borrar

int vaciarLista(tLista *lista);
int ponerAlFinal(tLista *lista, const void *dato, unsigned tamDato);


int insertarOrdenado(tLista *lista, const void *dato, unsigned tamDato, tCompararFn comparar, int conDup, Acumular acum);
int sacarPrimeroLista(tLista *lista, void *dest, unsigned tamDest);
int sacarUltimoLista(tLista *lista, void *dest, unsigned tamDest);

int insertarAlFinal(tLista *lista, const void *d, unsigned tamDato);
int eliminarPorClave(tLista *lista, void *d, unsigned tamDato, Cmp cmp);

//Definidas:
void mapLista(const tLista *lista, void (*accion)(const void *));

void mostrarLista(const tLista *lista, Mostrar mostrar);

#endif // LISTA_SIMPLE_ENLACE_H
