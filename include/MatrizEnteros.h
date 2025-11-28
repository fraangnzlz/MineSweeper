#ifndef MATRIZENTEROS_H
#define MATRIZENTEROS_H

#include <string>
using namespace std;
class MatrizEnteros {
public:
    /**@brief Inicializa la clase MatrizEnteros
        @param fil NÃºmero de filas de la matriz.
     * @param col NÃºmero de columnas de la matriz.
     * @param def valor por defecto de la matriz (de inicializaciÃ³n).
     */
    MatrizEnteros(int fil, int col, int def );

    MatrizEnteros();
    /**@brief dejar vacÃ­o*/
    MatrizEnteros(const MatrizEnteros& orig);
    /**@brief dejar vacÃ­o*/
    ~MatrizEnteros(); //DESTRUCTOR

    /**@brief Devuelve un string que contiene la matriz. Se usarÃ¡
     * \n al final de cada fila y se dejarÃ¡ un espacio entre los elementos.
     * Ejemplo (matriz de 2 filas y 5 columnas:
     * 1 2 3 4 5 \n 9 8 7 6 4 \n
     * Cuando se imprima con cout se mostrarÃ¡:
     * 1 2 3 4 5
     * 9 8 7 6 4
     */
    string matriztostring();

    /**
     * @brief Devuelve el nÃºmero de filas de la matriz
        @return numero filas
     */
    int numfilas();
    /**
     * @brief Devuelve el nÃºmero de columnas de la matriz
     * @return numero columnas
     */
    int numcolumnas();

    /**
     * @brief Devuelve una referencia a un valor de la matriz lo que permite
     * su modificaciÃ³n
     * @param fil nÃºmero de fila.
     * @param col nÃºmero de columna.
     * Ejemplo de uso:
     * 1 2 3
     * 4 5 6
     * 7 8 9
     *  m.putValue(1,1) = 4
     * 1 2 3
     * 4 4 6
     * 7 8 9
     */
    int & putValue(int fil, int col);

    /**
     * @brief Devuelve un valor de la matriz
     * @param fil
     * @param col
     * @return el valor de esa posiciÃ³n de la matriz
     */
    int getValue(int fil, int col);


    /**
     * @brief Todos los valores de la matriz pasan a ser el valor por defecto
     * (elimina la informaciÃ³n).
     * @param defecto El valor al que poner todos los valores de la matriz.
     */
    void inicializarMatriz(int def);

    //3 NUEVOS METODOS A USAR EN ESTA PRACTICA
    void liberarMemoria();
    MatrizEnteros& operator=(const MatrizEnteros& obj);

    friend ostream & operator<< (ostream & flujo, const MatrizEnteros &m);

    /**
     * @brief Modifica el tamaÃ±o de la matriz. Si la nueva matriz es mÃ¡s grande
     * que la original entonces se conservan los valores. Si es mÃ¡s chica se borra
     * la informaciÃ³n.
     * @param newf nuevo tamaÃ±o de fila
     * @param newc nuevo tamaÃ±o de columna
     */
    void resize(int newf, int newc, int value);
private:
    int **m;
    int filas;
    int columnas;

};


#endif /* MATRIZENTEROS_H */