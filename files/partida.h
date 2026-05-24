#ifndef PARTIDA_H_
#define PARTIDA_H_

typedef struct tLista tLista;

<<<<<<< Updated upstream
//int  jugarPartida();// VA A INICIALIZAR Y LUEGO VA A MANEJAR EL LOOP

//int  inicializarPartida(); // VA A CARGAR TCONFIG Y GENERAR EL TABLERO
=======
#include "tablero.h"
#include "cola.h"
#include "movimiento.h"
#include "config.h"
#include "jugador.h"
#include "estado.h"
#include "consola.h"
#include "menu.h"

#define PASO 1
#define ID_JUGADOR 1

#define MENU_DIR    "\nIngrese direccion (F = Adelante / B = Atras): "
#define OPC_DIR     "FB"
#define MSJ_ERR_DIR "Direccion invalida. Use F (adelante) o B (atras).\n"
>>>>>>> Stashed changes

//int  procesarEntrada(); // DETECTA MOVIMIENTO DEL JUGADOR

//int  actualizarPartida(); // ACTUALIZA LOS BANDIDOS Y LOS PREMIOS, CHECKEA FIN DE PARTIDA

//int  renderizarPartida(); // DIBUJA EL TABLERO

<<<<<<< Updated upstream
//int  finalizarPartida(); // GUARDA EL RANKING
=======
void dibujarEstadoDelJuego(tListaDE *tablero, tJugador *jugador);

void procesarEntrada(tCola *movimientos, tJugador *jugador);   // Pide un ENTER para tirar el dado por menu
                                                               // Pide la direccion por medio de la funcion de menu -> Nada mas dice: "Ingrese direccion (Adelante - 'F' o Atras 'B'): ",
                                                               // el resto del HUD se encarga la funcion anterior

int  calcularMovBandido(tTablero *tablero, tCola *movimientos); // Se puede usar verPrimero para los bandidos inteligentes y calcular en base al mov del jugador
                                                                // Funcion para calcular movimientos de bandidos

int  dibujarAnimacionMov(tTablero *tablero, tJugador *jugador, tCola *movimientos, tEstado *estado); // debe dibujar el HUD al mismo tiempo por eso necesita tJugador
                                                                //Funcion para animar el movimiento del jugador y los bandidos, consume la informacion guardada en la cola de movimientos
int  actualizarEstado(tTablero *tablero, tJugador *jugador, tEstado *estado);

int  dibujarAnimacionEstado(tTablero *tablero, tJugador *jugador, tEstado *estado);

int  finalizarPartida(); // GUARDA EL RANKING ->

int  inicializarEstado(tEstado *est, int cantBandidos);
>>>>>>> Stashed changes

#endif // PARTIDA_H_
