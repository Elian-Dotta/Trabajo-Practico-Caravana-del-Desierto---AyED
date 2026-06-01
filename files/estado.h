#ifndef ESTADO_H_
#define ESTADO_H_

typedef struct
{
    int Oobtenido,
        //Oactivo,
        Operdido,
        //Tobtenida,
        Tactiva,
        Tfinalizada,
        IDBandDesaparecido,
        JganaPuntos,
        JganaVida,
        JpierdeVida,
        Jgana;
}tEstado;

void inicializarEstado(tEstado *estado);





#endif // ESTADO_H_
