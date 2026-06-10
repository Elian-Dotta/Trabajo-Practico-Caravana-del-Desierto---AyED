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
