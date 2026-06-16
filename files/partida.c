#include "partida.h"
#include "menu.h"

// INICIALIZA, FINALIZA Y MANEJA EL LOOP DEL JUEGO
void jugarPartida(tJugador *jugador)// VA A INICIALIZAR Y LUEGO VA A MANEJAR EL LOOP
{
    tPartida partida;

    inicializarPartida(&partida, jugador);

    while(partida.corriendo)
    {
        dibujarEstadoDelJuego(&partida); // ESTADO PARA LA ELECCION DEL JUGADOR

        // si quedo aturdido por una tormenta, pierde este turno (no mueve), pero los bandidos si
        partida.enRecuperacion = partida.saltarTurno;
        partida.saltarTurno = 0;
        if(partida.enRecuperacion)
            escribirEnLog(&partida.log, MSJ_TURNO_PERDIDO);
        else
            procesarEntrada(&partida); // JUGADOR TIRA DADO Y ELIGE DIRECCION, SE ENCOLAN LOS MOVIMIENTOS

        actualizarMovimientos(&partida); // SE CALCULA Y ENCOLAN LOS MOVIMIENTO DE LOS BANDIDOS

        dibujarAnimacionMov(&partida); // SE DESENCOLA LOS MOVIMIENTOS Y SE LOS DIBUJA PASO A PASO

        actualizarEstado(&partida); // SE ACTUALIZA EL ESTADO DE JUEGO EN LA POSICION FINAL DE LOS ELEMENTOS, SE PASAN BOOLEANOS CON EL ESTADO DEL JUEGO A LA SIG FUNCION

        dibujarAnimacionEstado(&partida); // SE ANIMA EL CAMBIO DE ESTADO DE ACUERDO A LO QUE INDIQUEN LOS BOOLEANOS
    }

    finalizarPartida(&partida); // DEBERIA IMPRIMIR EL HISTORICO DE MOVIMIENTOS DEL JUGADOR Y GUARDAR EN ARCHIVO LAS ESTADISTICAS DE LA PARTIDA

    *jugador = partida.jugador; // devuelve al menu las estadisticas actualizadas de la partida
}

// FUNCIONES LLAMADAS POR JUGAR PARTIDA


int  inicializarPartida(tPartida *p, tJugador *jugador)// VA A CARGAR TCONFIG Y GENERAR EL TABLERO

{
    //tConfig config = { 25, 3, 2, 3, 1, 2, 3};
    p->jugador = *jugador;   // se conserva nombre/nick del jugador del menu

    // estadisticas frescas para esta partida (no arrastrar las de la partida anterior)
    p->jugador.puntaje = 0;
    p->jugador.cantMov = 0;
    p->jugador.posJug  = 1;
    vaciarCola(&p->jugador.hisMovJugador);   // historial de movimientos vacio

    cargarConfig(&p->config);

    crearLista(&p->bandInteligentes);

    crearLog(&p->log);

    crearTablero(&p->tablero, p->config, &p->bandInteligentes);

    inicializarEstado(&p->estado);

    asignarVida(&p->jugador, p->config.vidas_ini);

    crearCola(&p->movimientos);

    p->corriendo = 1;
    p->saltarTurno = 0;
    p->enRecuperacion = 0;

    return 1;
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

    char        msjDado[40];

    // 1) pedir ENTER y tirar el dado (1 a 6)
    ingresarDato("Presione ENTER para tirar el dado...", enter);
    pasos = tirarDado(1, 6);

    snprintf(msjDado, sizeof(msjDado), "Sacaste un %d!\n", pasos);
    mostrar(msjDado);

    // 2) pedir la direccion (el menu valida que sea 'F' o 'B')
    dir = menu("Ingrese direccion (Adelante 'F' / Atras 'B'): ",
               "FB", 1, "Direccion invalida\n");

    // 3) armar el movimiento del jugador y encolarlo
    mov.id   = JUGADORID;
    mov.dir  = dir;
    mov.cant = pasos;
    ponerEnCola(&p->movimientos, &mov, sizeof(mov));

    // registrar el movimiento del jugador (contador + historial FX/BX)
    aumentarMovimiento(&p->jugador);
    guardarMovimientoJugador(&p->jugador, &mov);

    return 1;
}

