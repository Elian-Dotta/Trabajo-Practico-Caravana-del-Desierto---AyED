#include "consola.h"

void dibujarEscena(tTablero *tablero, tJugador *jugador, tEstado *estado)
{
    mostrarTitulo();
    mostrarSeparador();
    mostrarTablero(tablero);
    mostrarSeparador();
    mostrarHud(jugador, estado);
    mostrarSeparador();
    //MOSTRARLOG();
}

void mostrarTitulo()
{
    printf("CARAVANA DEL DESIERTO\n");
}

void mostrarSeparador()
{
    // PARA HACER VARIABLE USAR FOR
    printf("\n-------------------------------------------\n");
}

void mostrarHud(tJugador* jugador, tEstado *estado)
{

}
