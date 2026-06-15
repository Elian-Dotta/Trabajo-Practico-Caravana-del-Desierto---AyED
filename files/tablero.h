#ifndef TABLERO_H_
#define TABLERO_H_

// SE ENCARGA DE CREAR, MODIFICAR, MOSTRAR Y DESTRUIR EL TABLERO DE JUEGO

#include <stdlib.h>
#include <time.h>
#include <stdlib.h>
#include <time.h>

#include "casilla.h"
#include "estado.h"
#include "config.h"
#include "lista_doble_enlace_circular.h"
#include "lista_simple_enlace.h"
#include "cola.h"

#define MSJ_LISTA_MAPA_VACIO "EL TABLERO NO FUE GENERADO"
#define TAM_BUFFER 30

#ifndef IZQ
#define IZQ -1
#endif
#ifndef DER
#define DER 1
#endif

int compararEnteros(const void *a, const void *b);

typedef tListaDE tTablero;

// FUNCIONES DE GENERACION
int  crearTablero(tTablero* tablero, tConfig config, tLista *bandidosInteligentes);

int  generarTablero(tTablero* tablero, int *contElem, int cantPos);
int  distribuirElementos(tTablero* tablero, int *contElem, tConfig config, tLista *bandidosInteligentes);

// FUNCION PARA MOVER ELEMENTOS
int  moverElementoPorId(tTablero* tablero, int id, int mov);

int  obtenerIdElementoPorTipo(tTablero* tablero, char tipoElem);
void posicionarTablero(tTablero* tablero, int idElem);

// FUNCIONES PARA ANIMACION DE ESTADO
int  insertarAlLadoDeElemento(tTablero *tablero, int direccion, char elemRef, char elemNue);
int  cambiarElemento(tTablero *tablero, char elemAct, char elemNue);
int  eliminarElemento(tTablero *tablero, char elemAct);

// FUNCIONES DE ACTUALIZACION
void obtenerMovimientoBandidos(tTablero *tablero, tCola *movimientos, tLista *bandInteligentes, int posJug, int cantPos);
void actualizarEstadoDelJugador(tTablero* tablero, tEstado *estado, tLista *bandinteligentes);

// FUNCION DE PREGUNTA
int  elementosJuntos(tTablero *tablero, const char tipo1, const char tipo2);


void mostrarTablero(tTablero* tablero);
int  cmpInt(const void *a, const void *b);

void destruirTablero(tTablero *tablero);

//int  compararEnteros(const void *a, const void *b);
//tTablero posicionarTablero(tTablero* tablero, int idElemPosicion);

void convertirMapaACadena(tTablero *tablero, char *buffer, unsigned orientacion, unsigned indice);
//void mostrarMapa(const tListaDE *lista, void(*mostrar)(const void *));
//int borrarMapa(tListaDE *lista);

//int  agregarElemento();

#endif // TABLERO_H_
