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


#define PASO 1

#define MSJ_PUNTOS              "El jugador ha obtenido un premio\n"
#define MSJ_VIDA                "El jugador ha obtenido una vida extra\n"
#define MSJ_OASISOBTENIDO       "El jugador ha conseguido la proteccion del Oasis\n"
#define MSJ_OASISPERDIDO        "El jugador ha perdido la proteccion del Oasis\n"
#define MSJ_TORMENTAACTIVA      "El jugador ha sido aturdido por una Tormenta de Arena"
#define MSJ_TORMENTAFINALIZADA  "El jugador se ha recuperado de la Tormenta de Arena"
#define MSJ_BANDIDOATACA        "Un bandido ataco al jugador\n"
#define MSJ_JUGADORDANIADO      "El jugador ha perdido una vida\n"
#define MSJ_BANDIDODESAPARECE   "Un bandido ha desaparecido\n"
#define MSJ_JUGADORGANA         "FELICITACIONES, GANASTE LA PARTIDA\n"
#define MSJ_JUGADORPIERDE       "El jugador ha perdido la partida\n"

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

int  jugarPartida();// VA A INICIALIZAR Y LUEGO VA A MANEJAR EL LOOP

int  inicializarPartida(tPartida *partida); // VA A CARGAR TCONFIG Y GENERAR EL TABLERO

int  dibujarEstadoDelJuego(tPartida *partida);

int  procesarEntrada(tPartida *partida);   // Pide un ENTER para tirar el dado por menu
                                                               // Pide la direccion por medio de la funcion de menu -> Nada mas dice: "Ingrese direccion (Adelante - 'F' o Atras 'B'): ",
                                                               // el resto del HUD se encarga la funcion anterior

int  actualizarMovimientos(tPartida *partida);
// SE CORRIGE DESPUES CONCIDERANDO QUE tPARTIDA TIENE LOS PARAMETROS NECESARIOS
// Se puede usar verPrimero para los bandidos inteligentes y calcular en base al mov del jugador
// Funcion para calcular movimientos de bandidos

int  dibujarAnimacionMov(tPartida *partida); // debe dibujar el HUD al mismo tiempo por eso necesita tJugador
                                                                //Funcion para animar el movimiento del jugador y los bandidos, consume la informacion guardada en la cola de movimientos
int  actualizarEstado(tPartida *partida);

int  dibujarAnimacionEstado(tPartida *partida);

int  finalizarPartida(tPartida *partida); // GUARDA EL RANKING ->

#endif // PARTIDA_H_
