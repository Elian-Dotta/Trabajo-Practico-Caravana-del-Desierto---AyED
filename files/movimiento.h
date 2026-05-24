#ifndef MOVIMIENTO_H_
#define MOVIMIENTO_H_

typedef struct
{
    int  id;
    char dir;
    int  cant;
}tMovimiento;

int tirarDado(); // Lucas

int calcularDireccion(char dir);

//int calcularMovBandido()

#endif // MOVIMIENTO_H_
