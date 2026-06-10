#ifndef REGISTRO_H_
#define REGISTRO_H_


// MODULO USADO PARA EL GUARDADO DE PARTIDA Y JUGADOR.

typedef struct
{
    char     nombre[31];
    unsigned indiceRegistro;
}tIndiceNombre;

void enlistarNickNames(void *idxNombre, void *contexto);

#endif // REGISTRO_H_
