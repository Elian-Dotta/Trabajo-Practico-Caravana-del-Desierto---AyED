#include "registro.h"


// Lee una linea de stdin, descarta el '\n' y la acota a tam-1 caracteres.
// Repite mientras la entrada sea vacia.
static void leerTexto(const char *msj, char *out, int tam)
{
    char buffer[256];

    do
    {
        mostrar(msj);
        if(fgets(buffer, sizeof(buffer), stdin) == NULL)
        {
            out[0] = '\0';
            return;
        }
        buffer[strcspn(buffer, "\n")] = '\0';   // saca el salto de linea
    } while(buffer[0] == '\0');

    strncpy(out, buffer, tam - 1);
    out[tam - 1] = '\0';
}


// Pide el nombre del jugador. Si ya existe en los registros,
// permite reconocerlo entre sus homonimos; si no, lo da de alta pidiendo un
// nickname unico. Deja en *j el nombre y el nick definitivos.
void ingresarJugador(tJugador *j)
{
    char            nombre[31];
    char            nickname[11];
    tArbolBinBusq   idxNombre;
    tArbolBinBusq   idxNick;
    tIndiceNombre   auxNombre;
    tIndiceNickname auxNick;
    regJugador      sel;
    FILE           *fJug;
    int             existe = 0;

    limpiarPantalla();
    mostrar("CARAVANA DEL DESIERTO\n\n");

    // 1) pedir el nombre del jugador
    leerTexto("Ingrese su nombre: ", nombre, sizeof(nombre));

    // 2) cargar el indice de nombres persistido (si no existe, queda vacio)
    cargarIndiceDesdeArchivo(&idxNombre, ARCHIDXNOMBRE, &auxNombre, sizeof(tIndiceNombre));

    // 3) si hay registros, ofrecer los homonimos para reconocer al jugador
    fJug = fopen(ARCHJUGADORES, "rb");
    if(fJug)
    {
        existe = revisarUsuarioRepetido(&idxNombre, nombre, fJug, &sel);
        fclose(fJug);
    }

    if(existe)
    {
        guardarNombreYNick(j, sel.nombre, sel.nickname);
        return;
    }

    // 4) alta: pedir un nickname que no este en uso
    cargarIndiceDesdeArchivo(&idxNick, ARCHIDXNICK, &auxNick, sizeof(tIndiceNickname));
    do
    {
        leerTexto("Ingrese un nickname (unico, hasta 10 caracteres): ", nickname, sizeof(nickname));
        strcpy(auxNick.nickname, nickname);
        if(buscarElemArbolBinBusq(&idxNick, &auxNick, sizeof(tIndiceNickname), cmpClaveNickname))
        {
            mostrar("Ese nickname ya esta en uso. Pruebe con otro.\n");
            nickname[0] = '\0';
        }
    } while(nickname[0] == '\0');

    darDeAlta(nombre, nickname, &idxNombre, &idxNick, ARCHJUGADORES, ARCHIDXNOMBRE, ARCHIDXNICK);
    guardarNombreYNick(j, nombre, nickname);
}


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

    if(strcmp(idx->nombre, nombre) == 0)
    {
        fflush(archJugadores);
        fseek(archJugadores, idx->indiceRegistro * sizeof(regJugador), SEEK_SET);
        fread(&registro, sizeof(regJugador), 1, archJugadores);

        // se guarda el registro COMPLETO (nombre + nick): armarMensaje y la
        // seleccion en revisarUsuarioRepetido lo leen como regJugador entero.
        insertarAlFinalLista(nicknames, &registro, sizeof(regJugador));
    }
}

void asigJugNick(void *idx, const void *jug, unsigned long nroRegistro) // EN LA BUSQUEDA NO NECESITO EL NRO DE REGISTRO.
{
    tIndiceNickname *i = (tIndiceNickname*)idx;
    regJugador *j = (regJugador*)jug;

    strcpy(i->nickname, j->nickname);
    i->indiceRegistro = nroRegistro;
}


void armarMensaje(void *jugador, void *msjBuffer)
{
    void **buf = (void**)msjBuffer;
    char  *texto = (char*)buf[0];
    int   *contador = (int*)buf[1];

    // concatena al final del buffer y avanza el numero de opcion para que
    // cada homonimo (y luego NINGUNO) tenga su propio numero correlativo.
    sprintf(texto + strlen(texto), "%d. %s %s\n", *contador,
            ((regJugador*)jugador)->nickname, ((regJugador*)jugador)->nombre);
    (*contador)++;
}

int darDeAlta(const char* nombre, const char *nickname, tArbolBinBusq* arbolIdxNombre, tArbolBinBusq* arbolIdxNick, const char* archJug, const char* archIdxNombre, const char *archIdxNick)
{
    tIndiceNombre indNombre;
    tIndiceNickname indNick;
    regJugador reg;

    FILE* fJug = fopen(archJug, "a+b");
    if(!fJug)
    {
        return 0;
    }

    strcpy(reg.nombre, nombre);
    strcpy(reg.nickname, nickname);
    strcpy(indNombre.nombre, nombre);
    strcpy(indNick.nickname, nickname);


    fseek(fJug, 0, SEEK_END);

    int pos = (ftell(fJug)/sizeof(regJugador));

    indNombre.indiceRegistro = pos;
    indNick.indiceRegistro = pos;

    fwrite(&reg, sizeof(regJugador), 1, fJug);

    insertarArbolBinBusq(arbolIdxNombre, &indNombre, sizeof(tIndiceNombre), cmpClaveNombre);
    insertarArbolBinBusq(arbolIdxNick, &indNick, sizeof(tIndiceNickname), cmpClaveNickname);

    guardarArchivoIndice(arbolIdxNombre, archIdxNombre, sizeof(tIndiceNombre));
    guardarArchivoIndice(arbolIdxNick, archIdxNick, sizeof(tIndiceNickname));

    fclose(fJug);

    return 1;
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
        // primera partida: crear el archivo vacio y continuar
        part = fopen(ARCHPARTIDAS, "wb");
        if(part)
            fclose(part);
        part = fopen(ARCHPARTIDAS, "rb");
        if(!part)
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
