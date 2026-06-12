#ifndef MOVIMIENTO_H_
#define MOVIMIENTO_H_

#include <stdlib.h>

typedef struct
{
    int  id;
    char dir;
    int  cant;
}tMovimiento;

int tirarDado(unsigned minNro, unsigned maxNro);

int  calcularDireccion(char dir);
void cambiarDireccion(tMovimiento *mov);

#endif // MOVIMIENTO_H_
