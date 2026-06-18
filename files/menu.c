// === Modulo menu: menus genericos e ingreso ===
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "menu.h"
#include "consola.h"

// Inicia jugador y menu principal
void juego()
{
    //mostrar("Caravana Del Desierto\n");

    tJugador jugador;

    inicializarJugador(&jugador);

    ingresarJugador(&jugador);

    menuPrincipal(&jugador);
}

// Bucle del menu principal
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

// Menu generico que valida la opcion
char menu(const char *msj, const char *opc, int conErr, const char *msjErr)
{
    char opcion;
    int valido = 0;
    int priVez = 1;

    do
    {
        mostrar(msj);

        if (!priVez && conErr && msjErr)
            mostrar(msjErr);

        //mostrar("\nOpcion: ");

        //limpiarBuffer();

        if (scanf(" %c", &opcion) != 1)
            opcion = '\0';

        limpiarBuffer();

        opcion = (char) toupper((unsigned char) opcion);

        valido = (strchr(opc, opcion) != NULL);
        priVez = 0;
    } while (!valido);

    return opcion;
}

// Lee un texto del usuario
void ingresarDato(const char* msj, char *out)
{
    mostrar(msj);
    scanf("%[^\n]", out);
    while (getchar() != '\n' && !feof(stdin));
}



// Menu generico de opciones numericas
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

        limpiarBuffer(); // consume el resto de la linea (evita el '\n' que rompia el fgets siguiente)

        valido = (opcion >= 1 && opcion <= cantOpciones);
        priVez = 0;
    } while(!valido);

    return opcion;
}
