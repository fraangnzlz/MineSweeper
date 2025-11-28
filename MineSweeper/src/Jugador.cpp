#include "../include/Jugador.h"
#include <cstring>
#include <iostream>



Jugador::Jugador() { //Constructor. Deja los valores a 0
    numpartidasperdidas = 0;
    numpartidasganadas = 0;
    id = 0;
}

string Jugador::getNick() const{ //Devuelve un string con el nick del jugador.
    return nick; //la variable nick ya es un string
}

Jugador::Jugador(const Jugador& orig) { //Constructor de copia
    nick = orig.nick;
    id = orig.id;
    numpartidasganadas = orig.numpartidasganadas;
    numpartidasperdidas = orig.numpartidasperdidas;
}

Jugador::~Jugador() {
    //No hay memoria dinamica, asi que no hay que liberar memoria
}

int Jugador::numPartidasGanadas() const{ //Funcion const para que pueda ser usado en los operadores de comparación.
    return numpartidasganadas;
}
int & Jugador::numPartidasGanadas(){
    return numpartidasganadas;
}

int & Jugador::numPartidasPerdidas(){
    return numpartidasperdidas;
}
//como solo almacenamos las partidas ganadas y las perdidas necesitamos
//calcular las partidas jugadas como suma de ambas. Mejor así que duplicar
//información
int Jugador::numPartidasJugadas() const {
    int partidasjugadas;
    partidasjugadas = numpartidasganadas + numpartidasperdidas;
    return partidasjugadas;
}
int Jugador::GnumPartidasJugadas() const {
    return numpartidasperdidas+numpartidasganadas;
}
int Jugador::GnumPartidasGanadas() const {
    return numpartidasganadas;
}
string & Jugador::setNick() { //Metodo para devolver el nick que se le asigne
    return nick;
}
int Jugador::getId() const{
    return id; //No nos dicen que sea en forma de string, asi q lo dejamos asi
}

Jugador::Jugador(int newid, string nuevoNick){ //Crea un objeto jugador con un id y nick determinados
    id = newid;
    nick = nuevoNick;


}
//devolvemos referencia al valor para cambiarlo desde fuera
int & Jugador::setId(){
    return id;
}

Jugador & Jugador::operator=(const Jugador & orig){
    /* Queremos devolver una referencia del objeto ORIG, por lo que si no es orig
     hemos de hacer como en el CONSTRUCTOR DE COPIA */
    if (this != &orig) {
        nick = orig.nick;
        id = orig.id;
        numpartidasganadas = orig.numpartidasganadas;
        numpartidasperdidas = orig.numpartidasperdidas;
    }
    return *this;  //Devolver la referencia con *this como nos indican
}

//Comparamos dos jugadores en funcion de partidasganadas/partidasjugadas
//implementamos todos los operadores
bool operator==( const Jugador & izq, const Jugador & dch){
    double media1,media2;

    if (izq.numPartidasJugadas()== 0) {
        media1 = 0;
    }else {
        media1 = (izq.numPartidasGanadas() / izq.numPartidasJugadas());
    }

    if (dch.numPartidasJugadas() == 0) {
        media2 = 0;
    }else{
        media2 = (dch.numPartidasGanadas() / dch.numPartidasJugadas());
    }

    if ( media1 > media2) {
        cout<<"\nEl jugador 1 es mejor";
        return false;
    }else if (media2 > media1){             //Podemos simplificarlo pero lo he preferido hacer asi
        cout<<"\nEl jugador 2 es mejor";
        return false;
    }else {
        cout << "\nLas medias son iguales";
        return true;
    }
}

bool operator!=( const Jugador & izq, const  Jugador & dch){ //Si las medias son diferentes
    double media1, media2;
    if (izq.numPartidasJugadas() == 0) {
        media1 = 0;
    }else {
        media1 = (izq.numPartidasGanadas() / izq.numPartidasJugadas()) ;
    }

    if (dch.numPartidasJugadas() == 0) {
        media2 = 0;
    }else {
        media2 = (dch.numPartidasGanadas() / dch.numPartidasJugadas()) ;
    }
    return media1 != media2; //En un metodo bool, si pasa esto devuelve true, si no false
}

bool operator<( const Jugador &izq, const Jugador & dch) {
    double media1, media2;
    if (izq.numPartidasJugadas() == 0) {
        media1 = 0;
    }else {
        media1 = (izq.numPartidasGanadas() / izq.numPartidasJugadas()) ;
    }

    if (dch.numPartidasJugadas() == 0) {
        media2 = 0;
    }else {
        media2 = (dch.numPartidasGanadas() / dch.numPartidasJugadas()) ;
    }
    return media1 < media2;
}

bool operator>( const Jugador &izq, const Jugador & dch){
    double media1, media2;
    if (izq.numPartidasJugadas() == 0) {
        media1 = 0;
    }else {
        media1 = (izq.numPartidasGanadas() / izq.numPartidasJugadas()) ;
    }

    if (dch.numPartidasJugadas() == 0) {
        media2 = 0;
    }else {
        media2 = (dch.numPartidasGanadas() / dch.numPartidasJugadas()) ;
    }
    return media1 > media2;
}
bool operator<=( const Jugador &izq,  const Jugador & dch){
    double media1, media2;
    if (izq.numPartidasJugadas() == 0) {
        media1 = 0;
    }else {
        media1 = ((float)izq.numPartidasGanadas() / izq.numPartidasJugadas()) ;
    }

    if (dch.numPartidasJugadas() == 0) {
        media2 = 0;
    }else {
        media2 = ((float)dch.numPartidasGanadas() / dch.numPartidasJugadas()) ;
    }
    return media1 <= media2;
}
bool operator>=( const Jugador &izq, const Jugador & dch){
    double media1, media2;
    if (izq.numPartidasJugadas() == 0) {
        media1 = 0;
    }else {
        media1 = ((float)izq.numPartidasGanadas() / izq.numPartidasJugadas()) ;
    }

    if (dch.numPartidasJugadas() == 0) {
        media2 = 0;
    }else {
        media2 = ((float)dch.numPartidasGanadas() / dch.numPartidasJugadas()) ;
    }
    return media1 >= media2; //True si esto pasa
}


//imprimimos todos los datos del jugador
ostream & operator << (ostream & flujo, const Jugador & jug){
    flujo << jug.getId() << " "
          << jug.getNick() << " "
          << jug.numPartidasGanadas() << " "
          << jug.numPartidasJugadas(); //Devuelve partidas JUGADAS, no perdidas, como dice el guion
    return flujo;
} //He tenido que cambiar y poner const en el metodo getNick ya que lo estoy llamando en uno const
