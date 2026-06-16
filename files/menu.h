#ifndef MENU_H_
#define MENU_H_

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "consola.h"
#include "partida.h"
#include "ranking.h"

#define MENU_JUEGO "\
-----------------------------------\n\
\tCARAVANA DEL DESIERTO\n\
-----------------------------------\n\
[J] Jugar nueva partida\n\
[R] Ver ranking\n\
[S] Salir\n"

#define OPC_JUEGO "JRS"

#define JUGAR_PARTIDA 'J'
#define MOSTRAR_RANKING 'R'
#define SALIR_DEL_JUEGO 'S'

#define MSJ_SALIDA "Saliendo del juego...\n"

#define MSJ_ERR_OPC "Opcion invalida. Intente nuevamente.\n"

void juego();

void menuPrincipal(tJugador *jugador);

char menu(const char* msj, const char *opc, int conErr, const char *msjErr);

int  menuNum(const char* msj, int cantOpciones, int conErr, const char *msjErr);

void ingresarDato(const char* msj, char *out);




#endif // MENU_H_
