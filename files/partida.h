// === Partida: coordina el loop del juego ===
#ifndef PARTIDA_H_
#define PARTIDA_H_

// ENGLOBA LOS MODULOS PARA EL FUNCIONAMIENTO DE LA PARTIDA
#include <stdlib.h>

#include "tablero.h"
#include "cola.h"
#include "movimiento.h"
#include "config.h"
#include "jugador.h"
#include "estado.h"
#include "consola.h"
#include "animacion.h"
#include "timer.h"


#define PASO 1


#define MSJ_PUNTOS              "El jugador ha obtenido un premio\n"
#define MSJ_VIDA                "El jugador ha obtenido una vida extra\n"
#define MSJ_OASISOBTENIDO       "El jugador ha conseguido la proteccion del Oasis\n"
#define MSJ_OASISPERDIDO        "El jugador ha perdido la proteccion del Oasis\n"
#define MSJ_TORMENTAACTIVA      "El jugador ha sido aturdido por una Tormenta de Arena\n"
#define MSJ_TORMENTAFINALIZADA  "El jugador se ha recuperado de la Tormenta de Arena\n"
#define MSJ_BANDIDOATACA        "Un bandido ataco al jugador\n"
#define MSJ_JUGADORDANIADO      "El jugador ha perdido una vida\n"
#define MSJ_BANDIDODESAPARECE   "Un bandido ha desaparecido\n"
#define MSJ_JUGADORGANA         "FELICITACIONES, GANASTE LA PARTIDA"
#define MSJ_JUGADORPIERDE       "El jugador ha perdido la partida"

// Estado completo de una partida
typedef struct
{
    tTablero tablero;
    tJugador jugador;
    tCola    movimientos;
    tEstado  estado;
    tLista   bandInteligentes; // LISTA DE ENTEROS, IDS
    tLog     log;
    tConfig  config;
    int      corriendo;
}tPartida;

void jugarPartida(tJugador* jugador);// VA A INICIALIZAR Y LUEGO VA A MANEJAR EL LOOP

int  inicializarPartida(tPartida *partida, tJugador* jugador); // VA A CARGAR TCONFIG Y GENERAR EL TABLERO

int  dibujarEstadoDelJuego(tPartida *partida);

int  procesarEntrada(tPartida *partida);

int  actualizarMovimientos(tPartida *partida);


int  dibujarAnimacionMov(tPartida *partida);  //Funcion para animar el movimiento del jugador y los bandidos, consume la informacion guardada en la cola de movimientos

int  actualizarEstado(tPartida *partida);

int  dibujarAnimacionEstado(tPartida *partida);

int  finalizarPartida(tPartida *partida);

#endif // PARTIDA_H_
