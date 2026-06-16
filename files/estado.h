#ifndef ESTADO_H_
#define ESTADO_H_

typedef struct Estado
{
    int Oobtenido,
        tieneOasis,
        Operdido,
        Tactiva,
        tieneTormenta,
        Tfinalizada,
        BandAtaca,
        IDBandDesaparecido[2],
        Bandidos,
        JganaPuntos,
        JganaVida,
        JpierdeVida,
        Jgana,
        Jpierde;
}tEstado;

void inicializarEstado(tEstado *estado);

void reiniciarEstado(tEstado *estado);

#endif // ESTADO_H_
