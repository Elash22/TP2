#include <iostream>

class Coordenada{
private:
    int fila;
    int columna;
};

class Soldado{
private:
    Coordenada posicion;
};

class Cartas{
private:
    char tipo;
};

class Jugador{
private:
    Soldado* soldados;
    Cartas* cartas;
    int cantidadSoldados;
    int nroJugador;
};

class Tablero{
private:
    int turno;
    //Cubo de listas
};

class Partida{
private:
    Tablero terrenoDeJuego;
    Jugador* jugadores;
};

