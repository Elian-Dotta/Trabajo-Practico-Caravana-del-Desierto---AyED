#include "lista_doble_enlace_circular.h"

int vaciarListaC(tListaDE *lista)
{

    tNodoDE *actualNodo = *lista;
    int cont = 0;

    if(NULL == actualNodo)
        return 0;

    actualNodo = actualNodo->sig;

    while(actualNodo != *lista){
        tNodoDE *auxNodo = actualNodo;
        free(auxNodo->info);
        free(auxNodo);
        actualNodo = actualNodo->sig;
        cont++;
    }

    free(actualNodo->info);
    free(actualNodo);

    *lista = NULL;

    return ++cont;
}


void crearListaDE(tListaDE *pl)
{
    *pl = NULL;
}

//int buscarPorClaveListaDE(tListaDE *lista, const void* clave, unsigned tam, Cmp cmp)

int listaVaciaDE(const tListaDE *pl)
{
    return *pl == NULL;
}


int buscarPorClaveListaDE(tListaDE *lista, const void* clave, unsigned tam, Cmp cmp, Accion accion, void* contexto)


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

        accion(act,contexto);
        return 1;
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

/*
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
*/
/*
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
*/

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

//FUNCION SOLO USADA PARA POSICIONAR TABLERO, ELIAN HIZO UNA MEJOR
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

