#include "partida.h"
#include "menu.h"

// INICIALIZA, FINALIZA Y MANEJA EL LOOP DEL JUEGO
int  jugarPartida()// VA A INICIALIZAR Y LUEGO VA A MANEJAR EL LOOP
{
    tPartida partida;

    inicializarPartida(&partida);

    while(partida.corriendo)
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

    crearLog(&p->log);

    crearTablero(&p->tablero, p->config, &p->bandInteligentes);

    inicializarEstado(&p->estado, p->config.max_band);

    inicializarJugador(&p->jugador, p->config.vidas_ini);

    crearCola(&p->movimientos);

    p->corriendo = 1;
}

int  dibujarEstadoDelJuego(tPartida *p)
{
    dibujarEscena(&p->tablero, &p->jugador, &p->estado, &p->log);
    return 1;
}

int  procesarEntrada(tPartida *p)
{
    tMovimiento mov;
    char        enter[8];
    int         pasos;
    char        dir;

    // 1) pedir ENTER y tirar el dado (1 a 6)
    ingresarDato("Presione ENTER para tirar el dado...", enter);
    pasos = tirarDado(1, 6);

    // 2) pedir la direccion (el menu valida que sea 'F' o 'B')
    dir = menu("Ingrese direccion (Adelante 'F' / Atras 'B'): ",
               "FB", 1, "Direccion invalida\n");

    // 3) armar el movimiento del jugador y encolarlo
    mov.id   = JUGADORID;
    mov.dir  = dir;
    mov.cant = pasos;
    ponerEnCola(&p->movimientos, &mov, sizeof(mov));

    return 1;
}

