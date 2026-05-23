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

    while(contCas < cantPos)
    {
        insertarAlFinalDeListaDE(tablero, crearCasilla(), sizeof(tCasilla));
        if(contCas == 0)
        {
            elem.id_elem = *idElem;
            elem.tipo_elem = 'I';
            actualizarPosRelativaListaDE(tablero, &elem, sizeof(tElem), 0, insertarEnCasilla);
            (*idElem)++;
            elem.id_elem = *idElem;
            elem.tipo_elem = 'J';
            actualizarPosRelativaListaDE(tablero, &elem, sizeof(tElem), 0, insertarEnCasilla);
            (*idElem)++;
        }
        if(contCas == cantPos - 1)
        {
            elem.id_elem = *idElem;
            elem.tipo_elem = 'S';
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
        numAle = rand() % config.cant_pos;
        if(insertarOrdenado(&numAleatorios, &numAle, sizeof(int), cmpInt, 0, NULL))
            elemInsertados++;
    }

    elemInsertados = 0;

    while(elemInsertados < cantElem)
    {
        sacarDelInicio(&numAleatorios, &pos, sizeof(int));
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
    }
}

int  moverElementoPorId(tListaDE* tablero, int id, int mov) // EL ID ES EL ID DEL ELEMENTO, Y MOV ES UN NUMERO POSITIVO PARA LA DERECHA, NEGATIVO PARA LA IZQUIERDA
{
    tElem elemAActualizar;
    elemAActualizar.id_elem = id;

    actualizarPorID(tablero, &elemAActualizar, sizeof(tElem), cmpElem, eliminarDeCasilla);
    actualizarPosRelativaLista(tablero, &elemAActualizar, sizeof(tElem), mov, insertarEnCasilla);

    return 1;
}

int  cmpInt(const void *a, const void *b)
{
    int *n1 = a;
    int *n2 = b;

    return n1 - n2;
}

// ------------------------------------------------------------------------------------------------------------------




void mostrarMapa(const tListaDE *lista, void(*mostrar)(const void *)){ // NO DEBERIAMOS PODER RECORRER POR LOS CAMPOS INTERNOS DEL TDA
/*
    Forma provisoria de mostrar mapa (casillas no se ajustan tal que sean todos iguales en ancho).
    Ver si conviene hacer un map y generar una cadena con los elementos de la lista de cada nodo casilla.
*/
    tNodoDE *auxNodo = *lista;
    int casilla = 1;

    if(NULL == auxNodo){
        printf("\n %s", MSJ_LISTA_MAPA_VACIO);
        return;
    }

    do{

        tLista listaNodo = auxNodo->dato;

        printf("\n %02d. [ ", casilla);

        mapLista(&listaNodo, mostrar);

        printf(" ]");
        casilla++;
        auxNodo = auxNodo->proxNodo;

    }while(auxNodo != *lista);

}

int borrarMapa(tListaDE *lista){
/*
    Esto es un wrapper que:
    1) Libera cada lista simple (sus nodos) de cada casilla (lista doble circular)
    2) Libera cada nodo de la lista doblemente enlazada circular.
    Devuelve la cantidad de elementos eliminados (casillas y elementos en lista de nodos)
    Requiere la funcion definida:
        - vaciarListaC : Vaciar Lista Doblemente Enlazada Circular
*/
    borrarListasElementosCasillas(lista);
    return vaciarListaC(lista);
}
