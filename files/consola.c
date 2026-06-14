#include "consola.h"


void dibujarEscena(tTablero *tablero, tJugador *jugador, tEstado *estado, tLog *log)
{
    limpiarPantalla();

    mostrarSeparador();

    mostrarTitulo();

    mostrarSeparador();

    mostrarTablero(tablero);

    mostrarSeparador();

    mostrarHUD(jugador, estado);

    mostrarSeparador();

    mostrarLog(log);
}

void dibujarFinDePartida(tTablero *tablero, tJugador *jugador, tLog *log)
{
    limpiarPantalla();
    mostrarSeparador();

    mostrarTitulo();
    mostrarSeparador();

    mostrarTablero(tablero);
    mostrarSeparador();

    mostrarEstadisticas(jugador);
    mostrarSeparador();

    mostrarLog(log);
    mostrarSeparador();

    mostrarMovimientosJugador(jugador);
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


void mostrarHUD(tJugador* jugador, tEstado* estado)
{
    //vidas, puntaje, cant mov, oasis si/no
    printf("Vidas: %d\t",jugador->vida);
    printf("\tPuntaje: %d\n",jugador->puntaje);
    printf("Cantidad de movimientos: %d/n",jugador->cantMov);
    printf("Protección de oasis: ");
    if(estado->Oobtenido==1)
    {
        printf("SI\n");
    }
    else
    {
        printf("NO\n");
    }
}


void limpiarBuffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void limpiarPantalla()
{
    printf("\033[2J\033[H");
}
