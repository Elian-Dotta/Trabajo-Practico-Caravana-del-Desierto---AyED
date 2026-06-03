#include "tablero.h"

int  crearTablero(tListaDE* tablero, tConfig config)
{
    int idElem = 0;

    srand(time(NULL));

    crearListaDE(tablero);

    generarTablero(tablero, &idElem, config.cant_pos);

    distribuirElementos(tablero, &idElem, config);

}

int  generarTablero(tListaDE* tablero, int *idElem, int cantPos)
{
    tElem elem;
    int contCas = 0;

    while(contCas < cantPos) //bucle infinito
    {
        insertarAlFinalDeListaDE(tablero, crearCasilla(), sizeof(tCasilla));
        if(contCas == 0)
        {
            elem.id_elem = *idElem;
            elem.tipo_elem = 'I';
            elem.nro_casilla = contCas;
            actualizarPosRelativaListaDE(tablero, &elem, sizeof(tElem), 0, insertarEnCasilla);
            (*idElem)++;
            elem.id_elem = *idElem;
            elem.tipo_elem = 'J';
            elem.nro_casilla = contCas;
            actualizarPosRelativaListaDE(tablero, &elem, sizeof(tElem), 0, insertarEnCasilla);
            (*idElem)++;
        }
        if(contCas == cantPos - 1)
        {
            elem.id_elem = *idElem;
            elem.tipo_elem = 'S';
            elem.nro_casilla = contCas;
            actualizarPosRelativaListaDE(tablero, &elem, sizeof(tElem), 0, insertarEnCasilla);
            (*idElem)++;
        }
    }
}

int  distribuirElementos(tListaDE* tablero, int *idElem, tConfig config)
{
    int elemFaltantes[] = { config.max_band,
                              config.max_prem,
                              config.max_vid_ext,
                              config.max_oasis,
                              config.max_tormenta };

    char elemTipo[] = { 'B', 'P', 'V', 'O', 'T'};
    int cantElem = 0,
        elemInsertados = 0,
        i,
        pos;
    for(i = 0; i < 5; i++)
    {
        cantElem += elemFaltantes[i];
    }

    tLista numAleatorios;
    crearLista(&numAleatorios);
    int numAle;
    tElem elem;

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
            elem.nro_casilla = pos;
            actualizarPosLista(tablero, &elem, sizeof(tElem), pos, insertarEnCasilla);
            elemInsertados++;
        }
    }
}

int  moverElementoPorId(tListaDE* tablero, int id, int mov) // EL ID ES EL ID DEL ELEMENTO, Y MOV ES UN NUMERO POSITIVO PARA LA DERECHA, NEGATIVO PARA LA IZQUIERDA
{
    tElem elemAActualizar;
    elemAActualizar.id_elem = id;

    actualizarPorClaveListaDE(tablero, &elemAActualizar, sizeof(tElem), cmpElem, eliminarDeCasilla); // ESTA FUNCION DEVUELVE EL DATO SIN ACTUALIZAR
    elemAActualizar.nro_casilla+=mov;
    actualizarPosRelativaListaDE(tablero, &elemAActualizar, sizeof(tElem), mov, insertarEnCasilla);

    return 1;
}

int  generarMovBandido(tTablero* tablero, tCola *mov)
{
    //recorrerListaDE()
}

int  compararEnteros(const void *a, const void *b)
{
    int *n1 = a;
    int *n2 = b;

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
