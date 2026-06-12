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


void crearListaDE(tListaDE *pl)
{
    *pl = NULL;
}

int buscarPorClaveListaDE(tListaDE *lista, const void* clave, unsigned tam, Cmp cmp, Accion accion, void* contexto)

int listaVaciaDE(const tListaDE *pl)
{
    return *pl == NULL;
}


int insertarAlFinalDeListaDE(tListaDE *pl, const void *d, unsigned tamInfo)
{
    tNodoDE *nue;

    if((nue = (tNodoDE *)malloc(sizeof(tNodoDE))) == NULL ||
       (nue->info = malloc(tamInfo)) == NULL)
    {
        free(nue);
        return 0;
    }
    memcpy(nue->info, d, tamInfo);
    nue->tamInfo = tamInfo;

    if(*pl == NULL)                  // lista vacia: el nodo se apunta a si mismo
    {
        nue->sig = nue;
        nue->ant = nue;
    }
    else                            // insertar entre el cursor y su siguiente
    {
        nue->ant = *pl;
        nue->sig = (*pl)->sig;
        (*pl)->sig->ant = nue;
        (*pl)->sig = nue;
    }
    *pl = nue;                       // el cursor queda en el nuevo nodo
    return 1;
}


int vaciarListaDE(tListaDE *pl)
{
    tNodoDE *aux = *pl;
    int cant = 0;

    if(aux == NULL)
        return 0;

    (*pl)->ant->sig = NULL;          // rompo la circularidad para recorrer lineal
    while(aux)
    {
        tNodoDE *sig = aux->sig;

        cant++;
        free(aux->info);
        free(aux);
        aux = sig;
    }
    *pl = NULL;
    return cant;
}


void mostrarListaDE(tListaDE *pl, Mostrar mostrar)
{
    tNodoDE *aux = *pl;
    int primero = 1;

    if(aux == NULL)
        return;
    while(primero || aux != *pl)
    {
        primero = 0;
        mostrar(aux->info);
        aux = aux->sig;
    }
}


void recorrerListaDE(tListaDE *pl, Accion accion, void *contexto)
{
    tNodoDE *aux = *pl;
    int primero = 1;

    if(aux == NULL)
        return;
    while(primero || aux != *pl)
    {
        primero = 0;
        accion(aux->info, contexto);
        aux = aux->sig;
    }
}


int buscarPorClaveListaDE(tListaDE *pl, const void *clave, unsigned tam, Cmp cmp)
{
    tNodoDE *aux = *pl;
    int primero = 1;

    if(aux == NULL)
        return 0;
    while(primero || aux != *pl)
    {
        primero = 0;
        if(cmp(aux->info, clave) == 0)
        {
            *pl = aux;               // el cursor queda en el nodo hallado
            return 1;
        }
        aux = aux->sig;
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


int actualizarPosRelativaListaDE(tListaDE *pl, void *d, unsigned tamInfo,
                                 int pos, Acumular acum)
{
    if(*pl == NULL)
        return 0;
    while(pos > 0)                   // avanzar
    {
        *pl = (*pl)->sig;
        pos--;
    }
    while(pos < 0)                  // retroceder
    {
        *pl = (*pl)->ant;
        pos++;
    }
    return acum(&(*pl)->info, &(*pl)->tamInfo, d, tamInfo);
}

