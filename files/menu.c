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
