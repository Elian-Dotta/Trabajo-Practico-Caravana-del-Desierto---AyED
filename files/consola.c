#include "consola.h"


void dibujarEscena(tTablero *tablero, tJugador *jugador, tEstado *estado)
{
    mostrarTitulo();

    mostrarSeparador();

    mostrarTablero(tablero);

    mostrarSeparador();

    mostrarHud(jugador, estado);

    mostrarSeparador();

    mostrarLog();
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


<<<<<<< Updated upstream
=======
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


void limpiarBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
>>>>>>> Stashed changes
