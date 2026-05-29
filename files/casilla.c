#include "casilla.h"

tCasilla crearCasilla()
{
    tCasilla cas;

    crearLista(&cas);

    return cas;
}

int insertarEnCasilla(void **pl, unsigned *tamLista, void *d, unsigned tamDato)
{
    tCasilla *casilla = (tCasilla*)pl;
    tElem  *elem = (tElem*)d;

    insertarAlFinal(casilla, elem, tamDato);

    return 1;
}

int eliminarDeCasilla(void **pl, unsigned *tamLista, void *d, unsigned tamDato)
{
    tCasilla *casilla = (tCasilla*)pl;
    tElem  *elem = (tElem*)d;

    eliminarPorClave(casilla, elem, tamDato); // LA FUNCION QUE ELIMINAR DEBE DEVOLVER EL DATO POR EL MISMO PARAMETRO

    return 1;
}

void mostrarCasilla(const void *pl)
{
    tLista *casilla = pl;
    printf("[ ");
    mostrarLista(casilla, mostrarElemento);
    printf(" ] ");
}

void mostrarElemento(const void *elemVoid){
    tElem *elem = (tElem*)elemVoid;
    printf(" %c ", elem->tipo_elem);
}
