#include "partida.h"

int  jugarPartida()// VA A INICIALIZAR Y LUEGO VA A MANEJAR EL LOOP
{
    tLista tablero;

    inicializarPartida(&tablero);

    int corriendo = 1;

    while(corriendo)
    {
        renderizarPartida(); // MUESTRA LA PARTIDA EN SU ULTIMO ESTADO PARA QUE EL JUGADOR ELIJA QUE HACER Y HUD
        procesarEntrada();   // TOMA EN CUENTA LA DECISION DEL JUGADOR
        actualizarJugador(); // ACTUALIZA EN MEMORIA LA POSICION DEL JUGADOR
        renderizarPartida(); // MUESTRA EN PANTALLA LA NUEVA POSICION DEL JUGADOR

        actualizarBandido(); // ACTUALIZA EN MEMORIA LA POSICION DE LOS BANDIDOS CALCULANDO SU NUEVA POSICION // TIMER 5 SEGUNDOS ANTES DE MOSTRAR
        renderizarPartida(); // MUESTRA EL NUEVO LUGAR DE LOS BANDIDOS

        actualizarPartida(); // ACTUALIZA EL ESTADO DEL JUGADOR CON LA NUEVA DISPOSICION // TIMER 2 SEGUNDOS ANTES DE MOSTRAR
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


int  renderizarPartida(); // DIBUJA EL TABLERO Y DESPUES EL HUD

int  finalizarPartida(); // GUARDA EL RANKING
