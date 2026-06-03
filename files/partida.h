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

#define PASO 1

//typedef struct tListaDe tLista;

int  jugarPartida();// VA A INICIALIZAR Y LUEGO VA A MANEJAR EL LOOP

int  inicializarPartida(tTablero *tablero, tJugador *jugador, tCola *movimientos, tEstado *estado); // VA A CARGAR TCONFIG Y GENERAR EL TABLERO

int  dibujarEstadoDelJuego(tTablero *tablero, tJugador *jugador, tEstado *estado);

int  procesarEntrada(tCola *movimientos, tJugador *jugador);   // Pide un ENTER para tirar el dado por menu
                                                               // Pide la direccion por medio de la funcion de menu -> Nada mas dice: "Ingrese direccion (Adelante - 'F' o Atras 'B'): ",
                                                               // el resto del HUD se encarga la funcion anterior

int  calcularMovBandido(tTablero *tablero, tLista *bandidosInteligentes, int posJugador, int cantCasillaTablero, tCola *movimientos);
// Se puede usar verPrimero para los bandidos inteligentes y calcular en base al mov del jugador
// Funcion para calcular movimientos de bandidos

int  dibujarAnimacionMov(tTablero *tablero, tJugador *jugador, tCola *movimientos, tEstado *estado); // debe dibujar el HUD al mismo tiempo por eso necesita tJugador
                                                                //Funcion para animar el movimiento del jugador y los bandidos, consume la informacion guardada en la cola de movimientos
int  actualizarEstado(tTablero *tablero, tJugador *jugador, tEstado *estado);

int  dibujarAnimacionEstado(tTablero *tablero, tJugador *jugador, tEstado *estado);

int  finalizarPartida(); // GUARDA EL RANKING ->

int  inicializarEstado(tEstado *est, int cantBandidos);

#endif // PARTIDA_H_