int actualizarMovimientos(tPartida *p)
{
    obtenerMovimientoBandidos(&p->tablero, &p->movimientos, &p->bandInteligentes, verPosJugador(&p->jugador), p->config.cant_pos);
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
            moverElementoPorId(&p->tablero, idEscudoIzq, movRelativo, p->config.cant_pos);
            moverElementoPorId(&p->tablero, movActual.id, movRelativo, p->config.cant_pos);
            moverElementoPorId(&p->tablero, idEscudoDer, movRelativo, p->config.cant_pos);
        }
        else
        {
            moverElementoPorId(&p->tablero, movActual.id, movRelativo, p->config.cant_pos);
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
        pausaFrame();
    }
    return 1;
}

int  actualizarEstado(tPartida *p)
{
    actualizarEstadoDelJugador(&p->tablero, &p->estado, &p->bandInteligentes);
    return 1;
}

int  dibujarAnimacionEstado(tPartida *p)
{
    int protegido = p->estado.Oactivo;   // inmunidad obtenida al pasar por un oasis el turno anterior
    int protegidoProx;

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

    // TORMENTA: aturde y hace perder el proximo turno, salvo proteccion del oasis
    if(p->estado.Tactiva)
    {
        if(p->enRecuperacion)               // este turno era el perdido: se recupera
            escribirEnLog(&p->log, MSJ_TORMENTAFINALIZADA);
        else if(protegido)                  // el oasis anula la tormenta
            escribirEnLog(&p->log, MSJ_TORMENTA_PROTEGIDO);
        else
        {
            ejecutarAnimacion(&p->tablero, &p->jugador, &p->estado, &p->log, FRTORACT, animTorSeActiva, JUGADORID);
            escribirEnLog(&p->log, MSJ_TORMENTAACTIVA);
            p->saltarTurno = 1;             // perdera el proximo turno
        }
    }

    // BANDIDO: el jugador pierde una vida, salvo proteccion del oasis
    if(p->estado.JpierdeVida)
    {
        if(protegido)
            escribirEnLog(&p->log, MSJ_BANDIDO_PROTEGIDO);
        else
        {
            if(p->estado.BandAtaca)
                ejecutarAnimacion(&p->tablero, &p->jugador, &p->estado, &p->log, FRBANDAT, animBandidoAtaca, JUGADORID);
            ejecutarAnimacion(&p->tablero, &p->jugador, &p->estado, &p->log, FRJUGCAS1, animJugadorDaniado, JUGADORID);
            disminuirVida(&p->jugador);
            escribirEnLog(&p->log, MSJ_JUGADORDANIADO);
            if(p->estado.IDBandDesaparecido)
            {
                ejecutarAnimacion(&p->tablero, &p->jugador, &p->estado, &p->log, FRBANDES, animBandidoDesaparece, p->estado.IDBandDesaparecido);
                escribirEnLog(&p->log, MSJ_BANDIDODESAPARECE);
            }
            if(verVida(&p->jugador) == 0)
                p->estado.Jpierde = 1;
            else
            {
                // el jugador vuelve al campamento inicial (casilla 1)
                tElem jug;
                jug.id_elem = JUGADORID;
                buscarPorClaveListaDE(&p->tablero, &jug, sizeof(tElem), cmpCasIdElem);
                moverElementoPorId(&p->tablero, JUGADORID, 1 - jug.nro_casilla, p->config.cant_pos);
                modificarPosJug(&p->jugador, 1);
            }
        }
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

    // la proteccion del oasis dura el turno SIGUIENTE al que se pisa el oasis
    protegidoProx = p->estado.Oobtenido ? 1 : 0;

    reiniciarEstado(&p->estado);

    p->estado.Oactivo = protegidoProx;   // reiniciarEstado no toca Oactivo

    return 1;
}

int  finalizarPartida(tPartida *p)
{
    dibujarFinDePartida(&p->tablero, &p->jugador, &p->log);

    guardarPartida(&p->jugador);

    vaciarLista(&p->bandInteligentes);

    vaciarCola(&p->movimientos);

    vaciarLog(&p->log);

    destruirTablero(&p->tablero);

    return 1;
}


