#include "indice.h"

int indexarArchivo(const char *nombreArchivo, tArbolBinBusq *p, void *aux, unsigned tamDatoAux, void *indice, unsigned tamDatoIndice, Asignacion asig, Cmp cmp)
{
    FILE *fp;
    unsigned long numeroRegistro;

    fp = fopen(nombreArchivo, "rb");
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
        //insertarArbolBinBusq()
    }

    return 1;
}

void generarIndice(char* nombre, unsigned pos, tNodoArbol* arbolindice, FILE* fIndex)
{
    tIndiceNombre ind;
    ind.indiceRegistro=pos;
    strcpy(ind.nombre,nombre);
    insertarArbolBinBusq(&arbolindice,&ind,sizeof(tIndiceNombre),cmpInd);
    guardarArchivoIndice(&arbolindice,"indice.idx");
}

int cmpInd (const void* ind1, const void* ind2)
{
    return ((((tIndiceNombre*)ind1)->indiceRegistro)-(((tIndiceNombre*)ind2)->indiceRegistro));
}
