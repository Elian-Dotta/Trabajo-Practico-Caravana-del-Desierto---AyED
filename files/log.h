#ifndef LOG_H_
#define LOG_H_

/*
    MODULO PARA EL MANEJO DE MENSAJES PARA EL USUARIO
*/

#include <string.h>
#include "lista_simple_enlace.h"

#define MAX_MSJ 6

typedef struct
{
    tLista   mensajes; // DEBE SER UNA LISTA PARA NO LIBERAR LOS ELEMENTOS YA QUE DEBEN SER MOSTRADOS DE NUEVO
    unsigned cantMsj;
    //tLista histLog;
}tLog;

void crearLog(tLog *log);
int  escribirEnLog(tLog *log, const char *msj);
void mostrarLog(const tLog *log);
void mostrarMensaje(const void *m);
void vaciarLog(tLog *log);

#endif // LOG_H_
