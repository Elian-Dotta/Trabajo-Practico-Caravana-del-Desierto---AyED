#include "menu.h"


void juego()
{
    //mostrar("Caravana Del Desierto\n");

    tJugador jugador;

    ingresarJugador(&jugador);

    menuPrincipal(&jugador);
}

void menuPrincipal(tJugador *jugador)
{
    char opcion;

    do
    {
        limpiarPantalla();
        opcion = menu(MENU_JUEGO, OPC_JUEGO, 1, MSJ_ERR_OPC);

        switch(opcion)
        {
            case JUGAR_PARTIDA:
                    jugarPartida(jugador);
                    break;

            case MOSTRAR_RANKING:
                    ranking();
                    break;

            case SALIR_DEL_JUEGO:
                    mostrar(MSJ_SALIDA);
                    break;
        }
    }while(opcion != SALIR_DEL_JUEGO);

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

