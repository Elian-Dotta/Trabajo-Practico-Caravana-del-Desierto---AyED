#ifndef CASILLA_H_
#define CASILLA_H_

// SE ENCARGA DE CREAR, MODIFICAR, MOSTRAR Y DESTRUIR LAS CASILLAS DEL TABLERO DE JUEGO
// A CASILLA.H LE LLEGAN LOS PUNTEROS A LISTA QUE REPRESENTAN CADA CASILLA

#include "estado.h"
#include "lista_simple_enlace.h"

typedef tLista tCasilla;


typedef struct
{
    int  id_elem;
    char tipo_elem;
    int  nro_casilla;
}tElem; // Se pasa aca la definicion para corregir la inclusion circular.

typedef void (*ModificarEstado) (tEstado*,const tElem*);

/* // LA CASILLA NO DEBE CONOCER EL TABLERO
int crearCasillas(tListaDE *lista, unsigned cantCasillas);
int borrarListasElementosCasillas(tListaDE *lista);
int borrarCasillas(tListaDE *lista);
int insertarElementoCasilla(tListaDE *lista, const tElem *elem, unsigned casilla);
*/

tCasilla crearCasilla();
int insertarEnCasilla(void **pl, unsigned *tamLista, void *d, unsigned tamDato); // DEVUELVE 1 SI AÑADIO EL DATO, DEVUELVE 0 SI NO LO ENCONTRO
int eliminarDeCasilla(void **pl, unsigned *tamLista, void *d, unsigned tamDato, Cmp cmp); // DEVUELVE 1 SI ELIMINO EL DATO, DEVUELVE 0 SI NO LO ENCONTRO

void mostrarCasilla(void *pl);
void mostrarElemento(const void *elemVoid);
int recorrerLista(void **pl, ModificarEstado modEstado,tEstado* estado);

void cambiarEstado(void **pl, tEstado* estado);
void modEstado(tEstado* estado, const tElem* casilla);

#endif // CASILLA_H_
