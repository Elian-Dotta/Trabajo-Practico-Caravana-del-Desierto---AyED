#include "menu.h"

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



#include "menu.h"
#include "consola.h"

char menu(const char *msj, const char *opc, int conErr, const char *msjErr)
{
    char opcion;
    int valido = 0;

    do
    {
        mostrar(msj, stdout);

        if (conErr && msjErr != NULL)
            mostrar(msjErr, stdout);

        mostrar("\nOpcion: ", stdout);

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
    mostrar(msj, stdout);
    scanf(" %[^\n]", out);
    while (getchar() != '\n' && !feof(stdin));
}

