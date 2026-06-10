#ifndef MENU_H_
#define MENU_H_


char menu(const char* msj, const char *opc, int conErr, const char *msjErr);

int  menuNum(const char* msj, int cantOpciones, int conErr, const char *msjErr);

void ingresarDato(const char* msj, char *out);




#endif // MENU_H_
