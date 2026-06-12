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

void crearArbolBinBusq(tArbolBinBusq *p);

int  insertarArbolBinBusq(tArbolBinBusq *p, const void *d, unsigned tam,
                          int (*cmp)(const void *, const void *));

void recorrerEnOrdenSimpleArbolBinBusq(const tArbolBinBusq *p, void *params,
                          void (*accion)(void *, unsigned, void *));

int  cargarArchivoBinOrdenadoArbolBinBusq(tArbolBinBusq *p, const char *path,
                          unsigned tamInfo);

#endif // ARBOL_H_
