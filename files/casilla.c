// === Modulo casilla: elementos dentro de una posicion ===
#include "casilla.h"
#include "consola.h"
#include "animacion.h"

// Crea una casilla vacia
tCasilla crearCasilla()
{
    tCasilla cas;

    crearLista(&cas);

    return cas;
}

// Callback: inserta elemento al final
int insertarEnCasilla(void **pl, unsigned *tamLista, void *d, unsigned tamDato)
{
    (void)tamLista;
    tCasilla *casilla = (tCasilla*)(*pl);
    tElem  *elem = (tElem*)d;

    insertarAlFinalLista(casilla, elem, tamDato);

    return 1;
}


// Callback: elimina elemento por id
int eliminarDeCasilla(void **pl, unsigned *tamLista, void *d, unsigned tamDato)
{
    (void)tamLista;
    tCasilla *casilla = (tCasilla*)(*pl);
    tElem  *elem = (tElem*)d;

    eliminarPorClaveLista(casilla, elem, tamDato, cmpIdElem); // LA FUNCION QUE ELIMINAR DEBE DEVOLVER EL DATO POR EL MISMO PARAMETRO

    return 1;
}

// Inserta evitando tipos duplicados
int insertarSinDupCasilla(void **pl, unsigned *tamLista, void *d, unsigned tamDato)
{
    (void)tamLista;
    tCasilla *casilla = (tCasilla*)(*pl);
    tElem *elem = (tElem*)d;
    int ret;

    ret = insertarOrdenadoLista(casilla, elem, tamDato, cmpRestriccionCasilla, 0, NULL);
    // LA UTILIZAMOS PARA EVITAR DUPLICADOS NO PARA ORDENAR. LA FUNCION DE CMP DEVUELVE -1 SIEMPRE EXCEPTO DUPLICADOS QUE DEVUELVE 0


    return ret;
}

// Inserta a la izquierda de otro
int insertarIzqDeElemento(void **pl, unsigned *tamLista, void *d, unsigned tamDato)
{
    (void)tamLista; (void)tamDato;
    tCasilla *casilla = (tCasilla*)(*pl);
    tElem *ctxElem = (tElem*)d;

    tElem *nue = ctxElem;
    tElem *ref = ctxElem + 1;

    int ret;
    int pos = buscarPorClaveLista(casilla, ref, sizeof(tElem), cmpTipoElem);

    ret = insertarEnPosLista(casilla, nue, sizeof(tElem), pos);

    return ret;
}

// Inserta a la derecha de otro
int insertarDerDeElemento(void **pl, unsigned *tamLista, void *d, unsigned tamDato)
{
    (void)tamLista; (void)tamDato;
    tCasilla *casilla = (tCasilla*)(*pl);
    tElem *ctxElem = (tElem*)d;

    tElem *nue = ctxElem;
    tElem *ref = ctxElem + 1;

    int ret;
    int pos = buscarPorClaveLista(casilla, ref, sizeof(tElem), cmpTipoElem);

    ret = insertarEnPosLista(casilla, nue, sizeof(tElem), pos + 1);

    return ret;
}


// Cambia el tipo de un elemento
int cambiarTipoElemento(void **pl, unsigned *tamLista, void *d, unsigned tamDato)
{
    (void)tamLista; (void)tamDato;
    tCasilla *casilla = (tCasilla*)(*pl);
    tElem *ctxElem = (tElem*)d;

    tElem *nue = ctxElem;
    tElem *ref = ctxElem + 1;

    int ret;
    int pos = buscarPorClaveLista(casilla, ref, sizeof(tElem), cmpTipoElem);

    ret = actualizarPosLista(casilla, nue, sizeof(tElem), pos, cambiarTipo);

    return ret;
}

// Callback: elimina elemento por tipo
int eliminarDeCasillaTipo(void **pl, unsigned *tamLista, void *d, unsigned tamDato)
{
    (void)tamLista;
    tCasilla *casilla = (tCasilla*)(*pl);
    tElem  *elem = (tElem*)d;

    eliminarPorClaveLista(casilla, elem, tamDato, cmpTipoElem); // LA FUNCION QUE ELIMINAR DEBE DEVOLVER EL DATO POR EL MISMO PARAMETRO

    return 1;
}

// Callback: reemplaza el tipo
int cambiarTipo(void **act, unsigned *tamElem, void *d, unsigned tamDato)
{
    (void)tamElem; (void)tamDato;
    tElem *elemAct = *act;
    tElem *elemNue = d;

    elemAct->tipo_elem = elemNue->tipo_elem;

    return 1;
}

