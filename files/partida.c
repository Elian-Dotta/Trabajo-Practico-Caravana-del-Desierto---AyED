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

        procesarEntrada(&partida); // JUGADOR TIRA DADO Y ELIGE DIRECCION, SE ENCOLAN LOS MOVIMIENTOS

        actualizarMovimientos(&partida); // SE CALCULA Y ENCOLAN LOS MOVIMIENTO DE LOS BANDIDOS

        dibujarAnimacionMov(&partida); // SE DESENCOLA LOS MOVIMIENTOS Y SE LOS DIBUJA PASO A PASO

        actualizarEstado(&partida); // SE ACTUALIZA EL ESTADO DE JUEGO EN LA POSICION FINAL DE LOS ELEMENTOS, SE PASAN BOOLEANOS CON EL ESTADO DEL JUEGO A LA SIG FUNCION

        dibujarAnimacionEstado(&partida); // SE ANIMA EL CAMBIO DE ESTADO DE ACUERDO A LO QUE INDIQUEN LOS BOOLEANOS
    }

    finalizarPartida(&partida); // DEBERIA IMPRIMIR EL HISTORICO DE MOVIMIENTOS DEL JUGADOR Y GUARDAR EN ARCHIVO LAS ESTADISTICAS DE LA PARTIDA
}

// FUNCIONES LLAMADAS POR JUGAR PARTIDA


int  inicializarPartida(tPartida *p, tJugador *jugador)// VA A CARGAR TCONFIG Y GENERAR EL TABLERO

{
    //tConfig config = { 25, 3, 2, 3, 1, 2, 3};

    cargarConfig(&p->config);

    crearLista(&p->bandInteligentes);

    crearLog(&p->log);

    crearTablero(&p->tablero, p->config, &p->bandInteligentes);

    inicializarEstado(&p->estado);

    p->jugador = *jugador;

    asignarVida(&p->jugador, p->config.vidas_ini);

    crearCola(&p->movimientos);

    p->corriendo = 1;

    mostrar("INICIANDO PARTIDA...\n");
    wait(1);
    mostrar("CARGANDO: 1%\n");
    wait(1);
    mostrar("CARGANDO: 2%\n");
    wait(1);
    mostrar("CARGANDO: 3%\n");
    wait(0.4);
    mostrar("CARGANDO: 57%\n");
    wait(0.3);
    mostrar("CARGANDO: 99%\n");
    wait(0.5);
    mostrar("CARGANDO: 99,999%\n");
    wait(0.2);
    mostrar("CARGANDO: 100%\n");
    wait(0.1);
}

int  dibujarEstadoDelJuego(tPartida *p)
{
    dibujarEscena(&p->tablero, &p->jugador, &p->estado, &p->log);
    return 1;
}

int  procesarEntrada(tPartida *p)
{
    tMovimiento mov;
    char        enter;
    int         pasos;
    char        dir;
    char        buffer[TAM];
    if(!p->estado.tieneTormenta)
    {
        // 1) pedir ENTER y tirar el dado (1 a 6)
        escribirEnLog(&p->log, "Presione ENTER para tirar el dado...\n");
        dibujarEscena(&p->tablero, &p->jugador, &p->estado, &p->log);

        scanf("%c", &enter);
        pasos = tirarDado(1, 6);
        wait(0.3);

        sprintf(buffer, "Obtuviste un %d\n", pasos);
        escribirEnLog(&p->log, buffer);

        escribirEnLog(&p->log, "Ingrese direccion (Adelante 'F' / Atras 'B'): \n");
        dibujarEscena(&p->tablero, &p->jugador, &p->estado, &p->log);

        // 2) pedir la direccion (el menu valida que sea 'F' o 'B')
        dir = menu("",
                   "FB", 1, "Direccion invalida\n");

        // 3) armar el movimiento del jugador y encolarlo
        mov.id   = JUGADORID;
        mov.dir  = dir;
        mov.cant = pasos;
        aumentarMovimiento(&p->jugador);
        guardarMovimientoJugador(&p->jugador, &mov);
        ponerEnCola(&p->movimientos, &mov, sizeof(mov));
    }


    return 1;
}

int actualizarMovimientos(tPartida *p)
{
    obtenerMovimientoBandidos(&p->tablero, &p->movimientos, &p->bandInteligentes, verPosJugador(&p->jugador), p->config.cant_pos);
}


