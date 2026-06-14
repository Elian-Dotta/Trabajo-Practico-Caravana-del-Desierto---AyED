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

typedef tListaDE tTablero;

int  crearTablero(tTablero* tablero, tConfig config, tLista *bandidosInteligentes);

int  generarTablero(tTablero* tablero, int *contElem, int cantPos);
int  distribuirElementos(tTablero* tablero, int *contElem, tConfig config, tLista *bandidosInteligentes);

int  moverElementoPorId(tTablero* tablero, int id, int mov);
int  obtenerIdElementoPorTipo(tTablero* tablero, char tipoElem);
void posicionarTablero(tTablero* tablero, int idElem);

int  insertarAlLadoDeElemento(tTablero *tablero, int direccion, char elemRef, char elemNue);
int  cambiarElemento(tTablero *tablero, char elemAct, char elemNue);
int  eliminarElemento(tTablero *tablero, char elemAct);

int  generarMovBandido(tTablero* tablero, tCola *mov);
void actualizarEstadoDelJugador(tTablero* tablero, tEstado *estado, tLista *bandinteligentes);
//void actualizarEstadoDelJugador(tTablero* tablero, int posJug, tEstado *estado);

int  elementosJuntos(tTablero *tablero, const char tipo1, const char tipo2);

void mostrarTablero(tTablero* tablero); // muestra la lista
int  cmpInt(const void *a, const void *b);

void destruirTablero(tTablero *tablero);

//void mostrarMapa(const tListaDE *lista, void(*mostrar)(const void *));
//int borrarMapa(tListaDE *lista);

//int  agregarElemento();

#endif // TABLERO_H_
