#include "lista_simple_enlace.h"

int insertarOrdenado(tLista *lista, const void *dato, unsigned tamDato, tCompararFn comparar){

    tNodo *nuevoNodo;

    while((*lista) && comparar((*lista)->dato, dato)<0) // Por default ordena de menor a mayor
        lista = &(*lista)->proxNodo;


    if( NULL==(nuevoNodo=(tNodo*)malloc(sizeof(tNodo))) || NULL==(nuevoNodo->dato=(void*)malloc(tamDato)) ){
        free(nuevoNodo);
        return 0; //No hay memoria suficiente
    } //CREAR_NODO(nuevoNodo,tamDato); // Usando Macro

    memcpy(nuevoNodo->dato, dato, tamDato);
    nuevoNodo->tamDato=tamDato;
    nuevoNodo->proxNodo = *lista;
    *lista = nuevoNodo;
    return 1;
}


int desenlazarNodoPorClave(tLista *lista, tNodo **destNodo, const void *clave, int (*comparar)(const void*, const void*)){
/*
    Esta es una funcion que recibe una lista, recibe la direccion de memoria de un puntero a nodo de destino y una funcion de comparacion.
    Busca en la lista, los elementos que coincidan con la clave dada. Si los encuentra asigna la direccion de memoria del nodo encontrado en el
    puntero local de la funcion llamadora.
    Retorna 0 si no encuentra nada, o 1 si encuentra algo. (Ver si combiene que sea void)
*/

    if(NULL == *lista){
        *destNodo = NULL;
        return 0;
    }

    while(NULL != (*lista) && 0!=comparar((*lista)->dato, clave))
        lista = &(*lista)->proxNodo;

    *destNodo = *lista;

    if(NULL != (*lista) && 0 == comparar((*lista)->dato, clave))
        *lista = (*destNodo)->proxNodo; //o *lista = (*lista)->proxNodo

    return NULL == *destNodo?0:1;
}


int enlazarNodoOrdenado(tLista *lista, tNodo *nodo, int (*comparar)(const void*, const void*)){
/*
    Funcion que recibe por parametro la lista, la direccion de memoria de un nodo y una funcion de comparacion.
    Inserta el nodo ya creado (con memoria dinamica asignada) ordenadamente en la lista.
    Retorna 1 si la insercion se completa.
*/

    if (lista == NULL || nodo == NULL)
        return 0;

    nodo->proxNodo = NULL;

    while(NULL != (*lista) && comparar((*lista)->dato, nodo->dato)<0) // Por default ordena de menor a mayor
        lista = &(*lista)->proxNodo;

        nodo->proxNodo = *lista;

        *lista = nodo;

    return 1;
}

void recorrerLista(tLista *lista, Accion accion, void *contexto){ //Nombre anterior, mapLista
    tNodo *aux = *lista;
    while(aux)
    {
        accion(aux->dato, contexto);
        aux = aux->proxNodo;
    }
}

void mostrarLista(const tLista *lista, Mostrar mostrar){

    tNodo *aux = *lista;
    while(aux)
    {
        mostrar(aux->dato);
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


void recorrerLista(void **pl, Accion accion,void* contexto)
{
    tLista* puntero = pl;
    while (puntero!=NULL)
    {
        accion(contexto,puntero);
        puntero=&(*puntero)->proxNodo;
    }
    return;

}
