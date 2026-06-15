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
\t   CARAVANA DEL DESIERTO\n\
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

void menuPrincipal();

char menu(const char* msj, const char *opc, int conErr, const char *msjErr);

int  menuNum(const char* msj, int cantOpciones, int conErr, const char *msjErr);

void ingresarDato(const char* msj, char *out);

void mensajeSeparador(int margenIzqConsola, int cantLugares, int inicio);
void mensajeLineaVacia(int margenIzqConsola, int cantLugares);
void mensajeEnLinea(int margenIzqConsola, int cantLugares, const char* msj, int margenIzqTabla);
void mensajeEnLineaCentrado(int margenIzqConsola, int cantLugares, const char* msj);
void mensajeIngresoCadena(int margenIzqConsola, int cantLugares, char* buffer, int maxLenBuffer, int margenIzqTabla);
void ingresarDatosJugador(char *buffer, const char *msj, int maxLenBuffer, int cantEspacios, int margenIzqConsola, int margenIzqTabla);



#endif // MENU_H_
