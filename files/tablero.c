#include "tablero.h"

int  crearTablero(tTablero* tablero, tConfig config, tLista *bandidosInteligentes)
{
    int idElem = 0;

    srand(time(NULL));

    crearListaDE(tablero);

    generarTablero(tablero, &idElem, config.cant_pos);

    distribuirElementos(tablero, &idElem, config, bandidosInteligentes);
}

int  generarTablero(tListaDE* tablero, int *idElem, int cantPos)
{
    tElem elem;
    int contCas = 0;

    while(contCas < cantPos)
    {
        insertarAlFinalDeListaDE(tablero, crearCasilla(), sizeof(tCasilla));
        if(contCas == 0)
        {
            elem.id_elem = *idElem;
            elem.tipo_elem = INICIO;
            elem.nro_casilla = contCas;
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
            elem.nro_casilla = contCas;
            actualizarPosRelativaListaDE(tablero, &elem, sizeof(tElem), 0, insertarEnCasilla);
            (*idElem)++;
        }
        contCas++;
    }
}

int  distribuirElementos(tTablero* tablero, int *contElem, tConfig config, tLista *bandidosInteligentes)
{
    int elemFaltantes[] = { config.max_band,
                              config.max_prem,
                              config.max_vid_ext,
                              config.max_oasis,
                              config.max_tormenta };

    char elemTipo[] = { BANDIDO, PREMIO, VIDAEXTRA, OASIS, TORMENTA};
    int cantElem = 0,
        elemInsertados = 0,
        indiceElem,
        posInsercion,
        nroCasilla = 0;

    for(indiceElem = 0; indiceElem < 5; indiceElem++)
    {
        cantElem += elemFaltantes[indiceElem];
    }

    tLista numAleatorios;
    crearLista(&numAleatorios);
    int numAle;
    tElem elem;

    while(elemInsertados < cantElem)
    {
        posInsercion = rand() % config.cant_pos;
        indiceElem = rand() % 5;
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
    }

    elem.tipo_elem = INICIO;
    buscarPorClaveListaDE(tablero, &elem, sizeof(tElem), cmpCasTipoElem);
    recorrerListaDE(tablero, asignarNroCasilla, &nroCasilla);

    return 1;

/* // VERSION ANTERIOR, CON UNICO ELEMENTO POR CASILLA
     CON NUMEROS ALEATORIOS PREDEFINIDOS PARA LA POSICION
     CON ACCESO POR INDICE SIMIL VECTOR
     CON LOGICA ANCLADA A LA FUNCION DE GENERACION

    while(elemInsertados < cantElem)
    {
        numAle = (rand() % config.cant_pos - 1 ) + 1;
        if(insertarOrdenado(&numAleatorios, &numAle, sizeof(int), cmpInt, 0, NULL))
            elemInsertados++;
    }

    elemInsertados = 0;

    while(elemInsertados < cantElem)
    {
        sacarDeCola(&numAleatorios, &pos, sizeof(int));
        i = rand() % 5;
        if(elemFaltantes[i])
        {
            elemFaltantes[i]--;
            elem.id_elem = *idElem;
            (*idElem)++;
            elem.tipo_elem = elemTipo[i];

            actualizarPosLista(tablero, &elem, sizeof(tElem), pos, insertarEnCasilla);
            elemInsertados++;
        }
        else
        {
            ponerEnCola(&numAleatorios, &pos, sizeof(int));
        }
    }
*/

}

int  moverElementoPorId(tListaDE* tablero, int id, int mov)
{
    tElem elemAActualizar;
    elemAActualizar.id_elem = id;

    actualizarPorClaveListaDE(tablero, &elemAActualizar, sizeof(tElem), cmpCasIdElem, eliminarDeCasilla); // ESTA FUNCION DEVUELVE EL DATO SIN ACTUALIZAR
    elemAActualizar.nro_casilla+=mov;
    actualizarPosRelativaListaDE(tablero, &elemAActualizar, sizeof(tElem), mov, insertarEnCasilla);

    return 1;
}

int  obtenerIdElementoPorTipo(tTablero* tablero, char tipoElem)
{
    tElem elem;
    elem.tipo_elem = tipoElem;
    if(buscarPorClaveListaDE(tablero, &elem, sizeof(tElem), cmpCasTipoElem))
        return elem.id_elem;
    else
        return -1;
}

