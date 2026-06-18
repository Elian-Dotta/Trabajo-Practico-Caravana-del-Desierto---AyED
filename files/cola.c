// === Modulo cola: FIFO de movimientos ===
#include "cola.h"

#define minimo(X,Y) ((X) <= (Y) ? (X) : (Y))

// Inicializa una cola vacia
void crearCola(tCola *p)
{
    p->pri = NULL;
    p->ult = NULL;
}

// Indica si no hay memoria
int colaLlena(const tCola *p, unsigned cantBytes)
{
    (void)p;
    tNodo *aux = (tNodo *)malloc(sizeof(tNodo));
    void *info = malloc(cantBytes);
    free(aux);
    free(info);
    return aux == NULL || info == NULL;
}

// Encola un dato al final
int ponerEnCola(tCola *p, const void *d, unsigned cantBytes)
{
    tNodo *nue = (tNodo *)malloc(sizeof(tNodo));

    if( nue == NULL || (nue->info = malloc(cantBytes)) == NULL)
    {
        free(nue);
        return 0;
    }
    memcpy(nue->info,d,cantBytes);
    nue->tamInfo = cantBytes;
    nue->sig = NULL;
    if(p->ult)
        p->ult->sig = nue;
    else
        p->pri = nue;
    p->ult = nue;
    return 1;
}

// Copia el primero sin sacarlo
int verPrimeroCola(const tCola *p, void *d, unsigned cantBytes)
{
    if(p->pri == NULL)
        return 0;

    memcpy(d,p->pri->info,minimo(cantBytes,p->pri->tamInfo));
    return 1;
}

// Indica si la cola esta vacia
int colaVacia(const tCola *p)
{
    return p->pri == NULL;
}

// Desencola el primer dato
int sacarDeCola(tCola *p, void *d, unsigned cantBytes)
{
    tNodo *aux = p->pri;
    if(aux == NULL)
        return 0;
    p->pri = aux->sig;
    memcpy(d,aux->info,minimo(aux->tamInfo,cantBytes));
    free(aux->info);
    free(aux);
    if(p->pri == NULL)
        p->ult = NULL;
    return 1;
}

// Libera todos los nodos
void vaciarCola(tCola *p)
{
    while(p->pri)
    {
        tNodo *aux = p->pri;
        p->pri = aux->sig;
        free(aux->info);
        free(aux);
    }
    p->ult = NULL;
}
