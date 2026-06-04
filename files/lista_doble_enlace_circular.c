#include "lista_doble_enlace_circular.h"

int vaciarListaC(tListaDE *lista){

    tNodoDE *actualNodo = *lista;
    int cont = 0;

    if(NULL == actualNodo)
        return 0;

    actualNodo = actualNodo->proxNodo;

    while(actualNodo != *lista){
        tNodoDE *auxNodo = actualNodo;
        free(auxNodo->dato);
        free(auxNodo);
        actualNodo = actualNodo->proxNodo;
        cont++;
    }

    free(actualNodo->dato);
    free(actualNodo);

    *lista = NULL;

    return ++cont;
}

void recorrerListaDE(tListaDE *pl, Accion accion, void *contexto){

    tNodoDE *nodoActual = *pl;

    if(NULL == *pl)
        return;

    do{
        accion(nodoActual->dato,contexto);
        nodoActual = nodoActual->proxNodo;
    }while(nodoActual != *pl);
}

void mostrarListaDE(tListaDE *pl, Mostrar mostrar){

    tNodoDE *nodoActual = *pl;

    if(NULL == *pl)
        return;

    do{
        mostrar(nodoActual->dato);
        nodoActual = nodoActual->proxNodo;
    }while(nodoActual != *pl);
}

tNodoDE* buscarNodoPorClaveEnListaDE(const tListaDE *lista, const void* clave, Cmp comparar){

    tNodoDE *nodoActual = *lista;
    if(NULL == *lista)
        return NULL;
    do{
        if(0 == comparar(nodoActual->dato, clave))
            return nodoActual;
        nodoActual = nodoActual->proxNodo;
    }while(nodoActual != *lista);

    return NULL;
}
