#include "log.h"

#include "consola.h"

void crearLog(tLog *log)
{
    log->cantMsj = 0;
    crearLista(log->mensajes);
}

int  escribirEnLog(tLog *log, const char *msj)
{
    int ret; // VARIABLE PARA GUARDAR EL RETORNO DE INSERTAR AL INICIO
    unsigned tamMsj; // VARIABLE PARA CALCULAR EL TAMAÑO DEL MENSAJE INGRESADO
    char aux[TAM_BUFFER]; // BUFFER PARA SACAR EL ELEMENTO

    if(msj[0] == '\0') // SI NO HAY MENSAJE DEVOLVEMOS ERROR, TAMBIEN CONSIDERE !msj COMO CONDICION
        return 0;

    tamMsj = strlen(msj) + 1; // MAS UNO PORQUE STRLEN NO TOMA EN CUENTA EL \0, EN ESTE CASO ES NECESARIO QUE EL MEMCPY LO TENGA EN CUENTA

    if(log->cantMsj == MAX_MSJ) // SI EL LOG ESTA LLENO, SACAMOS EL PRIMERO DE LA LISTA, EL PRIMERO QUE FUE INGRESADO
        sacarPrimeroLista(&log->mensajes, aux, TAM_BUFFER);
    else    // SI NO ESTA LLENO AUMENTAMOS LA CANTIDAD
        log->cantMsj++;

    // QUEREMOS QUE EL BUFFER SE QUEDE LLENO SIEMPRE ASI QUE
    // SOLO AUMENTAMOS LA CANTIDAD EN CASO DE SER MENOR AL MAXIMO DE MENSAJES
    // E INSERTAMOS EL MENSAJE AL FINAL PORQUE EL LOG FUNCIONA COMO COLA
    ret = insertarAlFinalLista(&log->mensajes, msj, tamMsj);

    return ret;
}

void mostrarLog(const tLog *log)
{
    mostrarLista(log->mensajes, mostrarMensaje);
}

void mostrarMensaje(const void *m)
{
    const char *msj = m;

    mostrar(msj);
}

void vaciarLog(tLog *log)
{
    vaciarLista(log->mensajes);

    log->cantMsj = 0;
}
