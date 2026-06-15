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
