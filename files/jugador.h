#ifndef JUGADOR_H_
#define JUGADOR_H_

#include <string.h>

#include "cola.h"
#include "movimiento.h"
#include "menu.h"

#define TAM 128
#define MAX_MOV_LINEA

typedef struct sJugador
{
    unsigned vida,
             puntaje,
             cantMov,
             posJug;
    char     nombre[31],
             nickname[11];
    tCola    hisMovJugador;
}tJugador;


void inicializarJugador(tJugador* j, unsigned vida);
void aumentarVida(tJugador* j);
void disminuirVida(tJugador* j);
unsigned verVida(const tJugador* j);

void aumentarPuntaje(tJugador *j);
unsigned verPuntaje(const tJugador *j);

void aumentarMovimiento(tJugador *j);
unsigned verMovimiento(const tJugador *j);

void modificarPosJug(tJugador *j, int pos);
unsigned verPosJugador(const tJugador *j);

void guardarNombreYNick(tJugador *j, const char *nombre, const char* nick);
const char* verNombre(const tJugador *j);
const char* verNick(const tJugador *j);

void guardarMovimientoJugador(tJugador *j, tMovimiento* mov);
void mostrarMovimientosJugador(tJugador *j);

int pedirNombreYMostrarHomonimos(tArbolBinBusq *arbolIdxNombre, const char *archJug, regJugador *sel, char *nombreOut);
int pedirYRegistrarNickname(const char *nombre, tArbolBinBusq *arbolIdxNombre, tArbolBinBusq *arbolIdxNick, const char *archJug, const char *archIdxNombre, const char *archIdxNick, char *nicknameDest);
void ingresarJugador(tJugador *jugador);


#endif // JUGADOR_H_
