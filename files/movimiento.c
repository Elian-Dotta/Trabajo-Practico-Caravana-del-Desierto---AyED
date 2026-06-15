#include "movimiento.h"

int tirarDado(unsigned minNro, unsigned maxNro){ // La semilla (SRAND(time(NULL))...) deberia estar inicializada antes de ejecutar
    return minNro + rand() % (maxNro - minNro + 1);
}

int calcularDireccion(char dir)
{
    return dir == 'F' ? 1 : -1;
}

void cambiarDireccion(tMovimiento *mov)
{
    mov->dir = mov->dir == 'F' ? 'B' : 'F';
}

int calcularNroCasilla(int nroCasilla, int mov, int tamTablero)
{
    int nuevaPos = nroCasilla + mov;
    if(nuevaPos < 1)
        return tamTablero;
    else if(nuevaPos > tamTablero)
        return 1;
    else
        return nuevaPos;
}
