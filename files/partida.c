#include "partida.h"

// INICIALIZA, FINALIZA Y MANEJA EL LOOP DEL JUEGO
int  jugarPartida()// VA A INICIALIZAR Y LUEGO VA A MANEJAR EL LOOP
{
    tPartida partida;

    inicializarPartida(&partida);

    while(partida->corriendo)
    {
        dibujarEstadoDelJuego(&partida); // ESTADO PARA LA ELECCION DEL JUGADOR

        procesarEntrada(&partida); // JUGADOR TIRA DADO Y ELIGE DIRECCION, SE ENCOLAN LOS MOVIMIENTOS

        calcularMovBandido(&partida); // SE CALCULA Y ENCOLAN LOS MOVIMIENTO DE LOS BANDIDOS

        dibujarAnimacionMov(&partida); // SE DESENCOLA LOS MOVIMIENTOS Y SE LOS DIBUJA PASO A PASO

        actualizarEstado(&partida); // SE ACTUALIZA EL ESTADO DE JUEGO EN LA POSICION FINAL DE LOS ELEMENTOS, SE PASAN BOOLEANOS CON EL ESTADO DEL JUEGO A LA SIG FUNCION

        dibujarAnimacionEstado(&partida); // SE ANIMA EL CAMBIO DE ESTADO DE ACUERDO A LO QUE INDIQUEN LOS BOOLEANOS
    }

    finalizarPartida(&partida); // DEBERIA IMPRIMIR EL HISTORICO DE MOVIMIENTOS DEL JUGADOR Y GUARDAR EN ARCHIVO LAS ESTADISTICAS DE LA PARTIDA
}

// FUNCIONES LLAMADAS POR JUGAR PARTIDA


int  inicializarPartida(tPartida *p)// VA A CARGAR TCONFIG Y GENERAR EL TABLERO

{
    //tConfig config = { 25, 3, 2, 3, 1, 2, 3};
    cargarConfig(&p->config);

    crearLista(&p->bandInteligentes);

    crearLog(&p->log)

    crearTablero(&p->tablero, p->config, &p->bandidosInteligentes);

    inicializarEstado(&p->estado, p->config.max_band);

    inicializarJugador(&p->jugador, p->config.vidas_ini);

    crearCola(&p->movimientos);

    p->corriendo = 1;
}

int  dibujarEstadoDelJuego(tPartida *p)
{

}

int  procesarEntrada(tPartida *p)
{
    // PEDIR INPUT O SCANF VERIFICAR DATO VALIDO F O B
    // CREAR VARIABLE MOV Y ASIGNARLE LOS VALORES INGRESADOS
    // ENCOLAR

}

int  calcularMovBandido(tTablero *tablero, tLista *bandidosInteligentes, int posJugador, int cantCasillaTablero, tCola *movimientos)
{ // SE CORRIGE DESPUES CONCIDERANDO QUE tPARTIDA TIENE LOS PARAMETROS NECESARIOS
    tTablero     tableroInicio     = NULL;
    tElem        bandidoEncontrado = {0,'\0',0};
    tMovimiento  movimientoBandido;

    if(NULL == *tablero)
        return 0;

    recorrerListaDE(&tableroInicio, devolverPrimerBandido, &bandidoEncontrado);

    if(0 == bandidoEncontrado.id_elem)
        return 0; //No hay bandidos en el tablero

    movimientoBandido.id    = bandidoEncontrado.id_elem;
    movimientoBandido.cant  = tirarDado(1,6); //srand(...) -> semilla debe inicializarse al momento de inicializar el juego...

    if(0 == buscarPorClaveEnLista(bandidosInteligentes, bandidoEncontrado.id_elem, NULL, compararEnteros)){
        movimientoBandido.dir = tirarDado(0,1)?'F':'B';
    }else{
        int distDer = 0, distIzq = 0;
        distanciasEntreElementos(bandidoEncontrado.nro_casilla, posJugador, cantCasillaTablero, &distDer, &distIzq);
        distDer = abs(distDer - movimientoBandido.cant);
        distIzq = abs(distIzq - movimientoBandido.cant);
        movimientoBandido.dir = distDer<distIzq?'F':'B';
    }

    ponerEnCola(movimientos, &movimientoBandido, sizeof(tMovimiento));

    return 1;
}

