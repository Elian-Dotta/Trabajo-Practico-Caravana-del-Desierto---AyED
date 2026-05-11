#include "consola.h"

typedef struct
{
    char nombre[100];
    float puntaje;
    int cantMove;
}tRanking;


int mostrarMenu()
{
    int f=0;

    printf("---BIENVENIDOS A \"CARAVANA DEL DESIERTO\"---\n");
    printf("1. Iniciar Partida\n");
    printf("2. Mostrar Ranking\n");
    printf("3. Salir\n");
    scanf("%d",&f);

    while(f > 3 || f < 1)
    {
        printf("Numero invalido, ingrese una de las opciones disponibles\n");
        scanf("%d",&f);
    }

    return f;
}

void mostrarPedirNombre(char *name)
{
    printf("Ingrese su nombre o alias\n");
    fgets(name,100,stdin);
}

int mostrarPedirMov(int dado)
{
    int f=0;
    printf("Sacaste el numero %d",dado);
    printf("¿Hacia que direccion deseas moverte?\n");
    printf("1.Izquierda\n");
    printf("2.Derecha\n");
    scanf("%d",&f);

    while(f > 2 || f < 1)
    {
        printf("Numero invalido, ingrese una de las opciones disponibles\n");
        scanf("%d",&f);
    }

    return f;
}

//void mostrarTablero(tLista)
//{
//    //recorrerListaAccion(tLista , tLista, tam, mostrar)
//}

void mostrarEstadisticas()
{
    tRanking r;
    FILE *arch;

    arch = fopen("ranking.bin","rb");

    printf("---RANKING---\n");
    printf("NOMBRS\t\tPUNTAJE\t\tCANTIDAD DE MOVIMIENTOS\n");

    while(fread(&r,sizeof(r),1,arch))
    {
        printf("%s\t\t%f\t\t%d\n",r.nombre,r.puntaje,r.cantMove);
    }
}