void posicionarTablero(tTablero* tablero, int idElem)
{
    tElem elem;
    elem.id_elem = idElem;

    buscarPorClaveListaDE(tablero, &elem, sizeof(tElem), cmpCasIdElem);
}

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
}

int  cambiarElemento(tTablero *tablero, char elemAct, char elemNue)
{
    tElem ctxElem[2];
    ctxElem[0].tipo_elem = elemNue;
    ctxElem[1].tipo_elem = elemRef;

    actualizarPosRelativaListaDE(tablero, ctxElem, sizeof(ctxElem), 0, cambiarTipoElemento);
}

int  eliminarElemento(tTablero *tablero, char elemAct)
{
    tElem elim;
    elim.tipo_elem = elemAct;
    actualizarPosRelativaListaDE(tablero, &elim, sizeof(elim), 0, eliminarDeCasilla);
}

int  generarMovBandido(tTablero* tablero, tCola *mov)
{
    //recorrerListaDE()

    return 0;
}

int  elementosJuntos(tTablero *tablero, const char tipo1, const char tipo2)
{
    char tipos[2];
    tipos[0] = tipo1;
    tipos[1] = tipo2;

    return buscarPorClaveListaDE(tablero, tipos, sizeof(tipos), cmpCasTipos);
}

void  actualizarEstadoDelJugador(tTablero* tablero, int posJug, tEstado *estado, ModificarEstado modEstado, tLista *bandinteligentes)
{
    tElem jugador;
    jugador.id_elem=1;
    buscarPorClaveListaDE(tablero,&jugador,sizeof(tElem),cmpElem,cambiarEstado,estado);

    eliminarPorClave(bandinteligentes,estado->IDBandDesaparecido,sizeof(estado->IDBandDesaparecido),cmpElem);
}

int  compararEnteros(const void *a, const void *b){

   const int * n1 = a;
   const int * n2 = b;

   return n1 - n2;
}

tTablero posicionarTablero(tTablero* tablero, int idElemPosicion){ //Recordar que tTablero es tNodo*
/*
    Funcion que devuelve la direccion de memoria del nodo que tiene en su listaSE un tElem de ID "idPosicion".
        -> Para posicionar el nodoDE al inicio, este nodo sera aquel que en su listaSE (dentro del campo dato) tiene un elemento con ID 0.
*/
    if(NULL == *tablero)
        return NULL;

    return buscarNodoPorClaveEnListaDE(tablero, &idElemPosicion, elementoEnCasilla);
}

void mostrarTablero(tTablero* tablero){

    tTablero tableroInicio = NULL;

    if(NULL == *tablero){
        printf("\n [ %s ]", MSJ_LISTA_MAPA_VACIO);
        return;
    }
    tableroInicio = posicionarTablero(tablero, 0);
    mostrarListaDE(&tableroInicio, mostrarCasilla);
}

void convertirMapaACadena(tTablero *tablero, char *buffer, unsigned orientacion, unsigned indice){
/*
    Esta es una funcion que recibe un buffer y transforma el tablero en una cadena de texto, que puede usarse
    para mostrarla por stdout o bien para escribir el archivo caravana.txt de diferentes formas.
    Tiene los valores de parametros:
    -> Valores de Orientacion: 0 (Vertical) - 1 (Horizontal)
    -> Valores de Indice: 0 (Sin habilitar) - 1 (Habilitado)
    El buffer debe ser el adecuado en tam.
*/
    if(NULL == *tablero || NULL == buffer)
        return;
    if(0 != indice && 1 != indice)
        return;
    if(0 != orientacion && 1 != orientacion)
        return;

    switch(orientacion){
        case 0: { // Vertical
            if(!indice){
                recorrerListaDE(tablero, buffer, convertirMapaACadenaVerticalSinIndice);
                return;
            }
            recorrerListaDE(tablero, buffer, convertirMapaACadenaVerticalConIndice);
            corregirCadenadeMapaConIndice(buffer);
        }break;

        case 1: { // Horizontal
            if(!indice){
                recorrerListaDE(tablero, buffer, convertirMapaACadenaHorizontalSinIndice);
                return;
            }
            recorrerListaDE(tablero, buffer, convertirMapaACadenaHorizontalConIndice);
            corregirCadenadeMapaConIndice(buffer);
        }break;
    }
}


