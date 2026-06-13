#include <string.h>
#include "registro.h"


void enlistarNickNames(void *idxNombre, void *contexto)
{
    tIndiceNombre *idx = (tIndiceNombre*)idxNombre;

    void **ctx = (void**)contexto;

    tLista *nicknames = (tLista*)ctx[0];
    FILE *archJugadores = (FILE*)ctx[1];
    const char *nombre = (const char*)ctx[2];

    regJugador registro;
    char nickname[11];

    if(strcmp(idx->nombre, nombre) == 0)
    {
        fflush(archJugadores);
        fseek(archJugadores, idx->indiceRegistro * sizeof(regJugador), SEEK_SET);
        fread(&registro, sizeof(regJugador), 1, archJugadores);

        strcpy(nickname, registro.nickname);
        insertarAlFinalLista(nicknames, nickname, sizeof(nickname));
    }
}



int revisarUsuarioRepetido(tArbolBinBusq *indice, const char *nombre, FILE *fJug, regJugador *sel)
{
    tLista nicknames;
    char   buffer[TAM_MENU];
    int    contador = 1;
    int    op;

    // 1) juntar homonimos: recorre el indice por nombre; la accion encola los que coinciden
    crearLista(&nicknames);
    void *ctxArbol[3] = { &nicknames, fJug, (void *)nombre };
    recorrerEnOrdenSimpleArbolBinBusq(indice, ctxArbol, enlistarNickNames);

    // 2) armar el texto del menu recorriendo la lista
    buffer[0] = '\0';
    void *ctxMsg[2] = { buffer, &contador };
    recorrerLista(&nicknames, armarMensaje, ctxMsg);
    sprintf(buffer + strlen(buffer), "%d. NINGUNO\n", contador);

    // 3) mostrar el menu y leer la eleccion
    op = menuNumerico(buffer, contador, 1, "Opcion invalida\n");

    // 4) interpretar la respuesta
    if(op == contador)                       // eligio NINGUNO
    {
        vaciarLista(&nicknames);
        return 0;                            // -> dar de alta
    }
    buscarPorPosicionLista(&nicknames, sel, sizeof(regJugador), op - 1);
    vaciarLista(&nicknames);
    return 1;                                // -> jugador existente, *sel cargado
}
