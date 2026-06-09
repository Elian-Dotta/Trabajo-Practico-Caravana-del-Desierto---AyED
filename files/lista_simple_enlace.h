#ifndef LISTA_SIMPLE_ENLACE_H
#define LISTA_SIMPLE_ENLACE_H

#include <stdio.h>
#include <string.h> // Para funciones MEM
#include <stdlib.h> // Para uso de memoria dinamica y null
#include "nodos.h"

typedef tNodo* tLista; // La lista sera un puntero a Nodo. Es decir, la lista
// tendra la direccion de memoria de un nodo, no datos. Asi ocupara solo 8 Bytes (tam de puntero).

typedef int (*Cmp)(const void *, const void *);

void crearLista(tLista *p);
int  vaciarLista(tLista *p);
int  ponerAlFinal(tLista *p, const void *d, unsigned cantBytes);
int  sacarPrimeroLista(tLista *p, void *d, unsigned cantBytes);
int  mostrarLista(const tLista *p, void (*mostrar)(const void *, FILE *), FILE *fp);
int  eliminarPorClave(tLista *p, void *d, unsigned tamDato, Cmp cmp);

#endif // LISTA_SIMPLE_ENLACE_H
