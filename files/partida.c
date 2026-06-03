#include "partida.h"

// INICIALIZA, FINALIZA Y MANEJA EL LOOP DEL JUEGO
int  jugarPartida()// VA A INICIALIZAR Y LUEGO VA A MANEJAR EL LOOP
{
    tTablero tablero;
    tJugador jugador;
    tCola movimientos;
    tEstado estado;
    tLista bandidosInteligentes; // LISTA DE ENTEROS, IDS

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
    // PEDIR INPUT O SCANF VERIFICAR DATO VALIDO F O B
    // CREAR VARIABLE MOV Y ASIGNARLE LOS VALORES INGRESADOS
    // ENCOLAR

}

int  calcularMovBandido(tTablero *tablero, tLista *bandidosInteligentes, int posJugador, int cantCasillaTablero, tCola *movimientos)
{
    tTablero     tableroInicio     = NULL;
    const tElem *bandidoEncontrado = NULL;
    tMovimiento  movimientoBandido;

    if(NULL == *tablero)
        return 0;

    tableroInicio = posicionarTablero(tablero, 0);
    recorrerListaDE(&tableroInicio, devolverPrimerBandido, &bandidoEncontrado);

    if(NULL == bandidoEncontrado)
        return 0; //No hay bandidos en el tablero

    movimientoBandido.id    = bandidoEncontrado->id_elem;
    movimientoBandido.cant  = tirarDado(1,6); //srand(...) -> semilla debe inicializarse al momento de inicializar el juego...

    if(NULL == buscarPorClaveEnLista(bandidosInteligentes, bandidoEncontrado->id_elem, compararEnteros)){
        movimientoBandido.dir = tirarDado(0,1)?'F':'B';
    }else{
        int distDer = 0, distIzq = 0;
        distanciasEntreElementos(bandidoEncontrado->nro_casilla, posJugador, cantCasillaTablero, &distDer, &distIzq);
        distDer = abs(distDer - movimientoBandido.cant);
        distIzq = abs(distIzq - movimientoBandido.cant);
        movimientoBandido.dir = distDer<distIzq?'F':'B';
    }

    ponerEnCola(movimientos, &movimientoBandido, sizeof(tMovimiento));

    return 1;
}

int  dibujarAnimacionMov(tTablero *tablero, tJugador *jugador, tCola *movimientos, tEstado *estado)
{
    // HAY QUE DESENCOLAR LOS MOVIMIENTOS, E IR RESTANDOLES UNO PARA PROCESAR MOVIMIENTO POR MOVIMIENTO EN CADA FRAME
    // SE PUEDE USAR LA CANTIDAD DE BANDIDOS PARA IR CALCULANDO EL MOMENTO DONDE APARECE EL JUGADOR
    // O CAMBIAR LA ESTRUCTURA TMOV PARA AÑADIR EL ID, EL UNICO USO SERIA ESTE, PARA CALCULAR EL MOV DE LOS BANDIDOS NO SE NECESITA ID EN EL TMOV
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
    // DENTRO DE TABLERO.H RECORRE TABLERO, PARA CADA CASILLA ACTUALIZA ESTADO
    // TOMA EN CUENTA EL PREMIO, OASIS, TORMENTA Y BANDIDO EN LA POSICION FINAL
}

int  dibujarAnimacionEstado(tTablero *tablero, tJugador *jugador, tEstado *estado)
{
    // RESOLVER PRIMITIVAS NUEVAS
    // MATRIZ DE ANIMACIONES PREDEFINIDA
    // OASIS OBTENIDO (J) J (J) J (J)
    // OASIS DESOBTENIDO
    // JUGADO OBTUVO PREMIO *J* -> * J * -> J
//    IF(OASIS OBTENIDO)
//        FOR ANIMACION OASIS
//        DIBUJAR
    //
}

int  finalizarPartida();

int  inicializarEstado(tEstado *est, int cantBandidos)
{

}
