#include <string.h>
#include "registro.h"


void enlistarNickNames(void *idxNombre, void *contexto)
{
    tIndiceNombre *idx = (tIndiceNombre*)idxNombre;
    tLista *nicknames = (tLista*)contexto[0];
    FILE *archJugadores = (FILE*)contexto[1];
    const char *nombre = (const char*)contexto[2];

    regJugador registro;
    char nickname[11];

    if(strcmp(idx->nombre, nombre) == 0)
    {
        fflush(archJugadores);
        fseek(archJugadores, idx->indiceRegistro, SEEK_SET);
        fread(&registro, sizeof(regJugador), 1, archJugadores);

        strcpy(nickname, registro.nickname);
        insertarAlFinalLista(nicknames, nickname, sizeof(nickname));
    }

#include "lista_simple_enlace.h"


// La implementa Elian (deberia vivir en menu.h): menu que devuelve la opcion
// numerica elegida (1..cantOpciones).
int menuNumerico(const char *msj, int cantOpciones, int conErr, const char *msjErr);


int revisarUsuarioRepetido(tArbolBinBusq *indice, const char *nombre, FILE *fJug, regJugador *sel)
{
    tLista lista;
    char   buffer[TAM_MENU];
    int    contador = 1;
    int    op;

    // 1) juntar homonimos: recorre el indice por nombre; la accion encola los que coinciden
    crearLista(&lista);
    void *ctxArbol[3] = { &lista, fJug, (void *)nombre };
    recorrerEnOrdenSimpleArbolBinBusq(indice, ctxArbol, enlistarNickNames);

    // 2) armar el texto del menu recorriendo la lista
    buffer[0] = '\0';
    void *ctxMsg[2] = { buffer, &contador };
    recorrerLista(&lista, armarMensaje, ctxMsg);
    sprintf(buffer + strlen(buffer), "%d. NINGUNO\n", contador);

    // 3) mostrar el menu y leer la eleccion
    op = menuNumerico(buffer, contador, 1, "Opcion invalida\n");

    // 4) interpretar la respuesta
    if(op == contador)                       // eligio NINGUNO
    {
        vaciarLista(&lista);
        return 0;                            // -> dar de alta
    }
    buscarPorPosicionLista(&lista, sel, sizeof(regJugador), op - 1);
    vaciarLista(&lista);
    return 1;                                // -> jugador existente, *sel cargado
}
