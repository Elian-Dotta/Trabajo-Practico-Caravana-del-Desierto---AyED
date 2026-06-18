// === Cola: FIFO de movimientos ===
#ifndef COLA_H_
#define COLA_H_

#include <stdlib.h>
#include <string.h>
#include "nodos.h"


// Cola con puntero al primero y ultimo
typedef struct
{
    tNodo *pri,
          *ult;
}tCola;

void crearCola(tCola *c);
int  ponerEnCola(tCola *c, const void *d, unsigned tamDato);
int  sacarDeCola(tCola *c, void *d, unsigned tamDato);
int  verPrimero(const tCola *c, void *d, unsigned tamDato);
int  colaVacia(const tCola *c);
int  colaLlena(const tCola *c, unsigned tamDato);
void vaciarCola(tCola *c);

#endif // COLA_H_
