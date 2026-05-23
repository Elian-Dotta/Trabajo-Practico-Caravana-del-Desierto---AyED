#include "jugador.h"

void inicializarJugador(tJugador* j, unsigned vida)
{
    j->vida = vida;
    j->cantMov = 0;
    j->puntaje = 0;
    crearCola(&j->hisMovJugador);
}

void aumentarVida(tJugador* j)
{
    j->vida++;
}

void disminuirVida(tJugador* j)
{
    j->vida--;
}

unsigned verVida(const tJugador* j)
{
    return j->vida;
}

void aumentarPuntaje(tJugador *j)
{
    j->puntaje++;
}

unsigned verPuntaje(const tJugador *j)
{
    return j->puntaje;
}

void aumentarMovimiento(tJugador *j)
{
    j->cantMov++;
}

unsigned verMovimiento(const tJugador *j)
{
    return j->cantMov;
}

void guardarMovimientoJugador(tJugador *j, tMovimiento *mov)
{
    ponerEnCola(&j->hisMovJugador, mov, sizeof(tMovimiento));
}

void mostrarMovimientosJugador(tJugador *j)
{
    tMovimiento mov;
    // ACA SE MUESTRA AL FINALIZAR LA PARTIDA, HABRIA QUE VER DE QUE FORMA MOSTRAR
    // PERO COMO INICIO HAY QUE SACAR ELEMENTOS DE LA COLA Y MOSTRARLOS
    while(!colaVacia(&j->hisMovJugador))
    {
        sacarDeCola(&j->hisMovJugador, &mov, sizeof(tMovimiento));
        // MOSTRARLO -> A LO MEJOR UNA FUNCION DE CONSOLA.H, NUEVA O EXISTENTE
    }
}
