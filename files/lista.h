#ifndef LISTA_H_
#define LISTA_H_

typedef struct sNodo
{
    void         *info;
    unsigned      tamInfo;
    struct sNodo *sig,
                 *ant;
} tNodo;

typedef tNodo* tLista;

typedef int  (*Acumular)(void **, unsigned *, void *, unsigned);
typedef void (*Mostrar)(void *);

void crearLista(tLista *pl);
int  insertarAlFinal(tLista *pl, void *d, unsigned tamInfo);
int  actualizarPosLista(tLista *pl, void *d, unsigned tamInfo, unsigned pos, Acumular acum);
void mostrarLista(tLista *pl, Mostrar mostrar);

#endif // LISTA_H_
