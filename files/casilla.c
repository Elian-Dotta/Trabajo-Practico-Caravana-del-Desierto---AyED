#include "casilla.h"
#include "consola.h"

tCasilla crearCasilla()
{
    tCasilla cas;

    crearLista(&cas);

    return cas;
}

int insertarEnCasilla(void **pl, unsigned *tamLista, void *d, unsigned tamDato)
{
    tCasilla *casilla = *(tCasilla**)pl;
    tElem  *elem = (tElem*)d;

    insertarAlFinalLista(casilla, elem, tamDato);

    return 1;
}


int eliminarDeCasilla(void **pl, unsigned *tamLista, void *d, unsigned tamDato)
{
    tCasilla *casilla = *(tCasilla**)pl;
    tElem  *elem = (tElem*)d;

    eliminarPorClaveLista(casilla, elem, tamDato, cmpIdElem); // LA FUNCION QUE ELIMINAR DEBE DEVOLVER EL DATO POR EL MISMO PARAMETRO

    return 1;
}

// Igual que eliminarDeCasilla pero compara por TIPO (para las animaciones: ELIM por simbolo)
int eliminarTipoDeCasilla(void **pl, unsigned *tamLista, void *d, unsigned tamDato)
{
    tCasilla *casilla = *(tCasilla**)pl;
    tElem  *elem = (tElem*)d;

    eliminarPorClaveLista(casilla, elem, tamDato, cmpTipoElem);

    return 1;
}

int insertarSinDupCasilla(void **pl, unsigned *tamLista, void *d, unsigned tamDato)
{
    tCasilla *casilla = *(tCasilla**)pl;
    tElem *elem = (tElem*)d;
    int ret;

    ret = insertarOrdenadoLista(casilla, elem, tamDato, cmpRestriccionCasilla, 0, NULL);
    // LA UTILIZAMOS PARA EVITAR DUPLICADOS NO PARA ORDENAR. LA FUNCION DE CMP DEVUELVE -1 SIEMPRE EXCEPTO DUPLICADOS QUE DEVUELVE 0

    return ret;
}

int insertarIzqDeElemento(void **pl, unsigned *tamLista, void *d, unsigned tamDato)
{
    tCasilla *casilla = *(tCasilla**)pl;
    tElem *ctxElem = (tElem*)d;

    tElem *nue = ctxElem;
    tElem *ref = ctxElem + 1;

    int ret;
    int pos = buscarPorClaveLista(casilla, ref, sizeof(tElem), cmpTipoElem);

    ret = insertarEnPosLista(casilla, nue, sizeof(tElem), pos);

    return ret;
}

int insertarDerDeElemento(void **pl, unsigned *tamLista, void *d, unsigned tamDato)
{
    tCasilla *casilla = *(tCasilla**)pl;
    tElem *ctxElem = (tElem*)d;

    tElem *nue = ctxElem;
    tElem *ref = ctxElem + 1;

    int ret;
    int pos = buscarPorClaveLista(casilla, ref, sizeof(tElem), cmpTipoElem);

    ret = insertarEnPosLista(casilla, nue, sizeof(tElem), pos + 1);

    return ret;
}

int cambiarTipoElemento(void **pl, unsigned *tamLista, void *d, unsigned tamDato)
{
    tCasilla *casilla = *(tCasilla**)pl;
    tElem *ctxElem = (tElem*)d;

    tElem *nue = ctxElem;
    tElem *ref = ctxElem + 1;

    int ret;
    int pos = buscarPorClaveLista(casilla, ref, sizeof(tElem), cmpTipoElem);

    ret = actualizarPosLista(casilla, nue, sizeof(tElem), pos, cambiarTipo);

    return ret;
}

int cambiarTipo(void **act, unsigned *tamElem, void *d, unsigned tamDato)
{
    tElem *elemAct = *act;
    tElem *elemNue = d;

    elemAct->tipo_elem = elemNue->tipo_elem;

    return 1;
}

