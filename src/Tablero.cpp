#include "../include/Tablero.h"
#include <fstream>
#include <string>
#include "../include/MatrizEnteros.h"

using namespace std;

Tablero::Tablero(int f, int c, int numbombas){
   inicializarTablero(f,c,numbombas);
}
//se inicializan las matrices a 2 matrices vacÃ­as con todo a 0
void Tablero::inicializarVariables(int f, int c){

}

void Tablero::inicializarTablero(int f, int c, int numbombas) {

   inicializarVariables(f, c);  // Inicializa las estructuras internas

   colocarBombas(numbombas);  // Coloca las bombas en el tablero
   calculardistancias(); //si no pongo el metodo como va a calcular las distancias
}

int Tablero::numfilas() {
   return tab.numfilas();
}
int Tablero::numcolumnas() {
   return tab.numcolumnas();
}


Tablero::Tablero(const Tablero & orig){
   tab = orig.tab;
   descubierto = orig.descubierto;
}

//muestra toda la informaciÃ³n del tablero
string Tablero::mostrarTableroEntero() {
   string resultado = "";

   for (int i = 0; i < tab.numfilas(); i++) {
      for (int j = 0; j < tab.numcolumnas(); j++) {
         if (tab.getValue(i, j) == NUMBOMBA) {
            resultado += "B ";
         } else {
            resultado += to_string(tab.getValue(i, j)) + " ";
         }
      }
      resultado += "\n";
   }

   return resultado;
}


//metodo para mostrar el tablero con las bombas. SI NO QUIERO QUE SALGA EL TABLERO CON TODO DESCUBIERTO SILENCIAR ESTE METODO
void Tablero::mostrartablerobombas() {
   cout << "Tablero con las bombas colocadas:\n" << mostrarTableroEntero() << endl;
}


Tablero::Tablero(){
   inicializarTablero(8, 8, 10);
}
//muestra toda la informaciÃ³n de lo que se ha abierto, lo que estÃ¡ cerrado
//y lo que estÃ¡ marcado
string Tablero::mostrarDescubierto(){
   return descubierto.matriztostring();
}
//Muestra el tablero tal y como lo debe de ver el jugador en el juego.
string Tablero::mostrarTableroaJugador() {
   string resultado = "";

   for (int i = 0; i < descubierto.numfilas(); i++) {
      for (int j = 0; j < descubierto.numcolumnas(); j++) {
         if (descubierto.getValue(i, j) == 0) {
            resultado += "? ";
         } else if (descubierto.getValue(i, j) == 1) {
            resultado += to_string(tab.getValue(i, j)) + " ";  //string IMPORTANTE ya que le sumamos un espacio
         } else {
            resultado += "B ";
         }
      }
      resultado += "\n";
   }
   return resultado;
}

void Tablero::colocarBombas(int numbombas) {
   random_device rd;
   mt19937 gen(rd());
   uniform_int_distribution<int> distFilas(0, tab.numfilas() - 1);
   uniform_int_distribution<int> distColumnas(0, tab.numcolumnas() - 1);

   // ✅ Asegurar que la matriz `tab` está inicializada con `0`
   for (int i = 0; i < tab.numfilas(); i++) {
      for (int j = 0; j < tab.numcolumnas(); j++) {
         tab.putValue(i, j) = 0;
      }
   }

   int bombasColocadas = 0;
   while (bombasColocadas < numbombas) {
      int randomfilas = distFilas(gen);
      int randomcolumnas = distColumnas(gen);

      // Si la celda no tiene bomba, coloca una
      if (tab.getValue(randomfilas, randomcolumnas) != NUMBOMBA) {
         tab.putValue(randomfilas, randomcolumnas) = NUMBOMBA; // ✅ Asignar la bomba
         bombasColocadas++;
      }
   }
}

//este metodo calcula el numero de bombas que hay alrededor de cada casilla

void Tablero::calculardistancias() {
   for (int i = 0; i < tab.numfilas(); i++) {
      for (int j = 0; j < tab.numcolumnas(); j++) {
         if (tab.getValue(i, j) == NUMBOMBA) {
            continue;  // Si ya hay una bomba, no se calcula nada
         }

         int contador = 0;

         // Recorremos las casillas vecinas (8 alrededor)
         for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
               // Saltar la propia casilla (i, j)
               if (dx == 0 && dy == 0) continue;

               int ni = i + dx;
               int nj = j + dy;

               // Validar que esté dentro del tablero
               if (ni >= 0 && ni < tab.numfilas() &&
                   nj >= 0 && nj < tab.numcolumnas()) {

                  if (tab.getValue(ni, nj) == NUMBOMBA) {
                     contador++;
                  }
                   }
            }
         }

         // Asignar el número de bombas cercanas
         tab.putValue(i, j) = contador;
      }
   }
}




void Tablero::saveFichero(string fich){
   ofstream archivo;  //OBJETO
   archivo.open(fich); //Abrimos el archivo

   archivo << tab.numfilas() << " " <<  tab.numcolumnas() << endl;
   archivo << mostrarTableroEntero() << endl;

   archivo << mostrarDescubierto() << endl;

   archivo.close();
}

