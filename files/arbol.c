#include <stdio.h>
#include "arbol.h"


void crearArbolBinBusq(tArbolBinBusq *p)
{
    *p = NULL;
}


int insertarArbolBinBusq(tArbolBinBusq *p, const void *d, unsigned tam,
                         int (*cmp)(const void *, const void *))
{
    tNodoArbol *nue;
    int rc;

    while(*p)
    {
        if((rc = cmp(d, (*p)->info)) < 0)
            p = &(*p)->izq;
        else if(rc > 0)
            p = &(*p)->der;
        else
            return CLA_DUP;
    }
    if((nue = (tNodoArbol *)malloc(sizeof(tNodoArbol))) == NULL ||
       (nue->info = malloc(tam)) == NULL)
    {
        free(nue);
        return SIN_MEM;
    }
    nue->tamInfo = tam;
    memcpy(nue->info, d, tam);
    nue->der = nue->izq = NULL;
    *p = nue;
    return TODO_BIEN;
}


void recorrerEnOrdenSimpleArbolBinBusq(const tArbolBinBusq *p, void *params,
                                       void (*accion)(void *, unsigned, void *))
{
    if(!*p)
        return;
    recorrerEnOrdenSimpleArbolBinBusq(&(*p)->izq, params, accion);
    accion((*p)->info, (*p)->tamInfo, params);
    recorrerEnOrdenSimpleArbolBinBusq(&(*p)->der, params, accion);
}


static unsigned leerDesdeArchivoBin(void **d, void *pf, unsigned pos, void *params)
{
    unsigned tam = *((unsigned *)params);

    if((*d = malloc(tam)) == NULL)
        return 0;
    fseek((FILE *)pf, pos * tam, SEEK_SET);
    if(fread(*d, tam, 1, (FILE *)pf) != 1)
    {
        free(*d);
        *d = NULL;
        return 0;
    }
    return tam;                  // devuelve el tamano real (no el conteo de fread)
}


static int cargarDesdeDatosOrdenadosRec(tArbolBinBusq *p, void *ds,
                          unsigned (*leer)(void **, void *, unsigned, void *),
                          int li, int ls, void *params)
{
    int m = (li + ls) / 2,
        r;

    if(li > ls)
        return TODO_BIEN;

    if((*p = (tNodoArbol *)malloc(sizeof(tNodoArbol))) == NULL ||
       !((*p)->tamInfo = leer(&(*p)->info, ds, m, params)))
    {
        free(*p);
        return SIN_MEM;
    }
    (*p)->izq = (*p)->der = NULL;

    if((r = cargarDesdeDatosOrdenadosRec(&(*p)->izq, ds, leer, li, m - 1, params)) != TODO_BIEN)
        return r;
    return cargarDesdeDatosOrdenadosRec(&(*p)->der, ds, leer, m + 1, ls, params);
}


int cargarArchivoBinOrdenadoArbolBinBusq(tArbolBinBusq *p, const char *path,
                                         unsigned tamInfo)
{
    int cantReg,
        r;
    FILE *pf;

    if(*p)
        return SIN_INICIALIZAR;
    if((pf = fopen(path, "rb")) == NULL)
        return ERROR_ARCH;

    fseek(pf, 0L, SEEK_END);
    cantReg = ftell(pf) / tamInfo;
    r = cargarDesdeDatosOrdenadosRec(p, pf, leerDesdeArchivoBin, 0, cantReg - 1, &tamInfo);

    fclose(pf);
    return r;
}
