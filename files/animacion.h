#ifndef ANIMACION_H_
#define ANIMACION_H_

// MODULO PARA LA DEFINICION DE LAS ANIMACIONES DE CAMBIO DE ESTADO DEL JUEGO

#include "tablero.h"
#include "jugador.h"
#include "estado.h"
#include "consola.h"
#include "log.h"

#define IZQ -1
#define DER 1

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
#define FLECHAIZQ '>'
#define FLECHADER '<'
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

#define INSIZQ(REF, NUE) insertarAlLadoDeElemento(tablero, IZQ, (REF), (NUE))
#define INSDER(REF, NUE) insertarAlLadoDeElemento(tablero, DER, (REF), (NUE))
#define CAMELEM(ACT, NUE) cambiarElemento(tablero, (ACT), (NUE))
#define ELIM(ELIM) eliminarElemento(tablero, (ELIM))


typedef int (*Animacion)(tTablero*, unsigned);


int animPremio           (tTablero *tablero, unsigned frame); // [ PJ ]-> [ *P*J ]-> [***J ]-> [ **J ]-> [ *j ]-> [ J ]
int animOasisObtenido    (tTablero *tablero, unsigned frame); // [OJ] -> [!O!J] -> [!O!(J)] -> [!O!J] -> [!O!(J)]-> [!O!J] -> [O(J)]
int animTorSeActiva      (tTablero *tablero, unsigned frame);
int animTorFinaliza      (tTablero *tablero, unsigned frame);
int animVidaExtra        (tTablero *tablero, unsigned frame);
int animOasisPerdido     (tTablero *tablero, unsigned frame);
int animBandidoAtaca     (tTablero *tablero, unsigned frame);
int animJugadorDaniado   (tTablero *tablero, unsigned frame);
int animBandidoDesaparece(tTablero *tablero, unsigned frame);
int animJugGana          (tTablero *tablero, unsigned frame);

void ejecutarAnimacion (tTablero *t, tJugador *j, tEstado *e, tLog *l, unsigned frame, Animacion anim);


#endif // ANIMACION_H_
