// === Modulo animacion: secuencias de cambio de estado ===
#include "animacion.h"

/*
    COMO FUNCIONA ESTE MODULO
    -------------------------
    Cada animacion es una mini-pelicula que se dibuja "cuadro por cuadro"
    (frame por frame). El MOTOR es ejecutarAnimacion(): repite N cuadros,
    y en cada uno llama a la animacion concreta (animPremio, animVidaExtra...)
    que MODIFICA el tablero un poquito. Despues se repinta la pantalla.

    Para modificar el tablero, las animaciones usan 4 macros (ver animacion.h):
      INSIZQ(REF, NUE) -> inserta el caracter NUE a la IZQUIERDA del elemento REF
      INSDER(REF, NUE) -> inserta el caracter NUE a la DERECHA del elemento REF
      CAMELEM(ACT, NUE)-> cambia el elemento ACT por NUE (misma celda)
      ELIM(X)          -> elimina el elemento X

    Los caracteres (ASTERISCO '*', FLECHAIZQ '|', ESCUDOIZQ '(', JUGMINUS 'j',
    ARENA1 '.', etc.) estan definidos como #define en animacion.h y casilla.h.
*/


// Reproduce una animacion cuadro a cuadro.
//   frame   = cuantos cuadros dura la animacion (ej: FRVIDAEX = 4)
//   anim    = QUE animacion dibujar (puntero a funcion: animPremio, animVidaExtra...)
//   IDAncla = id del elemento que queda fijo en pantalla (casi siempre el jugador)
void ejecutarAnimacion (tTablero *t, tJugador *j, tEstado *e, tLog *l, unsigned frame, Animacion anim, unsigned IDAncla)
{
    unsigned i;
    for( i = 1; i <= frame; i++)   // recorre los cuadros 1, 2, ..., frame
    {
        wait(1);                   // (1) pausa 1 seg -> le da el ritmo visible a la animacion
        posicionarTablero(t, IDAncla); // (2) "centra la camara" en el ancla (el jugador queda fijo)
        anim(t, i);                // (3) dibuja los cambios del cuadro i (modifica el tablero)
        dibujarEscena(t, j, e, l); // (4) repinta toda la pantalla con esos cambios
    }
}

// Animacion: captura de premio.
// El jugador llega al premio, brillan asteriscos a los lados, el premio se
// convierte en asterisco y desaparece, y el jugador "parpadea" (J -> j -> J).
void animPremio(tTablero *tablero, unsigned frame)
{
    switch(frame)
    {
        case 1:                          // brillan asteriscos a ambos lados del premio
            INSIZQ(PREMIO, ASTERISCO);   // '*P'
            INSDER(PREMIO, ASTERISCO);   // '*P*'
            break;
        case 2:                          // el premio se vuelve asterisco
            CAMELEM(PREMIO, ASTERISCO);  // 'P' -> '*'
            break;
        case 3:                          // se apaga un asterisco
            ELIM(ASTERISCO);
            break;
        case 4:                          // se apaga otro y el jugador se achica
            ELIM(ASTERISCO);
            CAMELEM(JUGADOR, JUGMINUS);  // 'J' -> 'j'
            break;
        case 5:                          // se apaga el ultimo y el jugador vuelve a normal
            ELIM(ASTERISCO);
            CAMELEM(JUGMINUS, JUGADOR);  // 'j' -> 'J'
            break;
    }
}

// Animacion: oasis obtenido (el jugador consigue el escudo).
// El oasis "destella" (!O!), y aparece/desaparece un escudo "( )" alrededor del
// jugador un par de veces, hasta quedar con el escudo puesto y el oasis apagado.
void animOasisObtenido(tTablero *tablero, unsigned frame)
{
    switch(frame)
    {
        case 1:                          // el oasis destella a los lados
            INSIZQ(OASIS, OASISACTIVO);  // '!O'
            INSDER(OASIS, OASISACTIVO);  // '!O!'
            break;
        case 2:                          // aparece el escudo alrededor del jugador
            INSIZQ(JUGADOR, ESCUDOIZQ);  // '(J'
            INSDER(JUGADOR, ESCUDODER);  // '(J)'
            break;
        case 3:                          // parpadeo: se va el escudo
            ELIM(ESCUDOIZQ);
            ELIM(ESCUDODER);
            break;
        case 4:                          // parpadeo: vuelve el escudo
            INSIZQ(JUGADOR, ESCUDOIZQ);
            INSDER(JUGADOR, ESCUDODER);
            break;
        case 5:                          // parpadeo: se va otra vez
            ELIM(ESCUDOIZQ);
            ELIM(ESCUDODER);
            break;
        case 6:                          // queda el escudo puesto y se apaga el oasis
            INSIZQ(JUGADOR, ESCUDOIZQ);
            INSDER(JUGADOR, ESCUDODER);
            ELIM(OASISACTIVO);           // borra el '!' izquierdo
            ELIM(OASISACTIVO);           // borra el '!' derecho
            break;
    }
}

