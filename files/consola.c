#include "consola.h"
#include <windows.h>


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
    printf("Vidas: %d\t", j->vida);
    printf("\tPuntaje: %d\n", j->puntaje);
    printf("Cantidad de movimientos: %d\n", j->cantMov);
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
    printf("Cantidad de movimientos: %d\n",jugador->cantMov);
    printf("Proteccion de oasis: ");
    if(estado->Oactivo==1)
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

void pausaFrame(void)
{
    fflush(stdout);          // asegura que el cuadro se vea antes de esperar
    Sleep(VELOCIDAD_ANIM);
}

void habilitarConsola(void)
{
    // Habilita el procesamiento de secuencias ANSI (necesario en Windows 10+ para que
    // "\033[2J\033[H" limpie la pantalla en vez de apilar los cuadros de animacion).
#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD modo = 0;

    if(GetConsoleMode(hOut, &modo))
        SetConsoleMode(hOut, modo | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
}
