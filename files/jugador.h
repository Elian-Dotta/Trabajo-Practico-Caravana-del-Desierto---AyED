#ifndef JUGADOR_H_
#define JUGADOR_H_

#include "cola.h"
#include "movimiento.h"

typedef struct sJugador
{
    unsigned vida,
             puntaje,
             cantMov;
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

void guardarMovimientoJugador(tJugador *j, tMovimiento* mov);
void mostrarMovimientosJugador(tJugador *j);

#endif // JUGADOR_H_
