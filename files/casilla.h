#ifndef CASILLA_H_
#define CASILLA_H_

    #include "lista_doble_enlace_circular.h"

    typedef struct
    {
        int  id_elem;
        char tipo_elem;
    }tElem; // Se pasa aca la definicio para corregir la inclusion circular.

    int crearCasillas(tListaDE *lista, unsigned cantCasillas);
    int borrarListasElementosCasillas(tListaDE *lista);
    int borrarCasillas(tListaDE *lista);
    int insertarElementoCasilla(tListaDE *lista, const tElem *elem, unsigned casilla);

    int insertarElementoCasillaOrdenado(tListaDE *lista, const tElem *elem, unsigned casilla, int(*comparar)(const void*, const void*));
    int moverElementoPorID(tListaDE *lista, unsigned id, char mov, int(*comparar)(const void *, const void *));

    /*
    int insertarEnCasilla(void **pl, unsigned *tamLista, void *d, unsigned tamDato);
    void mostrarCasillaV();
    */

#endif // CASILLA_H_
