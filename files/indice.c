#include "indice.h"

int indexarArchivo(const char *nombreArchivo, tArbolBinBusq *p, void *aux, unsigned tamDatoAux, void *indice, unsigned tamDatoIndice, Asignacion asig, Cmp cmp))
{
    FILE *fp;
    unsigned long numeroRegistro;

    fp = fopen(nombreArchivoJugadores, "rb");
    if(!fp)
    {
        return 0;
    }

    if(!aux || !indice || !asig)
        return 0;

    fread(aux, tamDatoAux, 1, fp);
    numeroRegistro = 0L;
    while(!feof(fp))
    {
        asig(indice, aux, numeroRegistro);
        insertarArbolBinBusq()
    }
}
