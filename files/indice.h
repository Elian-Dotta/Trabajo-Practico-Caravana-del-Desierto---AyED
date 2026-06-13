#ifndef INDICE_H_
#define INDICE_H_

#include <stdio.h>
#include <stdlib.h>
#include "arbol.h"

typedef struct
{
    char     nombre[31];
    unsigned indiceRegistro;
} tIndiceNombre;     // clave de busqueda: nombre ; valor: indice de registro en jugadores

typedef struct
{
    char     nickname[11];
    unsigned indiceRegistro;
} tIndiceNickname;   // clave de busqueda: nickname (unico) ; valor: indice de registro

// Construye una entrada de indice a partir de un registro de jugador + su nro de registro.
typedef void (*Asignacion)(void *, const void *, unsigned long);

// --- Asignaciones (regJugador -> entrada de indice) ---
void asigJugNombre(void *idx, const void *reg, unsigned long nroReg);
void asigJugNick(void *idx, const void *reg, unsigned long nroReg);

// --- Comparadores ---
int cmpClaveNombre(const void *a, const void *b);     // (nombre, nroReg): inserta y permite homonimos
int cmpSoloNombre(const void *a, const void *b);       // solo nombre: para buscar existencia por nombre
int cmpClaveNickname(const void *a, const void *b);    // nickname (unico)

// --- Operaciones ---
// Recorre el archivo de jugadores, arma cada entrada con 'asig' y la inserta en el arbol con 'cmp'.
int indexarArchivoJugadores(const char *pathJugadores, tArbolBinBusq *p,
                            void *aux, unsigned tamAux,
                            void *indice, unsigned tamIdx,
                            Asignacion asig, Cmp cmp);

// Guarda el arbol al archivo de indice con recorrido in-order (queda ORDENADO).
int guardarArchivoIndice(tArbolBinBusq *pa, const char *pathIndice, unsigned tamIdx);

// Carga el indice (archivo ordenado) reconstruyendo un arbol balanceado.
int cargarIndiceDesdeArchivo(tArbolBinBusq *pa, const char *pathIndice,
                             void *indice, unsigned tamIdx);

// 'aux' entra con la clave cargada (un registro con el campo clave puesto) y, si encuentra,
// sale pisado con el registro hallado. Devuelve 1 si encontro, 0 si no.
int buscarEnArchivoConIndice(FILE *fp, const tArbolBinBusq *pa,
                             void *aux, unsigned tamAux,
                             void *indice, unsigned tamIdx,
                             Asignacion asig, Cmp cmp);

#endif // INDICE_H_
