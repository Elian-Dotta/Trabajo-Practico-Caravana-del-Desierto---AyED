#ifndef NODOS_H
#define NODOS_H

    #define MIN(x,y) ( (x)>(y)?(y):(x) )
    #define MAX(x,y) ( (x)>(y)?(x):(y) )


    // LISTA DE ENLACE SIMPLE:
        typedef struct sNodo{
            void            *dato;
            unsigned        tamDato;
            struct sNodo    *proxNodo;
        }tNodo;

        typedef tNodo* tLista; // La lista sera un puntero a Nodo. Es decir, la lista
                               // tendrá la dirección de memoria de un nodo, no datos. Así ocupara solo 8 Bytes (tam de puntero).

    // LISTA DE ENLACE DOBLE
        typedef struct sNodoDE{
            void            *dato;
            unsigned         tamDato;
            struct sNodoDE    *proxNodo,
                            *antNodo;
        }tNodoDE;

        typedef tNodoDE* tListaDE;

#endif // NODOS_H
