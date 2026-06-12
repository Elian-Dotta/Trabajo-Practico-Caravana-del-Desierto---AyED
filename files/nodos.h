#ifndef NODOS_H
#define NODOS_H

#define MIN(x,y) ( (x)>(y)?(y):(x) )
#define MAX(x,y) ( (x)>(y)?(x):(y) )


// NODO DE ENLACE SIMPLE:
typedef struct sNodo
{
    void            *info;
    unsigned         tamInfo;
    struct sNodo    *sig;
} tNodo;

// NODO DE ENLACE DOBLE
typedef struct sNodoDE
{
    void            *info;
    unsigned         tamInfo;
    struct sNodoDE  *sig,
                    *ant;
} tNodoDE;

// NODO DE ARBOL BINARIO DE BUSQUEDA
typedef struct sNodoArbol
{
    void               *info;
    unsigned            tamInfo;
    struct sNodoArbol  *izq,
                       *der;
} tNodoArbol;



#endif // NODOS_H
