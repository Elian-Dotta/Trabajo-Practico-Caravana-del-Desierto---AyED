#include "tablero.h"

int  crearTablero(tListaDE* tablero, tConfig config)
{
    int idElem = 0;

    srand(time(NULL));

    crearLista(tablero);

    generarTablero(tablero, &idElem, config.cant_pos);

    distribuirElementos(tablero, &idElem, config);

}
int  generarTablero(tListaDE* tablero, int *idElem, int cantPos)
{
    tElem elem;
    int contCas = 0;

    while(contCas < cantPos)
    {
        insertarAlFinal(tablero, crearCasilla(), sizeof(tLista))
        if(contCas == 0)
        {
            elem.id_elem = *idElem;
            elem.tipo_elem = 'I';
            actualizarPosLista(tablero, &elem, sizeof(tElem), conCas, insertarEnCasilla);
            (*idElem)++;
            elem.id_elem = *idElem;
            elem.tipo_elem = 'J';
            actualizarPosLista(tablero, &elem, sizeof(tElem), conCas, insertarEnCasilla);
            (*idElem)++;
        }
        if(contCas = config.cant_pos - 1)
        {
            elem.id_elem = *idElem;
            elem.tipo_elem = 'S';
            actualizarPosLista(tablero, &elem, sizeof(tElem), conCas, insertarEnCasilla);
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

    while(elemInsertados < cantElem)
    {
        numAle = rand() % config.cant_pos;
        if(insertarEnOrden(&numAleatorios, &numAle, sizeof(int), cmpInt, 0, NULL))
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

int  cmpInt(void *a, void *b)
{
    int *n1 = a;
    int *n2 = b;

    return n1 - n2;
}

// ------------------------------------------------------------------------------------------------------------------

void mostrarElemento(const void *elemVoid){ //muestra el struct tElem
    tElem *elem = (tElem*)elemVoid;
    printf(" %c ", elem->tipo_elem);
}


void mostrarMapa(const tListaDE *lista, void(*mostrar)(const void *)){
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
