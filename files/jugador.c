#include "jugador.h"
#include "consola.h"

void inicializarJugador(tJugador* j)
{
    j->cantMov = 0;
    j->puntaje = 0;
    j->posJug = 1;
    crearCola(&j->hisMovJugador);
}

void asignarVida(tJugador *j, const unsigned vida)
{
    j->vida = vida;
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
        snprintf(buffer, sizeof(buffer), "[%d%c]", mov.cant, mov.dir);
        mostrar(buffer);
        contador++;

        if((contador % MAX_MOV_LINEA) == 0)
            mostrar("\n");
    }
}
