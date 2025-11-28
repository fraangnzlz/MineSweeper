#include "../include/ConjuntoJugadores.h"

//nuevo vector de jugadores con tamreservado a k y sin jugadores (0)
ConjuntoJugadores::ConjuntoJugadores(int k) {
    vectorJugadores = new Jugador[k]; //No *[k] ya que no es un puntero de punteros
    tamreservado = k;
    numjugadores = 0;
}

ConjuntoJugadores & ConjuntoJugadores::operator=(const ConjuntoJugadores & orig){
    //Copiamos en el vectorJugadores lo que haya en el orig
    if (this != & orig) {
        delete [] vectorJugadores;
        tamreservado = orig.tamreservado;
        numjugadores  = orig.numjugadores;
        vectorJugadores = new Jugador[tamreservado];

        for (int i = 0; i < tamreservado; i++) {
            vectorJugadores[i] = orig.vectorJugadores[i];
        }
    }
    return *this;
}

//como el operador = pero en este caso el objeto se crea desde 0 con lo que
//no hace falta hacer delete y se reserva directamente
ConjuntoJugadores::ConjuntoJugadores(const ConjuntoJugadores& orig) {
    tamreservado = orig.tamreservado;
    numjugadores = orig.numjugadores;
    vectorJugadores = new Jugador[tamreservado]; //Nuevo vector
    for (int i = 0; i < numjugadores;i++) {
        vectorJugadores[i] = orig.vectorJugadores[i];
    }
}

ConjuntoJugadores::~ConjuntoJugadores() {
    if (vectorJugadores != nullptr) {
        delete [] vectorJugadores;
    }
}

//Crea un vector de jugadores a partir de un vector de strings
//en este caso reservamos el tamanio justo y necesario para almacenar
//la información
ConjuntoJugadores::ConjuntoJugadores(int n, string* vnicks){
    vectorJugadores = new Jugador[n];
    tamreservado = n;
    numjugadores = n;
    for (int i = 0; i < n; i++) {
        vectorJugadores[i].setId() = (i+1);
        vectorJugadores[i].setNick() = vnicks[i];  //SetNick() para ASIGNARLE (devolver una referencia) el nick. Con getNick lo obtengo pero no lo devuelvo, por tanto no sale nada.
    }
}

//Ordenamos a todos los jugadores en función del criterio:
//partidasganadas/partidasjugadas
// y mostramos por pantalla
string ConjuntoJugadores::mostrarRanking(){
        //Voy a crear un vector que contenga lo mismo que vectorJugadores para asi no modificar el original y evitar errores innecesarios
        Jugador* copia = new Jugador[numjugadores];
        for (int i = 0; i < numjugadores; i++) {
            copia[i] = vectorJugadores[i];
        }
        //Utilizo el metodo de burbuja para ordenar
        for (int i = 0; i < numjugadores - 1; i++) {
            for (int j = 0; j < numjugadores - i - 1; j++) {
                float ratio1, ratio2;

                if (copia[j].numPartidasJugadas() == 0)  //Si partidas jugadas es 0, el ratio sera 0 obviamente
                    ratio1 = 0;
                else
                    ratio1 = (float)copia[j].numPartidasGanadas() / copia[j].numPartidasJugadas();

                if (copia[j + 1].numPartidasJugadas() == 0)
                    ratio2 = 0;
                else
                    ratio2 = (float)copia[j + 1].numPartidasGanadas() / copia[j + 1].numPartidasJugadas();

                if (ratio2 > ratio1) {
                    Jugador tmp = copia[j];
                    copia[j] = copia[j + 1];
                    copia[j + 1] = tmp;
                }
            }
        }

        //Con un string que llamaremos resultado mostramos el ranking
        string resultado;
        for (int i = 0; i < numjugadores; i++) {
            resultado += to_string(copia[i].getId()) + " ";
            resultado += copia[i].getNick() + " ";
            resultado += to_string(copia[i].numPartidasGanadas()) + " ";
            resultado += to_string(copia[i].numPartidasPerdidas()) + "\n";
        }
        delete[] copia;
        return resultado;
    }

//leemos un conjunto de jugadores de un fichero o flujo
//El fichero o obtención de datos se puede ver en el fichero ejemplo, es:
// 2
// 1 Juan 0 1
// 2 Pedro 1 1
//primero el numero de jugadores y luego en cada fila el id, nick
// partidas ganadas y partidas perdidas del jugador
std::istream & operator>> (std::istream & flujo,  ConjuntoJugadores & m){
    int n;
    flujo >> n;
    string nick;
    delete[] m.vectorJugadores;
    m.vectorJugadores = new Jugador[n];
    m.tamreservado = n;
    m.numjugadores = n;
    for (int i = 0; i < n; ++i) {
        int id, ganadas, perdidas;
        flujo >> id >> nick >> ganadas >> perdidas;
        Jugador j(id, nick);
        j.numPartidasGanadas() = ganadas;
        j.numPartidasPerdidas() = perdidas;
        m.vectorJugadores[i] = j;
    }
    return flujo;
}

