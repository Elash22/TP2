#include <iostream>
#include "partida.hpp"

using namespace std;
/*
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
*/
Partida::Partida(){
    this->tablero = NULL;
    this->jugadores = NULL;
    this->mazoDeCartas = NULL;

    this->cantidadDeJugadores = 0;
    this->cantidadDeSoldadosPorJugador = 0;
    this->turno = 1;
    this->nroMapa = 1;
}

void Partida::pedirDatos(int& mapaLargo, int& mapaAncho, int& mapaAlto){
    cout << "Bienvenidos, ingrese la cantidad de jugadores: ";
    this->cantidadDeJugadores = this->ingresarNumeroYValidar(MINIMO_JUGADORES, MAXIMO_JUGADORES);
    cout << endl << "Ingrese la cantidad de soldados por jugador con la que van a jugar: ";
    this->cantidadDeSoldadosPorJugador = this->ingresarNumeroYValidar(MINIMO_SOLDADOS, MAXIMO_SOLDADOS);

    unsigned int mapaLargo, mapaAncho, mapaAlto;
    cout << endl << "Ingrese el largo del mapa: ";
    mapaLargo = this->ingresarNumeroYValidar(MINIMO_LARGO_ANCHO_TABLERO,MAXIMO_LARGO_ANCHO_TABLERO);
    cout << endl << "Ingrese el ancho del mapa: ";
    mapaAncho = this->ingresarNumeroYValidar(MINIMO_LARGO_ANCHO_TABLERO,MAXIMO_LARGO_ANCHO_TABLERO);
    cout << endl << "Ingrese el alto del mapa: ";
    mapaAlto = this->ingresarNumeroYValidar(MINIMO_ALTO_TABLERO,MAXIMO_ALTO_TABLERO);

    cout << endl << "En que mapa desea jugar? (1 - " << CANTIDAD_MAPAS<< ")";
    this->nroMapa = this->ingresarNumeroYValidar(MINIMO_ALTO_TABLERO,MAXIMO_ALTO_TABLERO);
}

unsigned int ingresarNumeroYValidar(int minimo, int maximo){
    int numeroIngresado;
    cin << numeroIngresado;
    while(numeroIngresado < minimo || numeroIngresado > maximo){
        cout << endl << "Entrada incorrecta. Ingrese una cantidad mayor a " << minimo-1 << " y menor a " << maximo+1<<": ";
        cin << numeroIngresado;
    }
    return numeroIngresado;
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
    