cmake_minimum_required(VERSION 3.30)
project(PRACTICA_FINAL)

set(CMAKE_CXX_STANDARD 20)

add_executable(PRACTICA_FINAL src/main.cpp
        src/MatrizEnteros.cpp
        include/MatrizEnteros.h
        src/Tablero.cpp
        include/Tablero.h
        src/ConjuntoJugadores.cpp
        include/ConjuntoJugadores.h
        src/Jugador.cpp
        include/Jugador.h
        src/Partida.cpp
        include/Partida.h
        main.cpp)
