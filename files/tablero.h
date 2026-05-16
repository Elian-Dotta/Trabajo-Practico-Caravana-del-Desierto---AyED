#ifndef TABLERO_H_
#define TABLERO_H_

    #include <stdlib.h>
    #include <time.h>
    #include "casilla.h"
    #include "config.h"
    #include "lista_doble_enlace_circular.h"
    #include "lista_simple_enlace.h"

    #define MSJ_LISTA_MAPA_VACIO "EL MAPA NO FUE GENERADO"
    #define TAM_BUFFER 30



    typedef struct tLista tLista;
    typedef struct tConfig tConfig;

    int  crearTablero(tLista* tablero, tConfig config);
    int  generarTablero(tLista* tablero, int *contElem, int cantPos);
    int  distribuirElementos(tLista* tablero, int *contElem, tConfig config);
    void mostrarTablero(tLista* tablero); // muestra la lista
    void mostrarTablero2(); //-> metodo
    int  cmpInt(void *a, void *b);

// Definidas:
    void mostrarElemento(const void *elemVoid);
    void mostrarMapa(const tListaDE *lista, void(*mostrar)(const void *));
    int borrarMapa(tListaDE *lista);

#endif // TABLERO_H_
