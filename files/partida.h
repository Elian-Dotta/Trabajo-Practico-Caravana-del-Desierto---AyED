#ifndef PARTIDA_H_
#define PARTIDA_H_

#include "tablero.h"
#include "config.h"

typedef struct tLista tLista;

int  jugarPartida();// VA A INICIALIZAR Y LUEGO VA A MANEJAR EL LOOP

int  inicializarPartida(); // VA A CARGAR TCONFIG Y GENERAR EL TABLERO

int  procesarEntrada(); // DETECTA MOVIMIENTO DEL JUGADOR -> Lucas, Devuelve la decision del jugador

int  actualizarPartida(); // Encola movimiento del jugador y los bandidos, actualiza al jugador en base a lo que tenga la casilla con el jugador.

int  renderizarPartida(); // DIBUJA EL TABLERO -> Mostrar tablero -> Lucas

int  finalizarPartida(); // GUARDA EL RANKING ->

#endif // PARTIDA_H_
