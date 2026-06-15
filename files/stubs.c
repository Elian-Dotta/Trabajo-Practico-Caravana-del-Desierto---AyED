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

// --- lista simple (declaradas en lista_simple_enlace.h, sin cuerpo) ---
int insertarAlFinalLista(tLista *lista, const void *d, unsigned tamDato)
{ return ponerAlFinal(lista, d, tamDato); }

int eliminarPorClaveLista(tLista *lista, void *d, unsigned tamDato, Cmp cmp)
{ return eliminarPorClave(lista, d, tamDato, cmp); }

// --- lista doble circular ---
int actualizarPorClaveListaDE(tListaDE *pl, void *d, unsigned tamInfo, Cmp cmp, Acumular acum)
{
    if(buscarPorClaveListaDE(pl, d, tamInfo, cmp))
        return acum(&(*pl)->info, &(*pl)->tamInfo, d, tamInfo);
    return 0;
}
