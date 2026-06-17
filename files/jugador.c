// === Modulo jugador: datos y primitivas ===
#include "jugador.h"
#include "consola.h"

// Inicializa puntaje, movimientos y posicion
void inicializarJugador(tJugador* j)
{
    j->cantMov = 0;
    j->puntaje = 0;
    j->posJug = 1;
    j->dado = 0;
    crearCola(&j->hisMovJugador);
}

// Establece las vidas iniciales
void asignarVida(tJugador *j, const unsigned vida)
{
    j->vida = vida;
}

// Suma una vida
void aumentarVida(tJugador* j)
{
    j->vida++;
}

// Resta una vida
void disminuirVida(tJugador* j)
{
    j->vida--;
}

// Devuelve las vidas actuales
unsigned verVida(const tJugador* j)
{
    return j->vida;
}

// Suma un punto
void aumentarPuntaje(tJugador *j)
{
    j->puntaje++;
}

// Devuelve el puntaje
unsigned verPuntaje(const tJugador *j)
{
    return j->puntaje;
}

// Suma un movimiento al contador
void aumentarMovimiento(tJugador *j)
{
    j->cantMov++;
}

// Devuelve la cantidad de movimientos
unsigned verMovimiento(const tJugador *j)
{
    return j->cantMov;
}

// Mueve la posicion logica un lugar
void modificarPosJug(tJugador *j, int dir)
{
    if(dir == 'F')
        j->posJug++;
    else
        j->posJug--;
}

// Devuelve la posicion del jugador
unsigned verPosJugador(const tJugador *j)
{
    return j->posJug;
}

// Guarda nombre y nickname
void guardarNombreYNick(tJugador *j, const char *nombre, const char* nick)
{
    strcpy(j->nombre, nombre);
    strcpy(j->nickname, nick);
}

// Devuelve el nombre
const char* verNombre(const tJugador *j)
{
    return j->nombre;
}

// Devuelve el nickname
const char* verNick(const tJugador *j)
{
    return j->nickname;
}

// Guarda el valor del dado
void asignarDado(tJugador *j, int dado)
{
    j->dado = dado;
}

// Devuelve el valor del dado
int  verDado(const tJugador *j)
{
    return j->dado;
}


// Encola movimiento en el historico
void guardarMovimientoJugador(tJugador *j, tMovimiento *mov)
{
    ponerEnCola(&j->hisMovJugador, mov, sizeof(tMovimiento));
}

// Muestra el historico (formato FX/BX)
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
