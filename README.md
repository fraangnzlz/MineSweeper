# MineSweeper

Este proyecto es una implementación de consola del clásico juego del Buscaminas desarrollado en C++, aplicando los principios básicos de la Programación Orientada a Objetos.

## Estructura de Clases

El proyecto está diseñado de forma modular utilizando las siguientes entidades:

* **`Tablero`**: Controla la cuadrícula del juego, la colocación aleatoria de minas y la interfaz de casillas descubiertas o marcadas por el usuario.
* **`MatrizEnteros`**: Clase base para crear matrices bidimensionales dinámicas, encargada de la gestión segura de memoria y el redimensionamiento del área de juego.
* **`Partida`**: Controla el bucle de juego, gestionando las entradas del usuario, evaluando el final de la partida (victoria o derrota) y orquestando el guardado de progreso.
* **`Jugador` y `ConjuntoJugadores`**: `Jugador` registra el alias (nick), identificador y el historial de victorias y derrotas individuales. `ConjuntoJugadores` actúa como una colección de estos perfiles, ordenándolos por *winrate* para generar un ranking, y se encarga de la lectura/escritura en ficheros.

## Compilación y Ejecución

El programa exige un formato estricto en la línea de comandos para iniciar, esperando exactamente 11 argumentos (el nombre del ejecutable más 5 parejas de clave-valor). 

Para ejecutar tu proyecto, la estructura que espera el código es la siguiente:
` ` `bash
./buscaminas -f <filas> -c <columnas> -m <minas> -nick <ruta_fichero_jugadores> -fich <nombre_jugador>
` ` `
*Si no introduces la cantidad de parámetros o las etiquetas correctas, el programa te indicará el error de estructura y terminará la ejecución.*

## Mecánicas de Turno

Durante la partida, la consola te mostrará el tablero actualizado y pedirá tus comandos paso a paso. Para realizar un movimiento:
1. Introduce la **fila** y la **columna** que deseas modificar.
2. Elige la **acción** a ejecutar:
   * **0**: Abrir la posición.
   * **1**: Marcar la posición (señalar que hay una mina).
   * **2**: Desmarcar la posición.

Al concluir el juego, ya sea por victoria o al pisar una mina, tu historial de victorias y derrotas se actualizará de forma persistente y se mostrará el ranking global por pantalla.
