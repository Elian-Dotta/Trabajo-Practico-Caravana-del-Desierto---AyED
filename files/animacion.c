#include "animacion.h"


void ejecutarAnimacion (tTablero *t, tJugador *j, tEstado *e, tLog *l, unsigned frame, Animacion anim)
{
    int i;
    for( i = 1; i <= frame; i++)
    {
        anim(t, i);
        dibujarEscena(t, j, e, l);
    }
}

int animPremio(tTablero *tablero, unsigned frame)
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

int animOasisObtenido(tTablero *tablero, unsigned frame)
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

int animOasisPerdido(tTablero *tablero, unsigned frame)
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
int animTorSeActiva(tTablero *tablero, unsigned frame)
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
int animTorFinaliza(tTablero *tablero, unsigned frame)
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
int animVidaExtra(tTablero *tablero, unsigned frame)
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
int animBandidoAtaca(tTablero *tablero, unsigned frame)
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
int animBandidoDesaparece(tTablero *tablero, unsigned frame)
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
int animJugGana(tTablero *tablero, unsigned frame)
{
    switch(frame)
    {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
    }
}

int animJugadorDaniado(tTablero *tablero, unsigned frame)
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