int  calcularMovBandido(tPartida *p)
{
/*
    SE PIDE RECORRER LA LISTA DE, Y BUSCAR PARA CADA CASILLA LOS BANDIDOS,
    DE ESE BANDIDO, CALCULAR SU DISTANCIA AL JUGADOR Y GUARDAR EL ID DEL QUE TENGA MENOR DISTANCIA LUEGO DE TIRADO EL DADO (SI HAY DOS BANDIDOS EN UNA CASILLA)
    RECORRIDA TODA LA LISTA Y ELEGIDO EL BANDIDO DE MENOR DISTANCIA, VER SI ESE BANDIDO ESTA EN LA LISTA DE BANDIDOS INTELIGENTES
    SI ESTA EN LA LISTA DE BANDIDOS INTELIGENTES, ENTONCES MOVER EL BANDIDO EN EL SENTIDO (DERECHA O IZQUIERDA) MAS CONVENIENTE PARA LLEGAR AL JUGADOR
    SI NO ESTA EN LA LISTA REALIZAR ALEATORIAMENTE LA ELECCION DE IR A IZQUIERDA O DERECHA (TIRAR DADO (0,1))
*/
    tElem       bandidoMenorDistancia = {0};
    unsigned    resultadoDado         = tirarDado(1,6);
    void        *parametros[4]        = {&bandidoMenorDistancia, &p->jugador->posJug, &p->config->cant_pos, &resultadoDado};
    tMovimiento movimientoBandido;

    if(NULL == *tablero)
        return 0;

    recorrerListaDE(&p->tablero, bandidoMasCercanoAJugador, parametros);

    if(0 == bandidoEncontrado.id_elem)
        return 0; //NO HAY BANDIDOS

    movimientoBandido.id   = bandidoMenorDistancia.id_elem;
    movimientoBandido.cant = resultadoDado;

    if(0 == buscarPorClaveEnLista(p->bandInteligentes, bandidoMenorDistancia.id_elem, NULL, 0, compararEnteros)){
        movimientoBandido.dir = tirarDado(0,1)?'F':'B';
    }else{
        int movDir = devolverMenorDistanciaEntreElementos(bandidoMenorDistancia.nro_casilla, p->jugador.posJug, p->config.cant_pos, resultadoDado);
        movimientoBandido.dir = movDir>0?'F':'B';
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

int  actualizarEstado(tTablero *tablero, tJugador *jugador, tEstado *estado, tLista *bandidosInteligentes)
{
    actualizarEstadoDelJugador(&p->tablero, &p->estado, modEstado, &p->bandInteligentes);
}

int  dibujarAnimacionEstado(tTablero *tablero, tJugador *jugador, tEstado *estado)
{
    int mov;

    int idFlechaIzq,
        idFlechaDer;
    if(p->estado.JganaPuntos)
    {
        ejecutarAnimacion(&p->tablero, &p->jugador, &p->estado, &p->log, FRPREMIO, animPremio, JUGADORID);
        aumentarPuntaje(&p->jugador);
        escribirEnLog(&p->log, MSJ_PUNTOS);
    }

    if(p->estado.JganaVida)
    {
        ejecutarAnimacion(&p->tablero, &p->jugador, &p->estado, &p->log, FRVIDAEX, animVidaExtra, JUGADORID);
        aumentarVida(&p->jugador);
        escribirEnLog(&p->log, MSJ_VIDA);
    }

    if(p->estado.Oobtenido)
    {
        ejecutarAnimacion(&p->tablero, &p->jugador, &p->estado, &p->log, FROASISOB, animOasisObtenido, JUGADORID);
        escribirEnLog(&p->log, MSJ_OASISOBTENIDO);
    }

    if(p->estado.Tactiva)
    {
        ejecutarAnimacion(&p->tablero, &p->jugador, &p->estado, &p->log, FRTORACT, animTorActiva, JUGADORID);
        escribirEnLog(&p->log, MSJ_TORMENTAACTIVA);
        idFlechaIzq = obtenerIdElementoPorTipo(&p->tablero, FLECHAIZQ);
        idFlechaDer = obtenerIdElementoPorTipo(&p->tablero, FLECHADER);
    }

    if(p->estado.Tfinalizada)
    {
        ejecutarAnimacion(&p->tablero, &p->jugador, &p->estado, &p->log, FRTORFIN, animTorFinaliza, JUGADORID);
        escribirEnLog(&p->log, MSJ_TORMENTAFINALIZADA);
    }

    if(p->estado.BandAtaca)
    {
        ejecutarAnimacion(&p->tablero, &p->jugador, &p->estado, &p->log, FRBANDAT, animBandidoAtaca, JUGADORID);
        escribirEnLog(&p->log, MSJ_BANDIDOATACA);
    }

    if(p->estado.Operdido)
    {
        ejecutarAnimacion(&p->tablero, &p->jugador, &p->estado, &p->log, FROASISPE, animOasisPerdido, JUGADORID);
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
        ejecutarAnimacion(&p->tablero, &p->jugador, &p->estado, &p->log, FRJUGCAS1, animJugadorDaniado, JUGADORID);
        disminuirVida(&p->jugador);
        escribirEnLog(&p->log, MSJ_JUGADORDANIADO);
        if(verVida(&p->jugador)== 0)
            p->estado.Jpierde = 1;

    }
    if(p->estado.IDBandDesaparecido)
    {
        ejecutarAnimacion(&p->tablero, &p->jugador, &p->estado, &p->log, FRBANDES, animBandidoDesaparece, p->estado.IDBandDesaparecido);
        escribirEnLog(&p->log, MSJ_BANDIDODESAPARECE);
    }

    if(p->estado.Jgana)
    {
        ejecutarAnimacion(&p->tablero, &p->jugador, &p->estado, &p->log, FRJUGGANA, animJugGana, JUGADORID);
        escribirEnLog(&p->log, MSJ_JUGADORGANA);
        p->estado.Jpierde = 0;
        p->corriendo = 0;
    }

    if(p->estado.Jpierde)
    {
        ejecutarAnimacion(&p->tablero, &p->jugador, &p->estado, &p->log, FRJUGPIERDE, animJugPierde, JUGADORID);
        escribirEnLog(&p->log, MSJ_JUGADORPIERDE);
        p->corriendo = 0;
    }

    reiniciarEstado(&p->estado);
}

int  finalizarPartida(tPartida *p)
{
    dibujarFinDePartida(&p->tablero, &p->jugador, &p->log);

    guardarPartida(&p->jugador);

    vaciarLista(&p->bandInteligentes);

    vaciarCola(&p->movimientos);

    vaciarLog(&p->log);

    destruirTablero(&p->tablero);
}


