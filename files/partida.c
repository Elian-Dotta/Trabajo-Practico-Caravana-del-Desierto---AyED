#include "partida.h"

// INICIALIZA, FINALIZA Y MANEJA EL LOOP DEL JUEGO
int  jugarPartida()// VA A INICIALIZAR Y LUEGO VA A MANEJAR EL LOOP
{
    tTablero tablero;
    tJugador jugador;
    tCola movimientos;
    tEstado estado;

    inicializarPartida(&tablero, &jugador, &movimientos, &estado);

    int corriendo = 1;

    while(corriendo)
    {
        dibujarEstadoDelJuego(&tablero, &jugador, &estado); // ESTADO PARA LA ELECCION DEL JUGADOR

        procesarEntrada(&movimientos, &jugador); // JUGADOR TIRA DADO Y ELIGE DIRECCION, SE ENCOLAN LOS MOVIMIENTOS

        calcularMovBandido(&tablero, &movimientos); // SE CALCULA Y ENCOLAN LOS MOVIMIENTO DE LOS BANDIDOS

        dibujarAnimacionMov(&tablero, &jugador, &movimientos, &estado); // SE DESENCOLA LOS MOVIMIENTOS Y SE LOS DIBUJA PASO A PASO

        actualizarEstado(&tablero, &jugador, &estado); // SE ACTUALIZA EL ESTADO DE JUEGO EN LA POSICION FINAL DE LOS ELEMENTOS, SE PASAN BOOLEANOS CON EL ESTADO DEL JUEGO A LA SIG FUNCION

        dibujarAnimacionEstado(&tablero, &jugador, &estado); // SE ANIMA EL CAMBIO DE ESTADO DE ACUERDO A LO QUE INDIQUEN LOS BOOLEANOS
    }

    finalizarPartida(); // DEBERIA IMPRIMIR EL HISTORICO DE MOVIMIENTOS DEL JUGADOR Y GUARDAR EN ARCHIVO LAS ESTADISTICAS DE LA PARTIDA
}

// FUNCIONES LLAMADAS POR JUGAR PARTIDA

int  inicializarPartida(tTablero* tablero, tJugador *jugador, tCola *movimientos, tEstado *estado)// VA A CARGAR TCONFIG Y GENERAR EL TABLERO
{
    tConfig config = { 25, 3, 2, 3, 1, 2, 3};
    //cargarConfiguracion();

    crearTablero(tablero, config);

    inicializarEstado(estado, config.max_band);

    inicializarJugador(jugador, config.vidas_ini);

    crearCola(movimientos);
}

int  dibujarEstadoDelJuego(tTablero *tablero, tJugador *jugador, tEstado *estado)
{

}

int  procesarEntrada(tCola *movimientos, tJugador *jugador)
{

}

int  calcularMovBandido(tTablero *tablero, tCola *movimientos)
{

}

int  dibujarAnimacionMov(tTablero *tablero, tJugador *jugador, tCola *movimientos, tEstado *estado)
{
    // HAY QUE DESENCOLAR LOS MOVIMIENTOS, E IR RESTANDOLES UNO PARA PROCESAR MOVIMIENTO POR MOVIMIENTO EN CADA FRAME
    // SE PUEDE USAR LA CANTIDAD DE BANDIDOS PARA IR CALCULANDO EL MOMENTO DONDE APARECE EL JUGADOR
    // O CAMBIAR LA ESTRUCTURA TMOV PARA AÑADIR EL ID, EL UNICO USO SERIA ESTE, PARA CALCULAR EL MOV DE LOS BANDIDOS NO SE NECESITA ID EN EL TMOV
    int elemHastaJugador = 0;
    tMovimiento movActual;
    int movRelativo;

    // PENSE EN DIBUJAR UNA SECUENCIA ENTERA DE PASOS, OSEA CUANDO TODOS ELEMENTOS DEN UN PASO, DIBUJAR, PERO AHORA PENSE QUE ESTARIA BUENO DIBUJAR CADA PASO INDIVIDUALMENTE

    while(!colaVacia(movimientos))
    {
        sacarDeCola(movimientos, &movActual, sizeof(movActual));
        // movRelativo = mov.dir == 'F'? 1 : -1; // ESTA FORMA UTILIZA EL CAMPO DE LA ESTRUCTURA Y DEJA EL CODIGO MEDIO CRIPTICO AL USAR EL OPERADOR TERNARIO
        movRelativo = PASO * calcularDireccion(movActual.dir); // DEVUELVE 1 O -1 PARA MULTIPLICAR EL NUMERO DE CASILLAS POR LA DIRECCION
        moverElementoPorId(tablero, movActual.id, movRelativo);
        movActual.cant-= PASO;

        if(movActual.cant > 0)
            ponerEnCola(movimientos, &movActual, sizeof(movActual));

        dibujarEscena(tablero, jugador, estado);
    }
}

int  actualizarEstado(tTablero *tablero, tJugador *jugador, tEstado *estado)
{

}

int  dibujarAnimacionEstado(tTablero *tablero, tJugador *jugador, tEstado *estado)
{

}

int  finalizarPartida();

int  inicializarEstado(tEstado *est, int cantBandidos)
{

}
