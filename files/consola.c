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

void mostrar(const char *msj)
{
    if(msj[0] != '\0')
        printf("%s", msj);
}

void mostrarEstadisticas(tJugador *j)
{
    printf("Vidas: %u\t", j->vida);
    printf("\tPuntaje: %u\n", j->puntaje);
    printf("Cantidad de movimientos: %u/n", j->cantMov);
}

void mostrarTitulo()
{
    printf("CARAVANA DEL DESIERTO");
}


void mostrarSeparador()
{
    // PARA HACER VARIABLE USAR FOR
    printf("\n\n-------------------------------------------\n\n");
}


void mostrarHUD(tJugador* jugador, tEstado* estado)
{
    //vidas, puntaje, cant mov, oasis si/no
    printf("Vidas: %d\t", verVida(jugador));
    printf("\tPuntaje: %d\n", verPuntaje(jugador));
    printf("Cantidad de movimientos: %d\n", verMovimiento(jugador));
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
