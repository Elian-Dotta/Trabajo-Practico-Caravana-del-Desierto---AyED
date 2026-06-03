#include "casilla.h"

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

void mostrarCasilla(const void *pl)
{
    tLista *casilla = pl;
    printf("[ ");
    mostrarLista(casilla, mostrarElemento);
    printf(" ] ");
}

void mostrarElemento(const void *elemVoid){
    tElem *elem = (tElem*)elemVoid;
    printf(" %c ", elem->tipo_elem);
}

void distanciasEntreElementos(int posElem1, int posElem2, int cantCasillas, int *der, int *izq){
    *der = (posElem2 - posElem1 + cantCasillas) % cantCasillas; //distancia yendo de izquierda a derecha
    *izq = (posElem1 - posElem2 + cantCasillas) % cantCasillas; //distancia yendo de derecha a izquierda
}

int compararIDtElem(const void *voidE1, const void *voidE2){
    tElem *E1 = (tElem*)voidE1;
    tElem *E2 = (tElem*)voidE2;
    return E1->id_elem - E2->id_elem; //Funciona, si. Pero para nros muy grandes puede causar OF.
}

int compararTipotElem(const void *voidE1, const void *voidE2){
    tElem *E1 = (tElem*)voidE1;
    tElem *E2 = (tElem*)voidE2;
    return E1->tipo_elem == E2->tipo_elem;
}


int elementoEnCasilla(const void *voidCasilla, const void* voidIDElemento){
/* Funcion que recibe dirección de una casilla (campo dato de nodoDE) y un la dirección de memoria de un INT que guarda un ID de tElem
   La funcion crea un tElem auxiliar a partir del ID del elemento y la usa para buscar en la lista/casilla, la existencia de un nodo
   para el cual exista ese ID.
   Si encuentra una coincidencia, retorna 0. Si no encuentra una coincidencia, retorna 1 (Invertido para que tenga sentido como funcion callout de comparacion).
   Se diseña para ser usada como una funcion de comparacion para una funcion de recorrido generica
*/
    tElem auxElem = { *((int*)voidIDElemento), '\0', 0 };
    if(NULL != buscarNodoPorClaveEnLista((tCasilla*)voidCasilla,&auxElem,compararIDtElem))
        return 0; //Cero porque es el indicador de iguales o se encontro en una funcion de recorrido
    return 1;
}
void devolverPrimerBandido(void *voidCasilla, void *contexto){
    tCasilla*      casilla        = (tCasilla*)voidCasilla;
    const tElem**  dirElemDestino = (tElem**)contexto;
    tElem          elementoClave  = {0,'B',0};

    if(NULL == *dirElemDestino)
        *dirElemDestino = (tElem*)buscarPorClaveEnLista(casilla,&elementoClave, compararTipotElem);
}
