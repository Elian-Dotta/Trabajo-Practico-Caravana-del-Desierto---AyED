#include "lista_simple_enlace.h"


int insertarOrdenado(tLista *lista, const void *dato, unsigned tamDato, tCompararFn comparar){

    tNodo *nuevoNodo;

    while((*lista) && comparar((*lista)->info, dato)<0) // Por default ordena de menor a mayor
        lista = &(*lista)->sig;


    if( NULL==(nuevoNodo=(tNodo*)malloc(sizeof(tNodo))) || NULL==(nuevoNodo->info=(void*)malloc(tamDato)) ){
        free(nuevoNodo);
        return 0;
    } //CREAR_NODO(nuevoNodo,tamDato); // Usando Macro

    memcpy(nuevoNodo->info, dato, tamDato);
    nuevoNodo->tamInfo=tamDato;
    nuevoNodo->sig = *lista;
    *lista = nuevoNodo;
    return 1;
}

/*
int desenlazarNodoPorClave(tLista *lista, tNodo **destNodo, const void *clave, int (*comparar)(const void*, const void*)){

    Esta es una funcion que recibe una lista, recibe la direccion de memoria de un puntero a nodo de destino y una funcion de comparacion.
    Busca en la lista, los elementos que coincidan con la clave dada. Si los encuentra asigna la direccion de memoria del nodo encontrado en el
    puntero local de la funcion llamadora.
    Retorna 0 si no encuentra nada, o 1 si encuentra algo. (Ver si combiene que sea void)


    if(NULL == *lista){
        *destNodo = NULL;
        return 0;
    }

    while(NULL != (*lista) && 0!=comparar((*lista)->info, clave))
        lista = &(*lista)->sig;

    *destNodo = *lista;

    if(NULL != (*lista) && 0 == comparar((*lista)->info, clave))
        *lista = (*destNodo)->sig; //o *lista = (*lista)->proxNodo

    return NULL == *destNodo?0:1;
}
*/

/*
int enlazarNodoOrdenado(tLista *lista, tNodo *nodo, int (*comparar)(const void*, const void*)){

    Funcion que recibe por parametro la lista, la direccion de memoria de un nodo y una funcion de comparacion.
    Inserta el nodo ya creado (con memoria dinamica asignada) ordenadamente en la lista.
    Retorna 1 si la insercion se completa.


    if (lista == NULL || nodo == NULL)
        return 0;

    nodo->proxNodo = NULL;

    while(NULL != (*lista) && comparar((*lista)->dato, nodo->dato)<0) // Por default ordena de menor a mayor
        lista = &(*lista)->proxNodo;

        nodo->proxNodo = *lista;

        *lista = nodo;

    return 1;
}
*/

void recorrerLista(tLista *lista, Accion accion, void *contexto) // LUCAS
{ //Nombre anterior, mapLista
    tNodo *aux = *lista;
    while(aux)
    {
        accion(aux->info, contexto);
        aux = aux->sig;
    }
}
/*
void recorrerLista(tLista *pl, Accion accion,void* contexto) // MANUEL
{
    tLista* puntero = pl;
    while (puntero!=NULL)
    {
        accion(contexto, puntero);
        puntero=&(*puntero)->sig;
    }
    return;
}
*/
/*
void recorrerLista(tLista *lista, void (*accion)(void *, unsigned, void *), void *contexto) // SANTIAGO
{
    tNodo *aux = *lista;

    while(aux)
    {
        accion(aux->info, aux->tamInfo, contexto);
        aux = aux->sig;
    }
}
*/

/*
void mostrarLista(const tLista *lista, Mostrar mostrar)
{

    tNodo *aux = *lista;
    while(aux)
    {
        mostrar(aux->info);
        aux = aux->sig;
    }
}
*/

int mostrarLista(const tLista *p, Mostrar mostrar) // ME QUEDO CON ESTA IMPLEMENTACION QUE DEVUELVE EL NUMERO DE MOSTRADOS.
{
    int cant = 0;

    while(*p)
    {
        mostrar((*p)->info);
        p = &(*p)->sig;
        cant++;
    }
    return cant;
}

unsigned minimo(unsigned a, unsigned b)
{
    return a < b ? a : b;
}


void crearLista(tLista *p)
{
    *p = NULL;
}


int vaciarLista(tLista *p)
{
    int cant = 0;
    while(*p)
    {
        tNodo *aux = *p;

        cant++;
        *p = aux->sig;
        free(aux->info);
        free(aux);
    }
    return cant;
}


int ponerAlFinal(tLista *p, const void *d, unsigned cantBytes)
{
    tNodo *nue;

    while(*p)
        p = &(*p)->sig;
    if((nue = (tNodo *)malloc(sizeof(tNodo))) == NULL ||
       (nue->info = malloc(cantBytes)) == NULL)
    {
        free(nue);
        return 0;
    }
    memcpy(nue->info, d, cantBytes);
    nue->tamInfo = cantBytes;
    nue->sig = NULL;
    *p = nue;
    return 1;
}


int sacarPrimeroLista(tLista *p, void *d, unsigned cantBytes)
{
    tNodo *aux = *p;

    if(aux == NULL)
        return 0;
    *p = aux->sig;
    memcpy(d, aux->info, minimo(cantBytes, aux->tamInfo));
    free(aux->info);
    free(aux);
    return 1;
}

int eliminarPorClave(tLista *lista, void *d, unsigned tamDato, Cmp cmp)
{
    tLista *elim = lista,
           *auxSig;

    if (elim==NULL)
    {
        return 0;
    }

    int comp = cmp((*elim)->info,d);
    while(comp!=0)
    {
        elim=&(*elim)->sig;
        comp = cmp((*elim)->info,d);
    }
    if (comp==0)
    {
        auxSig=&(*elim)->sig;
        free((*elim)->info);
        free(*elim);
        elim=auxSig;
        return 1;
    }
    return 0;

}

int buscarPorClaveEnLista(const tLista *lista, const void* clave, void *destDato, unsigned tamDest, tCompararFn comparar){
    tNodo *aux = *lista;
    while(aux){
        if(0 == comparar(aux->info, clave)){
            if(destDato)
                memcpy(destDato, aux->info, minimo(tamDest, aux->tamInfo));
            return 1;
        }
        aux = aux->sig;
    }
    return 0;
}

int buscarPorPosicionLista(tLista *lista, void *dest, unsigned tam, int pos)
{
    tNodo *aux = *lista;

    while(pos > 0 && aux)
    {
        aux = aux->sig;
        pos--;
    }
    if(aux == NULL)
        return 0;
    memcpy(dest, aux->info, minimo(tam, aux->tamInfo));
    return 1;
}
