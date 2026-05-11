#include "lista.h"
#include "casilla.h"


tLista crearCasilla()
{
    tLista cas;

    crearLista(&cas);

    return cas;
}

int insertarEnCasilla(void **pl, unsigned *tamLista, void *d, unsigned tamDato)
{
    tLista *casilla = pl;
    tElem  *elem = d;

    insertarAlFinal(casilla, elem, tamDato);

    return 1;
}
