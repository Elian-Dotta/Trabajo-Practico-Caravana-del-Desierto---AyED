#ifndef NODOS_H
#define NODOS_H

#define MIN(x,y) ( (x)>(y)?(y):(x) )
#define MAX(x,y) ( (x)>(y)?(x):(y) )


// NODO DE ENLACE SIMPLE:
typedef struct sNodo
{
    void            *dato;
    unsigned        tamDato;
    struct sNodo    *proxNodo;
} tNodo;

// NODO DE ENLACE DOBLE
typedef struct sNodoDE
{
    void            *dato;
    unsigned         tamDato;
    struct sNodoDE    *proxNodo,
               *antNodo;
} tNodoDE;



#endif // NODOS_H
