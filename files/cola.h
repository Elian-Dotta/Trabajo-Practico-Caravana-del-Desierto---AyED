#ifndef COLA_H_
#define COLA_H_

#include "nodos.h"

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
int  colaLlena(const tCola *c, void *d, unsigned tamDato);
void vaciarCola(tCola *c);

#endif // COLA_H_
