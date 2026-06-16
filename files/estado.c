#include "estado.h"

void inicializarEstado(tEstado *e)
{
    e->BandAtaca = 0;
    e->IDBandDesaparecido = 0;
    e->Jgana = 0;
    e->JganaPuntos = 0;
    e->JganaVida = 0;
    e->Jpierde = 0;
    e->JpierdeVida = 0;
    e->Oactivo = 0;
    e->Oobtenido = 0;
    e->Operdido = 0;
    e->Tactiva = 0;
    e->Tfinalizada = 0;
}

void reiniciarEstado(tEstado *e)
{
    e->BandAtaca = 0;
    e->IDBandDesaparecido = 0;
    e->JganaPuntos = 0;
    e->JganaVida = 0;
    e->JpierdeVida = 0;
    e->Oobtenido = 0;
    e->Operdido = 0;
    e->Tfinalizada = 0;
    e->Tactiva = 0;          // se recalcula cada turno segun la casilla del jugador
}
