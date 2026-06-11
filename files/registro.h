#ifndef REGISTRO_H_
#define REGISTRO_H_

#include <stdio.h>
#include "arbol.h"

// MODULO USADO PARA EL GUARDADO DE PARTIDA Y JUGADOR.

typedef struct
{
    char nombre[31];
    char nickname[11];
} regJugador;        // REGISTRO DEL ARCHIVO JUGADORES

typedef struct
{
    char     nombre[31];
    unsigned indiceRegistro;
} tIndiceNombre;     // TIPO DEL INDICE (clave: nombre, valor: indice de registro en jugadores)


#define TAM_MENU 512

// Revisa los homonimos de 'nombre' y resuelve si el jugador es uno existente o nuevo (Santiago).
//   Devuelve 1 si el jugador dijo ser uno de los listados (deja *sel con su registro);
//            0 si eligio NINGUNO (hay que darlo de alta).
int  revisarUsuarioRepetido(tArbolBinBusq *indice, const char *nombre,
                            FILE *fJug, regJugador *sel);

// Accion para recorrer el indice y enlistar los homonimos (la implementa Elian).
// Firma exigida por recorrerEnOrdenSimpleArbolBinBusq: (void *info, unsigned tamInfo, void *params)
void enlistarNickNames(void *info, unsigned tamInfo, void *params);

// Accion para armar una linea del menu (la implementa Manuel).
// Firma exigida por recorrerLista: (void *info, unsigned tamInfo, void *params)
void armarMensaje(void *info, unsigned tamInfo, void *params);


#endif // REGISTRO_H_
