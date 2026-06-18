Caravana del Desierto

Trabajo Práctico - Algoritmos y Estructuras de Datos  |  Comisiones 02-3300

1. Presentación
Una caravana intenta atravesar una antigua ruta comercial para llegar a una ciudad refugio antes de que se agoten sus recursos. 
A lo largo del trayecto existen tesoros, provisiones, oasis, tormentas de arena y bandidos. 
El desierto es hostil e impredecible. En cada turno el jugador arrojará un dado virtual que generará un valor aleatorio entre 1 y 6. El valor obtenido determinará exactamente la cantidad de posiciones que deberá desplazarse en ese turno.
 Los bandidos se desplazan automáticamente tratando de interceptar al jugador. 
Cada decisión cuenta. La caravana debe avanzar. El desierto no perdona errores.

2. Descripción general
Caravana del Desierto es un juego por turnos, implementado en lenguaje C. El jugador debe atravesar una ruta desértica desde el Campamento Inicial hasta la Ciudad Refugio, aprovechando recursos (premios, vidas extra, oasis) y evitando tormentas de arena y bandidos. En cada turno el jugador arroja un dado virtual (valor 1 a 6) y elige avanzar (F) o retroceder (B) exactamente esa cantidad de posiciones. Los bandidos se desplazan automáticamente intentando interceptar al jugador . La partida termina cuando el jugador alcanza la Ciudad Refugio o pierde todas sus vidas.


3. Arquitectura por capas
El proyecto se divide en archivos .h/.c con responsabilidades únicas. Regla de diseño: los módulos de menor nivel no dependen de los de mayor nivel. Cada módulo de lista es el único que accede a sus estructuras internas (encapsulamiento).
Partida: coordina el flujo principal y el loop de la partida.
Consola: renderiza escenas y mensajes; encapsula todo printf (función mostrar).
Tablero: administra el tablero (crea, modifica, muestra y destruye); implementado sobre ListaDE.
Casilla: administra los elementos dentro de cada casilla; implementado sobre ListaSE.
ListaDE: ruta circular doblemente enlazada; único que accede a sus nodos.
ListaSE: lista simple enlazada (casillas, log, ranking); único que accede a sus nodos.
Estado / Jugador / Movimiento / Animación / Log / Timer: estado del juego, jugador, movimientos, dado, animaciones, log y temporizador.
Registro / Índice / Arbol / Ranking: capa de datos: registro de jugadores y partidas, índice sobre Árbol Binario de Búsqueda.


4. Estructuras de datos
Lista Circular Doblemente Enlazada (ListaDE): Modela la ruta del desierto . Permite avanzar, retroceder y dar la vuelta al tablero en el caso de los bandidos.
Lista Simple Enlazada (ListaSE): contenido de cada casilla (varios elementos por posición), el log de eventos y el ranking.
Cola (FIFO): los movimientos del jugador y de los bandidos se encolan, luego se desencolan para animarlos y actualizar el estado. También guarda el histórico de movimientos del jugador.
Arbol Binario de Búsqueda (índice): indexa el archivo de jugadores; se persiste en archivos binarios y se reconstruye al iniciar.


5. Gestión de datos (archivos)
config.txt: (entrada) parámetros de configuración: cantidad de posiciones, vidas iniciales y máximos de bandidos, premios, vidas extra, oasis y tormentas.
caravana.txt: (salida) representación textual del tablero generado al iniciar cada partida.
jugadores.bin: registro binario de jugadores (nombre y nickname).
partida.bin: registro binario de partidas (nickname, nro de partida, puntaje y cantidad de movimientos).
nombre.idx / nickname.idx: índices persistidos (ABB) por nombre y por nickname; al iniciar el juego, de existir registros, se accede a través del índice persistido.


6. Flujo de la partida (loop principal)
Cada turno ejecuta, en orden, las siguientes funciones coordinadas por el módulo Partida:
dibujarEstadoDelJuego: dibuja tablero, HUD y log, y deja lugar para la entrada.
procesarEntrada: tira el dado, pide la direccion (F/B) y encola el movimiento del jugador.
actualizarMovimientos: calcula y encola los movimientos de los bandidos (lógica de la computadora).
dibujarAnimacionMov: desencola los movimientos y los anima paso a paso sobre el tablero.
actualizarEstado: determina el nuevo estado según la posición final de los elementos.
dibujarAnimacionEstado: anima los cambios de estado (premios, oasis, tormentas, ataques).
Al finalizar se muestra el histórico de movimientos del jugador (formato FX / BX) y se guardan las estadísticas de la partida.


7. Reglas del juego implementadas
Dado: genera un valor entero aleatorio entre 1 y 6 que determina el desplazamiento.
Recursos: Premio (P) suma 1 punto; Vida extra (V) suma una vida.
Oasis (O): otorga protección el turno siguiente (no se pierde vida por bandidos ni tormentas).
Tormenta (T): hace perder el siguiente turno, salvo que el jugador este protegido por un oasis.
Bandido (B): si jugador y bandido quedan en la misma posición, el jugador pierde una vida, vuelve al Campamento Inicial y el bandido se elimina.
Límites: los bandidos se mueven en forma circular (atraviesan inicio y salida); el jugador rebota al sobrepasar la Ciudad Refugio, completando el valor exacto del dado.


8. Convención de representación del tablero
Caracteres ASCII: J (Jugador), I (Inicio), S (Salida/Ciudad Refugio), P (Premio), V (Vida extra), O (Oasis), T (Tormenta), B (Bandido) y . (posición vacía / ruta despejada).
Cada posición se escribe entre corchetes. Cuando una casilla contiene varios elementos, sus caracteres se escriben juntos sin espacio, ordenados por prioridad. Los bandidos pueden apilarse en una misma casilla. En el archivo de caravana, una casilla vacia se representa como [.]. 
Ejemplo:  [IJ][.][OP][TBBB][.][.][VB][.][.][STP]


10. Características adicionales (declaradas y documentadas)
Log de eventos: franja de mensajes bajo la escena para input y eventos del juego, separada del HUD.
Animaciones de estado: secuencias visuales de cambio de estado (escudo de oasis, flechas de tormenta, jugador que pasa a minúscula al ser dañado, bandido que desaparece).
Ranking (Top 10): ordenado por puntaje total acumulado de cada jugador; admite jugadores distintos con igual puntaje.
Alta de jugador: validación de nickname único y reconocimiento de homónimos (mismo nombre, distinto nickname) al ingresar.
Escenario dinámico: se genera un nuevo escenario en cada partida respetando los parámetros de configuración.
11. Compilacion y ejecucion
Lenguaje: C (estándar C11). Proyecto Code::Blocks (CaravanaDelDesierto.cbp) dividido en archivos .h y .c.
Estado: compila con 0 errores y 0 warnings.
Requisitos: el archivo config.txt debe encontrarse en el directorio de ejecución. Los archivos .bin y .idx se generan automáticamente al jugar.


12. Integrantes del equipo
DNI       Apellido y nombres 
45495729  Dotta, Elian Agustin
45481129  Amarilla, Santiago Daniel
45991825  Perez Puente, Manuel
46195413  Costilla, Lucas Leonel