int  dibujarAnimacionMov(tPartida *p)
{
    // HAY QUE DESENCOLAR LOS MOVIMIENTOS, E IR RESTANDOLES UNO PARA PROCESAR MOVIMIENTO POR MOVIMIENTO EN CADA FRAME
    // SE PUEDE USAR LA CANTIDAD DE BANDIDOS PARA IR CALCULANDO EL MOMENTO DONDE APARECE EL JUGADOR
    // O CAMBIAR LA ESTRUCTURA TMOV PARA AÑADIR EL ID, EL UNICO USO SERIA ESTE, PARA CALCULAR EL MOV DE LOS BANDIDOS NO SE NECESITA ID EN EL TMOV
    tMovimiento movActual;
    int movRelativo;
    char buffer[TAM];
    int posJug;

    int idEscudoIzq,
        idEscudoDer;

    if(p->estado.tieneOasis)
    {
        idEscudoIzq = obtenerIdElementoPorTipo(&p->tablero, ESCUDOIZQ);
        idEscudoDer = obtenerIdElementoPorTipo(&p->tablero, ESCUDODER);
    }

    // PENSE EN DIBUJAR UNA SECUENCIA ENTERA DE PASOS, OSEA CUANDO TODOS ELEMENTOS DEN UN PASO, DIBUJAR, PERO AHORA PENSE QUE ESTARIA BUENO DIBUJAR CADA PASO INDIVIDUALMENTE

    while(!colaVacia(&p->movimientos))
    {
        sacarDeCola(&p->movimientos, &movActual, sizeof(movActual));



        if(movActual.id == JUGADORID)
        {
            posJug = verPosJugador(&p->jugador);
            if(posJug == 1 && movActual.dir == 'B' ||
               posJug == p->config.cant_pos && movActual.dir == 'F')
                cambiarDireccion(&movActual);
            modificarPosJug(&p->jugador, movActual.dir);
        }

        // movRelativo = mov.dir == 'F'? 1 : -1; // ESTA FORMA UTILIZA EL CAMPO DE LA ESTRUCTURA Y DEJA EL CODIGO MEDIO CRIPTICO AL USAR EL OPERADOR TERNARIO
        movRelativo = PASO * calcularDireccion(movActual.dir); // DEVUELVE 1 O -1 PARA MULTIPLICAR EL NUMERO DE CASILLAS POR LA DIRECCION



        if(movActual.id == JUGADORID && p->estado.tieneOasis &&
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
            /*
            if(movActual.id == JUGADORID && (elementosJuntos(&p->tablero, JUGADOR, INICIO) ||
                                             elementosJuntos(&p->tablero, JUGADOR, SALIDA)) &&
               )
            */
            ponerEnCola(&p->movimientos, &movActual, sizeof(movActual));
        }
        if(movActual.id == JUGADORID)
        {
            snprintf(buffer, TAM, "Jugador se movio a la %s\n", movActual.dir == 'F'? "derecha" : "izquierda");
            escribirEnLog(&p->log, buffer);
        }
        else
        {
            snprintf(buffer, TAM, "Un bandido se movio a la %s\n", movActual.dir == 'F'? "derecha" : "izquierda");
            escribirEnLog(&p->log, buffer);
        }

        wait(1);
        dibujarEscena(&p->tablero, &p->jugador, &p->estado, &p->log);
    }

    return 1;
}

int  actualizarEstado(tPartida *p)
{
    actualizarEstadoDelJugador(&p->tablero, &p->estado, &p->bandInteligentes);
}

int  dibujarAnimacionEstado(tPartida *p)
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

    if(!p->estado.BandAtaca && p->estado.Operdido)
    {
        ejecutarAnimacion(&p->tablero, &p->jugador, &p->estado, &p->log, FROASISPE, animOasisPerdido, JUGADORID);
        escribirEnLog(&p->log, MSJ_OASISPERDIDO);
    }

    if(p->estado.Oobtenido)
    {
        ejecutarAnimacion(&p->tablero, &p->jugador, &p->estado, &p->log, FROASISOB, animOasisObtenido, JUGADORID);
        escribirEnLog(&p->log, MSJ_OASISOBTENIDO);
    }

    if(p->estado.Tactiva)
    {
        ejecutarAnimacion(&p->tablero, &p->jugador, &p->estado, &p->log, FRTORACT, animTorSeActiva, JUGADORID);
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


    if(p->estado.BandAtaca && p->estado.Operdido)
    {
        ejecutarAnimacion(&p->tablero, &p->jugador, &p->estado, &p->log, FROASISPE, animOasisPerdido, JUGADORID);
        escribirEnLog(&p->log, MSJ_OASISPERDIDO);

        if(p->estado.Bandidos > 1)
        {
            if(p->estado.IDBandDesaparecido[0])
            {
                ejecutarAnimacion(&p->tablero, &p->jugador, &p->estado, &p->log, FRBANDES, animBandidoDesaparece, p->estado.IDBandDesaparecido[0]);
                escribirEnLog(&p->log, MSJ_BANDIDODESAPARECE);
            }
            ejecutarAnimacion(&p->tablero, &p->jugador, &p->estado, &p->log, FRBANDAT, animBandidoAtaca, JUGADORID);
            escribirEnLog(&p->log, MSJ_BANDIDOATACA);
        }
    }

    if(p->estado.JpierdeVida)
    {
        mov = (p->jugador.posJug - 1) * - 1;
        moverElementoPorId(&p->tablero, JUGADORID, mov, p->config.cant_pos);
        if(p->estado.Tactiva)
        {
            moverElementoPorId(&p->tablero, idFlechaIzq, mov, p->config.cant_pos);
            moverElementoPorId(&p->tablero, idFlechaDer, mov, p->config.cant_pos);
        }
        ejecutarAnimacion(&p->tablero, &p->jugador, &p->estado, &p->log, FRJUGCAS1, animJugadorDaniado, JUGADORID);
        disminuirVida(&p->jugador);
        escribirEnLog(&p->log, MSJ_JUGADORDANIADO);
        if(verVida(&p->jugador)== 0)
            p->estado.Jpierde = 1;

    }
    if(p->estado.IDBandDesaparecido[0] && !p->estado.Operdido)
    {
        ejecutarAnimacion(&p->tablero, &p->jugador, &p->estado, &p->log, FRBANDES, animBandidoDesaparece, p->estado.IDBandDesaparecido[0]);
        escribirEnLog(&p->log, MSJ_BANDIDODESAPARECE);
    }
    else if(p->estado.IDBandDesaparecido[1])
    {
        ejecutarAnimacion(&p->tablero, &p->jugador, &p->estado, &p->log, FRBANDES, animBandidoDesaparece, p->estado.IDBandDesaparecido[1]);
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


