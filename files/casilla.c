#include "casilla.h"

int crearCasillas(tListaDE *lista, unsigned cantCasillas){
/*
    Esta es una funcion a la cual se le pasa por parametro la lista (mapa o tablero), y sobre la lista
    va generando N (cantCasillas) casillas (que debe recibir por config.txt)
    Requiere la funcion definida:
        - insertarAlFinalHead : Funcion de insercion al final para listas doblemente enlazadas
            - Importante: insertarAlFinalHead se define y se implementa de forma que asigna NULL a cada casilla en su campo dato. Se aclara, porque excluira el uso de crearLista()
        - vaciarListaC : Funcion de vaciado de listas doblemente enlazadas
*/

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
/*
    Esta es una funcion que recorre la lista o mapa y libera cada lista se. I.e. recorre cada casilla
    Por cada casilla libera el campo "dato" que es una lista simple.
    Es decir, libera los nodos de la lista en la casilla.
    Requiere la funcion definida:
        - vaciarLista : Vaciar Lista Simplemente Enlazada
*/

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
/*
    Es un wrapper que libera la lista doblemente enlazada circular
    Libera cada casilla del mapa.
    Requiere la funcion definida:
        - vaciarListaC : Vaciar Lista Circular Doblemente Enlazada
*/
    return vaciarListaC(lista);
}


int insertarElementoCasilla(tListaDE *lista, const tElem *elem, unsigned casilla){
/*
    Este es una funcion que recibe por parametro la Lista DEC (mapa / tablero), la direccion de memoria de un elemento y un numero de casilla
    Con esos parametros, inserta el elemento al final de la Lista SE del nodo/casilla especificado
    Requiere la funcion definida:
        - ponerAlFinal : Insertar al Final de Listas Simplemente Enlazadas
            - Conviene un insertarOrdenado en lugar de poner al final, tal que acote la busqueda de un elemento en la lista (se cambiara despues)
             - De aplicarse, requiere un nuevo parametro (fx de comparacion).
*/
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


int compararIDsElem(const void *e1Void, const void *e2Void){

    tElem *elem1 = (tElem*)e1Void;
    tElem *elem2 = (tElem*)e2Void;

    if(elem1->id_elem > elem2->id_elem) return 1;
    if(elem1->id_elem < elem2->id_elem) return -1;

    return 0;
}


int insertarElementoCasillaOrdenado(tListaDE *lista, const tElem *elem, unsigned casilla, int(*comparar)(const void*, const void*)){
/*
    Funcion que realiza lo mismo que "insertarElementoCasilla(), pero en este caso, inserta ordenado en la lista
*/
    tNodoDE *auxNodoInsercion = *lista;
    tLista listaNodo;

    if(NULL == *lista)
        return 0;

    while(--casilla)
        auxNodoInsercion = auxNodoInsercion->proxNodo;

    listaNodo = auxNodoInsercion->dato;

    if(0 == insertarOrdenado(&listaNodo, elem, sizeof(tElem), comparar) )
        return 0;

    auxNodoInsercion->dato = (void**)listaNodo;

    return 1;
}

// Ver si se puede simplificar el recorrido de insertar en mapa elementos, al momento de la generacion, manteniendo referencia de algun "cursor" en la funcion llamadora
// que indique el nodo actual modificado, tal que no se recorra siempre desde el inicio la lista.

int moverElementoPorID(tListaDE *lista, unsigned id, char mov, int(*comparar)(const void *, const void *)){
/*
    Funcion que recibe la lista doblemente enlazada o mapa, un id de elemento (procurar ids distintos), el movimiento y una funcion de comparacion.
    Mueve segun lo definido en "mov" posiciones uno a uno. Es decir, una ejecucion de esta funcion solo movera 1 posicion.
    Ver si combiene que retorne info sobre si la casilla destino tiene un elemento I o F para manejar movimientos del jugador
    Ver si combiene definir una variable N, tal que el movimiento sea segun esa cantidad N, tal que no se llame tantas veces a la funcion.
*/

    tNodoDE *auxNodoDE = *lista;
    tLista  auxListaSE;
    tNodo   *elemSEMover = NULL;
    tElem   auxElem = {id, ' '};

    if(NULL == auxNodoDE)
        return 0; // El mapa no fue generado

    if('F' != mov && 'B' != mov) //F: Adelante - B: Atras
        return 0; // No es un movimiento valido.

    do{
        auxListaSE = (tLista)auxNodoDE->dato;
            desenlazarNodoPorClave(&auxListaSE, &elemSEMover, &auxElem, comparar);
        auxNodoDE->dato = (void*)auxListaSE;
        auxNodoDE = auxNodoDE->proxNodo;
    }while(auxNodoDE != *lista && NULL == elemSEMover);

    if(NULL == elemSEMover)
        return 0; // Elemento no encontrado en el mapa.

    auxNodoDE = ('F' == mov)?auxNodoDE:auxNodoDE->antNodo->antNodo;
    auxListaSE = (tLista)auxNodoDE->dato;
    enlazarNodoOrdenado(&auxListaSE, elemSEMover, comparar);
    auxNodoDE->dato = (void*)auxListaSE;

    return 1;
}


/*
tLista crearCasilla()
{
    tLista cas;

    crearLista(&cas);

    return cas;
}


int insertarEnCasilla(void **pl, unsigned *tamLista, void *d, unsigned tamDato)
{
    tLista *casilla = pl;
    tElem  *elem = d;

    insertarAlFinal(casilla, elem, tamDato);

    return 1;
}
*/
