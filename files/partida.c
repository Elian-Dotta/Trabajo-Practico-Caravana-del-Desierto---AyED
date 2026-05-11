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

int  inicializarPartida(tLista* tablero)// VA A CARGAR TCONFIG Y GENERAR EL TABLERO
{
    tConfig config = { 25, 3, 2, 3, 1, 2, 3};
    //cargarConfiguracion();

    crearTablero(tablero, config);
}

int  procesarEntrada(); // DETECTA MOVIMIENTO DEL JUGADOR

int  actualizarPartida(); // ACTUALIZA LOS BANDIDOS Y LOS PREMIOS, CHECKEA FIN DE PARTIDA

int  renderizarPartida(); // DIBUJA EL TABLERO

int  finalizarPartida(); // GUARDA EL RANKING
