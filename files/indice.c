#include <string.h>
#include "indice.h"
#include "registro.h"      // regJugador


// ---------------------------------------------------------------------------
//  Asignaciones: construyen la entrada de indice desde un regJugador
// ---------------------------------------------------------------------------
void asigJugNombre(void *idx, const void *reg, unsigned long nroReg)
{
    tIndiceNombre    *i = idx;
    const regJugador *r = reg;

    strcpy(i->nombre, r->nombre);
    i->indiceRegistro = (unsigned)nroReg;
}

void asigJugNick(void *idx, const void *reg, unsigned long nroReg)
{
    tIndiceNickname  *i = idx;
    const regJugador *r = reg;

    strcpy(i->nickname, r->nickname);
    i->indiceRegistro = (unsigned)nroReg;
}


// ---------------------------------------------------------------------------
//  Comparadores
// ---------------------------------------------------------------------------
int cmpClaveNombre(const void *a, const void *b)     // ordena por (nombre, nroReg)
{
    const tIndiceNombre *x = a, *y = b;
    int c = strcmp(x->nombre, y->nombre);
    return c ? c : (int)x->indiceRegistro - (int)y->indiceRegistro;
}

int cmpSoloNombre(const void *a, const void *b)       // compara solo el nombre
{
    return strcmp(((const tIndiceNombre *)a)->nombre,
                  ((const tIndiceNombre *)b)->nombre);
}

int cmpClaveNickname(const void *a, const void *b)    // nickname (unico)
{
    return strcmp(((const tIndiceNickname *)a)->nickname,
                  ((const tIndiceNickname *)b)->nickname);
}


// ---------------------------------------------------------------------------
//  Indexar: arma el arbol leyendo el archivo de jugadores (desordenado)
// ---------------------------------------------------------------------------
int indexarArchivoJugadores(const char *pathJugadores, tArbolBinBusq *p,
                            void *aux, unsigned tamAux,
                            void *indice, unsigned tamIdx,
                            Asignacion asig, Cmp cmp)
{
    FILE          *fp;
    unsigned long  nroReg = 0;

    if(!aux || !indice || !asig)
        return 0;
    if((fp = fopen(pathJugadores, "rb")) == NULL)
        return ERROR_ARCH;

    crearArbolBinBusq(p);
    while(fread(aux, tamAux, 1, fp) == 1)         // OJO: no while(!feof)
    {
        asig(indice, aux, nroReg);                // construye la entrada de indice
        insertarArbolBinBusq(p, indice, tamIdx, cmp);
        nroReg++;
    }
    fclose(fp);
    return TODO_BIEN;
}


// ---------------------------------------------------------------------------
//  Guardar: recorrido en orden -> el archivo queda ORDENADO
// ---------------------------------------------------------------------------
typedef struct { FILE *fp; unsigned tam; } ctxGuardar;

static void escribirNodo(void *info, void *params)
{
    ctxGuardar *c = params;
    fwrite(info, c->tam, 1, c->fp);
}

int guardarArchivoIndice(tArbolBinBusq *pa, const char *pathIndice, unsigned tamIdx)
{
    FILE       *fp;
    ctxGuardar  ctx;

    if((fp = fopen(pathIndice, "wb")) == NULL)
        return ERROR_ARCH;
    ctx.fp  = fp;
    ctx.tam = tamIdx;
    recorrerEnOrdenSimpleArbolBinBusq(pa, &ctx, escribirNodo);
    fclose(fp);
    return TODO_BIEN;
}


// ----------------------------------------------------------------------------
//  Cargar: carga balanceada desde el archivo de indice (que esta ordenado)
// ----------------------------------------------------------------------------
int cargarIndiceDesdeArchivo(tArbolBinBusq *pa, const char *pathIndice, void *indice, unsigned tamIdx)
{
    (void)indice;                       // no se usa con la carga balanceada
    crearArbolBinBusq(pa);
    return cargarArchivoBinOrdenadoArbolBinBusq(pa, pathIndice, tamIdx);
}


// ---------------------------------------------------------------------------
//  Buscar: arma la clave desde aux, busca en el arbol y lee el registro
//  'aux' entra con la clave puesta (el campo clave) y sale con el registro hallado.
// ---------------------------------------------------------------------------
int buscarEnArchivoConIndice(FILE *fp, const tArbolBinBusq *pa, void *aux, unsigned tamAux, void *indice, unsigned tamIdx, Asignacion asig, Cmp cmp)
{
    unsigned nroReg;

    asig(indice, aux, 0);                       // arma la entrada de indice desde aux (nroReg=0)
    if(!buscarElemArbolBinBusq(pa, indice, tamIdx, cmp))
        return 0;                               // no existe
    // 'indice' quedo con la entrada hallada; indiceRegistro es su ULTIMO campo (unsigned)
    nroReg = *(unsigned *)((char *)indice + tamIdx - sizeof(unsigned));
    fseek(fp, (long)nroReg * tamAux, SEEK_SET);
    fread(aux, tamAux, 1, fp);
    return 1;
}
