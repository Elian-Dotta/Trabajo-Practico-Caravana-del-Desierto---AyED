// === Modulo ListaDE: lista circular doble ===
#include "lista_doble_enlace_circular.h"

int insertarAlFinalHead(tListaDE *lista, const void *dato, unsigned tamDato)
{
    tNodoDE *auxNodo;

    if( NULL == (auxNodo = (tNodoDE*)malloc(sizeof(tNodoDE)) ) || NULL == (auxNodo->info = (void*)malloc(tamDato)  )){
        free(auxNodo);
        return 0;
    }

    memcpy(auxNodo->info, dato, tamDato);

    if(0 == tamDato){
        auxNodo->info = NULL;
        auxNodo->tamInfo = sizeof(void*);
    }else
        auxNodo->tamInfo = tamDato;

    if(NULL == *lista){
        auxNodo->sig = auxNodo;
        auxNodo->ant = auxNodo;
        *lista = auxNodo;
    }else{
        tNodoDE *ultimo  = (*lista)->ant;

        auxNodo->ant = ultimo;
        auxNodo->sig = *lista;

        ultimo->sig = auxNodo;
        (*lista)->ant = auxNodo;
    }

    return 1;
}


void crearListaDE(tListaDE *pl)
{
    *pl = NULL;
}


int listaVaciaDE(const tListaDE *pl)
{
    return *pl == NULL;
}


int buscarPorClaveListaDE(tListaDE *lista, const void* clave, unsigned tam, Cmp cmp);



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

    if(*pl == NULL)
    {
        nue->sig = nue;
        nue->ant = nue;
    }
    else
    {
        nue->ant = *pl;
        nue->sig = (*pl)->sig;
        (*pl)->sig->ant = nue;
        (*pl)->sig = nue;

    }
    *pl = nue;
    return 1;
}


int vaciarListaDE(tListaDE *pl)
{
    tNodoDE *aux = *pl;
    int cant = 0;

    if(aux == NULL)
        return 0;

    (*pl)->ant->sig = NULL;
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


int actualizarPorClaveListaDE(tListaDE *pl, void *d, unsigned tamInfo, Cmp cmp, Acumular acum)
{
    if(buscarPorClaveListaDE(pl, d, tamInfo, cmp))
        return acum(&(*pl)->info, &(*pl)->tamInfo, d, tamInfo);
    return 0;
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




int buscarPorClaveListaDE(tListaDE *pl, const void *clave, unsigned tam, Cmp cmp)
{
    (void)tam;
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
        accion(nodoActual->info,contexto);
        nodoActual = nodoActual->sig;
    }while(nodoActual != *pl);
}


void mostrarListaDE(tListaDE *pl, Mostrar mostrar){

    tNodoDE *nodoActual = *pl;

    if(NULL == *pl)
        return;

    do{
        mostrar(nodoActual->info);
        nodoActual = nodoActual->sig;
    }while(nodoActual != *pl);
}


tNodoDE* buscarNodoPorClaveEnListaDE(const tListaDE *lista, const void* clave, Cmp comparar){

    tNodoDE *nodoActual = *lista;
    if(NULL == *lista)
        return NULL;
    do{
        if(0 == comparar(nodoActual->info, clave))
            return nodoActual;
        nodoActual = nodoActual->sig;
    }while(nodoActual != *lista);

    return NULL;
}


