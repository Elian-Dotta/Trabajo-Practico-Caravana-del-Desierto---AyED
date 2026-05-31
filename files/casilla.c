#include "casilla.h"

/*
int crearCasillas(tListaDE *lista, unsigned cantCasillas){

    Esta es una funcion a la cual se le pasa por parametro la lista (mapa o tablero), y sobre la lista
    va generando N (cantCasillas) casillas (que debe recibir por config.txt)
    Requiere la funcion definida:
        - insertarAlFinalHead : Funcion de insercion al final para listas doblemente enlazadas
            - Importante: insertarAlFinalHead se define y se implementa de forma que asigna NULL a cada casilla en su campo dato. Se aclara, porque excluira el uso de crearLista()
        - vaciarListaC : Funcion de vaciado de listas doblemente enlazadas


    int cant = 0;

    while(cantCasillas--){

        if( 0 == insertarAlFinalHead(lista, NULL, 0) ){
            vaciarListaC(lista);
            return 0;
        }
        cant++;
    }

    return cant;
}


int borrarListasElementosCasillas(tListaDE *lista){

    Esta es una funcion que recorre la lista o mapa y libera cada lista se. I.e. recorre cada casilla
    Por cada casilla libera el campo "dato" que es una lista simple.
    Es decir, libera los nodos de la lista en la casilla.
    Requiere la funcion definida:
        - vaciarLista : Vaciar Lista Simplemente Enlazada


    tNodoDE *auxNodo = *lista;
    int cant = 0;

    do{
        tLista listaNodo = auxNodo->dato;
        cant += vaciarLista(&listaNodo);
        auxNodo->dato = (void**)listaNodo;
        auxNodo = auxNodo->proxNodo;
    }while(auxNodo != *lista);

    return cant;
}


int borrarCasillas(tListaDE *lista){

    Es un wrapper que libera la lista doblemente enlazada circular
    Libera cada casilla del mapa.
    Requiere la funcion definida:
        - vaciarListaC : Vaciar Lista Circular Doblemente Enlazada


//  De vaciar la lista circular se debe encargar el tablero
//  Habria que hacer un recorrer listaDE con la funcion de accion y mandar un vaciarLista de la simplemente enlazada o la funcion que llame a vaciarLista
//  Luego vaciar la listaDE en tablero
//  - E
    return vaciarListaC(lista);
}


int insertarElementoCasilla(tListaDE *lista, const tElem *elem, unsigned casilla){

    Este es una funcion que recibe por parametro la Lista DEC (mapa / tablero), la direccion de memoria de un elemento y un numero de casilla
    Con esos parametros, inserta el elemento al final de la Lista SE del nodo/casilla especificado
    Requiere la funcion definida:
        - ponerAlFinal : Insertar al Final de Listas Simplemente Enlazadas
            - Conviene un insertarOrdenado en lugar de poner al final, tal que acote la busqueda de un elemento en la lista (se cambiara despues)
             - De aplicarse, requiere un nuevo parametro (fx de comparacion).

    tNodoDE *auxNodoInsercion = *lista;
    tLista listaNodo;

    if(NULL == *lista)
        return 0;

    while(--casilla)
        auxNodoInsercion = auxNodoInsercion->proxNodo;

    listaNodo = auxNodoInsercion->dato;

    if(0 == ponerAlFinal(&listaNodo, elem, sizeof(tElem) ) )
        return 0;

    auxNodoInsercion->dato = (void**)listaNodo;

    return 1;
}
*/

tCasilla crearCasilla()
{
    tCasilla cas;

    crearLista(&cas);

    return cas;
}


int insertarEnCasilla(void **pl, unsigned *tamLista, void *d, unsigned tamDato)
{
    tCasilla *casilla = (tCasilla*)pl;
    tElem  *elem = (tElem*)d;

    insertarAlFinal(casilla, elem, tamDato);

    return 1;
}

int eliminarDeCasilla(void **pl, unsigned *tamLista, void *d, unsigned tamDato)
{
    tCasilla *casilla = (tCasilla*)pl;
    tElem  *elem = (tElem*)d;

    eliminarPorClave(casilla, elem, tamDato); // LA FUNCION QUE ELIMINAR DEBE DEVOLVER EL DATO POR EL MISMO PARAMETRO

    return 1;
}

int insertarSinDupCasilla(void **pl, unsigned *tamLista, void *d, unsigned tamDato)
{
    tCasilla *casilla = (tCasilla*)pl;
    tElem *elem = (tElem*)d;
    int ret;

    ret = insertarOrdenadoLista(casilla, elem, tamDato, cmpRestriccionCasilla, 0, NULL);
    // LA UTILIZAMOS PARA EVITAR DUPLICADOS NO PARA ORDENAR. LA FUNCION DE CMP DEVUELVE -1 SIEMPRE EXCEPTO DUPLICADOS QUE DEVUELVE 0

    return ret;
}

int  cmpRestriccionCasilla(const void *a, const void *b) // PODEMOS AGREGAR REGLAS NUEVAS DESDE ACA
{
    tElem *elemAct = (tElem*)a;
    tElem *elemNue = (tElem*)b;

    if(elemAct->tipo_elem == INICIO && elemNue->tipo_elem == BANDIDO) // EVITAMOS QUE APAREZCAN BANDIDOS EN EL INICIO
       return 0;

    if(elemAct->tipo_elem == elemNue->tipo_elem && elemNue->tipo_elem != BANDIDO) // EVITAMOS QUE APAREZCAN TIPOS REPETIDOS EXCEPTUANDO EL BANDIDO
        return 0;

    return -1;
}

void asignarNroCasilla(void *a, void *contexto)
{
    tCasilla *casilla = (tCasilla*)a;
    int *nroCasilla = (int*)contexto;

    recorrerLista(casilla, asignarNroCasElem,nroCasilla);
    (*nroCasilla)++;
}

void asignarNroCasElem(void *a, void *contexto)
{
    tElem *elem = (tElem*)a;
    int *nroCasilla = (int*)contexto;

    elem->nro_casilla = *nroCasilla;
}

void mostrarCasilla(void *pl)
{
    tLista *casilla = pl;

    mostrarLista(casilla, mostrarElemento);
}

void mostrarElemento(const void *elemVoid){ //muestra el struct tElem
    tElem *elem = (tElem*)elemVoid;
    printf(" %c ", elem->tipo_elem);
}