int  cmpRestriccionCasilla(const void *a, const void *b) // PODEMOS AGREGAR REGLAS NUEVAS DESDE ACA
{
    tElem *elemAct = (tElem*)a;
    tElem *elemNue = (tElem*)b;

    if(elemAct->tipo_elem == SALIDA)  // EN LA SALIDA NO PUEDE APARECER NADA MAS QUE LA SALIDA
        return 0;

    // OASIS y TORMENTA no pueden estar en la misma casilla
    if((elemAct->tipo_elem == OASIS    && elemNue->tipo_elem == TORMENTA) ||
       (elemAct->tipo_elem == TORMENTA && elemNue->tipo_elem == OASIS))
        return 0;

    if(elemAct->tipo_elem == INICIO && elemNue->tipo_elem == BANDIDO) // EVITAMOS QUE APAREZCAN BANDIDOS EN EL INICIO
       return 0;

    if(elemAct->tipo_elem == elemNue->tipo_elem && elemNue->tipo_elem != BANDIDO) // EVITAMOS QUE APAREZCAN TIPOS REPETIDOS EXCEPTUANDO EL BANDIDO
        return 0;

    return -1;
}

int  cmpCasIdElem(const void *a, const void *b)
{
    tCasilla *cas = (tCasilla*)a;
    tElem *elem = (tElem*)b;   // sirve de clave de busqueda Y de destino del elemento hallado

    // 0 = la casilla contiene el elemento (match para la lista DE), 1 = no lo contiene
    return buscarPorClaveEnLista(cas, elem, elem, sizeof(tElem), cmpIdElem) ? 0 : 1;
}

int  cmpCasTipoElem(const void *a, const void *b)
{
    tCasilla *cas = (tCasilla*)a;
    tElem *elem = (tElem*)b;   // sirve de clave de busqueda Y de destino del elemento hallado

    // 0 = la casilla contiene un elemento de ese tipo (match para la lista DE), 1 = no
    return buscarPorClaveEnLista(cas, elem, elem, sizeof(tElem), cmpTipoElem) ? 0 : 1;
}

int  cmpIdElem(const void *a, const void *b)
{
    tElem *e1 = (tElem*)a;
    tElem *e2 = (tElem*)b;

    return e1->id_elem - e2->id_elem;
}

int  cmpTipoElem(const void *a, const void *b)
{
    tElem *e1 = (tElem*)a;
    tElem *e2 = (tElem*)b;

    return e1->tipo_elem - e2->tipo_elem;   // 0 si son del mismo tipo (convencion estandar)
}

