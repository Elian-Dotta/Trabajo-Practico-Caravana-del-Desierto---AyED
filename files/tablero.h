#ifndef TABLERO_H_
#define TABLERO_H_

#include <stdlib.h>
#include <time.h>

typedef struct
{
    int  id_elem;
    char tipo_elem;
}tElem;

typedef struct tLista tLista;
typedef struct tConfig tConfig;

int  crearTablero(tLista* tablero, tConfig config);
int  generarTablero(tLista* tablero, int *contElem, int cantPos);
int  distribuirElementos(tLista* tablero, int *contElem, tConfig config);
void mostrarTablero(tLista* tablero); // muestra la lista
void mostrarTablero2(); //-> metodo
int  cmpInt(void *a, void *b);

#endif // TABLERO_H_
