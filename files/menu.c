#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "menu.h"
#include "consola.h"

char menu(const char *msj, const char *opc, int conErr, const char *msjErr)
{
    char opcion;
    int valido = 0;

    do
    {
        mostrar(msj);

        if (conErr && msjErr != NULL)
            mostrar(msjErr);

        mostrar("\nOpcion: ");

        if (scanf(" %c", &opcion) != 1)
            opcion = '\0';

        limpiarBuffer();

        opcion = (char) toupper((unsigned char) opcion);

        valido = (strchr(opc, opcion) != NULL);
        conErr = 1;
    } while (!valido);

    return opcion;
}

void ingresarDato(const char* msj, char *out)
{
    mostrar(msj);
    scanf(" %[^\n]", out);
    while (getchar() != '\n' && !feof(stdin));
}



int menuNum(const char* msj, int cantOpciones, int conErr, const char *msjErr)
{
    int opcion;
    int valido = 0;
    int priVez = 1;

    do
    {
        if(!priVez && conErr && msjErr)
        {
            mostrar(msjErr);
        }

        mostrar(msj);

        if(scanf("%d", &opcion) != 1)
            opcion = 0;

        valido = (opcion >= 1 && opcion <= cantOpciones);
        priVez = 0;
    } while(!valido);

    return opcion;
}

void mensajeSeparador(int margenIzqConsola, int cantLugares, int inicio){
    if(inicio)
        printf("\n%*s+", margenIzqConsola, "");
    else
        printf("%*s+", margenIzqConsola, "");
    for(int i=0; i<cantLugares ; i++)
        printf("-");
    printf("+\n");
}

void mensajeLineaVacia(int margenIzqConsola, int cantLugares){
    printf("%*s|%*s|\n", margenIzqConsola, "", cantLugares, "");
}

void mensajeEnLinea(int margenIzqConsola, int cantLugares, const char* msj, int margenIzqTabla){
    if( (strlen(msj)+margenIzqTabla) > cantLugares)
        return; // se rompe la visualizacion si se mostrase
    printf("%*s|%*s%s%*s|\n", margenIzqConsola, "", margenIzqTabla, "", msj, (int)(cantLugares-(strlen(msj)+margenIzqTabla)), "");
}

void mensajeEnLineaCentrado(int margenIzqConsola, int cantLugares, const char* msj){
    int lenMsj      = strlen(msj);
    int espacioTotal = cantLugares - lenMsj;
    int margenIzq   = espacioTotal / 2;
    int margenDer   = espacioTotal - margenIzq; // absorbe el impar

    if(lenMsj > cantLugares)
        return;

    printf("%*s|%*s%s%*s|\n", margenIzqConsola, "", margenIzq, "", msj, margenDer, "");
}

void mensajeIngresoCadena(int margenIzqConsola, int cantLugares, char* buffer, int maxLenBuffer, int margenIzqTabla){
    int i;
    printf("%*s|%*s> ", margenIzqConsola, "", margenIzqTabla, "");
    fgets(buffer, maxLenBuffer, stdin);
    // elimina el \n que deja fgets
    for(i = 0; buffer[i] != '\0'; i++)
        if(buffer[i] == '\n')
            buffer[i] = '\0';
}

void ingresarDatosJugador(char *buffer, const char *msj, int maxLenBuffer, int cantEspacios, int margenIzqConsola, int margenIzqTabla){
        mensajeSeparador(margenIzqConsola, cantEspacios, 1);
        mensajeLineaVacia(margenIzqConsola,cantEspacios);
        mensajeEnLinea(margenIzqConsola, cantEspacios, msj, margenIzqTabla);
        mensajeLineaVacia(margenIzqConsola,cantEspacios);
        mensajeIngresoCadena(margenIzqConsola,cantEspacios, buffer, maxLenBuffer, margenIzqTabla);
        mensajeLineaVacia(margenIzqConsola,cantEspacios);
        mensajeSeparador(margenIzqConsola, cantEspacios, 0);
}
