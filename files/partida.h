#ifndef PARTIDA_H_
#define PARTIDA_H_

typedef struct tLista tLista;

int  jugarPartida();// VA A INICIALIZAR Y LUEGO VA A MANEJAR EL LOOP

int  inicializarPartida(); // VA A CARGAR TCONFIG Y GENERAR EL TABLERO

int  procesarEntrada(); // DETECTA MOVIMIENTO DEL JUGADOR

int  actualizarPartida(); // ACTUALIZA LOS BANDIDOS Y LOS PREMIOS, CHECKEA FIN DE PARTIDA

int  renderizarPartida(); // DIBUJA EL TABLERO

int  finalizarPartida(); // GUARDA EL RANKING

#endif // PARTIDA_H_
