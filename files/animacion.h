/// @file animacion.h
///
/// @date 2024-06-01

#ifndef ANIMACION_H_
#define ANIMACION_H_

// MODULO PARA LA DEFINICION DE LAS ANIMACIONES DE CAMBIO DE ESTADO DEL JUEGO

#include "tablero.h"
#include "jugador.h"
#include "estado.h"
#include "consola.h"
#include "log.h"
#include "timer.h"

#define IZQ -1
#define DER 1

/// DEFINICION DE LOS ELEMENTOS DE ANIMACION DEL TABLERO
#define ASTERISCO '*'
#define ARENA1 '.'
#define ARENA2 ':'
#define ARENA3 ';'
#define ARENA4 '#'
#define ATURDIDOIZQ '{'
#define ATURDIDODER '}'
#define PUNALIZQ '<'
#define PUNALDER '>'
#define MANGO '-'
#define FLECHAIZQ '|'
#define FLECHADER '/'
#define DESAPARECE '_'
#define OASISACTIVO '!'
#define ESCUDOIZQ '('
#define ESCUDODER ')'
#define ESCUDOCAIDO ','
#define JUGMINUS 'j'
#define BANMINUS 'b'

#define FRPREMIO 5
#define FROASISOB 6
#define FROASISPE 4
#define FRTORACT 10
#define FRTORFIN 2
#define FRVIDAEX 4
#define FRBANDAT 3
#define FRBANDES 3
#define FRJUGGANA 5 // NO ESTA IMPLEMENTADA
#define FRJUGCAS1 2
#define FRJUGPIERDE 3

#define INSIZQ(REF, NUE) insertarAlLadoDeElemento(tablero, IZQ, (REF), (NUE))
#define INSDER(REF, NUE) insertarAlLadoDeElemento(tablero, DER, (REF), (NUE))
#define CAMELEM(ACT, NUE) cambiarElemento(tablero, (ACT), (NUE))
#define ELIM(ELIM) eliminarElemento(tablero, (ELIM))

/// @brief Definicion del tipo Animacion, que es un puntero a funcion que recibe un tablero y un numero de frame, y no devuelve nada. Se utiliza para definir las animaciones de cambio de estado del juego.
typedef void (*Animacion)(tTablero*, unsigned);

// PROTOTIPOS DE LAS ANIMACIONES
void animPremio           (tTablero *tablero, unsigned frame); // [ PJ ]-> [ *P*J ]-> [***J ]-> [ **J ]-> [ *j ]-> [ J ]
void animOasisObtenido    (tTablero *tablero, unsigned frame); // [OJ] -> [!O!J] -> [!O!(J)] -> [!O!J] -> [!O!(J)]-> [!O!J] -> [O(J)]
void animTorSeActiva      (tTablero *tablero, unsigned frame);
void animTorFinaliza      (tTablero *tablero, unsigned frame);
void animVidaExtra        (tTablero *tablero, unsigned frame);
void animOasisPerdido     (tTablero *tablero, unsigned frame);
void animBandidoAtaca     (tTablero *tablero, unsigned frame);
void animJugadorDaniado   (tTablero *tablero, unsigned frame);
void animBandidoDesaparece(tTablero *tablero, unsigned frame);
void animJugGana          (tTablero *tablero, unsigned frame);
void animJugPierde        (tTablero *tablero, unsigned frame);


/// @brief Funcion que ejecuta una animacion de cambio de estado del juego, recibiendo el tablero, el jugador, el estado, el log, el numero de frame, la animacion a ejecutar y el ID del ancla para posicionar el tablero. La funcion se encarga de esperar un segundo entre cada frame, posicionar el tablero en el ancla, ejecutar la animacion y dibujar la escena con el tablero, el jugador, el estado y el log actualizados.
/// @param t
/// @param j
/// @param e
/// @param l
/// @param frame
/// @param anim
/// @param IDAncla
void ejecutarAnimacion (tTablero *t, tJugador *j, tEstado *e, tLog *l, unsigned frame, Animacion anim, unsigned IDAncla);


#endif // ANIMACION_H_
