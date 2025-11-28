#ifndef TABLERO_H
#define TABLERO_H
#include "MatrizEnteros.h"
#include <iostream>
#include <string>
#include <random>
#include <fstream>

using namespace std;

/**
 @class Tablero La clase tablero representa un tablero de juego para el buscaminas
 * Ahora mismo solo estan disponibles los metodos relacionados con la inicializacion del tablero
 * En practicas posteriores se aniadiran los metodos de interaccion del usuario con la clase.
 *
 * La clase Tablero consta de 3 variables:
 *
 * @var tab es la matriz que contiene la informacion de donde estan localizadas las minas
 * y que se debe de mostrar al abrir cada casilla (el numero de minas alrededor de la casilla abierta)
 *
 * @var descubierto permite identificar que posiciones de la matriz estan abiertas, cuales se desconoce
 * lo que hay detras y que posiciones el jugador ha marcado como que el cree que hay una bomba. Actua
 * de interfaz con el usuario y permite saber que informacion se puede mostrar y que informacion no durante
 * el juego.Ã©
 *
 * @var NUMBOMBA es el numero entero que representa que en esa casilla hay una bomba. Se recomienda -1 ya
 * que es un valor numerico que nunca podrian alcanzar las otras casillas aunque se puede utilizar 9 para mejorar
 * la visualizacion del tablero en la terminal.
 */

class Tablero {
private:
    MatrizEnteros tab; // NUMBOMBA --> mina otro valor --> numero de minas alrededor de la casilla
    MatrizEnteros descubierto; // 0 --> no descubierto, 1 --> descubierto, 2 --> marcaje
    static const int NUMBOMBA=9; //valor numerico que indica que hay una bomba en esa casilla
    /**
     * @brief Coloca el numero de bombas que indica la variable numbombas de forma aleatoria por el tablero
     * Se asigna el valor NUMBOMBA a dichas casillas en la variable tab.
     * @param numbombas
     */
    void colocarBombas(int numbombas);

    /**
     * @pre Para llamar a esta funcion se deben de haber colocado las bombas por el tablero.
     * @brief Calcula, para cada casilla del tablero en la que no haya una bomba, el numero de bombas que
     * hay alrededor. Si no hay ninguna bomba alrededor de esa casilla, el valor es 0.
     */
    void calculardistancias();

    /**
     * @brief Se llama a esta funcion desde el constructor con parametros. Se encarga de inicializar el tablero
     * asignar las bombas y calcular las distancias. Por tanto, se llama a los metodos inicializarTablero
     * colocarBombas y calculardistancias en ese orden.
     * @param f filas del tablero
     * @param c columnas del tablero
     * @param numbombas numero de bombas que debe colocarse en el tablero.
     */
    void inicializarTablero(int f, int c, int numbombas);

    /**
     * @brief Inicializa las matrices de forma que todos los valores de las matrices sean 0 y tengan el numero de filas
     * y columnas especificadas por las variables f y c
     * @param f numero de filas que queremos que tenga el tablero
     * @param c numero de columnas que queremos que tenga el tablero.
     */
    void inicializarVariables(int f, int c);





public:

    /**
     * @brief Constructor sin parametros. Se puede elegir entre no hacer nada o reservar a unos valores
     * por defecto.
     */
    Tablero();

    /**
     * @brief Constructor con parametros. Este constructor llama a inicializarTablero. Inicializa un objeto
     * de la clase con un tablero de buscaminas de tamanio fxc y coloca aleatoriamente el numero de bombas
     * indicado en numbombas. Tambien se llama a calcularDistancias para rellenar el tablero.
     * @param f numero de filas del tablero de buscaminas
     * @param c numero de columnas del tablero de buscaminas
     * @param numbombas numero de bombas colocadas aleatoriamente en el tablero.
     */
    Tablero(int f, int c, int numbombas);
    bool abrirpos(int i, int j);
    void mostrartablerobombas();
    void abrirrecursivas(int i, int j);
    /**
     * Constructor de copia de la clase
     * @param orig objeto del que copiar los datos.
     */
    Tablero(const Tablero & orig);
    int numfilas();
    int numcolumnas();
    /**
     * @brief Imprime los valores de la matriz tab de la clase
     *
     * EJEMPLO DE MATRIZ (en este caso NUMBOMBA = 9):
     * 0 0 0 0 0 0 0 0
     * 1 1 0 0 1 2 2 1
     * 9 1 0 0 1 9 9 1
     * 1 1 0 0 1 2 2 1
     * 0 0 0 0 0 0 0 0
     *
     * @return Una cadena con toda la informacion del tablero.
     */
    string mostrarTableroEntero();

    /**
     * @brief Imprime los valores de la matriz descubierto.
     * @return Una cadena con la informacion de la variable descubierto
     */
    string mostrarDescubierto();

    /**
     * @brief Muestra el tablero tal y como lo veria el jugador en la partida.
     * Combina la informacion de tab y descubierto para decidir que mostrar.
     *
     * Si en descubierto[i][j] hay un 0, entonces la casilla no esta abierta
     * con lo que se imprime '?'.
     *
     * Si en descubierto[i][j] hay un 1, entonces la casilla esta abierta y se
     * imprime el valor de tab.
     *
     * Si en descubierto[i][j] hay un 2, entonces el jugador ha marcado la casilla
     * indicando que hay una bomba. Por tanto, se imprime 'B'.
     *
     * EJEMPLO:
     *
     * 0 0 0 0 0 0 0 0
     * 1 1 0 0 1 2 2 1
     * B 1 0 0 1 ? ? ?
     * 1 1 0 0 1 2 2 1
     * 0 0 0 0 0 0 0 0
     *
     * @return Un string que muestra la matriz describa.
     *
     *
     */
    string mostrarTableroaJugador();
  /**
     * @brief Almacena la informacion de la clase en la ruta de fichero indicada.
     * Primero se pone, en una linea el numero de filas y columnas, luego las 2 matrices
     * tal y como puede verse en el ejemplo de mas abajo.
     * @param fich ruta del fichero en donde almacenar la informacion de la clase
     *
     * EJEMPLO DE FORMATO:
     *
     * 8 8
     * 0 0 1 9 2 1 1 0
     * 0 0 1 1 2 9 1 0
     * 0 0 1 1 2 1 1 0
     * 0 1 2 9 1 0 0 0
     * 0 1 9 2 1 0 0 0
     * 0 1 1 1 0 0 0 0
     * 1 1 0 0 0 0 0 0
     * 9 1 0 0 0 0 0 0

     * 0 0 0 0 0 0 0 0
     * 0 0 0 0 0 0 0 0
     * 0 0 0 0 0 0 0 0
     * 0 0 0 0 0 0 0 0
     * 0 0 0 0 0 0 0 0
     * 0 0 0 0 0 0 0 0
     * 0 0 0 0 0 0 0 0
     * 0 0 0 0 0 0 0 0
     */
   void saveFichero(string fich);

    /**
     * @brief Rellena el objeto con la informacion almacenada en fich
     * Lee el fichero con el formato creado con saveFichero.
     * @param fich ruta del fichero en donde esta almacenado un objeto Tablero
     */
    void loadFichero(string fich);

    //METODOS A IMPLEMENTAR
    bool haganado();

    void marcarpos(int i, int j);

    void desmarcarpos(int i, int j);

    Tablero& operator=(const Tablero& otro);
};

#endif /* TABLERO_H */
