#ifndef LISTA_SIMPLE_ENLACE_H
#define LISTA_SIMPLE_ENLACE_H

#include <stdio.h>
#include <string.h> // Para funciones MEM
#include <stdlib.h> // Para uso de memoria dinamica y null
#include "nodos.h"

typedef tNodo* tLista; // La lista sera un puntero a Nodo. Es decir, la lista
// tendr� la direcci�n de memoria de un nodo, no datos. As� ocupara solo 8 Bytes (tam de puntero).

typedef void (*Mostrar) (const void*);
typedef int (*tCompararFn)(const void*, const void*);
typedef int (*Acumular) (void **, unsigned *, void *, unsigned);

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
int eliminarPorClaveLista(tLista *lista, void *d, unsigned tamDato);

//Definidas:
void mapLista(const tLista *lista, void (*accion)(const void *));
int desenlazarNodoPorClave(tLista *lista, tNodo **destNodo, const void *clave, int (*comparar)(const void*, const void*));
int enlazarNodoOrdenado(tLista *lista, tNodo *nodo, int (*comparar)(const void*, const void*));
void mostrarLista(const tLista *lista, Mostrar mostrar);

#endif // LISTA_SIMPLE_ENLACE_H
