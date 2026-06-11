#include "lista_simple_enlace.h"


static unsigned minimo(unsigned a, unsigned b)
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


int mostrarLista(const tLista *p,
                 void (*mostrar)(const void *, FILE *), FILE *fp)
{
    int cant = 0;

    while(*p)
    {
        mostrar((*p)->info, fp);
        p = &(*p)->sig;
        cant++;
    }
    return cant;
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


void recorrerLista(tLista *lista, void (*accion)(void *, unsigned, void *), void *contexto)
{
    tNodo *aux = *lista;

    while(aux)
    {
        accion(aux->info, aux->tamInfo, contexto);
        aux = aux->sig;
    }
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
