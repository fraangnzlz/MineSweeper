#include "./include/Partida.h"
#include "./include/Tablero.h"


int main(int argc, char** argv) {
    int contador = 0; //contador para ver los parametros correctos

    if (argc == 11) {
        //si ha metido 11 argumentos, hemos de comprobar que son los correctos
        //orden de los argumentos
        string argumentos = " -f -c -m -nick -fich";
        for (int i = 1; i < argc; i += 2) { // Empieza en 1 y recorre de 2 en 2
            if (string(argv[i]) == "-f" || string(argv[i]) == "-c" || string(argv[i]) == "-m" ||
                string(argv[i]) == "-fich" || string(argv[i]) == "-nick") {
                contador++;
            }
        }

    }if (contador == 5) { // Solo ejecuta si los parámetros son correctos

        int filas = stoi(argv[2]);  // "-f" está en argv[1], valor en argv[2]
        int columnas = stoi(argv[4]);  // "-c" está en argv[3], valor en argv[4]
        int minas = stoi(argv[6]);  // "-m" está en argv[5], valor en argv[6]
        string fichero = argv[8];  // "-nick" está en argv[7], valor en argv[8]
        string nombre = argv[10];  // "-fich" está en argv[9], valor en argv[10]

        Partida partida(fichero,filas,columnas,minas,nombre);
        partida.realizaPartida();

        }else if (argc < 11) {
            cerr << contador;
            cerr << "\nNo has introducido la cantidad de parametros correctos." << endl;
            cout << "\nIntroduce los parametros de nuevo correctamente con la siguiente estructura: "
            << "\n-f -c -m -nick -fich" << endl;
        }else {
            cerr << "\nError";
        }
    }
