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
    return !buscarPorClaveEnLista((tCasilla*)voidCasilla,&auxElem,NULL,compararIDtElem);
}

void devolverPrimerBandido(void *voidCasilla, void *contexto){
    tCasilla*      casilla        = (tCasilla*)voidCasilla;
    tElem*         dirElemDestino = (tElem*)contexto;
    tElem          elementoClave  = {0,'B',0};

    if(0 == dirElemDestino->id_elem)
        buscarPorClaveEnLista(casilla,&elementoClave, dirElemDestino, compararTipotElem);
}

//Accion para recorrido de listaSE
void accionCasillaACadena(void *e1, void *voidBuffer){ //Funcion de accion en recorrido de tLista, e1 es un nodo->dato
    tElem   *auxElem = (tElem*)e1;
    char    *buffer  = (char*)voidBuffer;
    unsigned longCad =  strlen(buffer);

    if(!longCad || '\n' == buffer[longCad - 1] || ' ' == buffer[longCad - 1])
        sprintf(buffer + longCad,"%c",auxElem->tipo_elem);
    else
        sprintf(buffer + longCad," %c",auxElem->tipo_elem);
}

//Accion para recorrido de ListaDE
void convertirMapaACadenaVerticalSinIndice(void *e1, void *voidBuffer){
    tCasilla  *auxCasilla = (tCasilla*)e1;
    char      *buffer     = (char*)voidBuffer;
    recorrerLista(auxCasilla, accionCasillaACadena, buffer);
    sprintf(buffer + strlen(buffer),"%c", '\n'); //pone el salto de linea
}

//Accion para recorrido de ListaDE
void convertirMapaACadenaVerticalConIndice(void *e1, void *voidBuffer){

    tCasilla  *auxCasilla = (tCasilla*)e1;
    char      *buffer     = (char*)voidBuffer;
    unsigned   longCad    =  strlen(buffer);
    unsigned   indice     = 1;

    if(!longCad) //la cadena no tiene nada inicaliza el indice
        sprintf(buffer, "%02d. ", 1);
    else{
        char *auxIni   = buffer + longCad - 1;
        int  auxIndice = longCad - 1; //indica cuanto se puede desplazarse a izquierda en la cadena

        while(auxIndice >= 0 && isdigit((unsigned char)buffer[auxIndice])){
            auxIni--;
            auxIndice--;
        }

        auxIni++; //porque al salir del while queda desplazado a una direccion sin digitos o fuera del area de control
        indice = (unsigned)atoi(auxIni);
        sprintf(buffer + strlen(buffer),"%s", ". ");
    }

    recorrerLista(auxCasilla, accionCasillaACadena, buffer);
    sprintf(buffer + strlen(buffer),"%c", '\n'); //pone el salto de linea
    sprintf(buffer + strlen(buffer), "%02d",indice + 1);
        //pone el proximo valor de indice sin el punto para no agregar condiciones de exclusion
        //cuando se llegue al final de la lista, creara un indicador "n" que no se usa, se debera borrar.
}

//Accion para recorrido de ListaDE
void convertirMapaACadenaHorizontalSinIndice(void *e1, void *voidBuffer){

    tCasilla  *auxCasilla = (tCasilla*)e1;
    char      *buffer     = (char*)voidBuffer;
    unsigned   longCadena =  strlen(buffer);

    if(0 == longCadena)
        sprintf(buffer + strlen(buffer), "%s", "[");
    else
        sprintf(buffer + strlen(buffer), "%s", " [");

    recorrerLista(auxCasilla, accionCasillaACadena, buffer);
    sprintf(buffer + strlen(buffer), "%s", " ]");
}

//Accion para recorrido de ListaDE
void convertirMapaACadenaHorizontalConIndice(void *e1, void *voidBuffer){

    tCasilla  *auxCasilla = (tCasilla*)e1;
    char      *buffer     = (char*)voidBuffer;
    unsigned   longCad    =  strlen(buffer);
    unsigned   indice     = 1;

    if(!longCad) //la cadena no tiene nada inicaliza el indice
        sprintf(buffer, "%02d.[ ", 1);
    else{
        char *auxIni   = buffer + longCad - 1;
        int  auxIndice = longCad - 1; //indica cuanto se puede desplazarse a izquierda en la cadena

        while(auxIndice >= 0 && isdigit((unsigned char)buffer[auxIndice])){
            auxIni--;
            auxIndice--;
        }

        auxIni++; //porque al salir del while queda desplazado a una direccion sin digitos o fuera del area de control
        indice = (unsigned)atoi(auxIni);
        sprintf(buffer + strlen(buffer),"%s", ".[");
    }

    recorrerLista(auxCasilla, accionCasillaACadena, buffer);
    sprintf(buffer + strlen(buffer),"%s", " ]");
    sprintf(buffer + strlen(buffer), " %02d",indice + 1);
        //pone el proximo valor de indice sin el punto para no agregar condiciones de exclusion
        //cuando se llegue al final de la lista, creara un indicador "n" que no se usa, se debera borrar.
}

void corregirCadenadeMapaConIndice(char *buffer){

    unsigned longCad   = strlen(buffer);
    char    *auxIni    = buffer + longCad - 1;
    int      auxIndice = longCad - 1; //indica cuanto se puede desplazarse a izquierda en la cadena

    if(!longCad)
        return;

    while(auxIndice >= 0 && isdigit((unsigned char)buffer[auxIndice])){
        auxIni--;
        auxIndice--;
    }

    auxIni++; // apunta al inicio del numero sobrante
    *auxIni = '\0'; // corta la cadena
}
