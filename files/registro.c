#include "registro.h"

void enlistarNickNames(void *idxNombre, void *contexto)
{
    tIndiceNombre *idx = (tIndiceNombre*)idxNombre;
    tLista *nicknames = (tLista*)contexto[0];
    FILE *archJugadores = (FILE*)contexto[1];
    const char *nombre = (const char*)contexto[2];

    regJugador registro;
    char nickname[11];

    if(strcmp(idx->nombre, nombre) == 0)
    {
        fflush(archJugadores);
        fseek(archJugadores, idx->indiceRegistro, SEEK_SET);
        fread(&registro, sizeof(regJugador), 1, archJugadores);

        strcpy(nickname, registro.nickname);
        insertarAlFinalLista(nicknames, nickname, sizeof(nickname));
    }
}
