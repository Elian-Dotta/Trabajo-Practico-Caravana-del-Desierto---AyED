// === Modulo ranking: top de jugadores por puntaje ===
#include "ranking.h"

void ranking() // FUNCION QUE CONTROLA EL FLUJO COMPLETO DEL RANKING
{
    tRanking ranking;

    inicializarRanking(&ranking); // PRIMERO LO INICIALIZA

    generarRankingDeArchivo(&ranking, ARCHPARTIDAS, ARCHJUGADORES); // LUEGO LO GENERA

    mostrarRanking(&ranking); // POR ULTIMO LO MUESTRA
}

// Inicializa el ranking vacio
void inicializarRanking(tRanking *ranking)
{
    crearLista(&ranking->ranking);
    ranking->cantLineas = 0;
}

// Arma el ranking desde los archivos
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

    cargarIndiceDesdeArchivo(&arNicknames, ARCHIDXNICK, &idx, sizeof(idx));

    while(obtenerLinea(archPartidas, archJugadores, &linea, &arNicknames))
    {
        insertarEnRanking(ranking, &linea);
    }

    return 1;
}

// Inserta linea ordenada por puntaje
int insertarEnRanking(tRanking *ranking, tLinea *linea)
{
    if(linea->nombre[0] == '\0' ||
       linea->nickname[0] == '\0')
        return 0;

    int ret;
    tLinea buffer;

    // conDup=1: dos jugadores pueden tener el MISMO puntaje y ambos deben
    // figurar (cmpLinea solo ordena por puntaje, no identifica al jugador).
    if((ret = insertarOrdenadoLista(&ranking->ranking, linea, sizeof(tLinea), (tCompararFn)cmpLinea, 1, NULL)))
    {
        if(ranking->cantLineas == MAX_RANKING)
            sacarUltimoLista(&ranking->ranking, &buffer, sizeof(tLinea));
        else
            ranking->cantLineas++;
    }

    return ret;
}

// Suma el puntaje total de un jugador
int obtenerLinea(FILE* archPartidas, FILE *archJugadores, tLinea *linea, tArbolBinBusq *indice)
{
    regPartida partida;
    regJugador jugador;
    tIndiceNickname idx;
    char nickAprocesar[11];
    linea->puntaje = 0;
    linea->nickname[0] = '\0';
    linea->nombre[0] = '\0';


    if(fread(&partida, sizeof(regPartida), 1, archPartidas) != 1)
        return 0;

    strcpy(nickAprocesar, partida.nickname);

    strcpy(linea->nickname, nickAprocesar);
    // la clave de busqueda va en 'aux' (jugador): buscarEnArchivoConIndice
    // arma la entrada de indice a partir de el con asigJugNick.
    strcpy(jugador.nickname, nickAprocesar);
    if(buscarEnArchivoConIndice(archJugadores, indice, &jugador, sizeof(regJugador), &idx, sizeof(tIndiceNickname), asigJugNick, cmpClaveNickname))
        strcpy(linea->nombre, jugador.nombre);

    // las partidas de un mismo nick estan agrupadas: sumar todas sus puntajes
    do
    {
        linea->puntaje += partida.puntaje;
    }
    while(fread(&partida, sizeof(regPartida), 1, archPartidas) == 1 &&
          strcmp(nickAprocesar, partida.nickname) == 0);

    // si se leyo un registro de OTRO nick, retroceder para procesarlo despues
    if(!feof(archPartidas))
        fseek(archPartidas, -1L * (long)sizeof(regPartida), SEEK_CUR);

    return 1;
}

// Muestra el ranking en pantalla
void mostrarRanking(tRanking *ranking)
{
    limpiarPantalla();
    unsigned contador = 1;
    mostrar(TITULO_RANKING);
    recorrerLista(&ranking->ranking, mostrarLinea, &contador);
    mostrar(MENSAJE_SALIDA);
    while(getchar() != '\n');   // espera un unico ENTER para salir
}

// Callback: imprime una linea
void mostrarLinea(void* linea, void *contexto)
{
    tLinea *l = (tLinea*)linea;
    char buffer[TAM_LINEA];
    unsigned *contador = contexto;
    snprintf(buffer, sizeof(buffer), "%2u. |%-10.10s|%-30.30s|%03d\n", *contador, l->nickname, l->nombre, l->puntaje);

    mostrar(buffer);
    (*contador)++;
}

// Libera el ranking
void destruirRanking(tRanking *ranking)
{
    vaciarLista(&ranking->ranking);
    ranking->cantLineas = 0;
}

// Ordena por puntaje descendente
int cmpLinea(void *a, void *b) // ORDEN ASCENDENTE
{
    tLinea *l1 = (tLinea*)a;
    tLinea *l2 = (tLinea*)b;

    return l2->puntaje - l1->puntaje;
}
