// === Casilla: elementos dentro de una posicion ===
#ifndef CASILLA_H_
#define CASILLA_H_

// SE ENCARGA DE CREAR, MODIFICAR, MOSTRAR Y DESTRUIR LAS CASILLAS DEL TABLERO DE JUEGO
// A CASILLA.H LE LLEGAN LOS PUNTEROS A LISTA QUE REPRESENTAN CADA CASILLA

#include <string.h>
#include <stdlib.h>
#include <ctype.h>
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

#define TAM_BUFFER 30

typedef tLista tCasilla;

// Elemento del tablero (tipo, id, casilla)
typedef struct
{
    int  id_elem;
    char tipo_elem;
    int  nro_casilla;
}tElem; // Se pasa aca la definicion para corregir la inclusion circular.



tCasilla crearCasilla();

// FUNCIONES DE INSERCION EN CASILLA
int insertarEnCasilla(void **pl, unsigned *tamLista, void *d, unsigned tamDato); // DEVUELVE 1 SI ANIADIO EL DATO, DEVUELVE 0 SI NO LO ENCONTRO

int eliminarDeCasilla(void **pl, unsigned *tamLista, void *d, unsigned tamDato); // DEVUELVE 1 SI ELIMINO EL DATO, DEVUELVE 0 SI NO LO ENCONTRO
int insertarSinDupCasilla(void **pl, unsigned *tamLista, void *d, unsigned tamDato); // INSERCION PARA LA GENERACION

// FUNCIONES DE MOFICACION DE ELEMENTOS EN CASILLA
int insertarIzqDeElemento(void **pl, unsigned *tamLista, void *d, unsigned tamDato);
int insertarDerDeElemento(void **pl, unsigned *tamLista, void *d, unsigned tamDato);
int cambiarTipoElemento(void **pl, unsigned *tamLista, void *d, unsigned tamDato);
int cambiarTipo(void **pl, unsigned *tamLista, void *d, unsigned tamDato);
int eliminarDeCasillaTipo(void **pl, unsigned *tamLista, void *d, unsigned tamDato);

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

int prioridadElem(char tipo);

void cambiarEstado(void *pl, void* estado);
void modEstado(void* estado, void* casilla);

void calcularMovBandido(void *pl, void* contexto);
void buscarYCalcularBandido(void *e, void *contexto);

void distanciasEntreElementos(int posElem1, int posElem2, int cantCasillas, int* der, int* izq);
int compararIDtElem(const void *voidE1, const void *voidE2);
int compararTipotElem(const void *voidE1, const void *voidE2);
int elementoEnCasilla(const void *voidCasilla, const void* voidIDElemento);
int devolverMenorDistanciaEntreElementos(int posElem1, int posElem2, int cantidadCasillas, int dado);

void acumularTipoElem(void *elemVoid, void *bufVoid);
void escribirCasillaArchivo(void *casillaVoid, void *archVoid);

void destruirCasilla(void **pl, void* contexto);

#endif // CASILLA_H_
