#ifndef CONJUNTOJUGADORES_H
#define CONJUNTOJUGADORES_H

#include "Jugador.h"
#include <iostream>
#include <fstream>

using namespace std;

class ConjuntoJugadores {
public:
    /**
     * @brief Inicializa el vector de jugadores a un tamaño reservado específico.
     * @param k tamaño reservado (este puede ir incrementándose conforme sea necesario).
     */
    ConjuntoJugadores(int k=5);

    /**
     * @brief Constructor de copia de la clase conjuntoJugadores
     * @param orig objeto ConjuntoJugadores desde donde se copia la información.
     */
    ConjuntoJugadores(const ConjuntoJugadores& orig);

    /**
     * @brief destructor de la clase. Libera el espacio reservado.
     */
    virtual ~ConjuntoJugadores();

    /**
     * @brief Se inicializa el objeto ConjuntoJugadores con la información del vector de nicks vnicks.
     *  Los ids se van asignando desde el 1
     * en adelante siguiendo el orden en que aparecen los nicks en el vector. Si se
     * utiliza este constructor entonces el tamaño reservado coincide con el número de
     * jugadores.
     * @param n Número de elementos en el vector vnicks.
     * @param vnicks Vector con los nicks de los jugadores.
     */
    ConjuntoJugadores(int n, string* vnicks);
    /**
     * @brief Devuelve un string que imprime la lista de jugadores ordenados por su
     * porcentaje de partidas ganadas (partidas ganadas/partidas jugadas).
     * @return Un string de los jugadores separados por el caracter \n. Cada linea
     * imprimirá en orden: id, nick, partidasganadas/partidasjugadas.
     * El jugador con mejor índice será el primero y el peor el último.
     */
    string mostrarRanking();

    /**
     * @brief Operador de asignación.
     * @param orig objeto ConjuntoJugadores que es asignado.
     * @return objeto ConjuntoJugadores con los datos de orig asignados.
     */
    ConjuntoJugadores & operator=(const ConjuntoJugadores & orig);

    /**
     * @brief Introduce en flujo la información toda la informacion del vector de jugadores.
     * Utilizamos el operador << de jugador para hacer este proceso y entre Jugador y
     * Jugador se introduce el caracter "\n" para que cada jugador aparezca en una línea
     * si lo imprimimos con cout. Antes de imprimir los jugadores se imprime el numero de jugadores,
     * luego \n y luego cada uno de los jugadores.
     */
    friend std::ostream & operator<< (std::ostream & flujo, const ConjuntoJugadores & m);

     /**
     * @brief Lee del flujo la información los jugadores que forman parte del vector.
     * Utilizamos el operador >> de jugador para leer cada uno de los jugadores. Entre Jugador y
     * Jugador se introduce el caracter "\n" para que cada jugador aparezca en una línea
     * si lo imprimimos con cout. El primer valor leido es un entero con el numero de jugadores.
     * Los datos en el flujo tienen la forma:
     * EJEMPLO:
     *  3
     *  1 Marcos 1 0
     *  2 Juanan 2 2
     *  3 Pedro 4 0
     *
     * Tanto << como >> pueden utilizarse para leer de ficheros como para imprimir por pantalla
     */
    friend std::istream & operator>> (std::istream & flujo,  ConjuntoJugadores & m);
    /**
    * @brief Añade un nuevo Jugador al vector de Jugadores.
    * @param newjug Nuevo jugador que se añade al vector.
    * @return El objeto ConjuntoJugadores con el jugador añadido. Debe estar ordenado
     * por id. Es importante tener en cuenta que los ids no tienen porque ser números
     * enteros continuos porque los jugadores se pueden eliminar del vector. Puede asumirse
     * que no hay ids repetidos. Puede utilizarse el método ordenaporId para ordenar el vector.
    */
    ConjuntoJugadores & operator+=(const Jugador& newjug);

    /**
     * @brief Elimina del vector de Jugadores al jugador que tenga como id el indicado.
     * @param jugid id del jugador a eliminar del vector.
     */
    void eliminaJugador(int jugid);

    /**
     * @brief Devuelve la posición en el vector del jugador cuyo id es igual al indicado.
     * @param jugid id del jugador que buscamos.
     * @return -1 si no hay ningún jugador con esa id o el número de posición en caso
     * de haberlo.
     */
    int buscaJugador(int jugid);

    /**
     * @brief Devuelve la posición en el vector del jugador cuyo nombre es igual al indicado.
     * @param nickbuscado nick del jugador que buscamos.
     * @return -1 si no hay ningún jugador con ese nombre o el número de posición en caso
     * de haberlo.
     */
    int buscaJugador(string nickbuscado);

    /**
     * @brief Minimiza el espacio reservado haciendo que tamreservado == numjugadores y ese sea
     * justo el número de espacios reservado en el vector.
     */
    void optimizar();

    /**
     * @brief operador de acceso al vector de Jugadores.
     * @param i posición del jugador que queremos devolver.
     * @return El objeto jugador que está localizado en la posición i.
     */
    Jugador & operator[](int i) const;

    /*
     * @brief Une dos conjuntos ConjuntoJugadores en 1 solo. left y right se unen y
     * se devuelve un conjunto ConjuntoJugadores que tiene a las personas que hay en
     * ambos conjuntos.
     * @param left ConjuntoJugador con los primeros Jugadores.
     * @param right Conjuntojugador con los segundo Jugadores.
     * @return un objeto ConjuntoJugadores con todos los elementos de los objetos
     * left y right.
     */
    friend ConjuntoJugadores operator+( const ConjuntoJugadores & left, const ConjuntoJugadores & right);
    int numJugadores() const;
private:
    /**
     * @brief Ordena los Jugadores de un objeto ConjuntoJugadores en base a su id.
     */
    void ordenaporId();

    /**
     * @brief Aumenta el tamaño reservado del vector. La información del vector de
     * Jugadores se mantiene.
     * @param newtam Nuevo tamaño de espacio reservado.
     */
    void resize(int newtam);



    /* Vector de objetos Jugador
     */
    Jugador * vectorJugadores;
    /* Número de jugadores en el objeto */
    int numjugadores;
    /*Tamaño reservado en el vector*/
    int tamreservado;
};



#endif /* CONJUNTOJUGADORES_H */

