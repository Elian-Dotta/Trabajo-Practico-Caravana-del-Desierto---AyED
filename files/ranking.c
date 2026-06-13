#include "ranking.h"

void ranking()
{
    tRanking ranking;

    inicializarRanking(&ranking);

    generarRankingDeArchivo(&ranking, ARCHPARTIDA, ARCHJUGADORES);

    mostrarRanking(&ranking);
}

void inicializarRanking(tRanking *ranking)
{
    crearLista(&ranking->ranking);
    ranking->cantLineas = 0;
}

int insertarEnRanking(tRanking *ranking, tLinea *linea);
{
    if(linea->nombre[0] == '\0' ||
       linea->nickname[0] == '\0')
        return 0;

    int ret;
    tLinea buffer;

    if(ret = insertarOrdenadoLista(&ranking->ranking, linea, sizeof(tLinea), cmpLinea, 0, NULL))
    {
        if(ranking->cantLineas == MAX_RANKING)
            sacarUltimoLista(&ranking->ranking, &buffer, sizeof(tLinea))
        else
            ranking->cantLinea++;
    }

    return ret;
}

int generarRankingDeArchivo(tRanking *ranking, const char* archPart, const char *archJug)
{
    FILE* archPartidas;
    archPartidas = fopen(archPart, "rb");
    if(!archPartidas)
    {
        return 0;
    }
    FILE* archJugadores;
    archJugadores = fopen(archJug, "rb");
    if(!archJugadores)
    {
        fclose(archPartidas);
        return 0;
    }

    tLinea linea;
    tArbolBinBusq arNicknames;
    crearArbolBinBusq(&arNicknames);
    tIndiceNickname idx;

    cargarIndiceDesdeArchivo(arNicknames, ARCHIDXNICK, &idx, sizeof(idx));

    while(obtenerLinea(archPartidas, archJugadores,&linea, &arNicknames))
    {
        insertarEnRanking(ranking, &linea);
    }
}

int mostrarRanking(tRanking *ranking)
{

}

int obtenerLinea(FILE* archPartidas, FILE *archJugadores, tLinea *linea, tArbolBinBusq *indice)
{
    regPartida partida;
    regJugador jugador;
    tIndiceNickname idx;
    char nickAprocesar[11];
    linea->puntaje = 0;
    linea->nickname[0] = '\0';


    if(fread(&partida, sizeof(regPartida), 1, archPartidas) != 1)
        return 0;

    strcpy(nickAprocesar, partida.nickname);

    while(feof(archPartidas) && strcmp(nickAprocesar, partida.nickname) == 0)
    {
        strcpy(linea->nickname, nickAprocesar);
        linea->puntaje+= partida.puntaje;
        buscarEnArchivoConIndice(archJugadores, indice, &jugador, sizeof(regJugador), idx, sizeof(tIndiceNickname), ,)

        fread(&partida, sizeof(regPartida), 1, archPartidas);
    }
}

void destruirRanking(tRanking *ranking);

int cmpLinea(void *a, void *b) // ORDEN ASCENDENTE
{
    tLinea *l1 = (tLinea*)a;
    tLinea *l2 = (tLinea*)b;

    return l2->puntaje - l1->puntaje;
}
