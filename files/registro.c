#include <string.h>
#include "registro.h"
#include "lista_simple_enlace.h"



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
    op = menuNum(buffer, contador, 1, "Opcion invalida\n");

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
