#ifndef REGISTRO_H_
#define REGISTRO_H_

#include <stdio.h>

#include "arbol.h"
#include "indice.h"
#include <string.h>
#include "lista_simple_enlace.h"
#include "menu.h"

#define TAM_MENU 512

#define ARCHIDXNICK "nickname.idx"
#define ARCHIDXNOMBRE "nombre.idx"
#define ARCHPARTIDAS "partida.bin"
#define ARCHJUGADORES "jugadores.bin"
#define ARCHPARTIDASTMP "partida.tmp"


// MODULO USADO PARA EL GUARDADO DE PARTIDA Y JUGADOR.

typedef struct
{
    char nombre[31];
    char nickname[11];
} regJugador;        // REGISTRO DEL ARCHIVO JUGADORES

typedef struct
{
    char nickname[11];
    unsigned nroPartida;
    unsigned puntaje;
    unsigned cantMovimientos;
} regPartida;




// Revisa los homonimos de 'nombre' y resuelve si el jugador es uno existente o nuevo (Santiago).
//   Devuelve 1 si el jugador dijo ser uno de los listados (deja *sel con su registro);
//            0 si eligio NINGUNO (hay que darlo de alta).
int  revisarUsuarioRepetido(tArbolBinBusq *indice, const char *nombre,
                            FILE *fJug, regJugador *sel);

// Accion para recorrer el indice y enlistar los homonimos (la implementa Elian).
// Firma exigida por recorrerEnOrdenSimpleArbolBinBusq: (void *info, unsigned tamInfo, void *params)
void enlistarNickNames(void *idxNombre, void *contexto);

// Accion para armar una linea del menu (la implementa Manuel).
// Firma exigida por recorrerLista: (void *info, unsigned tamInfo, void *params)
void armarMensaje(void *info, void *params);

int darDeAlta(const char* nombre, const char *nickname, tArbolBinBusq* arbolIdxNombre, tArbolBinBusq* arbolIdxNick, const char* archJug, const char* archIdxNombre, const char *archIdxNick);

void guardarPartida(tJugador *jugador);

#endif // REGISTRO_H_
