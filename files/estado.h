#ifndef ESTADO_H_
#define ESTADO_H_

typedef struct
{
    int Oobtenido,
        Operdido,
        IDBandDesaparecido,
        Jpierde,
        JganaVida,
        JpierdeVida;
}tEstado;

void inicializarEstado(tEstado *estado);

#endif // ESTADO_H_
