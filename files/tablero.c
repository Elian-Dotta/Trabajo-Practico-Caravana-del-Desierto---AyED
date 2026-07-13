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
int  generarTablero(tListaDE* tablero, int *idElem, int cantPos) // Genera casillas, inicio y salida
{
    tElem elem;
    tCasilla cas; //lista simple
    int contCas = 0;


    while(contCas < cantPos)
    {
        cas = crearCasilla(); //creo la lista en la casilla

        insertarAlFinalDeListaDE(tablero, &cas, sizeof(tCasilla)); //inserto en tablero la primer casilla(lista)
        if(contCas == 0) //inserto el inicio y el jugador
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
        if(contCas == cantPos - 1) //inserto salida
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

    char elemTipo[] = { BANDIDO, PREMIO, VIDAEXTRA, OASIS, TORMENTA}; //cargo los tipos de caracteres

    int disponibles[5]; //vector de que tipo de elementos tengo disponible
    int cantDisponibles = 0; //indica cuantos tipos hay disponible

    for(int i = 0; i < 5; i++)
    {
        if(elemFaltantes[i])
        {
            disponibles[cantDisponibles++] = i; //cargo el indice de que tipos tengo disponible
        }
    }

    int cantElem = 0,
        elemInsertados = 0,
        indiceElem,
        posInsercion,
        nroCasilla = 1;

    for(indiceElem = 0; indiceElem < 5; indiceElem++) //recorre todo el vector para saber la cantidad de elementos a insertar
    {
        cantElem += elemFaltantes[indiceElem];
    }

    tLista numAleatorios;
    crearLista(&numAleatorios);
    tElem elem;

    while(elemInsertados < cantElem)
    {
        posInsercion = rand() % config.cant_pos;
        indiceElem = disponibles[rand() % cantDisponibles]; //saco uno del vector de tipo disponibles
        if(elemFaltantes[indiceElem])
        {
            elem.id_elem = *contElem;
            elem.tipo_elem = elemTipo[indiceElem]; //cargo el char del tipo de elemento
            if(actualizarPosRelativaListaDE(tablero, &elem, sizeof(tElem), posInsercion, insertarSinDupCasilla)) // SI SE PUDO INSERTAR, ACTUALIZAMOS LOS INDICADORES DE FALTANTE
            {
                if(elem.tipo_elem == BANDIDO && // SI EL ELEMENTO INSERTADO ES UN BANDIDO
                   elemFaltantes[indiceElem] % 2 == 0) // SI EL BANDIDO ES UN BANDIDO PAR INGRESADO. FALTAN 4 -> PAR, FALTAN 3 -> IMPAR.
                    insertarAlFinalLista(bandidosInteligentes, &elem.id_elem, sizeof(int)); //LO INGRESO COMO INTELIGENTE

                elemFaltantes[indiceElem]--; // RESTAMOS UN ELEMENTO FALTANTE
                (*contElem)++;                 // AVANZAMOS EL ID DE LOS ELEMENTOS
                elemInsertados++;            // SUMAMOS UN ELEMENTO INSERTADO
            }
        }

        if(elemFaltantes[indiceElem] == 0) // si ya no quedan mas elementos de este tipo hay que sacarlos
        {
            int i;

            for(i = 0; i < cantDisponibles; i++)
            {
                if(disponibles[i] == indiceElem) //busca hasta encontrar el tipo de elemento en el vector disponible
                    break;
            }

            for(; i < cantDisponibles - 1; i++) //corro todo uno para la izquierda
                disponibles[i] = disponibles[i + 1];

            cantDisponibles--; //resto la cantidad de tipos disponibles
        }
    }

    elem.tipo_elem = INICIO;
    buscarPorClaveListaDE(tablero, &elem, sizeof(tElem), cmpCasTipoElem); //pongo el puntero al inicio
    recorrerListaDE(tablero, asignarNroCasilla, &nroCasilla); //le asigno un numero a cada casilla

    return 1;


}

// Mueve un elemento por id
int  moverElementoPorId(tListaDE* tablero, int id, int mov, int tamTablero)
{
    tElem elemAActualizar;
    elemAActualizar.id_elem = id;

    actualizarPorClaveListaDE(tablero, &elemAActualizar, sizeof(tElem), cmpCasIdElem, eliminarDeCasilla); //busca el elemento y lo borra
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

// Posiciona el "cursor" (puntero interno de la lista circular) en un elemento.
// No usa el resultado de la busqueda: lo que importa es el EFECTO COLATERAL:
// buscarPorClaveListaDE deja el puntero del tablero parado en la casilla del
// elemento con id 'idElem'. Como el tablero se dibuja empezando desde ahi,
// esto "centra la camara" en ese elemento (casi siempre el jugador).
void posicionarTablero(tTablero* tablero, int idElem)
{
    tElem elem;
    elem.id_elem = idElem;   // ficha de busqueda: solo necesito el id

    buscarPorClaveListaDE(tablero, &elem, sizeof(tElem), cmpCasIdElem);
}

// Inserta un caracter decorativo (elemNue) al lado de un elemento existente
// (elemRef). Es lo que disparan las macros INSIZQ / INSDER de las animaciones.
//   direccion = IZQ (-1) o DER (1): de que lado insertar
//   elemRef   = elemento de referencia que YA esta (ej: la 'V' de vida extra)
//   elemNue   = caracter nuevo a insertar al lado (ej: '|' flecha)
int  insertarAlLadoDeElemento(tTablero *tablero, int direccion, char elemRef, char elemNue)
{
    // 'static': conserva su valor entre llamadas. Le da a cada decorativo un id
    // unico y creciente (1000, 1001, ...), reservado para efectos temporales,
    // para que despues se lo pueda identificar y borrar sin chocar con ids reales.
    static int id = 1000; // IDs RESERVADOS PARA EFECTOS TEMPORALES

    // "Paquete" de 2 datos para el callback: [0] = el nuevo, [1] = la referencia
    tElem ctxElem[2];
    ctxElem[0].id_elem = id;       // el nuevo: su id unico
    ctxElem[0].tipo_elem = elemNue; // ...y su caracter
    ctxElem[1].tipo_elem = elemRef; // la referencia: solo el tipo, para ubicarla en la lista

    // Patron motor + callback: el motor recorre el tablero y el callback inserta
    if(direccion == IZQ)
        actualizarPosRelativaListaDE(tablero, ctxElem, sizeof(ctxElem), 0, insertarIzqDeElemento);
    else
        actualizarPosRelativaListaDE(tablero, ctxElem, sizeof(ctxElem), 0, insertarDerDeElemento);
    id++;          // proximo decorativo usara un id distinto
    return 1;
}

// Cambia un elemento existente por otro tipo (misma celda).
// Es lo que dispara la macro CAMELEM. Ej: convertir 'J' (jugador) en 'j'.
//   elemAct = el que esta ahora (referencia)
//   elemNue = el tipo nuevo que tendra
int  cambiarElemento(tTablero *tablero, char elemAct, char elemNue)
{
    tElem ctxElem[2];
    ctxElem[0].tipo_elem = elemNue;  // [0] = nuevo tipo
    ctxElem[1].tipo_elem = elemAct;  // [1] = tipo a buscar/reemplazar

    actualizarPosRelativaListaDE(tablero, ctxElem, sizeof(ctxElem), 0, cambiarTipoElemento);
    return 1;
}

// Elimina del tablero el primer elemento de un tipo dado.
// Es lo que dispara la macro ELIM. Ej: borrar un asterisco '*'.
int  eliminarElemento(tTablero *tablero, char elemAct)
{
    tElem elim;
    elim.tipo_elem = elemAct;  // solo necesito el tipo para encontrarlo
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
