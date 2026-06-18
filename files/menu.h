#ifndef MENU_H_
#define MENU_H_

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "consola.h"
#include "partida.h"
#include "ranking.h"

#define MENU_JUEGO "\n\
-----------------------------------------\n\
-                                       -\n\
-\t   CARAVANA DEL DESIERTO        -\n\
-                                       -\n\
-----------------------------------------\n\
-\t[J] Jugar nueva partida         -\n\
-\t   [R] Ver ranking              -\n\
-\t     [S] Salir                  -\n\
-                                       -\n\
Ingrese una opcion:"

#define OPC_JUEGO "JRS"

#define JUGAR_PARTIDA 'J'
#define MOSTRAR_RANKING 'R'
#define SALIR_DEL_JUEGO 'S'

#define MSJ_SALIDA "Saliendo del juego...\n"

#define MSJ_ERR_OPC "Opcion invalida. Intente nuevamente.\n"

void juego();

void menuPrincipal();

char menu(const char* msj, const char *opc, int conErr, const char *msjErr);

int  menuNum(const char* msj, int cantOpciones, int conErr, const char *msjErr);

void ingresarDato(const char* msj, char *out);




#endif // MENU_H_
