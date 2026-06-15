/* stubs.c - definiciones MINIMAS para que el proyecto LINKEE.
 * Generado solo para lograr la compilacion: son funciones declaradas en los .h
 * pero que todavia nadie implemento. La logica real la completa cada modulo/dueno.
 */
#include <stdio.h>
#include "consola.h"
#include "jugador.h"
#include "registro.h"
#include "lista_simple_enlace.h"
#include "lista_doble_enlace_circular.h"

// --- consola ---
void mostrar(const char *msj)            { if(msj) printf("%s", msj); }
void mostrarEstadisticas(tJugador *j)    { (void)j; }

// --- jugador ---
void ingresarJugador(tJugador *j)        { (void)j; }

// --- registro ---
void armarMensaje(void *info, void *params) { (void)info; (void)params; }
