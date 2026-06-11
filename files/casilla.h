#ifndef CASILLA_H_
#define CASILLA_H_

// SE ENCARGA DE CREAR, MODIFICAR, MOSTRAR Y DESTRUIR LAS CASILLAS DEL TABLERO DE JUEGO
// A CASILLA.H LE LLEGAN LOS PUNTEROS A LISTA QUE REPRESENTAN CADA CASILLA

#include "estado.h"
#include "lista_simple_enlace.h"

#define INICIO 'I'
#define JUGADOR 'J'
#define SALIDA 'S'
#define BANDIDO 'B'
#define TORMENTA 'T'
#define PREMIO 'P'
#define OASIS 'O'
#define VIDAEXTRA 'V'

#define JUGADORID 1

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

// FUNCIONES DE INSERCION EN CASILLA
int insertarEnCasilla(void **pl, unsigned *tamLista, void *d, unsigned tamDato); // DEVUELVE 1 SI AÑADIO EL DATO, DEVUELVE 0 SI NO LO ENCONTRO
int eliminarDeCasilla(void **pl, unsigned *tamLista, void *d, unsigned tamDato); // DEVUELVE 1 SI ELIMINO EL DATO, DEVUELVE 0 SI NO LO ENCONTRO
int insertarSinDupCasilla(void **pl, unsigned *tamLista, void *d, unsigned tamDato);

// FUNCIONES DE MOFICACION DE ELEMENTOS EN CASILLA
int insertarIzqDeElemento(void **pl, unsigned *tamLista, void *d, unsigned tamDato);
int insertarDerDeElemento(void **pl, unsigned *tamLista, void *d, unsigned tamDato);
int cambiarTipoElemento(void **pl, unsigned *tamLista, void *d, unsigned tamDato);

void mostrarCasilla(void *pl);
void mostrarElemento(const void *elemVoid);
void asignarNroCasilla(void *a, void *contexto);
void asignarNroCasElem(void *a, void *contexto);

int  cmpRestriccionCasilla(const void *a, const void *b);
int  cmpCasIdElem(const void *a, const void *b)
int  cmpCasTipoElem(const void *a, const void *b);
int  cmpIdElem(const void *a, const void *b);
int  cmpTipoElem(const void *a, const void *b);


void mostrarCasilla(void *pl);
void mostrarElemento(const void *elemVoid);
void recorrerLista(void **pl, ModificarEstado modEstado,tEstado* estado);

void cambiarEstado(void **pl, tEstado* estado);
void modEstado(tEstado* estado, const tElem* casilla);

#endif // CASILLA_H_
