#ifndef ESTADO_H_
#define ESTADO_H_

typedef struct Estado
{
    int Oobtenido,
        Oactivo,
        Operdido,
        Tactiva,
        Tfinalizada,
        BandAtaca,
        IDBandDesaparecido,
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
