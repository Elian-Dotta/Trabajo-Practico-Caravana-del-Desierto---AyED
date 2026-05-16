#include "lista_doble_enlace_circular.h"

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
