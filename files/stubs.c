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

int insertarOrdenadoLista(tLista *lista, const void *dato, unsigned tamDato,
                          tCompararFn comparar, int conDup, Acumular acum)
{ (void)comparar; (void)conDup; (void)acum; return ponerAlFinal(lista, dato, tamDato); }

int insertarEnPosLista(tLista *lista, void *d, unsigned tamDato, unsigned pos)
{ (void)pos; return ponerAlFinal(lista, d, tamDato); }

int sacarUltimoLista(tLista *lista, void *dest, unsigned tamDest)
{ (void)lista; (void)dest; (void)tamDest; return 0; }

int eliminarPorClaveLista(tLista *lista, void *d, unsigned tamDato, Cmp cmp)
{ return eliminarPorClave(lista, d, tamDato, cmp); }

int actualizarPosLista(tLista *lista, void *d, unsigned tamDato, unsigned pos, Acumular acum)
{ (void)lista; (void)d; (void)tamDato; (void)pos; (void)acum; return 0; }

int buscarPorClaveLista(tLista *lista, void *d, unsigned tamDato, Cmp cmp)
{ (void)lista; (void)d; (void)tamDato; (void)cmp; return 0; }

// --- lista doble circular ---
int actualizarPorClaveListaDE(tListaDE *pl, void *d, unsigned tamInfo, Cmp cmp, Acumular acum)
{
    if(buscarPorClaveListaDE(pl, d, tamInfo, cmp))
        return acum(&(*pl)->info, &(*pl)->tamInfo, d, tamInfo);
    return 0;
}
