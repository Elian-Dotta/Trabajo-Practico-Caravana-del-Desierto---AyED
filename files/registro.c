#include "registro.h"




int revisarUsuarioRepetido(tArbolBinBusq *indice, const char *nombre, FILE *fJug, regJugador *sel)
{
    tLista nicknames;
    char   buffer[TAM_MENU];
    int    contador = 1;
    int    op;

    // 1) juntar homonimos: recorre el indice por nombre; la accion encola los que coinciden
    crearLista(&nicknames);
    void *ctxArbol[3] = { &nicknames, fJug, (void *)nombre };
    recorrerEnOrdenSimpleArbolBinBusq(indice, ctxArbol, enlistarNickNames);

    // 2) armar el texto del menu recorriendo la lista
    buffer[0] = '\0';
    void *ctxMsg[2] = { buffer, &contador };
    recorrerLista(&nicknames, armarMensaje, ctxMsg);
    sprintf(buffer + strlen(buffer), "%d. NINGUNO\n", contador);

    // 3) mostrar el menu y leer la eleccion
    op = menuNum(buffer, contador, 1, "Opcion invalida\n");

    // 4) interpretar la respuesta
    if(op == contador)                       // eligio NINGUNO
    {
        vaciarLista(&nicknames);
        return 0;                            // -> dar de alta
    }
    buscarPorPosicionLista(&nicknames, sel, sizeof(regJugador), op - 1);
    vaciarLista(&nicknames);
    return 1;                                // -> jugador existente, *sel cargado
}


void enlistarNickNames(void *idxNombre, void *contexto)
{
    tIndiceNombre *idx = (tIndiceNombre*)idxNombre;

    void **ctx = (void**)contexto;

    tLista *nicknames = (tLista*)ctx[0];
    FILE *archJugadores = (FILE*)ctx[1];
    const char *nombre = (const char*)ctx[2];

    regJugador registro;
    char nickname[11];

    if(strcmp(idx->nombre, nombre) == 0)
    {
        fflush(archJugadores);
        fseek(archJugadores, idx->indiceRegistro * sizeof(regJugador), SEEK_SET);
        fread(&registro, sizeof(regJugador), 1, archJugadores);

        strcpy(nickname, registro.nickname);
        insertarAlFinalLista(nicknames, nickname, sizeof(nickname));
    }
}

void asigJugNick(void *idx, const void *jug, unsigned long nroRegistro) // EN LA BUSQUEDA NO NECESITO EL NRO DE REGISTRO.
{
    tIndiceNickname *i = (tIndiceNickname*)idx;
    regJugador *j = (regJugador*)jug;

    strcpy(i->nickname, j->nickname);
    i->indiceRegistro = nroRegistro;
}

int cmpClaveNickname(const void*a, const void*b)
{
    tIndiceNickname *i1 = (tIndiceNickname*)a;
    tIndiceNickname *i2 = (tIndiceNickname*)b;

    return strcmp(i1->nickname, i2->nickname);
}

void guardarPartida(tJugador *jugador)
{
    long cantRegistros;
    regPartida reg,
               regGuardar;
    int estado = 1; // BUSCANDO NICK

    FILE* part = fopen(ARCHPARTIDAS, "rb");
    if(!part)
    {
        return;
    }

    FILE* partTmp = fopen(ARCHPARTIDASTMP, "wb");
    if(!partTmp)
    {
        fclose(part);
        return;
    }

    fseek(part, 0, SEEK_END);
    cantRegistros = ftell(part) / sizeof(regPartida);
    fseek(part, 0, SEEK_SET);

    if(fread(&reg, sizeof(regPartida), 1, part) != 1)
    estado = 3;

    while(estado == 1)
    {
        if(strcmp(verNick(jugador), reg.nickname) != 0)
        {
            fwrite(&reg, sizeof(regPartida), 1, partTmp);
            fread(&reg, sizeof(regPartida), 1, part);
        }
        else
        {
            estado = 2; // AVANZANDO NICK
        }

        if(feof(part))
            estado = 3; // ENCONTRADA POSICION INSERCION
    }

    while(estado == 2)
    {
        if(strcmp(verNick(jugador), reg.nickname) == 0)
        {
            fwrite(&reg, sizeof(regPartida), 1, partTmp);
            fread(&reg, sizeof(regPartida), 1, part);
        }
        else
        {
            estado = 4; // ENCONTRADA POSICION INSERCION PERO FALTA INSERTAR UN REGISTRO EXTRA LEIDO
        }

        if(feof(part))
            estado = 3;
    }
    if(estado == 4 || estado == 3)
    {

        // SE ENCONTRO LA POSICION DE INSERCION
        regGuardar.nroPartida = cantRegistros + 1;
        strcpy(regGuardar.nickname, verNick(jugador));
        regGuardar.puntaje = verPuntaje(jugador);
        regGuardar.cantMovimientos = verMovimiento(jugador);
        fwrite(&regGuardar, sizeof(regPartida), 1, partTmp);


    }
    if(estado == 4) // FALTA COPIAR OTRO REGISTRO
    {
        fwrite(&reg, sizeof(regPartida), 1, partTmp);
        estado = 6; // SIGO COPIANDO EL RESTANTE
    }
    while(estado == 6 && !feof(part))
    {
        fread(&reg, sizeof(regPartida), 1, part);
        if(!feof(part))
            fwrite(&reg, sizeof(regPartida), 1, partTmp);
    }

    fclose(part);
    fclose(partTmp);

    remove(ARCHPARTIDAS);
    rename(ARCHPARTIDASTMP, ARCHPARTIDAS);
}
