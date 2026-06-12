#ifndef RANKING_H_
#define RANKING_H_

// MODULO USADO PARA EL CALCULO Y MUESTREO DEL RANKING
typedef struct
{
    char    nickname[11];
    char    nombre[31];
    int     puntaje;
}tRanking

void ranking();

int generarRanking(tLista* ranking);
int mostrarRanking(tLista* ranking);

#endif // RANKING_H_
