#include <iostream>
#include "partida.hpp"

using namespace std;

Partida::Partida(int cantidadDeJugadores){
    int largo;
    int ancho;
    int alto;
    this->turno = 1;
    for(int i = 1; i <= cantidadDeJugadores; i++){
        jugadores[i] = new Jugador(i);
    }
    cout << "Ingrese largo de su tablero: ";
    cin >> largo;
    cout << endl << "Ingrese ancho de su tablero: ";
    cin >> ancho;
    cout << endl << "Ingrese alto de su tablero: ";
    cin >> alto;
    this->tablero = new Tablero(largo, ancho, alto);
    this->estado = 0;
}

int Partida::getCantidadJugadores(){
    return this->cantidadDeJugadores;
}

int Partida::getTurno(){
    return this->turno;
}
  
void Partida::setTurno(int turnoNuevo){
    this->turno = turnoNuevo;
}

void Partida::setCantidadJugadores(int cantidadNueva){
    this->cantidadDeJugadores = cantidadNueva;
}

void Partida::cambiarTurno(){
    if(this->turno == this->cantidadDeJugadores){
        setTurno(1);
    }
    else{
        setTurno(this->turno++);
    }
}
    