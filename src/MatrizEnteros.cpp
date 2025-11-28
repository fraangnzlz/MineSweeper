#include "../include/MatrizEnteros.h"
#include <iostream>
using namespace std;


int MatrizEnteros::numfilas(){
   return filas;
}
int MatrizEnteros::numcolumnas(){
   return columnas;
}

MatrizEnteros::MatrizEnteros() {
   filas = 7;
   columnas = 7;
   int def = 0;

   m = new int*[filas];
   for (int i = 0; i < filas; i++) {
      m[i] = new int[columnas];
      for (int j = 0; j < columnas; j++) {
         m[i][j] = def;
      }
   }
}

int & MatrizEnteros::putValue(int fil, int col){
   if (fil < 0 || fil> filas || col < 0 || col > columnas) {
      cerr << "Error. Posición inválida";
   } else {
      return m[fil][col];
   }
   //Esta función asigna un valor en caso de que sea correcto el numero de fil y col.
   //Es un valor que puede cambiarse al ser de referencia
}

int MatrizEnteros::getValue(int fil, int col) {
   if (fil < 0 || fil > filas || col < 0 || col > columnas ) {
      cerr << "Error. Posición inválida";
   }else {
      return m[fil][col];
   }
   //Esta funcion devuelve el valor si está correcto el numero de fil y col.
}


MatrizEnteros::MatrizEnteros(int fil, int col, int def) {
      filas = fil;
      columnas = col;

      // Reservamos memoria para las filas
      m = new int*[filas];

      // Reservamos memoria para cada columna en cada fila
      for (int i = 0; i < filas; i++) {
         m[i] = new int[columnas];
      }

      // Inicializamos los valores al valor por defecto
      for (int i = 0; i < filas; i++) {
         for (int j = 0; j < columnas; j++) {
            m[i][j] = def;
         }
      }
   }


void MatrizEnteros::inicializarMatriz(int def){ //Constructor por defecto
   if (m != NULL) {
      for (int i = 0; i < filas; i++) {
         delete[] m; //Eliminamos memoria
      }
   }
   for (int i = 0; i < filas; i++) {
      for (int j = 0; j < columnas; j++) {
         m[i][j] = def;
      }
   }
   delete[] m; //Eliminamos memoria asignada
}
//vacio

void MatrizEnteros::liberarMemoria() { //metodo unicamente para eliminar memoria
   if (m != nullptr) {
      for (int i = 0; i < filas; i++) {
         delete m[i]; //ELIMINAMOS MEMORIA ASIGNADA
      }
   }
   delete [] m;
   m = nullptr;
}

MatrizEnteros::MatrizEnteros(const MatrizEnteros& orig) { //Constructor de copia
   //Este metodo ahora crea dos objetos DISJUNTOS
   filas = orig.filas;
   columnas = orig.columnas;
   //2 objeto
   m = new int*[filas];
   for (int i = 0; i < filas; i++) {
      m[i] = new int[columnas];
      for (int j = 0; j < columnas;j++) {
         m[i][j] = orig.m[i][j];
      }
   }
}

//vacio
MatrizEnteros::~MatrizEnteros() {
   liberarMemoria();
}

string MatrizEnteros::matriztostring(){
      string resultado = "";  // string para devolver la matriz

      for (int i = 0; i < filas; i++) {
         for (int j = 0; j < columnas; j++) {
            resultado = resultado + to_string(m[i][j]);
            if (j < columnas - 1) {
               resultado += " ";
            }
         }
         resultado += "\n";  //Salto de linea
      }
      return resultado;
   }


void MatrizEnteros::resize(int newf, int newc, int value) {
   //Si la nueva es mas grande se guarda la información
   int **nuevamatriz = new int*[newf];
   //Memoria para las columnas
   for (int i = 0; i < newf; i++) {
      nuevamatriz[i] = new int[newc];
   }
   int mfilas; //Variables para guardar cuantas filas y columnas hemos de almacenar para guardar su información
   int mcolumnas;
   if (newf < filas) {
      mfilas = newf;
   }else {
      mfilas = filas;
   }
   if (newc < columnas) {
      mcolumnas = newc;
   }else {
      mcolumnas = columnas;
   }
   for (int i = 0; i < mfilas; i++) {
      for (int j = 0; j < mcolumnas; j++) {
         nuevamatriz[i][j] = m[i][j];
      }
   }
   //En caso de que la matriz sea mayor, guardamos el valor de la variable value en dichas posiciones
   for (int i = 0; i < newf; i++) {
      for (int j = 0; j < newc; j++) {  //Llega hasta newc ya que va a ser EL TAMAÑO DE LA NUEVA MATRIZ SI O SI
         /*El tamaño de la nueva matriz no indica si newf o newc es menor, eso solo indica la cantidad de información
         que se va a guardar*/
         if (i >= mfilas || j >= mcolumnas) {
            nuevamatriz[i][j] = value;
         }
      }
   }
   liberarMemoria();
   //ACTUALIZAMOS INFORMACION
   m = nuevamatriz;
   filas = newf;
   columnas = newc;
}
MatrizEnteros& MatrizEnteros::operator=(const MatrizEnteros& obj){ //obj es el objeto
   //this en metodos operator
   if (this != &obj) {
      liberarMemoria();
   }
   filas = obj.filas;
   columnas = obj.columnas;
   //Ahora liberamos la memoria el objeto de destino, que va a ser m
   m = new int*[filas];
   for (int i = 0; i < filas; i++) {
      m[i] = new int[columnas];
      for (int j = 0; j < columnas; j++) {
         m[i][j] = obj.m[i][j]; //Copiamos la informacion
         //Tienen la informacion igual pero NO LOS DATOS, ya que no tienen el mismo espacio asignado
      }
   }
   return *this;
}

//Metodo operator<<

ostream & operator<< (ostream & flujo, const MatrizEnteros &obj) {
   //Debemos devolver la informacion del objeto con espacios
   for (int i = 0; i < obj.filas; i++) {
      for (int j = 0; j < obj.columnas; j++) {
         //columnas y filas solo da error, ya que este metodo no pertenece a la clase
         flujo << obj.m[i][j] << " "; //con espacios
      }
   }
   return flujo << endl;
}