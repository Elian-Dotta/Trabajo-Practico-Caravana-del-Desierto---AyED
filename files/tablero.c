#include "tablero.h"
#include "lista.h"
#include "casilla.h"

int  crearTablero(tLista* tablero, tConfig config)
{
    int idElem = 0;

    srand(time(NULL));

    crearLista(tablero);

    generarTablero(tablero, &idElem, config.cant_pos);

    distribuirElementos(tablero, &idElem, config);

}
int  generarTablero(tLista* tablero, int *idElem, int cantPos)
{
    tElem elem;
    int contCas = 0;

    while(contCas < cantPos)
    {
        insertarAlFinal(tablero, crearCasilla(), sizeof(tLista))
        if(contCas == 0)
        {
            elem.id_elem = *idElem;
            elem.tipo_elem = 'I';
            actualizarPosLista(tablero, &elem, sizeof(tElem), conCas, insertarEnCasilla);
            (*idElem)++;
            elem.id_elem = *idElem;
            elem.tipo_elem = 'J';
            actualizarPosLista(tablero, &elem, sizeof(tElem), conCas, insertarEnCasilla);
            (*idElem)++;
        }
        if(contCas = config.cant_pos - 1)
        {
            elem.id_elem = *idElem;
            elem.tipo_elem = 'S';
            actualizarPosLista(tablero, &elem, sizeof(tElem), conCas, insertarEnCasilla);
            (*idElem)++;
        }
    }
}

int  distribuirElementos(tLista* tablero, int *idElem, tConfig config)
{
    int elemFaltantes[] = { config.max_band,
                              config.max_prem,
                              config.max_vid_ext,
                              config.max_oasis,
                              config.max_tormenta };

    char elemTipo[] = { 'B', 'P', 'V', 'O', 'T'};
    int cantElem = 0,
        elemInsertados = 0,
        i,
        pos;
    for(i = 0; i < 5; i++)
    {
        cantElem += elemFaltantes[i];
    }

    tLista numAleatorios;
    crearLista(&numAleatorios);
    int numAle;

    while(elemInsertados < cantElem)
    {
        numAle = rand() % config.cant_pos;
        if(insertarEnOrden(&numAleatorios, &numAle, sizeof(int), cmpInt, 0, NULL))
            elemInsertados++;
    }

    elemInsertados = 0;

    while(elemInsertados < cantElem)
    {
        sacarDelInicio(&numAleatorios, &pos, sizeof(int));
        i = rand() % 5;
        if(elemFaltantes[i])
        {
            elemFaltantes[i]--;
            elem.id_elem = *idElem;
            (*idElem)++;
            elem.tipo_elem = elemTipo[i];
            actualizarPosLista(tablero, &elem, sizeof(tElem), pos, insertarEnCasilla);
        }
    }
}

int  cmpInt(void *a, void *b)
{
    int *c = a;
    int *d = b;

    return c - d;
}
