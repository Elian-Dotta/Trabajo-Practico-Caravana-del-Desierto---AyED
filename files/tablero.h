#ifndef TABLERO_H_
#define TABLERO_H_

typedef struct tConfig tConfig;

int  crearTablero(tLista* tablero, tConfig config);
int  distruibuirElementos(tLista* tablero, tConfig config); // Puede no ser necesaria

int  agregarElemento();

#endif // TABLERO_H_
