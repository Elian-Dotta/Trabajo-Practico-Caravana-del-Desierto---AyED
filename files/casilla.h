#ifndef CASILLA_H_
#define CASILLA_H_

typedef struct tElem tElem;
typedef tLista tLista;

tLista crearCasilla();
int insertarEnCasilla(void **pl, unsigned *tamLista, void *d, unsigned tamDato);
void mostrarCasillaV();

#endif // CASILLA_H_
