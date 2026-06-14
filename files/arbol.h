#ifndef ARBOL_H_
#define ARBOL_H_

#include <stdlib.h>
#include <string.h>
#include "nodos.h"

typedef tNodoArbol* tArbolBinBusq;

// Resultados
#define TODO_BIEN        0
#define SIN_MEM          1
#define CLA_DUP          2
#define SIN_INICIALIZAR  3
#define ERROR_ARCH       4

typedef int (*Cmp)(const void *, const void *);

#ifndef MINIMO
#define MINIMO(x,y) ((x) < (y) ? (x) : (y))
#endif

void crearArbolBinBusq(tArbolBinBusq *p);

int  insertarArbolBinBusq(tArbolBinBusq *p, const void *d, unsigned tam,
                          Cmp cmp);

void recorrerEnOrdenSimpleArbolBinBusq(const tArbolBinBusq *p, void *params,
                          void (*accion)(void *, void *));

int  cargarArchivoBinOrdenadoArbolBinBusq(tArbolBinBusq *p, const char *path,
                          unsigned tamInfo);

// Busca por clave. Devuelve 1 si la encontro (y copia el dato del nodo en d), 0 si no.
// 'd' entra con la clave cargada y sale pisado con el registro hallado.
int  buscarElemArbolBinBusq(const tArbolBinBusq *p, void *d, unsigned tam, Cmp cmp);

#endif // ARBOL_H_
