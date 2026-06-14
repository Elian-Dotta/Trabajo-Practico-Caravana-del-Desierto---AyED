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
int insertarSinDupCasilla(void **pl, unsigned *tamLista, void *d, unsigned tamDato); // INSERCION PARA LA GENERACION

// FUNCIONES DE MOFICACION DE ELEMENTOS EN CASILLA
int insertarIzqDeElemento(void **pl, unsigned *tamLista, void *d, unsigned tamDato);
int insertarDerDeElemento(void **pl, unsigned *tamLista, void *d, unsigned tamDato);
int cambiarTipo(void **pl, unsigned *tamLista, void *d, unsigned tamDato);

// FUNCIONES PARA MOSTRAR ELEMENTOS
void mostrarCasilla(const void *pl);
void mostrarElemento(const void *elemVoid);

// FUNCIONES DE ASIGNACION DE NUMERO
void asignarNroCasilla(void *a, void *contexto);
void asignarNroCasElem(void *a, void *contexto);

int  cmpRestriccionCasilla(const void *a, const void *b);
int  cmpCasIdElem(const void *a, const void *b);
int  cmpCasTipoElem(const void *a, const void *b);
int  cmpIdElem(const void *a, const void *b);
int  cmpTipoElem(const void *a, const void *b);
int  cmpCasTipos(const void *a, const void *b);

int cambiarEstado(void **pl, void* estado);
void modEstado(void* estado, void* casilla);

void distanciasEntreElementos(int posElem1, int posElem2, int cantCasillas, int *der, int *izq);

void destruirCasilla(void **pl, void* contexto);

#endif // CASILLA_H_
