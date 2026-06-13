#ifndef MENU_H_
#define MENU_H_

<<<<<<< Updated upstream
=======
#define MENU_JUEGO "\
-----------------------------------\n\
\t   CARAVANA DEL DESIERTO\n\
-----------------------------------\n\
[J] Jugar nueva partida\n\
[R] Ver ranking\n\
[S] Salir\n"

#define OPC_JUEGO "JRS"

#define MSJ_ERR_OPC "Opcion invalida. Intente nuevamente.\n"

char menu(const char* msj, const char *opc, int conErr, const char *msjErr);

void ingresarDato(const char* msj, char *out);

>>>>>>> Stashed changes

char menu(const char* msj, const char *opc, int conErr, const char *msjErr);

int  menuNum(const char* msj, int cantOpciones, int conErr, const char *msjErr);

void ingresarDato(const char* msj, char *out);




#endif // MENU_H_
