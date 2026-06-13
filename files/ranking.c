#include "ranking.h"

void ranking() // FUNCION QUE CONTROLA EL FLUJO COMPLETO DEL RANKING
{
    tRanking ranking;

    inicializarRanking(&ranking); // PRIMERO LO INICIALIZA

    generarRankingDeArchivo(&ranking, ARCHPARTIDA, ARCHJUGADORES); // LUEGO LO GENERA

    mostrarRanking(&ranking); // POR ULTIMO LO MUESTRA
}

void inicializarRanking(tRanking *ranking)
{
    crearLista(&ranking->ranking);
    ranking->cantLineas = 0;
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

    while(obtenerLinea(archPartidas, archJugadores, &linea, &arNicknames))
    {
        insertarEnRanking(ranking, &linea);
    }

    return 1;
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

    while(!feof(archPartidas) && strcmp(nickAprocesar, partida.nickname) == 0)
    {
        strcpy(linea->nickname, nickAprocesar);
        linea->puntaje+= partida.puntaje;
        buscarEnArchivoConIndice(archJugadores, indice, &jugador, sizeof(regJugador), &idx, sizeof(tIndiceNickname), asigJugNick, cmpClaveNickname);
        strcpy(linea->nombre, jugador->nombre);

        fread(&partida, sizeof(regPartida), 1, archPartidas);
    }

    fseek(archPartidas, -1 * sizeof(regPartida), SEEK_CUR);
}

void mostrarRanking(tRanking *ranking)
{
    unsigned contador = 1;
    mostrar(TITULO_RANKING);
    recorrerLista(ranking->ranking, mostrarLinea, &contador);
    mostrar(MENSAJE_SALIDA);
}

void mostrarLinea(void* linea, void *contexto)
{
    tLinea *l = (tLinea*)linea;
    char buffer[TAM_LINEA];
    unsigned *contador = contexto;
    snprintf(buffer, sizeof(buffer), "%2u. |%-10.10s|%-30.30s|%03d\n", *contador, l->nickname, l->nombre, l->puntaje);

    mostrar(buffer);
    (*contador)++;
}

void destruirRanking(tRanking *ranking)
{
    vaciarLista(ranking->ranking);
    ranking->cantLineas = 0;
}

int cmpLinea(void *a, void *b) // ORDEN ASCENDENTE
{
    tLinea *l1 = (tLinea*)a;
    tLinea *l2 = (tLinea*)b;

    return l2->puntaje - l1->puntaje;
}
