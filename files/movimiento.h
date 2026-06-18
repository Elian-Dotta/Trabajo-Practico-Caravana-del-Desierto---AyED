// === Movimiento: dado y desplazamientos ===
#ifndef MOVIMIENTO_H_
#define MOVIMIENTO_H_

#include <stdlib.h>

// Movimiento (id, direccion, cantidad)
typedef struct
{
    int  id;
    char dir;
    int  cant;
}tMovimiento;

int tirarDado(unsigned minNro, unsigned maxNro);

int  calcularDireccion(char dir);
void cambiarDireccion(tMovimiento *mov);
int calcularNroCasilla(int nroCasilla, int mov, int tamTablero);

#endif // MOVIMIENTO_H_
