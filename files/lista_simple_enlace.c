#include "lista_simple_enlace.h"

void mapLista(const tLista *lista, void (*accion)(const void*))
{
    tNodo *aux = *lista;
    while(aux)
    {
        accion(aux->dato);
        aux = aux->proxNodo;
    }
}


int eliminarPorClave(tLista *lista, void *d, unsigned tamDato, Cmp cmp)
{
    tLista *elim = lista,
           *auxSig;

    if (elim==NULL)
    {
        return 0;
    }

    int comp = cmp((*elim)->dato,d);
    while(comp!=0)
    {
        elim=&(*elim)->proxNodo;
        comp = cmp((*elim)->dato,d);
    }
    if (comp==0)
    {
        auxSig=&(*elim)->proxNodo;
        free((*elim)->dato);
        free(*elim);
        elim=auxSig;
        return 1;
    }
    return 0;

}

