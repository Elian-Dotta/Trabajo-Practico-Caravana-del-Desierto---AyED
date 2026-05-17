#ifndef PARTIDA_H_
#define PARTIDA_H_

#include "tablero.h"
#include "config.h"

typedef struct
{
    int Oobtenido,
        Operdido,
        Bdesaparece,
        Jpierde,
        JganaVida,
        JpierdeVida;
}tEstado;

typedef struct tLista tLista;

int  jugarPartida();// VA A INICIALIZAR Y LUEGO VA A MANEJAR EL LOOP

int  inicializarPartida(tListaDE *tablero, tJugador *jugador, tCola *movimientos); // VA A CARGAR TCONFIG Y GENERAR EL TABLERO

int  dibujarEstadoDelJuego(tListaDE *tablero, tJugador *jugador);

int  procesarEntrada(tCola *movimientos, tJugador *jugador);   // Pide un ENTER para tirar el dado por menu
                                                               // Pide la direccion por medio de la funcion de menu -> Nada mas dice: "Ingrese direccion (Adelante - 'F' o Atras 'B'): ",
                                                               // el resto del HUD se encarga la funcion anterior
// Funcion para calcular movimientos de bandidos
int  calcularMovBandido(tListaDE *tablero, tCola *movimientos); // Se puede usar verPrimero para los bandidos inteligentes y calcular en base al mov del jugador

//Funcion para animar el movimiento del jugador y los bandidos, consume la informacion guardada en la cola de movimientos
int  dibujarAnimacionMov(tListaDE *tablero, tJugador *jugador, tCola *movimientos); // debe dibujar el HUD al mismo tiempo por eso necesita tJugador

int  actualizarEstado(tListaDE *tablero, tJugador *jugador, tEstado *estado);

int  dibujarAnimacionEstado(tListaDE *tablero, tJugador *jugador, tEstado *estado);

int  finalizarPartida(); // GUARDA EL RANKING ->

#endif // PARTIDA_H_