void Tablero::loadFichero(string fich){
   ifstream archivo(fich); // Abrimos el archivo en modo lectura
   if (!archivo.is_open()) {
      cerr << "Error: No se pudo abrir el archivo " << fich << " para cargar.\n";
      return;
   }

   int filas, columnas;
   archivo >> filas >> columnas; // Leer dimensiones del tablero

   // Verificar si las dimensiones son válidas
   if (filas <= 0 || columnas <= 0) {
      cerr << "Error: Dimensiones inválidas en el archivo.\n";
      archivo.close();
      return;
   }

   // Inicializar las matrices con las dimensiones leídas
   inicializarVariables(filas, columnas);

   // Leer la matriz 'tab' (estado de las bombas y números)
   for (int i = 0; i < filas; i++) {
      for (int j = 0; j < columnas; j++) {
         int valor;
         if (!(archivo >> valor)) { // Verifica si la lectura fue exitosa
            cerr << "Error: Datos corruptos en la matriz tab en " << fich << ".\n";
            archivo.close();
            return;
         }
         tab.putValue(i, j) = valor;
      }
   }

   // Leer la línea en blanco que separa las matrices
   archivo.ignore();  // Ignora el último salto de línea
   string linea;
   getline(archivo, linea); // Leer la línea vacía

   // Leer la matriz 'descubierto' (estado de las casillas visibles)
   for (int i = 0; i < filas; i++) {
      for (int j = 0; j < columnas; j++) {
         int valor;
         if (!(archivo >> valor)) { // Verifica si la lectura fue exitosa
            cerr << "Error: Datos corruptos en la matriz descubierto en " << fich << ".\n";
            archivo.close();
            return;
         }
         descubierto.putValue(i, j) = valor;
      }
   }

   archivo.close(); // Cerrar el archivo después de leer
}

/*Analiza el tablero y devuelve false si el user no ha ganado o true si ha marcado todas las bombas
 Por tanto, para ganar tienes que marcar todas las bombas/casillas sin bombas = true
 Si fallas,es decir, abres alguna bomba = false
 Entonces, hay que recorrer el tablero del objeto tab junto al tablero descubierto para ver si el descubierto coindice
 con el tab.
Si tab[i][j] no es bomba y descubierto[i][j] = 1, bien y tiene una bomba alrededor
Si tab[i][j] no es bomba y descubierto[i][j] = -1, ha ganado ya que ha marcado la bobma con -1
*/

bool Tablero::haganado() {
   for (int i = 0; i < tab.numfilas(); i++) {
      for (int j = 0; j < tab.numcolumnas(); j++) {
         // Si NO es bomba y NO está descubierta, aún no ha ganado
         if (tab.getValue(i, j) != NUMBOMBA && descubierto.getValue(i, j) != 1) {
            return false;
         }
      }
   }
   return true; // Todas las casillas sin bomba han sido abiertas
}



//Metodo operator=
Tablero& Tablero::operator=(const Tablero& otro) { //otro es un objeto de tablero
   if (this != &otro) { //para evitar que se le asigne a otro. SE UTILIZA EN OPERATOR= SIEMPRE
      tab = otro.tab;
      descubierto = otro.descubierto;
   }
   return *this; //retorna &otro
}

bool Tablero::abrirpos(int i, int j) {
   if (i < 0 || j < 0 || i >= tab.numfilas() || j >= tab.numcolumnas()) {
      return true;  // Coordenadas inválidas, no pasa nada
   }

   if (tab.getValue(i, j) == NUMBOMBA) {
      cout << "¡Bomba encontrada en (" << i << ", " << j << ")! Juego terminado." << endl;

      // Revelar todas las bombas
      for (int x = 0; x < tab.numfilas(); x++) {
         for (int y = 0; y < tab.numcolumnas(); y++) {
            if (tab.getValue(x, y) == NUMBOMBA) {
               descubierto.putValue(x, y) = 1;
            }
         }
      }

      return false;  // Perdió
   }

   abrirrecursivas(i, j);  // Abrimos en cascada

   return true;  // Sigue el juego
}


//La casilla seleccionada por el jugador, ponemos en descubierto un -1 ya que cree que hay una bomba
void Tablero::marcarpos(int i, int j) {
   //COMPROBACIONES
   if (i < 0 || j < 0 || i >= tab.numfilas() || j >= tab.numcolumnas()) {
      cerr <<"\nCasilla invalida";
      return;
   }
   //NO BUCLES FOR ya que no queremos recorrer todas, solo la seleccionada
   if (descubierto.getValue(i,j) == 0) { // si es = 0 es que esta sin descubrir
      descubierto.putValue(i,j) = -1; //la marca como sospecha de bomba (-1)
   }
}

//Si la casilla esta marcada, la desmarcamos y se pone como no abierta
void Tablero::desmarcarpos(int i, int j) {
   for (int i = 0; i < tab.numfilas();i++) {
      for (int j = 0; j < tab.numcolumnas();j++) {
         //si la casilla igual = -1, se le asigna el valor 0, no abierta
         if (descubierto.getValue(i,j) == -1) {
            descubierto.putValue(i,j) = 0; //valor de no abierta
         }
      }
   }
}

//HE CREADO ESTE METODO PARA ABRIR LAS CASILLAS RECURSIVAS EN CASO DE ABRIR 1 Y SER ESTAS IGUAL A O
void Tablero::abrirrecursivas(int i, int j) {
   if (i < 0 || j < 0 || i >= tab.numfilas() || j >= tab.numcolumnas()) return;
   if (descubierto.getValue(i, j) == 1) return;  // Ya está abierta

   descubierto.putValue(i, j) = 1;  // Abrir la casilla

   if (tab.getValue(i, j) == 0) {
      // Expandimos a las 8 casillas vecinas si no hay bombas cercanas
      for (int di = -1; di <= 1; di++) {
         for (int dj = -1; dj <= 1; dj++) {
            if (di != 0 || dj != 0) {
               abrirrecursivas(i + di, j + dj);
            }
         }
      }
   }
}