// Animacion: oasis perdido.
// El escudo "( )" se tambalea (cae y se levanta) y finalmente se rompe y desaparece.
void animOasisPerdido(tTablero *tablero, unsigned frame)
{
    switch(frame)
    {
        case 1:                              // el escudo se cae (se vuelve ',')
            CAMELEM(ESCUDOIZQ, ESCUDOCAIDO);  // '(' -> ','
            CAMELEM(ESCUDODER, ESCUDOCAIDO);  // ')' -> ','
            break;
        case 2:                              // se vuelve a levantar
            CAMELEM(ESCUDOCAIDO, ESCUDOIZQ);
            CAMELEM(ESCUDOCAIDO, ESCUDODER);
            break;
        case 3:                              // se cae de nuevo
            CAMELEM(ESCUDOIZQ, ESCUDOCAIDO);
            CAMELEM(ESCUDODER, ESCUDOCAIDO);
            break;
        case 4:                              // se rompe del todo y desaparece
            ELIM(ESCUDOCAIDO);
            ELIM(ESCUDOCAIDO);
            break;
    }
}

// Animacion: tormenta se activa.
// La arena (. : ; #) se va "armando" de a poco desde la tormenta hacia el
// jugador, lo envuelve y termina dejandolo ATURDIDO entre llaves "{ }".
void animTorSeActiva(tTablero *tablero, unsigned frame)
{
    switch(frame)
    {
        // Los cuadros 1..9 hacen "rodar" la arena cambiando un nivel por otro
        // (ARENA1='.', ARENA2=':', ARENA3=';', ARENA4='#') y agregando granos
        // a los lados de la tormenta y del jugador, simulando el viento.
        case 1:
            INSIZQ(TORMENTA, ARENA1);
            break;
        case 2:
            CAMELEM(ARENA1, ARENA2);
            INSDER(TORMENTA, ARENA1);
            break;
        case 3:
            CAMELEM(ARENA2, ARENA3);
            CAMELEM(ARENA1, ARENA2);
            INSDER(JUGADOR, ARENA1);
            break;
        case 4:
            CAMELEM(ARENA3, ARENA4);
            CAMELEM(ARENA2, ARENA3);
            CAMELEM(ARENA1, ARENA2);
            break;
        case 5:
            INSIZQ(JUGADOR, ASTERISCO);
            CAMELEM(ARENA3, ARENA4);
            CAMELEM(ARENA2, ARENA3);
            CAMELEM(ARENA4, ARENA3);
            break;
        case 6:
            CAMELEM(ARENA3, ARENA1);
            CAMELEM(ARENA3, ARENA4);
            CAMELEM(ARENA4, ARENA3);
            break;
        case 7:
            INSDER(JUGADOR, ASTERISCO);
            ELIM(ARENA1);
            CAMELEM(ARENA3, ARENA2);
            CAMELEM(ARENA4, ARENA3);
            break;
        case 8:
            CAMELEM(ARENA2, ARENA1);
            CAMELEM(ARENA3, ARENA2);
            break;
        case 9:
            ELIM(ARENA1);
            CAMELEM(ARENA2, ARENA1);
            break;
        case 10:                              // ultimo cuadro: el jugador queda aturdido
            ELIM(ARENA1);
            CAMELEM(ASTERISCO, ATURDIDOIZQ);  // '*' -> '{'
            CAMELEM(ASTERISCO, ATURDIDODER);  // '*' -> '}'
            break;

    }
}
// Animacion: tormenta finaliza.
// Las llaves de aturdimiento "{ }" se vuelven asteriscos y se apagan: el
// jugador se recupera.
void animTorFinaliza(tTablero *tablero, unsigned frame)
{
    switch(frame)
    {
        case 1:                               // las llaves se vuelven asteriscos
            CAMELEM(ATURDIDOIZQ, ASTERISCO);  // '{' -> '*'
            CAMELEM(ATURDIDODER, ASTERISCO);  // '}' -> '*'
            break;
        case 2:                               // se apagan los asteriscos
            ELIM(ASTERISCO);
            ELIM(ASTERISCO);
            break;
    }
}

