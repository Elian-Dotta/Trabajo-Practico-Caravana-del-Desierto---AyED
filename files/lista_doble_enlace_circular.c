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


int insertarAlFinalHead(tListaDE *lista, const void *dato, unsigned tamDato){

    tNodoDE *auxNodo;

    if( NULL == (auxNodo = (tNodoDE*)malloc(sizeof(tNodoDE)) ) || NULL == (auxNodo->dato = (void*)malloc(tamDato)  )){
        free(auxNodo);
        return 0;
    }

    memcpy(auxNodo->dato, dato, tamDato);

    if(0 == tamDato){
        auxNodo->dato = NULL;
        auxNodo->tamDato = sizeof(void*);
    }else
        auxNodo->tamDato = tamDato;

    if(NULL == *lista){
        auxNodo->proxNodo = auxNodo;
        auxNodo->antNodo = auxNodo;
        *lista = auxNodo; // se insertaria al princio de lista
    }else{
        tNodoDE *ultimo  = (*lista)->antNodo;

        auxNodo->antNodo = ultimo;
        auxNodo->proxNodo = *lista;

        ultimo->proxNodo = auxNodo;
        (*lista)->antNodo = auxNodo;
    }

    return 1;

}



int buscarPorClaveListaDE(tListaDE *lista, const void* clave, unsigned tam, Cmp cmp, Accion accion, void* contexto)
{
    tListaDE *act = lista,
             *ini = lista;

    if (act==NULL)
    {
        return 0;
    }
    int comp = cmp((*act)->dato,clave);
    if (comp < 0)
        {
            act=&(*act)->proxNodo;
            comp = cmp((*act)->dato,clave);
        }
        else
            {
                act=&(*act)->antNodo;
                comp = cmp((*act)->dato,clave);
            }

    while((comp!=0)&&(act!=ini))
    {
        if (comp < 0)
        {
            act=&(*act)->proxNodo;
            comp = cmp((*act)->dato,clave);
        }
        else
            {
                act=&(*act)->antNodo;
                comp = cmp((*act)->dato,clave);
            }
    }
    if(comp==0)
    {
        accion(act,contexto);
        return 1;
    }

    return 0;
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

