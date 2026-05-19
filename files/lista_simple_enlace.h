#ifndef LISTA_SIMPLE_ENLACE_H
#define LISTA_SIMPLE_ENLACE_H

    #include <stdio.h>
    #include <string.h> // Para funciones MEM
    #include <stdlib.h> // Para uso de memoria dinamica y null
    #include "nodos.h"

    //void crearLista(tLista *lista);
    //int listaVacia(const tLista *lista);
    //int listaLlena(const tLista *lista, unsigned tamDato); //No se requiere el dato en principio, ver si borrar
    int vaciarLista(tLista *lista);
    int ponerAlFinal(tLista *lista, const void *dato, unsigned tamDato);
    int sacarPrimeroLista(tLista *lista, void *dest, unsigned tamDest);
    int sacarUltimoLista(tLista *lista, void *dest, unsigned tamDest);

//Definidas:
    typedef int (*tCompararFn)(const void*, const void*);
        int insertarOrdenado(tLista *lista, const void *dato, unsigned tamDato, tCompararFn comparar);
    void mapLista(const tLista *lista, void (*accion)(const void *));
    int desenlazarNodoPorClave(tLista *lista, tNodo **destNodo, const void *clave, int (*comparar)(const void*, const void*));
    int enlazarNodoOrdenado(tLista *lista, tNodo *nodo, int (*comparar)(const void*, const void*));

#endif // LISTA_SIMPLE_ENLACE_H
