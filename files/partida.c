// === Modulo partida: coordina el loop del juego ===
#include "partida.h"
#include "menu.h"

// INICIALIZA, FINALIZA Y MANEJA EL LOOP DEL JUEGO
// Inicializa y corre el loop
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


// Carga config y arma el tablero
int  inicializarPartida(tPartida *p, tJugador *jugador)// VA A CARGAR TCONFIG Y GENERAR EL TABLERO

{
    //tConfig config = { 25, 3, 2, 3, 1, 2, 3};

    cargarConfig(&p->config);

    crearLista(&p->bandInteligentes);

    crearLog(&p->log);

    crearTablero(&p->tablero, p->config, &p->bandInteligentes);

    generarArchivoTablero(&p->tablero, ARCH_CARAVANA); // consigna c: volcar el tablero a caravana.txt

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

    return 1;
}

// Dibuja la escena del turno
int  dibujarEstadoDelJuego(tPartida *p)
{
    dibujarEscena(&p->tablero, &p->jugador, &p->estado, &p->log);
    return 1;
}

// Tira dado y encola movimiento
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
        pasos = tirarDado(6, 6);
        wait(0.3);

        sprintf(buffer, "Has sacado un %d!\n", pasos);
        escribirEnLog(&p->log, buffer);
        asignarDado(&p->jugador, pasos);

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

// Encola movimientos de los bandidos
int actualizarMovimientos(tPartida *p)
{
    obtenerMovimientoBandidos(&p->tablero, &p->movimientos, &p->bandInteligentes, verPosJugador(&p->jugador), p->config.cant_pos);
    return 1;
}


// Anima los movimientos encolados
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
            if((posJug == 1 && movActual.dir == 'B') ||
               (posJug == p->config.cant_pos && movActual.dir == 'F'))
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

        wait(0.7);
        dibujarEscena(&p->tablero, &p->jugador, &p->estado, &p->log);
    }

    return 1;
}

// Calcula el nuevo estado del juego
int  actualizarEstado(tPartida *p)
{
    actualizarEstadoDelJugador(&p->tablero, &p->estado, &p->bandInteligentes);
    return 1;
}