//para mostrar por pantalla o escribir en fichero los datos del vector de
//jugadores
std::ostream & operator<< (std::ostream & flujo, const ConjuntoJugadores & m){
    for (int i = 0; i < m.numjugadores;i++) {
        flujo << m.vectorJugadores[i] <<"\n";
    }
    return flujo;
}

//anaide un jugador al final del vector
ConjuntoJugadores & ConjuntoJugadores::operator+=(const Jugador& newjug){
    if (numjugadores == tamreservado) {
        resize(tamreservado + 1); //Ampliamos en 1 la posicion para que quepa el jugador nuevo
    }
    vectorJugadores[numjugadores++] = newjug;
    ordenaporId(); //METODO DE CONJUNTOJUGADORES, NO DE JUGADOR
    return *this;
}

//elimina un jugador del vector de jugadores en funcion del id
void ConjuntoJugadores::eliminaJugador(int jugid) {
    //Eliminamos al jugador que tenga el mismo id que la variable jugid
    for (int i = 0; i < numjugadores; i++) {
        if (vectorJugadores[i].getId() == jugid) {
            for (int j = i; j < numjugadores - 1; j++) {
                vectorJugadores[j] = vectorJugadores[j + 1];
            }
            numjugadores--;
        }
    }
}

//buscamos la posicion de un jugador que tiene un determinado id
int ConjuntoJugadores::buscaJugador(int jugid){
    //Devuelve la posicion que coincida con el id de jugid
    for (int i = 0; i < numjugadores; i++) {
        if (vectorJugadores[i].getId() == jugid)
            return i;
        }
    return -1;
}

int ConjuntoJugadores::numJugadores() const{
    return numjugadores;
}

//buscamos al jugador por el nick y devolvemos -1 si no existe
int ConjuntoJugadores::buscaJugador(string nickbuscado){
    for (int i = 0; i < numjugadores; i++) {
       if (vectorJugadores[i].getNick() == nickbuscado)
           return i;
       }
        return -1;
       }

// optimizar hace que numjugadores == tamreservado,
// no reservamos ninguna posición de más

void ConjuntoJugadores::optimizar(){
    if (tamreservado == numjugadores) return;
    Jugador* nuevovector = new Jugador[numjugadores];
    for (int i = 0; i < numjugadores; i++) {
        nuevovector[i] = vectorJugadores[i]; //Copiamos los datos
    }
    delete [] vectorJugadores;
    vectorJugadores = nuevovector;
    tamreservado = numjugadores;
}

Jugador & ConjuntoJugadores::operator[](int i) const{
    //Devuelve al jugador que esta en la posicion i
    return vectorJugadores[i];
}
void ConjuntoJugadores::ordenaporId() {
    for (int i = 0; i < numjugadores - 1; ++i) {
        for (int j = 0; j < numjugadores - i - 1; ++j) {
            if (vectorJugadores[j].getId() > vectorJugadores[j + 1].getId()) {
                Jugador cambio = vectorJugadores[j];
                vectorJugadores[j] = vectorJugadores[j + 1];
                vectorJugadores[j + 1] = cambio;
            }
        }
    }
}


void ConjuntoJugadores::resize(int newtam) {
    if (newtam <= tamreservado){   // El operador !> NO ES VALIDO. COMPROBACION
        cerr << "\nNewtam no es mayor por lo que no se pude redimensionar" << endl;
    }else {
        Jugador* copia = new Jugador[newtam]; //Evitamos hacer cambios en el vectorJugadores
        for (int i = 0; i < numjugadores; i++) {
            copia[i] = vectorJugadores[i];
        }
        delete [] vectorJugadores;
        vectorJugadores = copia;
        tamreservado = newtam;
    }
}

//Une dos objetos conjunto jugadores
ConjuntoJugadores operator+( const ConjuntoJugadores & left, const ConjuntoJugadores & right){
    //Une conjuntos con +. Tambien hemos de ordenarlos segun su ID
    ConjuntoJugadores conjunto(left.numjugadores + right.numjugadores);

    for (int i = 0; i < left.numjugadores; i++) {
        conjunto += left.vectorJugadores[i];
    }
    for (int j = 0; j < right.numjugadores;j++) {
        conjunto += right.vectorJugadores[j];
    }
    conjunto.ordenaporId(); //Con conjunto delante ya que en un metodo con operador +, que es una funcion FRIEND, no del metodo
    return conjunto;
}