// Reglas de que puede convivir
int  cmpRestriccionCasilla(const void *a, const void *b) // PODEMOS AGREGAR REGLAS NUEVAS DESDE ACA
{
    tElem *elemAct = (tElem*)a;
    tElem *elemNue = (tElem*)b;

    if(elemAct->tipo_elem == INICIO && elemNue->tipo_elem != JUGADOR) // EVITAMOS QUE APAREZCAN BANDIDOS EN EL INICIO
       return 0;

    if(elemNue->tipo_elem != BANDIDO && elemAct->tipo_elem == elemNue->tipo_elem)  // EVITAMOS QUE APAREZCAN TIPOS REPETIDOS EXCEPTUANDO EL BANDIDO
        return 0;

    /*
    #define INICIO 'I'
    #define JUGADOR 'J'
    #define SALIDA 'S'
    #define BANDIDO 'B'
    #define TORMENTA 'T'
    #define PREMIO 'P'
    #define OASIS 'O'
    #define VIDAEXTRA 'V'
    */

    // Un bandido nuevo nunca se considera "duplicado" (cmp != 0): asi pueden
    // apilarse varios bandidos en una misma casilla (la excepcion a tipos unicos).
    return elemNue->tipo_elem != BANDIDO
           ? prioridadElem(elemAct->tipo_elem) - prioridadElem(elemNue->tipo_elem)
           : -1;
}

// Prioridad de dibujo de cada tipo
int prioridadElem(char tipo)
{
    switch(tipo)
    {
        case INICIO:        return 1;
        case SALIDA:        return 2;
        case JUGADOR:       return 3;
        case OASIS:         return 4;
        case TORMENTA:      return 5;
        case VIDAEXTRA:     return 6;
        case PREMIO:        return 7;
        case BANDIDO:       return 8;

        case ASTERISCO:     return 200;
        case ARENA1:        return 201;
        case ARENA2:        return 202;
        case ARENA3:        return 203;
        case ARENA4:        return 204;
        case ATURDIDOIZQ:   return 205;
        case ATURDIDODER:   return 206;
        case PUNALIZQ:      return 207;
        case PUNALDER:      return 208;
        case MANGO:         return 209;
        case FLECHAIZQ:     return 210;
        case FLECHADER:     return 211;
        case DESAPARECE:    return 212;
        case OASISACTIVO:   return 213;
        case ESCUDOIZQ:     return 214;
        case ESCUDODER:     return 215;
        case ESCUDOCAIDO:   return 216;
        case JUGMINUS:      return 217;
        case BANMINUS:      return 218;

        default:            return 999;
    }
}

// Compara: casilla contiene ese id
int  cmpCasIdElem(const void *a, const void *b)
{
    tCasilla *cas = (tCasilla*)a;
    tElem *elem = (tElem*)b;

    int ret = buscarPorClaveLista(cas, elem, sizeof(tElem), cmpIdElem);

    if(ret != -1)
        return 0;
    else
        return 1;
}

// Compara: casilla contiene ese tipo
int  cmpCasTipoElem(const void *a, const void *b)
{
    tCasilla *cas = (tCasilla*)a;
    tElem *elem = (tElem*)b;

    int ret = buscarPorClaveLista(cas, elem, sizeof(tElem), cmpTipoElem);

    if(ret != -1)
        return 0;
    else
        return 1;
}

// Compara dos elementos por id
int  cmpIdElem(const void *a, const void *b)
{
    tElem *e1 = (tElem*)a;
    tElem *e2 = (tElem*)b;

    return e1->id_elem - e2->id_elem;
}

// Compara dos elementos por tipo
int  cmpTipoElem(const void *a, const void *b)
{
    tElem *e1 = (tElem*)a;
    tElem *e2 = (tElem*)b;

    return prioridadElem(e1->tipo_elem) - prioridadElem(e2->tipo_elem);
}

// Compara: casilla tiene ambos tipos
int  cmpCasTipos(const void *a, const void *b)
{
    tCasilla* cas = (tCasilla*)a;
    char* tipos = (char*)b;
    tElem elem;
    int tiene1,
        tiene2;

    elem.tipo_elem = tipos[0];
    tiene1 = buscarPorClaveLista(cas, &elem, sizeof(tElem), cmpTipoElem);
    elem.tipo_elem = tipos[1];
    tiene2 = buscarPorClaveLista(cas, &elem, sizeof(tElem), cmpTipoElem);

    return tiene1 && tiene2;
}

// Numera la casilla y sus elementos
void asignarNroCasilla(void *a, void *contexto)
{
    tCasilla *casilla = (tCasilla*)a;
    int *nroCasilla = (int*)contexto;

    recorrerLista(casilla, asignarNroCasElem,nroCasilla);
    (*nroCasilla)++;
}

// Asigna numero de casilla al elemento
void asignarNroCasElem(void *a, void *contexto)
{
    tElem *elem = (tElem*)a;
    int *nroCasilla = (int*)contexto;

    elem->nro_casilla = *nroCasilla;
}


// Callback: dibuja una casilla
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

// Callback: dibuja un elemento
void mostrarElemento(const void *elemVoid)
{
    tElem *elem = (tElem*)elemVoid;
    char buffer[3];
    snprintf(buffer, sizeof(buffer), "%c", elem->tipo_elem);
    mostrar(buffer);
}


