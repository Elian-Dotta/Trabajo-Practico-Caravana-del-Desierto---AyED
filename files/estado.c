// === Modulo estado: flags del turno ===
#include "estado.h"

// Pone todos los flags en cero
void inicializarEstado(tEstado *e)
{
    e->BandAtaca = 0;
    e->IDBandDesaparecido[0] = 0;
    e->IDBandDesaparecido[1] = 0;
    e->Jgana = 0;
    e->JganaPuntos = 0;
    e->JganaVida = 0;
    e->Jpierde = 0;
    e->JpierdeVida = 0;
    e->tieneOasis = 0;
    e->Oobtenido = 0;
    e->Operdido = 0;
    e->Tactiva = 0;
    e->tieneTormenta = 0;
    e->Tfinalizada = 0;
}

// Resetea flags entre turnos
void reiniciarEstado(tEstado *e)
{
    e->BandAtaca = 0;
    e->IDBandDesaparecido[0] = 0;
    e->IDBandDesaparecido[1] = 0;
    e->JganaPuntos = 0;
    e->JganaVida = 0;
    e->JpierdeVida = 0;
    e->Oobtenido = 0;
    e->Operdido = 0;
    e->Tfinalizada = 0;
    e->Tactiva = 0;
}