int  cmpCasTipos(const void *a, const void *b)
{
    tCasilla* cas = (tCasilla*)a;
    char* tipos = (char*)b;
    tElem elem;
    int tiene1,
        tiene2;

    elem.tipo_elem = tipos[0];
    tiene1 = buscarPorClaveEnLista(cas, &elem, NULL, 0, cmpTipoElem);
    elem.tipo_elem = tipos[1];
    tiene2 = buscarPorClaveEnLista(cas, &elem, NULL, 0, cmpTipoElem);

    // 0 = la casilla tiene ambos tipos (match para la lista DE), 1 = no
    return (tiene1 && tiene2) ? 0 : 1;
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


void mostrarCasilla(const void *pl)
{
    const tCasilla *casilla = (const tCasilla*)pl;
    char buffer[TAM_BUFFER];
    snprintf(buffer, TAM_BUFFER, "[");
    mostrar(buffer);
    mostrarLista(casilla, mostrarElemento);
    snprintf(buffer, TAM_BUFFER, "]");
    mostrar(buffer);
}

void mostrarElemento(const void *elemVoid)
{
    tElem *elem = (tElem*)elemVoid;
    char buffer[3];
    snprintf(buffer, sizeof(buffer), "%c", elem->tipo_elem);
    mostrar(buffer);
}


void calcularMovBandido(void *pl, void* contexto)
{
    tCasilla *cas = (tCasilla*)pl;

    recorrerLista(cas, buscarYCalcularBandido, contexto);
}

void buscarYCalcularBandido(void *e, void *contexto)
{
    tElem *elem = (tElem*)e;

    void **ctx = (void**)contexto;

    tCola *movimientos       = (tCola*)ctx[0];
    tLista *bandInteligentes = (tLista*)ctx[1];
    int *posJug              = (int*)ctx[2];
    int *cantPos             = (int*)ctx[3];
    tMovimiento movimientoBandido;
    int resultadoDado;

    if(elem->tipo_elem == BANDIDO)
    {
        resultadoDado = tirarDado(1, 6);

        movimientoBandido.id   = elem->id_elem;
        movimientoBandido.cant = resultadoDado;

        if(0 == buscarPorClaveLista(bandInteligentes, &elem->id_elem, sizeof(tElem),cmpIdElem))
        {
            movimientoBandido.dir = tirarDado(0,1)?'F':'B';
        }
        else{
            int movDir = devolverMenorDistanciaEntreElementos(elem->nro_casilla, *posJug, *cantPos, resultadoDado);
            movimientoBandido.dir = movDir>0?'F':'B';
        }

        ponerEnCola(movimientos, &movimientoBandido, sizeof(tMovimiento));
    }
}

int devolverMenorDistanciaEntreElementos(int posElem1, int posElem2, int cantidadCasillas, int dado){
    // DEVUELVE LA MENOR DISTANCIA ENTRE DOS ELEMENTOS, SI ESA MENOR DISTANCIA SE ENCUENTRA
    // YENDO DE DE LA POS ACTUAL A IZQUIERDA, LA DEVUELVE EN NEGATIVO
    int der, izq;
    distanciasEntreElementos(posElem1, posElem2, cantidadCasillas, &der, &izq);
    der = abs(der - dado);
    izq = abs(izq - dado);
    return der < izq? der : (-1)*izq;
}

void distanciasEntreElementos(int posElem1, int posElem2, int cantCasillas, int* der, int* izq)
{
    *der = (posElem2 - posElem1 + cantCasillas) % cantCasillas; //distancia yendo de izquierda a derecha
    *izq = (posElem1 - posElem2 + cantCasillas) % cantCasillas; //distancia yendo de derecha a izquierda
}

void cambiarEstado(void *pl, void* estado)
{
    // Solo detecta que hay en la casilla del jugador (setea los flags crudos del estado).
    // La logica de inmunidad/turno perdido la maneja dibujarAnimacionEstado.
    tLista *lista = (tLista*)pl;
    tElem elem;
    elem.id_elem = JUGADORID;

    if(buscarPorClaveLista(lista, &elem, sizeof(tElem), cmpIdElem) != -1)
        recorrerLista(lista, modEstado, estado);
}



void modEstado(void* est, void* e)
{
    // recorrerLista llama accion(info, contexto): 1er arg = elemento, 2do = estado
    tElem   *casilla = (tElem*)est;     // el elemento de la casilla (mal llamado 'casilla')
    tEstado *estado  = (tEstado*)e;     // el estado del juego (contexto)

    if (casilla->tipo_elem == BANDIDO)
    {
        estado->JpierdeVida = 1;
        estado->IDBandDesaparecido=(casilla)->id_elem;
        estado->Bandidos++;
        estado->BandAtaca = 1;
    }
    if (casilla->tipo_elem == OASIS)
    {
        estado->Oobtenido=1;
    }
    if (casilla->tipo_elem == PREMIO)
    {
        estado->JganaPuntos=1;
    }
    if (casilla->tipo_elem == VIDAEXTRA)
    {
        estado->JganaVida=1;
    }
    if (casilla->tipo_elem == TORMENTA)
    {
        estado->Tactiva=1;
    }
    if (casilla->tipo_elem == SALIDA)
    {
        estado->Jgana=1;
    }

}


void destruirCasilla(void **pl, void* contexto)
{
    tCasilla *cas = (tCasilla*)pl;
    vaciarLista(cas);
}