// Recorre la casilla buscando bandidos
void calcularMovBandido(void *pl, void* contexto)
{
    tCasilla *cas = (tCasilla*)pl;

    recorrerLista(cas, buscarYCalcularBandido, contexto);
}

// Genera el movimiento de un bandido
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

        if(buscarPorClaveLista(bandInteligentes, &elem->id_elem, sizeof(tElem),cmpIdElem) == -1)
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

// Menor distancia en ruta circular
int devolverMenorDistanciaEntreElementos(int posElem1, int posElem2, int cantidadCasillas, int dado){
    // DEVUELVE LA MENOR DISTANCIA ENTRE DOS ELEMENTOS, SI ESA MENOR DISTANCIA SE ENCUENTRA
    // YENDO DE DE LA POS ACTUAL A IZQUIERDA, LA DEVUELVE EN NEGATIVO
    int der, izq;
    distanciasEntreElementos(posElem1, posElem2, cantidadCasillas, &der, &izq);
    der = abs(der - dado);
    izq = abs(izq - dado);
    return der < izq? der : (-1)*izq;
}

// Distancias por izquierda y derecha
void distanciasEntreElementos(int posElem1, int posElem2, int cantCasillas, int* der, int* izq)
{
    *der = (posElem2 - posElem1 + cantCasillas) % cantCasillas; //distancia yendo de izquierda a derecha
    *izq = (posElem1 - posElem2 + cantCasillas) % cantCasillas; //distancia yendo de derecha a izquierda
}

// Actualiza el estado segun la casilla
void cambiarEstado(void *pl, void* estado)
{
    tLista *lista = (tLista*)pl;
    tEstado *est = (tEstado*)estado;
    tElem elem;
    elem.id_elem = JUGADORID;

    if(buscarPorClaveLista(lista, &elem, sizeof(tElem), cmpIdElem) != -1)
    {
         recorrerLista(lista, modEstado, estado);

        if ((est->tieneOasis == 1))
        {
            est->tieneOasis = 0;
            est->Operdido = 1;
        }
        if (est->Oobtenido==1)
        {
            est->tieneOasis=1;
        }
        if(est->tieneOasis && est->Tactiva)
        {
            est->Tactiva = 0;
        }
        if((est->tieneTormenta==1) && (est->Tactiva==0))
        {
            est->tieneTormenta=0;
            est->Tfinalizada=1;
        }
        else if (est->Tactiva==1)
        {
            if(est->tieneTormenta==1)
            {
                est->Tactiva = 0;
                est->tieneTormenta = 0;
                est->Tfinalizada = 1;
            }
            else
                est->tieneTormenta=1;

        }
        if ((est->JpierdeVida == 1)&&(est->tieneOasis==1))
        {
            if (est->Bandidos==1)
            {
                est->JpierdeVida=0;

            }
            est->tieneOasis=0;
            est->Operdido=1;
        }
    }
}



// Aplica el efecto de cada elemento
void modEstado(void* e, void* est)
{
    tEstado *estado = (tEstado*)est;
    tElem *casilla = (tElem*)e;         // DEBERIA DE LLAMARSE ELEMENTO.

    switch(casilla->tipo_elem)
    {
        case BANDIDO:
            estado->JpierdeVida = 1;
            if(!estado->IDBandDesaparecido[0])
                estado->IDBandDesaparecido[0] = casilla->id_elem;
            else if(!estado->IDBandDesaparecido[1])
                estado->IDBandDesaparecido[1] = casilla->id_elem;
            estado->Bandidos++;
            estado->BandAtaca = 1;
            break;

        case OASIS:
            estado->Oobtenido = 1;
            break;

        case PREMIO:
            estado->JganaPuntos = 1;
            break;

        case VIDAEXTRA:
            estado->JganaVida = 1;
            break;

        case TORMENTA:
            estado->Tactiva = 1;
            break;

        case SALIDA:
            estado->Jgana = 1;
            break;
    }
}

// Callback: acumula tipos en buffer
void acumularTipoElem(void *elemVoid, void *bufVoid)
{
    tElem *elem = (tElem*)elemVoid;
    char  *buf  = (char*)bufVoid;
    unsigned n  = strlen(buf);

    buf[n]     = elem->tipo_elem;
    buf[n + 1] = '\0';
}

// Escribe una casilla en el archivo: [contenido] o [.] si esta vacia.
// Escribe una casilla en el archivo
void escribirCasillaArchivo(void *casillaVoid, void *archVoid)
{
    tCasilla *casilla = (tCasilla*)casillaVoid;
    FILE     *arch    = (FILE*)archVoid;
    char      contenido[TAM_BUFFER];

    contenido[0] = '\0';
    recorrerLista(casilla, acumularTipoElem, contenido);

    if(contenido[0] == '\0')
        fprintf(arch, "[.]");          // posicion vacia / ruta despejada
    else
        fprintf(arch, "[%s]", contenido);
}


// Libera los elementos de la casilla
void destruirCasilla(void **pl, void* contexto)
{
    (void)contexto;
    tCasilla *cas = (tCasilla*)pl;
    vaciarLista(cas);
}
