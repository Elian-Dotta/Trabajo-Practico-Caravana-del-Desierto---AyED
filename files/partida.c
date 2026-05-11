#include "partida.h"

int  jugarPartida()// VA A INICIALIZAR Y LUEGO VA A MANEJAR EL LOOP
{
    tLista tablero;

    inicializarPartida(&tablero);

    int corriendo = 1;

    while(corriendo)
    {
        renderizarPartida();
        procesarEntrada();
        actualizarPartida();
        renderizarPartida();
    }

    finalizarPartida();
}

int  inicializarPartida(); // VA A CARGAR TCONFIG Y GENERAR EL TABLERO

int  procesarEntrada(); // DETECTA MOVIMIENTO DEL JUGADOR

int  actualizarPartida(); // ACTUALIZA LOS BANDIDOS Y LOS PREMIOS, CHECKEA FIN DE PARTIDA

int  renderizarPartida(); // DIBUJA EL TABLERO

int  finalizarPartida(); // GUARDA EL RANKING
