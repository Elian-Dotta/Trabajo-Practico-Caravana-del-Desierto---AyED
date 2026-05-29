#ifndef CASILLA_H_
#define CASILLA_H_

// SE ENCARGA DE CREAR, MODIFICAR, MOSTRAR Y DESTRUIR LAS CASILLAS DEL TABLERO DE JUEGO
// A CASILLA.H LE LLEGAN LOS PUNTEROS A LISTA QUE REPRESENTAN CADA CASILLA


#include "lista_simple_enlace.h"

typedef tLista tCasilla;

typedef struct
{
    int  id_elem;
    char tipo_elem;
    int  nro_casilla;
}tElem; // Se pasa aca la definicion para corregir la inclusion circular.

tCasilla crearCasilla();
int insertarEnCasilla(void **pl, unsigned *tamLista, void *d, unsigned tamDato); // DEVUELVE 1 SI A�ADIO EL DATO, DEVUELVE 0 SI NO LO ENCONTRO
int eliminarDeCasilla(void **pl, unsigned *tamLista, void *d, unsigned tamDato); // DEVUELVE 1 SI ELIMINO EL DATO, DEVUELVE 0 SI NO LO ENCONTRO

void mostrarCasilla(const void *pl);
void mostrarElemento(const void *elemVoid);

void distanciasEntreElementos(int posElem1, int posElem2, int cantCasillas, int *der, int *izq);

#endif // CASILLA_H_
