// === Modulo animacion: secuencias de cambio de estado ===
#include "animacion.h"


// Reproduce una animacion cuadro a cuadro
void ejecutarAnimacion (tTablero *t, tJugador *j, tEstado *e, tLog *l, unsigned frame, Animacion anim, unsigned IDAncla)
{
    unsigned i;
    for( i = 1; i <= frame; i++)
    {
        wait(1);
        posicionarTablero(t, IDAncla);
        anim(t, i);
        dibujarEscena(t, j, e, l);
    }
}

// Animacion: captura de premio
void animPremio(tTablero *tablero, unsigned frame)
{
    switch(frame)
    {
        case 1:
            INSIZQ(PREMIO, ASTERISCO);
            INSDER(PREMIO, ASTERISCO);
            break;
        case 2:
            CAMELEM(PREMIO, ASTERISCO);
            break;
        case 3:
            ELIM(ASTERISCO);
            break;
        case 4:
            ELIM(ASTERISCO);
            CAMELEM(JUGADOR, JUGMINUS);
            break;
        case 5:
            ELIM(ASTERISCO);
            CAMELEM(JUGMINUS, JUGADOR);
            break;
    }
}

// Animacion: oasis obtenido (escudo)
void animOasisObtenido(tTablero *tablero, unsigned frame)
{
    switch(frame)
    {
        case 1:
            INSIZQ(OASIS, OASISACTIVO);
            INSDER(OASIS, OASISACTIVO);
            break;
        case 2:
            INSIZQ(JUGADOR, ESCUDOIZQ);
            INSDER(JUGADOR, ESCUDODER);
            break;
        case 3:
            ELIM(ESCUDOIZQ);
            ELIM(ESCUDODER);
            break;
        case 4:
            INSIZQ(JUGADOR, ESCUDOIZQ);
            INSDER(JUGADOR, ESCUDODER);
            break;
        case 5:
            ELIM(ESCUDOIZQ);
            ELIM(ESCUDODER);
            break;
        case 6:
            INSIZQ(JUGADOR, ESCUDOIZQ);
            INSDER(JUGADOR, ESCUDODER);
            ELIM(OASISACTIVO);
            ELIM(OASISACTIVO);
            break;
    }
}

// Animacion: oasis perdido
void animOasisPerdido(tTablero *tablero, unsigned frame)
{
    switch(frame)
    {
        case 1:
            CAMELEM(ESCUDOIZQ, ESCUDOCAIDO);
            CAMELEM(ESCUDODER, ESCUDOCAIDO);
            break;
        case 2:
            CAMELEM(ESCUDOCAIDO, ESCUDOIZQ);
            CAMELEM(ESCUDOCAIDO, ESCUDODER);
            break;
        case 3:
            CAMELEM(ESCUDOIZQ, ESCUDOCAIDO);
            CAMELEM(ESCUDODER, ESCUDOCAIDO);
            break;
        case 4:
            ELIM(ESCUDOCAIDO);
            ELIM(ESCUDOCAIDO);
            break;
    }
}

// Animacion: tormenta se activa
void animTorSeActiva(tTablero *tablero, unsigned frame)
{
    switch(frame)
    {
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
        case 10:
            ELIM(ARENA1);
            CAMELEM(ASTERISCO, ATURDIDOIZQ);
            CAMELEM(ASTERISCO, ATURDIDODER);
            break;

    }
}
// Animacion: tormenta finaliza
void animTorFinaliza(tTablero *tablero, unsigned frame)
{
    switch(frame)
    {
        case 1:
            CAMELEM(ATURDIDOIZQ, ASTERISCO);
            CAMELEM(ATURDIDODER, ASTERISCO);
            break;
        case 2:
            ELIM(ASTERISCO);
            ELIM(ASTERISCO);
            break;
    }
}

// Animacion: vida extra
void animVidaExtra(tTablero *tablero, unsigned frame)
{
    switch(frame)
    {
        case 1:
            INSIZQ(VIDAEXTRA, FLECHAIZQ);
            INSDER(VIDAEXTRA, FLECHADER);
            break;
        case 2:
            CAMELEM(FLECHAIZQ, ESCUDOIZQ);
            CAMELEM(FLECHADER, ESCUDODER);
            break;
        case 3:
            ELIM(VIDAEXTRA);
            CAMELEM(JUGADOR, JUGMINUS);
            break;
        case 4:
            ELIM(ESCUDOIZQ);
            ELIM(ESCUDODER);
            CAMELEM(JUGMINUS, JUGADOR);
            break;
    }
}

// Animacion: bandido ataca
void animBandidoAtaca(tTablero *tablero, unsigned frame)
{
    switch(frame)
    {
        case 1:
            INSIZQ(BANDIDO, PUNALIZQ);
            INSIZQ(BANDIDO, MANGO);
            break;
        case 2:
            CAMELEM(JUGADOR, JUGMINUS);
            ELIM(MANGO);
            break;
        case 3:
            CAMELEM(JUGMINUS, DESAPARECE);
            ELIM(PUNALIZQ);
            break;
    }
}

// Animacion: bandido desaparece
void animBandidoDesaparece(tTablero *tablero, unsigned frame)
{
    switch(frame)
    {
        case 1:
            CAMELEM(BANDIDO, BANMINUS);
            break;
        case 2:
            CAMELEM(BANMINUS, DESAPARECE);
            break;
        case 3:
            ELIM(DESAPARECE);
            break;
    }
}

// Animacion: el jugador gana
void animJugGana(tTablero *tablero, unsigned frame)
{
    switch(frame)
    {
        case 1:
            CAMELEM(JUGADOR, JUGMINUS);
            break;
        case 2:
            CAMELEM(JUGMINUS, JUGADOR);
            break;
        case 3:
            CAMELEM(JUGADOR, JUGMINUS);
            break;
        case 4:
            CAMELEM(JUGMINUS, JUGADOR);
            break;
        case 5:
        case 6:
        case 7:
            break;
    }
}

// Animacion: jugador danado
void animJugadorDaniado(tTablero *tablero, unsigned frame)
{
    switch(frame)
    {
        case 1:
            CAMELEM(DESAPARECE, JUGMINUS);
            break;
        case 2:
            CAMELEM(JUGMINUS, JUGADOR);
            break;
    }
}

// Animacion: el jugador pierde
void animJugPierde(tTablero *tablero, unsigned frame)
{
    switch(frame)
    {
        case 1:
            CAMELEM(JUGADOR, JUGMINUS);
            break;
        case 2:
            CAMELEM(JUGMINUS, DESAPARECE);
            break;
        case 3:
            ELIM(DESAPARECE);
            break;

    }
}
