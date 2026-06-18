// === Modulo consola: render y encapsula printf ===
#include "consola.h"


// Dibuja tablero, HUD y log
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

// Pantalla final con estadisticas
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

    mostrarSeparador();
    mostrar("\nPresione ENTER para continuar...\n");
    getchar();
}

// Encapsula printf de un texto
void mostrar(const char *msj)
{
    if(msj[0] != '\0')
        printf("%s", msj);
}

// Muestra vidas, puntaje y movimientos
void mostrarEstadisticas(tJugador *j)
{
    printf("Vidas: %u\t", j->vida);
    printf("\tPuntaje: %u\n", j->puntaje);
    printf("Cantidad de movimientos: %u", j->cantMov);
}

// Imprime el titulo del juego
void mostrarTitulo()
{
    printf("CARAVANA DEL DESIERTO");
}


// Imprime una linea separadora
void mostrarSeparador()
{
    // PARA HACER VARIABLE USAR FOR
    printf("\n\n-------------------------------------------\n\n");
}


// Muestra vidas, puntaje, oasis, tormenta
void mostrarHUD(tJugador* jugador, tEstado* estado)
{
    //vidas, puntaje, cant mov, oasis si/no
    printf("Vidas: %d\t", verVida(jugador));
    printf("\tPuntaje: %d\n", verPuntaje(jugador));
    printf("Cantidad de movimientos: %d\n", verMovimiento(jugador));
    printf("Proteccion de Oasis: ");
    if(estado->tieneOasis == 1)
        printf("SI\n");
    else
        printf("NO\n");
    printf("Tapado por Arena: ");
    if(estado->tieneTormenta == 1)
        printf("SI\n");
    else
        printf("NO\n");
    printf("Dado obtenido: ");
    if(verDado(jugador))
        printf("%d", verDado(jugador));
    else
        printf("NO");
}


// Descarta lo que queda en stdin
void limpiarBuffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Limpia la pantalla de la consola
void limpiarPantalla()
{
    printf("\033[2J\033[H");
}
