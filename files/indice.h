#ifndef INDICE_H_
#define INDICE_H_

#include "arbol.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    char     nombre[31];
    unsigned indiceRegistro;
} tIndiceNombre;     // TIPO DEL INDICE (clave: nombre, valor: indice de registro en jugadores)

typedef struct
{
    char nickname[11];
    unsigned indiceRegistro;
} tIndiceNickname;

typedef void (*Asignacion)(void *, const void *, unsigned long);
// EN LA BUSQUEDA NO NECESITA EL NUMERO DE REGISTRO PERO PARA LA IDEXACION SI.
// PARA UTILIZAR LA MISMA FUNCION EN BUSQUEDA QUE EN INDICE SE PUEDE ASIGNAR TAMBIEN EL REGISTRO
// YA QUE EN LA BUSQUEDA SE PISA EL DATO CON EL QUE DEVUELVA EL ARBOL, PARA QUE LA VARIABLE ESTE INICIADA AL USAR LA ASIGNACION MANDAR UN 0 DESDE LA BUSQUEDA.

int indexarArchivoJugadores(const char *nombreArchivoJugadores, tArbolBinBusq *p, void *aux, unsigned tamDatoAux, void *indice, unsigned tamDatoIndice, Asignacion asig, Cmp cmp);
int guardarArchivoIndice(tArbolBinBusq *pa, const char* nombreArchivoIndice);
int cargarIndiceDesdeArchivo(tArbolBinBusq *pa, const char* nombreArchivoIndice, void *indice, unsigned tamDatoIdx);
// LE LLEGA EL ARCHIVO INDEXADO, LE LLEGA EL INDICE, LLEGA LA VARIABLE CON LA CLAVE A BUSCAR CARGADA
int buscarEnArchivoConIndice(FILE *fp, const tArbolBinBusq *pa, void *aux, unsigned tamDatoAux, void *indice, unsigned tamDatoIdx, Asignacion asig, Cmp cmp); // MANDAR UN CERO A LA ASIGNACION

void generarIndice(char* nombre, unsigned pos,tNodoArbol* arbolindice, FILE* fIndex);
int cmpInd (const void* ind1, const void* ind2);
// ENTRA NUEVA PERSONA.
// LO DAMOS DE ALTA, VOLVEMOS A CREAR LOS INDICE, GUARDAMOS EN ARCHIVO

#endif // INDICE_H_

