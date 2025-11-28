#include "../include/Partida.h"
#include <fstream>

Partida::Partida(Tablero & newtab, ConjuntoJugadores & newjug){
    tab=newtab;
    jugs=newjug;
}

Partida::Partida(string fich, int fils, int cols, int numbombas, string nickjugador){
    inicializaPartida(fich,fils,cols,numbombas,nickjugador);
}

bool Partida::Turno(){
    bool correcto=true;
    int fila,columna,accion;

    cout << tab.mostrarTableroaJugador();
    cout << "Indica la casilla: " << endl;
    cin >> fila >> columna;
    cout << "Accion (0:abrir posicion, 1:marcar posicion, 2:desmarcar posicion):" << endl;
    cin >> accion;
        if (accion == 0) {
            correcto = tab.abrirpos(fila, columna);
        } else if (accion == 1) {
            tab.marcarpos(fila, columna);
        } else if (accion == 2) {
            tab.desmarcarpos(fila, columna);
        }
    return correcto;
}

void Partida::inicializaPartida(string fichero, int fils, int cols, int numbombas, string nick){
    fich = fichero;
    nickJugador=nick;
    Tablero tabcopia(fils,cols,numbombas);
    tab = tabcopia;
    tab.mostrartablerobombas();
}

void Partida::saveJugadores() {
    ofstream file(fich); //ofstream para pasarle parametros
    if (file.is_open()){
        file << jugs;
        file.close();
    }
}

void Partida::loadJugadores() {
    ifstream file(fich);  //ifstream file para copiar del fichero
    if (file.is_open()) {
        file >> jugs;
        file.close();
    }
}
void Partida::realizaPartida() {
    loadJugadores();
    cout << nickJugador << endl;


    bool correcto=true;
        while (correcto && !tab.haganado()) {
            correcto = Turno();
        }

    if(jugs.buscaJugador(nickJugador)==-1){
        Jugador jugaux(0,nickJugador);
        jugs+=jugaux;
    }

    int posicion;
    posicion = jugs.buscaJugador(nickJugador);
    if(tab.haganado()==1){
        cout << endl << "Has ganado la partida" << endl;
        jugs[posicion].numPartidasGanadas()++;
    } else if (tab.haganado()==0){
        cout << endl << "Has perdido." << endl;
        jugs[posicion].numPartidasPerdidas()++;
    }
    saveJugadores();
    cout << jugs.mostrarRanking();
}