// Anima los cambios de estado
int  dibujarAnimacionEstado(tPartida *p)
{

    int mov;

    int idAturIzq,
        idAturDer;
    if(p->estado.JganaPuntos) // 1 - CHECKEAMOS SI EL JUGADOR CAYO EN UN PREMIO.
    {
        ejecutarAnimacion(&p->tablero, &p->jugador, &p->estado, &p->log, FRPREMIO, animPremio, JUGADORID);
        aumentarPuntaje(&p->jugador);
        escribirEnLog(&p->log, MSJ_PUNTOS);
    }

    if(p->estado.JganaVida) // 2 - CHECKEAMOS SI EL JUGADOR OBTUVO UNA VIDA EXTRA.
    {
        ejecutarAnimacion(&p->tablero, &p->jugador, &p->estado, &p->log, FRVIDAEX, animVidaExtra, JUGADORID);
        aumentarVida(&p->jugador);
        escribirEnLog(&p->log, MSJ_VIDA);
    }

    // 3 - SI EL JUGADOR NO FUE ATACADO Y TIENE OASIS DEL TURNO ANTERIOR LO PIERDE DE FORMA PACIFICA.
    if(!p->estado.BandAtaca && p->estado.Operdido)
    {
        ejecutarAnimacion(&p->tablero, &p->jugador, &p->estado, &p->log, FROASISPE, animOasisPerdido, JUGADORID);
        escribirEnLog(&p->log, MSJ_OASISPERDIDO);
    }

    // 4 - SI EL JUGADOR CAE EN UN OASIS LO OBTIENE, SI TENIA DE ANTES LO OBTIENE DESPUES DE PERDERLO.
    if(p->estado.Oobtenido)
    {
        if(p->estado.tieneOasis)
        {   // 4.5 - SI EL JUGADOR TENIA OASIS LO PIERDE ANTES DE OBTENER UNO NUEVO, NO SE ACUMULAN OASIS.
            ejecutarAnimacion(&p->tablero, &p->jugador, &p->estado, &p->log, FROASISPE, animOasisPerdido, JUGADORID);
            escribirEnLog(&p->log, MSJ_OASISPERDIDO);
        }
        ejecutarAnimacion(&p->tablero, &p->jugador, &p->estado, &p->log, FROASISOB, animOasisObtenido, JUGADORID);
        escribirEnLog(&p->log, MSJ_OASISOBTENIDO);
    }

    // 5 - ACTIVAMOS EL EFECTO DE LA TORMENTA.
    if(p->estado.Tactiva)
    {
        ejecutarAnimacion(&p->tablero, &p->jugador, &p->estado, &p->log, FRTORACT, animTorSeActiva, JUGADORID);
        escribirEnLog(&p->log, MSJ_TORMENTAACTIVA);
    }

    // 6 - FINALIZAMOS EL EFECTO DE LA TORMENTA
    if(p->estado.Tfinalizada)
    {
        ejecutarAnimacion(&p->tablero, &p->jugador, &p->estado, &p->log, FRTORFIN, animTorFinaliza, JUGADORID);
        escribirEnLog(&p->log, MSJ_TORMENTAFINALIZADA);
    }

    // 7 - SI ESTAMOS EN LA CASILLA DE LA SALIDA, NO NOS PUEDEN ATACAR Y GANAMOS
    if(p->estado.Jgana)
    {
        ejecutarAnimacion(&p->tablero, &p->jugador, &p->estado, &p->log, FRJUGGANA, animJugGana, JUGADORID);
        escribirEnLog(&p->log, MSJ_JUGADORGANA);
        p->estado.Jpierde = 0;
        p->corriendo = 0;
    }
    else // 8 - SI NO GANAMOS PROCESAMOS ATAQUES DE BANDIDOS
    {
        // 9 - SI EL BANDIDO ATACA Y NO PERDEMOS OASIS, SIMPLEMENTE SE PIERDE VIDA Y EL JUGADOR SE MUEVE AL INICIO
        if(p->estado.BandAtaca && !p->estado.Operdido)
        {
            ejecutarAnimacion(&p->tablero, &p->jugador, &p->estado, &p->log, FRBANDAT, animBandidoAtaca, JUGADORID);
            escribirEnLog(&p->log, MSJ_BANDIDOATACA);
        } // 10 - SI EL BANDIDO ATACA Y PERDEMOS OASIS
        else if(p->estado.BandAtaca && p->estado.Operdido)
        {
            // 11 - EL BANDIDO ATACA
            ejecutarAnimacion(&p->tablero, &p->jugador, &p->estado, &p->log, FRBANDAT, animBandidoAtaca, JUGADORID);
            escribirEnLog(&p->log, MSJ_BANDIDOATACA);
            // 12 - JUGADOR PIERDE EL OASIS
            ejecutarAnimacion(&p->tablero, &p->jugador, &p->estado, &p->log, FROASISPE, animOasisPerdido, JUGADORID);
            escribirEnLog(&p->log, MSJ_OASISPERDIDO);
            // 13 - SI HAY OTRO BANDIDO EN LA CASILLA, ESTE TAMBIEN ATACA AL JUGADOR
            if(p->estado.Bandidos > 1)
            {
                if(p->estado.IDBandDesaparecido[0]) // 14 - DESAPARECE EL PRIMER BANDIDO QUE ATACO.
                {
                    ejecutarAnimacion(&p->tablero, &p->jugador, &p->estado, &p->log, FRBANDES, animBandidoDesaparece, p->estado.IDBandDesaparecido[0]);
                    escribirEnLog(&p->log, MSJ_BANDIDODESAPARECE);
                    // 15 - JUGADOR VUELVE A SU FORMA
                    ejecutarAnimacion(&p->tablero, &p->jugador, &p->estado, &p->log, FRJUGCAS1, animJugadorDaniado, JUGADORID);
                }
                // 16 - EL SEGUNDO BANDIDO ATACA AL JUGADOR QUE NO TIENE OASIS
                ejecutarAnimacion(&p->tablero, &p->jugador, &p->estado, &p->log, FRBANDAT, animBandidoAtaca, JUGADORID);
                escribirEnLog(&p->log, MSJ_BANDIDOATACA);
            }
        }
        // 17 - EL JUGADOR EFECTIVAMENTE PERDIO VIDA Y VUELVE A LA CASILLA INICIAL
        if(p->estado.JpierdeVida)
        {
            // El jugador vuelve al Campamento Inicial (casilla 1). 'posJug' esta en
            // sincronia con la casilla real, asi que este desplazamiento la lleva a 1.
            mov = (p->jugador.posJug - 1) * - 1;
            // 18 - SI SUCEDIO EN UN TURNO QUE ESTABA ATURDIDO LLEVAMOS TAMBIEN EL EFECTO DE ATURDIMIENTO
            if(p->estado.Tactiva)
            {
                idAturIzq = obtenerIdElementoPorTipo(&p->tablero, ATURDIDOIZQ);
                idAturDer = obtenerIdElementoPorTipo(&p->tablero, ATURDIDODER);
                moverElementoPorId(&p->tablero, idAturIzq, mov, p->config.cant_pos);
                moverElementoPorId(&p->tablero, JUGADORID, mov, p->config.cant_pos);
                moverElementoPorId(&p->tablero, idAturDer, mov, p->config.cant_pos);
            }
            else
                moverElementoPorId(&p->tablero, JUGADORID, mov, p->config.cant_pos);
            // Mantener la posicion logica sincronizada con la ficha: sin esto, 'posJug'
            // quedaba con el valor viejo y se desincronizaba de la casilla real (el
            // jugador "rebotaba"/teletransportaba en el medio del tablero).
            p->jugador.posJug = 1;
            // 19 - JUGADOR VUELVE A SU FORMA EN LA CASILLA 1
            ejecutarAnimacion(&p->tablero, &p->jugador, &p->estado, &p->log, FRJUGCAS1, animJugadorDaniado, JUGADORID);
            disminuirVida(&p->jugador);
            escribirEnLog(&p->log, MSJ_JUGADORDANIADO);
            if(verVida(&p->jugador)== 0) // 20 - SI LA VIDA LLEGA A CERO EL JUGADOR PIERDE
                p->estado.Jpierde = 1;

        }
        // 21 - SI PASO EL CASO 9, SIMPLEMENTE DESAPARECE EL PRIMER BANDIDO
        if(p->estado.IDBandDesaparecido[0] && !p->estado.Operdido)
        {
            ejecutarAnimacion(&p->tablero, &p->jugador, &p->estado, &p->log, FRBANDES, animBandidoDesaparece, p->estado.IDBandDesaparecido[0]);
            escribirEnLog(&p->log, MSJ_BANDIDODESAPARECE);
        } // 22 - SI EL JUGADOR TENIA OASIS, ENTONCES PERDIO VIDA POR EL SEGUNDO BANDIDO ASI QUE DESAPARECE ESTE ULTIMO.
        else if(p->estado.IDBandDesaparecido[1])
        {
            ejecutarAnimacion(&p->tablero, &p->jugador, &p->estado, &p->log, FRBANDES, animBandidoDesaparece, p->estado.IDBandDesaparecido[1]);
            escribirEnLog(&p->log, MSJ_BANDIDODESAPARECE);
        }


        // 23 - POR ULTIMO TENEMOS EN CUENTA SI EL JUGADOR PERDIO LA PARTIDA.
        if(p->estado.Jpierde)
        {
            ejecutarAnimacion(&p->tablero, &p->jugador, &p->estado, &p->log, FRJUGPIERDE, animJugPierde, JUGADORID);
            escribirEnLog(&p->log, MSJ_JUGADORPIERDE);
            p->corriendo = 0;
        }

    }

    reiniciarEstado(&p->estado);

    return 1;
}

// Cierra la partida y guarda
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


