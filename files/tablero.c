// === Modulo tablero: la ruta sobre ListaDE ===
#include "tablero.h"
#include "movimiento.h"

// Crea el tablero y lo puebla
int  crearTablero(tTablero* tablero, tConfig config, tLista *bandidosInteligentes)
{
    int idElem = 0;

    srand(time(NULL));

    crearListaDE(tablero);

    generarTablero(tablero, &idElem, config.cant_pos);

    distribuirElementos(tablero, &idElem, config, bandidosInteligentes);

    return 1;
}

// Genera casillas, inicio y salida
int  generarTablero(tListaDE* tablero, int *idElem, int cantPos)
{
    tElem elem;
    tCasilla cas;
    int contCas = 0;


    while(contCas < cantPos)
    {
        cas = crearCasilla();

        insertarAlFinalDeListaDE(tablero, &cas, sizeof(tCasilla));
        if(contCas == 0)
        {
            elem.id_elem = *idElem;
            elem.tipo_elem = INICIO;
            elem.nro_casilla = contCas + 1;
            actualizarPosRelativaListaDE(tablero, &elem, sizeof(tElem), 0, insertarEnCasilla);
            (*idElem)++;
            elem.id_elem = *idElem;
            elem.tipo_elem = JUGADOR;

            elem.nro_casilla = contCas;
            actualizarPosRelativaListaDE(tablero, &elem, sizeof(tElem), 0, insertarEnCasilla);
            (*idElem)++;
        }
        if(contCas == cantPos - 1)
        {
            elem.id_elem = *idElem;
            elem.tipo_elem = SALIDA;
            elem.nro_casilla = contCas + 1;
            actualizarPosRelativaListaDE(tablero, &elem, sizeof(tElem), 0, insertarEnCasilla);
            (*idElem)++;
        }
        contCas++;
    }

    return 1;
}

// Distribuye elementos al azar
int  distribuirElementos(tTablero* tablero, int *contElem, tConfig config, tLista *bandidosInteligentes)
{
    int elemFaltantes[] = { config.max_band,
                              config.max_prem,
                              config.max_vid_ext,
                              config.max_oasis,
                              config.max_tormenta };

    char elemTipo[] = { BANDIDO, PREMIO, VIDAEXTRA, OASIS, TORMENTA};

    int disponibles[5];
    int cantDisponibles = 0;

    for(int i = 0; i < 5; i++)
    {
        if(elemFaltantes[i])
        {
            disponibles[cantDisponibles++] = i;
        }
    }

    int cantElem = 0,
        elemInsertados = 0,
        indiceElem,
        posInsercion,
        nroCasilla = 1;

    for(indiceElem = 0; indiceElem < 5; indiceElem++)
    {
        cantElem += elemFaltantes[indiceElem];
    }

    tLista numAleatorios;
    crearLista(&numAleatorios);
    tElem elem;

    while(elemInsertados < cantElem)
    {
        posInsercion = rand() % config.cant_pos;
        indiceElem = disponibles[rand() % cantDisponibles];
        if(elemFaltantes[indiceElem])
        {
            elem.id_elem = *contElem;
            elem.tipo_elem = elemTipo[indiceElem];
            if(actualizarPosRelativaListaDE(tablero, &elem, sizeof(tElem), posInsercion, insertarSinDupCasilla)) // SI SE PUDO INSERTAR, ACTUALIZAMOS LOS INDICADORES DE FALTANTE
            {
                if(elem.tipo_elem == BANDIDO && // SI EL ELEMENTO INSERTADO ES UN BANDIDO
                   elemFaltantes[indiceElem] % 2 == 0) // SI EL BANDIDO ES UN BANDIDO PAR INGRESADO. FALTAN 4 -> PAR, FALTAN 3 -> IMPAR.
                    insertarAlFinalLista(bandidosInteligentes, &elem.id_elem, sizeof(int));

                elemFaltantes[indiceElem]--; // RESTAMOS UN ELEMENTO FALTANTE
                (*contElem)++;                 // AVANZAMOS EL INDICE DE LOS ELEMENTOS
                elemInsertados++;            // SUMAMOS UN ELEMENTO INSERTADO
            }
        }

        if(elemFaltantes[indiceElem] == 0)
        {
            int i;

            for(i = 0; i < cantDisponibles; i++)
            {
                if(disponibles[i] == indiceElem)
                    break;
            }

            for(; i < cantDisponibles - 1; i++)
                disponibles[i] = disponibles[i + 1];

            cantDisponibles--;
        }
    }

    elem.tipo_elem = INICIO;
    buscarPorClaveListaDE(tablero, &elem, sizeof(tElem), cmpCasTipoElem);
    recorrerListaDE(tablero, asignarNroCasilla, &nroCasilla);

    return 1;


}

