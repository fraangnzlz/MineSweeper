#ifndef PARTIDA_H
#define PARTIDA_H
#include "Tablero.h"
#include "ConjuntoJugadores.h"


#include <iostream>
#include <cstring>


class Partida {
public:
    Partida(Tablero &newtab, ConjuntoJugadores &newjug);
    Partida(string fich, int fils, int cols, int numbombas, string nickjugador);
    void inicializaPartida(string fich, int fils, int cols, int numbombas, string nickjugador);
    bool Turno();
    Partida(const Partida & orig);
    void saveJugadores();
    void loadJugadores();
    void realizaPartida();

private:
    Tablero tab; //objeto de clase Tablero
    ConjuntoJugadores jugs;
    string fich;
    string nickJugador;

};

#endif //PARTIDA_H
