#ifndef INDICE_H_
#define INDICE_H_

#include "arbol.h"

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

int indexarArchivoJugadores(const char *nombreArchivoJugadores, tArbolBinBusq *p, void *aux, unsigned tamDatoAux, void *indice, unsigned tamDatoIndice, Asignacion asig, Cmp cmp));
int guardarArchivoIndice(tArbolBinBusq *pa, const char* nombreArchivoIndice);
int cargarIndiceDesdeArchivo(tArbolBinBusq *pa, const char* nombreArchivoIndice, void *indice, unsigned tamDatoIdx);
// LE LLEGA EL ARCHIVO INDEXADO, LE LLEGA EL INDICE, LLEGA LA VARIABLE CON LA CLAVE A BUSCAR CARGADA
int buscarEnArchivoConIndice(FILE *fp, const tArbolBinBusq *pa, void *aux, unsigned tamDatoAux, void *indice, unsigned tamDatoIdx, Asignacion asig, Cmp cmp);

// ENTRA NUEVA PERSONA.
// LO DAMOS DE ALTA, VOLVEMOS A CREAR LOS INDICE, GUARDAMOS EN ARCHIVO

#endif // INDICE_H_

