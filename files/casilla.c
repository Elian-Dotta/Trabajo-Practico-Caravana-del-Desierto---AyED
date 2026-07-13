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

// Funcion para insertar en casilla(lista)
int insertarEnCasilla(void **pl, unsigned *tamLista, void *d, unsigned tamDato)
{
    (void)tamLista; //no se usa
    tCasilla *casilla = (tCasilla*)(*pl); //casteo el puntero a lista a un puntero a tCasilla
    tElem  *elem = (tElem*)d; //casteo el dato a elemento de la casilla

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

// Callback de insertarAlLadoDeElemento (caso IZQ): mete 'nue' a la IZQUIERDA de 'ref'.
// Recibe punteros genericos (void*) porque el motor de la lista es generico;
// adentro los castea a los tipos reales. 'd' apunta al paquete ctxElem[2].
int insertarIzqDeElemento(void **pl, unsigned *tamLista, void *d, unsigned tamDato)
{
    (void)tamLista; (void)tamDato;          // no se usan: el molde del callback los exige igual
    tCasilla *casilla = (tCasilla*)(*pl);    // la lista de esta casilla (tipo real)
    tElem *ctxElem = (tElem*)d;              // el paquete de 2 elementos

    tElem *nue = ctxElem;                    // ctxElem[0] = el caracter nuevo a insertar
    tElem *ref = ctxElem + 1;               // ctxElem[1] = el elemento de referencia

    int ret;
    int pos = buscarPorClaveLista(casilla, ref, sizeof(tElem), cmpTipoElem); // ¿en que posicion esta 'ref'?

    ret = insertarEnPosLista(casilla, nue, sizeof(tElem), pos); // inserta EN esa pos -> empuja 'ref' a la derecha

    return ret;
}

// Callback de insertarAlLadoDeElemento (caso DER): mete 'nue' a la DERECHA de 'ref'.
// Identico al anterior, pero inserta en pos+1 (justo despues de la referencia).
int insertarDerDeElemento(void **pl, unsigned *tamLista, void *d, unsigned tamDato)
{
    (void)tamLista; (void)tamDato;
    tCasilla *casilla = (tCasilla*)(*pl);
    tElem *ctxElem = (tElem*)d;

    tElem *nue = ctxElem;                    // [0] = nuevo
    tElem *ref = ctxElem + 1;               // [1] = referencia

    int ret;
    int pos = buscarPorClaveLista(casilla, ref, sizeof(tElem), cmpTipoElem);

    ret = insertarEnPosLista(casilla, nue, sizeof(tElem), pos + 1); // pos+1 = a la derecha de 'ref'

    return ret;
}


// Callback de cambiarElemento: reemplaza el TIPO de 'ref' por el de 'nue' (misma celda).
int cambiarTipoElemento(void **pl, unsigned *tamLista, void *d, unsigned tamDato)
{
    (void)tamLista; (void)tamDato;
    tCasilla *casilla = (tCasilla*)(*pl);
    tElem *ctxElem = (tElem*)d;

    tElem *nue = ctxElem;                    // [0] = tipo nuevo
    tElem *ref = ctxElem + 1;               // [1] = tipo a buscar

    int ret;
    int pos = buscarPorClaveLista(casilla, ref, sizeof(tElem), cmpTipoElem); // ubica el elemento a cambiar

    ret = actualizarPosLista(casilla, nue, sizeof(tElem), pos, cambiarTipo); // aplica el cambio con el callback cambiarTipo

    return ret;
}

// Callback de eliminarElemento: borra de la casilla el primer elemento del tipo dado.
int eliminarDeCasillaTipo(void **pl, unsigned *tamLista, void *d, unsigned tamDato)
{
    (void)tamLista;
    tCasilla *casilla = (tCasilla*)(*pl);
    tElem  *elem = (tElem*)d;                // el elemento (solo importa su tipo_elem)

    eliminarPorClaveLista(casilla, elem, tamDato, cmpTipoElem); // LA FUNCION QUE ELIMINAR DEBE DEVOLVER EL DATO POR EL MISMO PARAMETRO

    return 1;
}

// Callback usado por cambiarTipoElemento: pisa el tipo del elemento encontrado.
// 'act' apunta al elemento que ya esta en la lista; 'd' trae el tipo nuevo.
int cambiarTipo(void **act, unsigned *tamElem, void *d, unsigned tamDato)
{
    (void)tamElem; (void)tamDato;
    tElem *elemAct = *act;                   // el elemento existente en la casilla
    tElem *elemNue = d;                      // el que trae el tipo nuevo

    elemAct->tipo_elem = elemNue->tipo_elem; // el cambio real: solo se pisa la letra del tipo

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

        movimientoBandido.id   = elem->id_elem; //guardo el id del bandido que se va a mover
        movimientoBandido.cant = resultadoDado;

        if(buscarPorClaveLista(bandInteligentes, &elem->id_elem, sizeof(tElem),cmpIdElem) == -1) //reviso si el bandido es inteligente en la lista de bandidos inteligentes
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
    der = abs(der - dado); // le resto el dado para ver porque lado es mas viable
    izq = abs(izq - dado); // los hago positivos
    return der < izq? der : (-1)*izq;  //multiplica por -1 para ir a la izquierda
}

// Distancias por izquierda y derecha
void distanciasEntreElementos(int posElem1, int posElem2, int cantCasillas, int* der, int* izq)
{
    *der = (posElem2 - posElem1 + cantCasillas) % cantCasillas; //distancia yendo de izquierda a derecha
    *izq = (posElem1 - posElem2 + cantCasillas) % cantCasillas; //distancia yendo de derecha a izquierda
    // el %cantCasillas es por si da una vuelta
}

// Actualiza el estado segun la casilla
void cambiarEstado(void *pl, void* estado)
{
    tLista *lista = (tLista*)pl;
    tEstado *est = (tEstado*)estado;
    tElem elem;
    elem.id_elem = JUGADORID;

    if(buscarPorClaveLista(lista, &elem, sizeof(tElem), cmpIdElem) != -1) //busca al jugador
    {
         recorrerLista(lista, modEstado, estado); //recorre la lista y actualiza el estado

        if ((est->tieneOasis == 1)) //// si YA tenias oasis de antes
        {
            est->tieneOasis = 0;    //lo perdes
            est->Operdido = 1;   // marca "perdido el oasis"
        }
        if (est->Oobtenido==1) //si obtuvo el oasis lo activo
        {
            est->tieneOasis=1;
        }
        if(est->tieneOasis && est->Tactiva)  // si tiene oasis y hay tormenta, se desactiva
        {
            est->Tactiva = 0;
        }
        if((est->tieneTormenta==1) && (est->Tactiva==0)) //estabas aturdido y ya NO hay tormenta
        {
            est->tieneTormenta=0;   // te recuperas
            est->Tfinalizada=1;  // marca "sali de la tormenta"
        }
        else if (est->Tactiva==1)   // hay tormenta en la casilla
        {
            if(est->tieneTormenta==1)   // y ademas ya estabas aturdido
            {
                est->Tactiva = 0;
                est->tieneTormenta = 0; // se cancela / termin�s aturdimiento
                est->Tfinalizada = 1;
            }
            else
                est->tieneTormenta=1;   // reci�n ahora qued�s aturdido

        }
        if ((est->JpierdeVida == 1)&&(est->tieneOasis==1))  // ibas a perder vida PERO ten�s escudo
        {
            if (est->Bandidos==1)   // si era un solo bandido
            {
                est->JpierdeVida=0;  // NO perd�s vida

            }
            est->tieneOasis=0;  // pero el escudo se consume
            est->Operdido=1;
        }
    }
}



// Aplica el efecto de cada elemento
void modEstado(void* e, void* est) //obtiene estado de jugador y casilla
{
    tEstado *estado = (tEstado*)est;
    tElem *casilla = (tElem*)e;         // DEBERIA DE LLAMARSE ELEMENTO.

    switch(casilla->tipo_elem)
    {
        case BANDIDO:
            estado->JpierdeVida = 1; //digo que va a perder una vida
            if(!estado->IDBandDesaparecido[0])  //solo puede atacar dos a la vez para que no protega el oasis
                estado->IDBandDesaparecido[0] = casilla->id_elem;  //agrego el id de bandido desaparecido
            else if(!estado->IDBandDesaparecido[1]) //solo puede atacar dos a la vez
                estado->IDBandDesaparecido[1] = casilla->id_elem;   //agrego el id de bandido desaparecido
            estado->Bandidos++; //cuento la cantidad de bandidos para saber si protege oasis
            estado->BandAtaca = 1; //flag bandido ataca
            break;

        case OASIS:
            estado->Oobtenido = 1; //hay oasis
            break;

        case PREMIO:
            estado->JganaPuntos = 1; //hay puntos
            break;

        case VIDAEXTRA:
            estado->JganaVida = 1; //hay vida
            break;

        case TORMENTA:
            estado->Tactiva = 1; //hay tormenta
            break;

        case SALIDA:
            estado->Jgana = 1; //hay salida
            break;
    }
}

// Callback: acumula tipos en buffer
void acumularTipoElem(void *elemVoid, void *bufVoid)
{
    tElem *elem = (tElem*)elemVoid;
    char  *buf  = (char*)bufVoid;
    unsigned n  = strlen(buf); //devuelve la cantidad de caracteres, osea la pos final

    buf[n]     = elem->tipo_elem;
    buf[n + 1] = '\0';
}

// Escribe una casilla en el archivo: [contenido] o [.] si esta vacia.
void escribirCasillaArchivo(void *casillaVoid, void *archVoid)
{
    tCasilla *casilla = (tCasilla*)casillaVoid;
    FILE     *arch    = (FILE*)archVoid;
    char      contenido[TAM_BUFFER];

    contenido[0] = '\0';
    recorrerLista(casilla, acumularTipoElem, contenido);

    (*contador)++; //para enumerar las casillas
    contenido[0] = '\0';
    recorrerLista(casilla, acumularTipoElem, contenido);
    fprintf(arch, "%02d:", *contador); //printea numero de casilla
    if(contenido[0] == '\0')
        fprintf(arch, "[.]");          // posicion vacia / ruta despejada
    else
        fprintf(arch, "[%s]", contenido);
    {
        fprintf(arch, "[%s]\n", contenido);
    }
}


// Libera los elementos de la casilla
void destruirCasilla(void **pl, void* contexto)
{
    (void)contexto;
    tCasilla *cas = (tCasilla*)pl;
    vaciarLista(cas);
}
