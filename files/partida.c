#include "partida.h"

int  jugarPartida()// VA A INICIALIZAR Y LUEGO VA A MANEJAR EL LOOP
{
    tListaDE tablero;
    tJugador jugador;
    tCola movimientos;
    tEstado estado;

    inicializarPartida(&tablero, &jugador, &movimientos);

    int corriendo = 1;

    while(corriendo)
    {
        dibujarEstadoDelJuego(&tablero, &jugador, &movimientos); // ESTADO PARA LA ELECCION DEL JUGADOR

        procesarEntrada(&movimientos, &jugador); // JUGADOR TIRA DADO Y ELIGE DIRECCION, SE ENCOLAN LOS MOVIMIENTOS

        calcularMovBandido(&tablero, &movimientos); // SE CALCULA Y ENCOLAN LOS MOVIMIENTO DE LOS BANDIDOS

        dibujarAnimacionMov(&tablero, &jugador, &movimientos); // SE DESENCOLA LOS MOVIMIENTOS Y SE LOS DIBUJA PASO A PASO

        actualizarEstado(&tablero, &jugador, &estado); // SE ACTUALIZA EL ESTADO DE JUEGO EN LA POSICION FINAL DE LOS ELEMENTOS, SE PASAN BOOLEANOS CON EL ESTADO DEL JUEGO A LA SIG FUNCION

        dibujarAnimacionEstado(&tablero, &jugador, &estado); // SE ANIMA EL CAMBIO DE ESTADO DE ACUERDO A LO QUE INDIQUEN LOS BOOLEANOS
    }

    finalizarPartida(); // DEBERIA IMPRIMIR EL HISTORICO DE MOVIMIENTOS DEL JUGADOR Y GUARDAR EN ARCHIVO LAS ESTADISTICAS DE LA PARTIDA
}

int  inicializarPartida(tLista* tablero)// VA A CARGAR TCONFIG Y GENERAR EL TABLERO
{
    tConfig config = { 25, 3, 2, 3, 1, 2, 3};
    //cargarConfiguracion();

    crearTablero(tablero, config);
}

int  dibujarEstadoDelJuego(tListaDE *tablero, tJugador *jugador);

int  procesarEntrada(tCola *movimientos, tJugador *jugador);

int  calcularMovBandido(tListaDE *tablero, tCola *movimientos);

int  dibujarAnimacionMov(tListaDE *tablero, tJugador *jugador, tCola *movimientos);

int  actualizarEstado(tListaDE *tablero, tJugador *jugador, tEstado *estado);

int  dibujarAnimacionEstado(tListaDE *tablero, tJugador *jugador, tEstado *estado);

int  finalizarPartida();
