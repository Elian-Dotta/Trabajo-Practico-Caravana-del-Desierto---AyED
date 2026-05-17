#ifndef LISTA_DOBLE_ENLACE_CIRCULAR_H
#define LISTA_DOBLE_ENLACE_CIRCULAR_H

    #include <string.h>
    #include <stdlib.h>
    #include "nodos.h"

/*
    typedef int  (*Acumular)(void **, unsigned *, void *, unsigned);
    typedef void (*Mostrar)(void *);

    int  insertarAlFinal(tListaDE *pl, void *d, unsigned tamInfo);
    int  actualizarPosLista(tListaDE *pl, void *d, unsigned tamInfo, unsigned pos, Acumular acum);
    void mostrarLista(tListaDE *pl, Mostrar mostrar);

    void mapLista(const tListaDE *lista, void (*accion)(const void *));
*/
    void crearListaC(tListaDE *lista);
    int vaciarListaC(tListaDE *lista);
    int listaVaciaC(tListaDE *lista);

//Definidas:
    int insertarAlFinalHead(tListaDE *lista, const void *dato, unsigned tamDato);
    /*
        Implementacion a Priori:
            - El head apuntara siempre al primer elemento insertado en la lista.
            - Considerar si vale la pena crear una estructura de forma; tListaC con referencias a nodo ultimo insertado y nodo primero insertado
                - Considerar si esa estructura debe generarse en el stack o en el heap.
            - Si se implementa la forma original de lista doblemente enlazada, donde head apunta al ultimo insertado. En lista circular, se complica
              definir cual es el primero y cual es el ultimo, al no existir CTEs NULL de identificacion.
                - Particularmente si se hacen inserciones al comienzo luego de inserciones iniciales y sucesivas el final.
                - p.ej.: una insercion al inicio, entonces head apunta al inicio. Luego insertar al final no podria realizarse a partir de head de forma generica.
                - tal vez con varios ifs¿¿ idk
            - Entiendase head como referencia a la lista en el main.
    */

#endif // LISTA_DOBLE_ENLACE_CIRCULAR_H