int  dibujarAnimacionMov(tPartida *p)
{
    // HAY QUE DESENCOLAR LOS MOVIMIENTOS, E IR RESTANDOLES UNO PARA PROCESAR MOVIMIENTO POR MOVIMIENTO EN CADA FRAME
    // SE PUEDE USAR LA CANTIDAD DE BANDIDOS PARA IR CALCULANDO EL MOMENTO DONDE APARECE EL JUGADOR
    // O CAMBIAR LA ESTRUCTURA TMOV PARA AÑADIR EL ID, EL UNICO USO SERIA ESTE, PARA CALCULAR EL MOV DE LOS BANDIDOS NO SE NECESITA ID EN EL TMOV
    tMovimiento movActual;
    int movRelativo;

    int idEscudoIzq,
        idEscudoDer;

    if(p->estado.Oactivo)
    {
        idEscudoIzq = obtenerIdElementoPorTipo(&p->tablero, ESCUDOIZQ);
        idEscudoDer = obtenerIdElementoPorTipo(&p->tablero, ESCUDODER);
    }

    // PENSE EN DIBUJAR UNA SECUENCIA ENTERA DE PASOS, OSEA CUANDO TODOS ELEMENTOS DEN UN PASO, DIBUJAR, PERO AHORA PENSE QUE ESTARIA BUENO DIBUJAR CADA PASO INDIVIDUALMENTE

    while(!colaVacia(&p->movimientos))
    {
        sacarDeCola(&p->movimientos, &movActual, sizeof(movActual));

        // movRelativo = mov.dir == 'F'? 1 : -1; // ESTA FORMA UTILIZA EL CAMPO DE LA ESTRUCTURA Y DEJA EL CODIGO MEDIO CRIPTICO AL USAR EL OPERADOR TERNARIO
        movRelativo = PASO * calcularDireccion(movActual.dir); // DEVUELVE 1 O -1 PARA MULTIPLICAR EL NUMERO DE CASILLAS POR LA DIRECCION

        if(movActual.id == JUGADORID && p->estado.Oactivo &&
           idEscudoIzq != -1 && idEscudoDer != -1)
        {
            moverElementoPorId(&p->tablero, idEscudoIzq, movRelativo);
            moverElementoPorId(&p->tablero, movActual.id, movRelativo);
            moverElementoPorId(&p->tablero, idEscudoDer, movRelativo);
        }
        else
        {
            moverElementoPorId(&p->tablero, movActual.id, movRelativo);
        }

        movActual.cant-= PASO;

        if(movActual.cant > 0)
        {
            if(movActual.id == JUGADORID && (elementosJuntos(&p->tablero, JUGADOR, INICIO) ||
                                             elementosJuntos(&p->tablero, JUGADOR, SALIDA)))
            {
                cambiarDireccion(&movActual);
            }
            ponerEnCola(&p->movimientos, &movActual, sizeof(movActual));
        }


        dibujarEscena(&p->tablero, &p->jugador, &p->estado, &p->log);
    }
}



int  actualizarEstado(tPartida *p)
{

}


int  dibujarAnimacionEstado(tPartida *p)
{
    int mov;

    int idFlechaIzq,
        idFlechaDer;
    if(p->estado.JganaPuntos)
    {
        ejecutarAnimacion(&p->tablero, &p->jugador, &p->estado, &p->log, FRPREMIO, animPremio);
        aumentarPuntaje(&p->jugador);
        escribirEnLog(&p->log, MSJ_PUNTOS);
    }

    if(p->estado.JganaVida)
    {
        ejecutarAnimacion(&p->tablero, &p->jugador, &p->estado, &p->log, FRVIDAEX, animVidaExtra);
        aumentarVida(&p->jugador);
        escribirEnLog(&p->log, MSJ_VIDA);
    }

    if(p->estado.Oobtenido)
    {
        ejecutarAnimacion(&p->tablero, &p->jugador, &p->estado, &p->log, FROASISOB, animOasisObtenido);
        escribirEnLog(&p->log, MSJ_OASISOBTENIDO);
    }

    if(p->estado.Tactiva)
    {
        ejecutarAnimacion(&p->tablero, &p->jugador, &p->estado, &p->log, FRTORACT, animTorActiva);
        escribirEnLog(&p->log, MSJ_TORMENTAACTIVA);
        idFlechaIzq = obtenerIdElementoPorTipo(&p->tablero, FLECHAIZQ);
        idFlechaDer = obtenerIdElementoPorTipo(&p->tablero, FLECHADER);
    }

    if(p->estado.Tfinalizada)
    {
        ejecutarAnimacion(&p->tablero, &p->jugador, &p->estado, &p->log, FRTORFIN, animTorFinaliza);
        escribirEnLog(&p->log, MSJ_TORMENTAFINALIZADA);
    }

    if(p->estado.BandAtaca)
    {
        ejecutarAnimacion(&p->tablero, &p->jugador, &p->estado, &p->log, FRBANDAT, animBandidoAtaca);
        escribirEnLog(&p->log, MSJ_BANDIDOATACA);
    }

    if(p->estado.Operdido)
    {
        ejecutarAnimacion(&p->tablero, &p->jugador, &p->estado, &p->log, FROASISPE, animOasisPerdido);
        escribirEnLog(&p->log, MSJ_OASISPERDIDO);
    }

    if(p->estado.JpierdeVida)
    {
        mov = (j->posJug - 1) * - 1;
        moverElementoPorId(&p->tablero, JUGADORID, mov);
        if(p->estado.Tactiva)
        {
            moverElementoPorId(&p->tablero, idFlechaIzq, mov);
            moverElementoPorId(&p->tablero, idFlechaDer, mov);
        }
        ejecutarAnimacion(&p->tablero, &p->jugador, &p->estado, &p->log, FRJUGCAS1, animJugadorDaniado);
        disminuirVida(&p->jugador);
        escribirEnLog(&p->log, MSJ_JUGADORDANIADO);
        posicionarTableroPorIdElem(t, p->estado.IDBandDesaparecido);
    }
    if(p->estado.IDBandDesaparecido)
    {
        ejecutarAnimacion(&p->tablero, &p->jugador, &p->estado, &p->log, FRBANDES, animBandidoDesaparece);
        escribirEnLog(&p->log, MSJ_BANDIDODESAPARECE);
    }

    if(p->estado.Jgana)
    {
        ejecutarAnimacion(&p->tablero, &p->jugador, &p->estado, &p->log, FRJUGGANA, animJugGana);
        escribirEnLog(&p->log, MSJ_JUGADORGANA);
    }

    reiniciarEstado(&p->estado);
}

int  finalizarPartida(tPartida *p);


