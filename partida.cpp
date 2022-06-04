#include <iostream>
#include "partida.hpp"

#define CANTIDAD_CARTAS_POR_JUGADOR 4

using namespace std;

Partida::Partida(int cantidadDeJugadores, int nroMapa, int largo, int ancho, int alto){
    int largo;
    int ancho;
    int alto;
    this->turno = 1;
    for(int i = 1; i <= cantidadDeJugadores; i++){
        jugadores[i] = new Jugador(i);
    }
    this->tablero = new Tablero(largo, ancho, alto, nroMapa);
    this->estado = 0;
}

int Partida::getCantidadJugadores(){
    // recorrer el arreglo de jugadores y contar aquellos que tienen soldados
    // return this->cantidadDeJugadores;
}

int Partida::getTurno(){
    return this->turno;
}

void Partida::setCantidadJugadores(int cantidadNueva){
    this->cantidadDeJugadores = cantidadNueva;
}

void pedirDatos(int& cantidadJugadores, int& cantidadSoldados, int& largo, int& ancho, int& alto, int& nroMapa){
    cout << "Bienvenidos, ingrese la cantidad de jugadores: ";
    cin >> cantidadJugadores;
    cout << endl << "Ingrese la cantidad de soldados con la que van a jugar: ";
    cin >> cantidadSoldados;
    pedirDatosMapa(largo, ancho, alto);
    cout << endl << "En que mapa desea jugar? (1 - 4)";
    cin >> nroMapa;
}

void pedirDatosMapa(int& largo, int&ancho, int& alto){
    cout << endl << "Ingrese el largo del mapa: ";
    cin >> largo;
    cout << endl << "Ingrese el ancho del mapa: ";
    cin >> ancho;
    cout << endl << "Ingrese el alto del mapa: ";
    cin >> alto;
}

//Pre: La coordenada debe ser previamente declarada
//Post: Asigna los datos a la coordenada
//Para el grupo: hice las funciones con tipo de unidad por si en un futuro las necesitamos para asignar barcos y aviones
void pedirDatosUnidad(Coordenada* posicion, string tipoUnidad){
    int fila, columna, altura;
    cout << "Ingrese fila: " << endl;
    cin >> fila;
    posicion->setFila(fila);
    cout << "Ingrese columna: " << endl;
    cin >> columna;
    posicion->setColumna(columna);
    if(tipoUnidad != "soldado"){
        cout << "Ingrese Altura: " << endl;
        cin >> altura;
        posicion->setAltura(altura);
    }
    else{
        posicion->setAltura(0); //Altura del terreno basico
    }
}

// Es necesaria?
void asignarUnidad(Partida* partida, Jugador* player, int nroUnidad, string tipoUnidad){
    Coordenada auxiliar;
    pedirDatosUnidad(&auxiliar, tipoUnidad);
    //Aca habria que asignar la unidad a la lista de unidades de cada jugador
}

// Es necesaria?
bool esSoldado(string tipoUnidad){
    return (tipoUnidad == "Soldado");
}

void inicializarSoldadosAJugadores(Partida* partida, int soldadosXJugador){
    // REHACER
    for(int i = 0; i <= partida->getCantidadJugadores(); i++){
        for(int j = 0; j <= soldadosXJugador; j++){
            //Aca habria que asignar soldados con asignar unidad, i es el nro del jugador, j el nro del soldado
        }
    }   
}
    