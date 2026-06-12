#include "movimiento.h"

int calcularDireccion(char dir)
{
    return dir == 'F' ? 1 : -1;
}

void cambiarDireccion(tMovimiento *mov)
{
    mov->dir = mov->dir == 'F' ? 'B' : 'F';
}
