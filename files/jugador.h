#ifndef JUGADOR_H_
#define JUGADOR_H_

#include "cola.h"
#include "movimiento.h"

typedef struct sJugador
{
    unsigned vida,
             puntaje,
             cantMov,
             posJug;
    tCola    hisMovJugador;
}tJugador;

typedef struct
{
    char nombre[31];
    char nickname[11];
} regJugador;

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

void guardarMovimientoJugador(tJugador *j, tMovimiento* mov);
void mostrarMovimientosJugador(tJugador *j);


#endif // JUGADOR_H_
