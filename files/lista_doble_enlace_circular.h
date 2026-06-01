#ifndef LISTA_DOBLE_ENLACE_CIRCULAR_H
#define LISTA_DOBLE_ENLACE_CIRCULAR_H

#include <string.h>
#include <stdlib.h>
#include "nodos.h"
/*
=======
#include "estado.h"
>>>>>>> origin/manuel
*/
typedef tNodoDE* tListaDE;

//  - LA LISTA DOBLEMENTE ENLAZADA SIEMPRE QUEDA APUNTANDO AL ULTIMO ELEMENTO QUE PROCESO, SEA AÑADIRLO, ACTUALIZARLO O ELIMINARLO(EN ESTE CASO QUEDA AL LADO DEL ELIMINADO)
//  - DEBE HABER UNA FUNCION DE ACTUALIZAR POSICION DE LISTA YA QUE NO VAMOS A ELIMINAR LAS CASILLAS, SOLO ACTUALIZAR SU CONTENIDO
//  - EL ACCESO A LA ESTRUCTURA NODO DEBE QUEDAR UNICAMENTE A DISPOSICION DEL TDA, SINO ROMPEMOS ENCAPSULAMIENTO
// EL ACCESO AL DATO VA A SER SIEMPRE POR UNA FUNCION DE ACUMULAR O MOSTRAR O COMPARACION, COMO PUNTERO A FUNCION ENVIADO A LA PRIMITIVA
// LAS FUNCIONES PRIMITIVAS VAN A SER HECHAS A BENEFICIO DE LA LOGICA DEL JUEGO PERO IGUAL NO VAN A SABER QUE EXISTE EL JUEGO EN SI
// EL JUEGO TAMPOCO VA A SABER DE LA EXISTENCIA DE LOS NODOS EN SI
// TABLERO NO PUEDE METERSE A LA CASILLA Y CASILLA NO PUEDE METERSE EN EL TABLERO
// TABLERO DEBE LLAMAR A FUNCIONES DE CASILLA POR MEDIO DE LISTADE, CASILLA VAN A SER FUNCIONES PARA MANEJAR LA CASILLA
// Y CASILLA VA A LLAMAR A FUNCIONES DE LISTASE



typedef int  (*Acumular)(void **, unsigned *, void *, unsigned);
typedef void (*Mostrar)(const void *);


typedef void (*Accion)(void *, void *);
typedef int  (*Cmp)(const void *, const void *);
//typedef void (*Accion)(tNodoDE **, tEstado*);

int  insertarAlFinalDeListaDE(tListaDE *pl, void *d, unsigned tamInfo);
int  actualizarPosLista(tListaDE *pl, void *d, unsigned tamInfo, unsigned pos, Acumular acum); // ESTA FUNCION FUNCIONARIA SI LA LISTADE QUEDARIA APUNTANDO AL INICIO
// PERO NO FUNCIONA ASI, LA PLANTIE ANTES DE SABER COMO FUNCIONABA LA DE. MEJOR UTILIZAR ACTUALIZAR POR ID Y POR POS RELATIVA
// COMO REEMPLAZO SE PUEDE JUSTO LUEGO DE AÑADIR UNA CASILLA A LA LISTA UTILIZAR ACTUALIZAR POR POS RELATIVA
void mostrarListaDE(tListaDE *pl, Mostrar mostrar);

void crearListaDE(tListaDE *lista);
int  vaciarListaDE(tListaDE *lista);
int  listaVaciaDE(tListaDE *lista);

int buscarPorClaveListaDE(tListaDE *lista, const void* clave, unsigned tam, Cmp cmp, Accion accion, tEstado* estado);


// ESTA FUNCION PODRIA DEVOLVER LA POSICION PERO DENUEVO, ES CIRCULAR Y DE ASI QUE QUEDA APUNTANDO AL ULTIMO ELEMENTO PROCESADO
// A LO MEJOR PODEMOS ACTUALIZAR UNA POSICION DEL TABLERO POR ID DE ELEMENTO, ESO ES UNA BUSQUEDA Y UNA ACTUALIZACION EN LA MISMA PRIMITIVA
// SINO UNA FUNCION QUE DEJE EL PUNTERO DE LA LISTA EN LA POSICION A ACTUALIZAR POR ID, Y LUEGO OTRA QUE ACTUALICE POSICION ACTUAL

int  actualizarPorClaveListaDE(tListaDE *pl, void *d, unsigned tamInfo, Cmp cmp, Acumular acum);                  // PARA ACTUALIZAR POR ID
int  actualizarPosRelativaListaDE(tListaDE *pl, void *d, unsigned tamInfo, int pos, Acumular acum);  // PARA ACTUALIZAR RELATIVO A LA ULTIMA POSICION DE PUNTERO

void recorrerListaDE(tListaDE *pl, Accion accion, void *contexto);

// PARA CHECKEAR POR EL INICIO Y EL FIN SE PUEDE BUSCAR POR ID Y DEVOLVER LA POSICION O DEJAR APUNTADO AL ULTIMO ELEMENTO
// ID ELEM INICIO = 0, ID ELEM JUG = 1, ID ELEM FIN = 2

// EL ID DE LOS BANDIDOS SE PUEDE OBTENER POR TIPO ELEM, QUE ENCUENTRE EL PRIMERO, OSEA UNA BUSQUEDA, COMO LA DE ACTUALIZAR POR CLAVE PERO SIN ACTUALIZAR
// SE BUSCA EL ID DEL BANDIDO Y SE CALCULA EL MOV QUE VA A TENER. PODRIAMOS TENER EL ID DE LOS BANDIDOS INTELIGENTES Y DE LOS NO INTELIGENTES ANOTADOS.
// PERO ESO REQUIERE UNA VARIABLE GLOBAL YA QUE LOS BANDIDOS SE ASIGNAN EN GENERAR TABLERO


//Definidas:
int insertarAlFinalHead(tListaDE *lista, const void *dato, unsigned tamDato);
/*
        Implementacion a Priori:
            - El head apuntara siempre al primer elemento insertado en la lista.
            - Considerar si vale la pena crear una estructura de forma; tListaC con referencias a nodo ultimo insertado y nodo primero insertado
                - Considerar si esa estructura debe generarse en el stack o en el heap.
            - Si se implementa la forma original de lista doblemente enlazada, donde head apunta al ultimo insertado. En lista circular, se complica
              definir cual es el primero y cual es el ultimo, al no existir CTEs NULL de identificacion.
                - Particularmente si se hacen inserciones al comienzo luego de inserciones iniciales y sucesivas el final.
                - p.ej.: una insercion al inicio, entonces head apunta al inicio. Luego insertar al final no podria realizarse a partir de head de forma generica.
                - tal vez con varios ifs¿¿ idk
            - Entiendase head como referencia a la lista en el main.
    */

#endif // LISTA_DOBLE_ENLACE_CIRCULAR_H
