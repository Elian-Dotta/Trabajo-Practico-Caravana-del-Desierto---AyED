#ifndef RANKING_H_
#define RANKING_H_

#include "lista_simple_enlace.h"
// MODULO USADO PARA EL CALCULO Y MUESTREO DEL RANKING

#define MAX_RANKING 10

typedef struct
{
    tLista ranking;
    unsigned cantLineas;
}tRanking;

typedef struct
{
    char    nickname[11];
    char    nombre[31];
    int     puntaje;
}tLinea;

void ranking();

void inicializarRanking(tRanking *ranking);

int insertarEnRanking(tRanking *ranking);

int generarRankingDeArchivo(tRanking *ranking, const char* arch);

int mostrarRanking(tRanking *ranking);

void mostrarLinea(const void* linea);

void calcularLinea()

void destruirRanking(tRanking *ranking);

int cmpLinea(void *, void *); // ORDEN ASCENDENTE

#endif // RANKING_H_
