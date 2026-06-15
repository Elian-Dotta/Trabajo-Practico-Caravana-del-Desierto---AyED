#include "config.h"
#define TAM 100
#define ERROR 0
#define OK 1

int cargarConfig(tConfig *t)
{
    FILE *arch;
    char buffer[TAM];
    char *puntero;

    arch = fopen("config.txt","r");
    if(!arch)
    {
        printf("\nError al leer el archivo config.txt");
        return ERROR;
    }


    fgets(buffer,TAM,arch);
    puntero = strrchr(buffer,':');
    puntero++;
    t->cant_pos = atoi(puntero);

    fgets(buffer,TAM,arch);
    puntero = strrchr(buffer,':');
    puntero++;
    t->vidas_ini = atoi(puntero);

    fgets(buffer,TAM,arch);
    puntero = strrchr(buffer,':');
    puntero++;
    t->max_band = atoi(puntero);

    fgets(buffer,TAM,arch);
    puntero = strrchr(buffer,':');
    puntero++;
    t->max_prem = atoi(puntero);

    fgets(buffer,TAM,arch);
    puntero = strrchr(buffer,':');
    puntero++;
    t->max_vid_ext = atoi(puntero);

    fgets(buffer,TAM,arch);
    puntero = strrchr(buffer,':');
    puntero++;
    t->max_oasis = atoi(puntero);

    fgets(buffer,TAM,arch);
    puntero = strrchr(buffer,':');
    puntero++;
    t->max_tormenta = atoi(puntero);

    fclose(arch);

    return OK;
}


