#include <iostream>
#include "partida.hpp"
#include "unidad.hpp"
#include "jugador.hpp"

using namespace std;

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

    cout << endl << "Ingrese el largo del mapa: ";
    mapaLargo = this->ingresarNumeroYValidar(MINIMO_LARGO_ANCHO_TABLERO,MAXIMO_LARGO_ANCHO_TABLERO);
    cout << endl << "Ingrese el ancho del mapa: ";
    mapaAncho = this->ingresarNumeroYValidar(MINIMO_LARGO_ANCHO_TABLERO,MAXIMO_LARGO_ANCHO_TABLERO);
    cout << endl << "Ingrese el alto del mapa: ";
    mapaAlto = this->ingresarNumeroYValidar(MINIMO_ALTO_TABLERO,MAXIMO_ALTO_TABLERO);

    cout << endl << "En que mapa desea jugar? (1 - " << CANTIDAD_MAPAS<< ")";
    this->nroMapa = this->ingresarNumeroYValidar(MINIMO_ALTO_TABLERO,MAXIMO_ALTO_TABLERO);
}

unsigned int Partida::ingresarNumeroYValidar(int minimo, int maximo){
    int numeroIngresado;
    cin >> numeroIngresado;
    while(numeroIngresado < minimo || numeroIngresado > maximo){
        cout << endl << "Entrada incorrecta. Ingrese una cantidad mayor a " << (minimo-1) << " y menor a " << maximo+1 << ": ";
        cin >> numeroIngresado;
    }
    return numeroIngresado;
}

void Partida::inicializarPartida(){
    int mapaLargo, mapaAncho, mapaAlto;
    this->pedirDatos(mapaLargo, mapaAncho, mapaAlto);

    this->jugadores = new Jugador*[this->getCantidadJugadores()];
    
    for(unsigned int i=0; i<this->getCantidadJugadores(); i++){
        this->jugadores[i] = new Jugador(i);
    }

    this->tablero = new Tablero(mapaLargo, mapaAncho, mapaAlto, this->nroMapa);

    this->inicializarMazo();
    
    this->inicializarSoldadosAJugadores();
}

unsigned int Partida::getCantidadJugadores(){
    // recorrer el arreglo de jugadores y contar aquellos que tienen soldados
    // return this->cantidadDeJugadores;
}

unsigned int Partida::getCantidadDeSoldadosPorJugador(){
    return this->cantidadDeSoldadosPorJugador;
}

int Partida::getTurno(){
    return this->turno;
}

void Partida::setCantidadJugadores(int cantidadNueva){
    this->cantidadDeJugadores = cantidadNueva;
}

void Partida::pedirCoordenadasUnidad(unsigned int& largo, unsigned int& ancho , unsigned int& alto, TipoDeUnidad tipo){
    cout << endl << "Ingrese largo: ";
    largo = this->ingresarNumeroYValidar(1,this->tablero->getLargo());
    cout << endl << "Ingrese ancho: ";
    ancho = this->ingresarNumeroYValidar(1,this->tablero->getAncho());
    // Se coloca a la unidad en tierra firme
    while(this->tablero->getCasillero(largo, ancho, 1)->getTipoDeTerreno() == agua){
        cout << endl << "Posicion Invalida. La posicion corresponde a agua.";
        cout << endl << "Ingrese largo: ";
        largo = this->ingresarNumeroYValidar(1,tablero->getLargo());
        cout << endl << "Ingrese ancho: ";
        ancho = this->ingresarNumeroYValidar(1,tablero->getAncho());
    }
    alto = 0;
    if(tipo != soldado && tipo != barco){
        cout << "Ingrese altura: ";
        alto = this->ingresarNumeroYValidar(1, tablero->getAlto());
    }
}

void Partida::asignarUnidadAlCasillero(Jugador* jugador, int nroUnidad, TipoDeUnidad tipo){
    unsigned int largo, ancho, alto;
    
    pedirCoordenadasUnidad(largo, ancho, alto, tipo);
    Casillero * casillero = this->tablero->getCasillero(largo, ancho, alto);
    Unidad* unidad = new Unidad(tipo, nroUnidad, casillero->getCoordenada());
    casillero->setUnidad(unidad);
    jugador->asignarUnidad(unidad);    
}

bool Partida::esSoldado(Unidad unidad){
    return (unidad.getTipoDeUnidad() == soldado);
}

void Partida::inicializarSoldadosAJugadores(){
    for(unsigned int i = 0; i <= this->getCantidadJugadores(); i++){
        for(unsigned int j = 0; j <= this->getCantidadDeSoldadosPorJugador(); j++){
            asignarUnidadAlCasillero(this->jugadores[i], j, soldado);
        }
    }   
}
    