// Mueve un elemento por id
int  moverElementoPorId(tListaDE* tablero, int id, int mov, int tamTablero)
{
    tElem elemAActualizar;
    elemAActualizar.id_elem = id;

    actualizarPorClaveListaDE(tablero, &elemAActualizar, sizeof(tElem), cmpCasIdElem, eliminarDeCasilla);
    elemAActualizar.nro_casilla = calcularNroCasilla(elemAActualizar.nro_casilla, mov, tamTablero);
    actualizarPosRelativaListaDE(tablero, &elemAActualizar, sizeof(tElem), mov, insertarEnCasilla);

    return 1;
}

// Devuelve el id de un tipo
int  obtenerIdElementoPorTipo(tTablero* tablero, char tipoElem)
{
    tElem elem;
    elem.tipo_elem = tipoElem;
    if(buscarPorClaveListaDE(tablero, &elem, sizeof(tElem), cmpCasTipoElem))
        return elem.id_elem;
    else
        return -1;
}

// Posiciona el cursor en un elemento
void posicionarTablero(tTablero* tablero, int idElem)
{
    tElem elem;
    elem.id_elem = idElem;

    buscarPorClaveListaDE(tablero, &elem, sizeof(tElem), cmpCasIdElem);
}

// Inserta un elemento al lado de otro
int  insertarAlLadoDeElemento(tTablero *tablero, int direccion, char elemRef, char elemNue)
{
    static int id = 1000; // IDs RESERVADOS PARA EFECTOS TEMPORALES
    tElem ctxElem[2];
    ctxElem[0].id_elem = id;
    ctxElem[0].tipo_elem = elemNue;
    ctxElem[1].tipo_elem = elemRef;

    if(direccion == IZQ)
        actualizarPosRelativaListaDE(tablero, ctxElem, sizeof(ctxElem), 0, insertarIzqDeElemento);
    else
        actualizarPosRelativaListaDE(tablero, ctxElem, sizeof(ctxElem), 0, insertarDerDeElemento);
    id++;
    return 1;
}

// Cambia un tipo por otro
int  cambiarElemento(tTablero *tablero, char elemAct, char elemNue)
{
    tElem ctxElem[2];
    ctxElem[0].tipo_elem = elemNue;
    ctxElem[1].tipo_elem = elemAct;

    actualizarPosRelativaListaDE(tablero, ctxElem, sizeof(ctxElem), 0, cambiarTipoElemento);
    return 1;
}

// Elimina un elemento por tipo
int  eliminarElemento(tTablero *tablero, char elemAct)
{
    tElem elim;
    elim.tipo_elem = elemAct;
    actualizarPosRelativaListaDE(tablero, &elim, sizeof(elim), 0, eliminarDeCasillaTipo);
    return 1;
}

// Indica si dos tipos coinciden
int  elementosJuntos(tTablero *tablero, const char tipo1, const char tipo2)
{
    char tipos[2];
    tipos[0] = tipo1;
    tipos[1] = tipo2;

    return buscarPorClaveListaDE(tablero, tipos, sizeof(tipos), cmpCasTipos);
}

// FUNCIONES DE ACTUALIZACION
// Calcula movimientos de los bandidos
void obtenerMovimientoBandidos(tTablero *tablero, tCola *movimientos, tLista *bandInteligentes, int posJug, int cantPos)
{
    void *contexto[4];
    contexto[0] = movimientos;
    contexto[1] = bandInteligentes;
    contexto[2] = &posJug;
    contexto[3] = &cantPos;

    recorrerListaDE(tablero, calcularMovBandido, contexto);
}

// Actualiza estado segun posicion final
void  actualizarEstadoDelJugador(tTablero* tablero, tEstado *estado, tLista *bandinteligentes)
{
    recorrerListaDE(tablero, cambiarEstado, estado);
    eliminarPorClaveLista(bandinteligentes, &estado->IDBandDesaparecido, sizeof(estado->IDBandDesaparecido), compararEnteros);
}

// Compara dos enteros
int  compararEnteros(const void *a, const void *b){

   const int * n1 = a;
   const int * n2 = b;

   return n1 - n2;
}


// Muestra el tablero por pantalla
void mostrarTablero(tTablero* tablero)
{
    if(NULL == *tablero){
        printf("\n [ %s ]", MSJ_LISTA_MAPA_VACIO);
        return;
    }
    posicionarTablero(tablero, 0); // POSICIONA EN EL INICIO
    mostrarListaDE(tablero, mostrarCasilla);
}

// Acumula en 'buf' los caracteres de los elementos de una casilla.


// Vuelca el tablero a caravana.txt
int generarArchivoTablero(tTablero* tablero, const char *path)
{
    void *ctx[2];
    int contador = 0;
    FILE *arch;

    if(NULL == *tablero)
        return 0;
    if((arch = fopen(path, "wt")) == NULL)
        return 0;

    ctx[0] = arch;
    ctx[1] = &contador;

    posicionarTablero(tablero, 0);     // arrancar desde el Inicio
    recorrerListaDE(tablero, escribirCasillaArchivo, ctx);
    fprintf(arch, "\n");

    fclose(arch);
    return 1;
}


// Libera el tablero completo
void destruirTablero(tTablero *tablero)
{
    recorrerListaDE(tablero, (Accion)destruirCasilla, NULL);
    vaciarListaDE(tablero);
}
