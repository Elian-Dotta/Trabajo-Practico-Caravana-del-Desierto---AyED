#include "jugador.h"

void inicializarJugador(tJugador* j, unsigned vida)
{
    j->vida = vida;
    j->cantMov = 0;
    j->puntaje = 0;
    j->posJug = 1;
    crearCola(&j->hisMovJugador);
}

void aumentarVida(tJugador* j)
{
    j->vida++;
}

void disminuirVida(tJugador* j)
{
    j->vida--;
}

unsigned verVida(const tJugador* j)
{
    return j->vida;
}

void aumentarPuntaje(tJugador *j)
{
    j->puntaje++;
}

unsigned verPuntaje(const tJugador *j)
{
    return j->puntaje;
}

void aumentarMovimiento(tJugador *j)
{
    j->cantMov++;
}

unsigned verMovimiento(const tJugador *j)
{
    return j->cantMov;
}

void modificarPosJug(tJugador *j, int pos)
{
    j->posJug = pos;
}

unsigned verPosJugador(const tJugador *j)
{
    return j->posJug;
}

void guardarNombreYNick(tJugador *j, const char *nombre, const char* nick)
{
    strcpy(j->nombre, nombre);
    strcpy(j->nickname, nick);
}

const char* verNombre(const tJugador *j)
{
    return j->nombre;
}

const char* verNick(const tJugador *j)
{
    return j->nickname;
}

void guardarMovimientoJugador(tJugador *j, tMovimiento *mov)
{
    ponerEnCola(&j->hisMovJugador, mov, sizeof(tMovimiento));
}

void mostrarMovimientosJugador(tJugador *j)
{
    tMovimiento mov;
    char buffer[TAM];
    unsigned contador = 0;
    mostrar("El jugador realizo los siguientes movimientos:\n");
    mostrar("(NF - N lugares hacia adelante, NB - N lugares hacia atras)\n\n");
    while(!colaVacia(&j->hisMovJugador))
    {
        sacarDeCola(&j->hisMovJugador, &mov, sizeof(tMovimiento));
        snprintf(buffer, sizeof(buffer), "[%d%c]", mov->cant, mov->dir);
        mostrar(buffer);
        contador++;

        if(contador % MAX_MOV_LINEA == 0)
            mostrar("\n");
    }
}

int pedirNombreYMostrarHomonimos(tArbolBinBusq *arbolIdxNombre, const char *archJug, regJugador *sel, char *nombreOut)
{
    char  nombre[31];
    FILE *fJug;
    int   resultado;

    mensajeIngresarDatosJugador(nombre, "Ingresa tu nombre:", 31, 40, 2, 2);

    strcpy(nombreOut, nombre);

    fJug = fopen(archJug, "rb");
    if(!fJug)
        return 0;

    resultado = revisarUsuarioRepetido(arbolIdxNombre, nombre, fJug, sel);
    fclose(fJug);
    return resultado;
}

int pedirYRegistrarNickname( const char    *nombre, tArbolBinBusq *arbolIdxNombre, tArbolBinBusq *arbolIdxNick, const char *archJug,
                             const char    *archIdxNombre,
                             const char    *archIdxNick,
                             char          *nicknameDest)
{
    char            nickname[11];
    tIndiceNickname busqueda;
    int             existe;

    do
    {
        mensajeIngresarDatosJugador(nickname, "Ingresa tu nickname:", 11, 40,2,2);

        strncpy(busqueda.nickname, nickname, sizeof(busqueda.nickname) - 1);
        busqueda.nickname[sizeof(busqueda.nickname) - 1] = '\0';
        busqueda.indiceRegistro = 0;

        existe = buscarElemArbolBinBusq(arbolIdxNick,&busqueda, sizeof(tIndiceNickname), cmpClaveNickname);
        if(existe)
        {
            mensajeSeparador(2, 40, 1);
            mensajeLineaVacia(2, 40);
            mensajeEnLineaCentrado(2, 40, "!! NICKNAME EN USO !!");
            mensajeLineaVacia(2, 40);
            mensajeEnLinea(2, 40, nickname, 2);
            mensajeLineaVacia(2, 40);
            mensajeEnLinea(2, 40, "Ingresa otro...", 2);
            mensajeLineaVacia(2, 40);
            mensajeSeparador(2, 40, 0);
        }

    } while(existe);
    strcpy(nicknameDest, nickname);
    return darDeAlta(nombre, nickname, arbolIdxNombre, arbolIdxNick, archJug, archIdxNombre, archIdxNick);
}

void ingresarJugador(tJugador *jugador){

    tArbolBinBusq arbolIdxNombre, arbolIdxNick;
    crearArbolBinBusq(&arbolIdxNombre);
    crearArbolBinBusq(&arbolIdxNick);
    cargarIndiceDesdeArchivo(&arbolIdxNombre, ARCHIDXNOMBRE, NULL, sizeof(tIndiceNombre));
    cargarIndiceDesdeArchivo(&arbolIdxNick, ARCHIDXNICK, NULL, sizeof(tIndiceNickname));
    regJugador sel;
    char       nombre[31];
    char       nickname[11]:

    if(0 == pedirNombreYMostrarHomonimos(&arbolIdxNombre, ARCHJUGADORES, &sel, nombre))
    {// no existe o eligio NINGUNO: dar de alta
        pedirYRegistrarNickname(nombre, &arbolIdxNombre, &arbolIdxNick, ARCHJUGADORES, ARCHIDXNOMBRE, ARCHIDXNICK, nickname);
    }else{
        strcpy(nombre, sel.nombre);
        strcpy(nickname, sel.nickname);
    }
    inicializarJugador(jugador);
    guardarNombreYNick(jugador, nombre, nickname);
}