// Animacion: vida extra.
// Aparecen flechas "| /" que se transforman en un escudo "( )", la vida extra
// desaparece, el jugador parpadea y vuelve a la normalidad.
void animVidaExtra(tTablero *tablero, unsigned frame)
{
    switch(frame)
    {
        case 1:                              // aparecen las flechas a los lados de la 'V'
            INSIZQ(VIDAEXTRA, FLECHAIZQ);     // '|V'
            INSDER(VIDAEXTRA, FLECHADER);     // '|V/'
            break;
        case 2:                              // las flechas se vuelven escudo
            CAMELEM(FLECHAIZQ, ESCUDOIZQ);    // '|' -> '('
            CAMELEM(FLECHADER, ESCUDODER);    // '/' -> ')'
            break;
        case 3:                              // desaparece la vida extra y el jugador se achica
            ELIM(VIDAEXTRA);
            CAMELEM(JUGADOR, JUGMINUS);       // 'J' -> 'j'
            break;
        case 4:                              // se va el escudo y el jugador vuelve a normal
            ELIM(ESCUDOIZQ);
            ELIM(ESCUDODER);
            CAMELEM(JUGMINUS, JUGADOR);       // 'j' -> 'J'
            break;
    }
}

// Animacion: bandido ataca.
// Aparece un punal "<-" junto al bandido, golpea al jugador (que se achica) y
// el jugador termina "desapareciendo" ('_') por el dano.
void animBandidoAtaca(tTablero *tablero, unsigned frame)
{
    switch(frame)
    {
        case 1:                          // aparece el punal con su mango a la izq del bandido
            INSIZQ(BANDIDO, PUNALIZQ);    // '<B'
            INSIZQ(BANDIDO, MANGO);       // '-<B'
            break;
        case 2:                          // el jugador se achica y se va el mango (el punal "viaja")
            CAMELEM(JUGADOR, JUGMINUS);   // 'J' -> 'j'
            ELIM(MANGO);
            break;
        case 3:                          // el jugador queda danado y se va el punal
            CAMELEM(JUGMINUS, DESAPARECE);// 'j' -> '_'
            ELIM(PUNALIZQ);
            break;
    }
}

// Animacion: bandido desaparece.
// El bandido se achica (B -> b), se desvanece (b -> '_') y finalmente se borra.
void animBandidoDesaparece(tTablero *tablero, unsigned frame)
{
    switch(frame)
    {
        case 1:                            // el bandido se achica
            CAMELEM(BANDIDO, BANMINUS);     // 'B' -> 'b'
            break;
        case 2:                            // se desvanece
            CAMELEM(BANMINUS, DESAPARECE);  // 'b' -> '_'
            break;
        case 3:                            // se borra del tablero
            ELIM(DESAPARECE);
            break;
    }
}

// Animacion: el jugador gana.
// El jugador "festeja" parpadeando (J -> j -> J...). Los cuadros 5,6,7 estan
// vacios a proposito: solo agregan tiempo (pausas) al final del festejo.
void animJugGana(tTablero *tablero, unsigned frame)
{
    switch(frame)
    {
        case 1:
            CAMELEM(JUGADOR, JUGMINUS);   // 'J' -> 'j'
            break;
        case 2:
            CAMELEM(JUGMINUS, JUGADOR);   // 'j' -> 'J'
            break;
        case 3:
            CAMELEM(JUGADOR, JUGMINUS);
            break;
        case 4:
            CAMELEM(JUGMINUS, JUGADOR);
            break;
        case 5:                          // cuadros sin cambios: solo pausa
        case 6:
        case 7:
            break;
    }
}

// Animacion: jugador danado (se recupera tras el ataque del bandido).
// Parte del estado "desaparecido" ('_') y reaparece: '_' -> 'j' -> 'J'.
void animJugadorDaniado(tTablero *tablero, unsigned frame)
{
    switch(frame)
    {
        case 1:                            // reaparece achicado
            CAMELEM(DESAPARECE, JUGMINUS);  // '_' -> 'j'
            break;
        case 2:                            // vuelve a su tamano normal
            CAMELEM(JUGMINUS, JUGADOR);     // 'j' -> 'J'
            break;
    }
}

// Animacion: el jugador pierde.
// El jugador se achica, se desvanece y desaparece: J -> j -> '_' -> (nada).
void animJugPierde(tTablero *tablero, unsigned frame)
{
    switch(frame)
    {
        case 1:
            CAMELEM(JUGADOR, JUGMINUS);     // 'J' -> 'j'
            break;
        case 2:
            CAMELEM(JUGMINUS, DESAPARECE);  // 'j' -> '_'
            break;
        case 3:
            ELIM(DESAPARECE);               // se borra del tablero
            break;

    }
}
