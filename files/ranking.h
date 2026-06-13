#ifndef RANKING_H_
#define RANKING_H_

#include "lista_simple_enlace.h"
#include "indice.h"
#include "registro.h"
// MODULO USADO PARA EL CALCULO Y MUESTREO DEL RANKING

#define MAX_RANKING 10
#define TAM_LINEA 128

#define TITULO_RANKING "TOP| NICKNAME | NOMBRE                       | PUNTAJE\n"
                    //  123|1234567890|123456789012345678901234567890|123
#define MENSAJE_SALIDA "Presione ENTER para salir..."

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

int generarRankingDeArchivo(tRanking *ranking, const char* archPart, const char* archJug);

int obtenerLinea(FILE* archPartidas, FILE *archJugadores, tLinea *linea, tArbolBinBusq *indice);

int mostrarRanking(tRanking *ranking);

void mostrarLinea(void* linea, void *contexto);

void destruirRanking(tRanking *ranking);

int cmpLinea(void *, void *); // ORDEN ASCENDENTE

#endif // RANKING_H_
