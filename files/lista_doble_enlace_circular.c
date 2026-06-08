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


int buscarPorClaveListaDE(tListaDE *lista, const void* clave, unsigned tam, Cmp cmp, Accion accion, void* estado)
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
        accion(act,estado);
        return 1;
    }

    return 0;
}
