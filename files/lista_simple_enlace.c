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
