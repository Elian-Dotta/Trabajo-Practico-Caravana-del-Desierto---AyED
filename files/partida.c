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

int  calcularMovBandido(tPartida *p)
{
    // LLAMAR A RECORRER DESDE UNA FUNCION DE TABLERO
    // RECORRER PARA CALCULAR PARA BANDIDO
    // LA ACCION VA A VERIFICAR SI ES BANDIDO -> CALCULARBANDIDO
    // SI ES BANDIDO GENERA UN MOV ALEATORIO CON EL ID DEL BANDIDO // 50 PORCIENTO SER INTELIGENTE
    // LO ENCOLA EN LA COLA ENVIADA POR CONTEXTO
    // ENVIAMOS POSICION DEL JUGADOR POR CONTEXTO
    // POR MEDIO DE RECORRERLISTADE
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
    actualizarEstadoDelJugador(&p->tablero, &p->estado, modEstado, &p->bandInteligentes);
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
        if(verVida(&p->jugador)== 0)
            p->estado.Jpierde = 1;

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
        p->estado.Jpierde = 0;
        p->corriendo = 0;
    }

    if(p->estado.Jpierde)
    {
        ejecutarAnimacion(&p->tablero, &p->jugador, &p->estado, &p->log, FRJUGPIERDE, animJugPierde);
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


