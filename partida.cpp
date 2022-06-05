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

    cout << endl << "En que mapa desea jugar? (1 - " << CANTIDAD_MAPAS<< "): ";
    this->nroMapa = this->ingresarNumeroYValidar(0,CANTIDAD_MAPAS);
}

unsigned int Partida::ingresarNumeroYValidar(unsigned int minimo, unsigned int maximo){
    unsigned int numeroIngresado;
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

// PRE:
// POST: crea punteros a Carta. Agrega cartas en forma aleatoria al vector de punteros a carta.
void Partida::inicializarMazo(){
    // TODO
}

// PRE: haya cartas en el mazo
// POST: saca una carta en orden y coloca el puntero a NULL (libera memoria)
Carta Partida::sacarCartaDelMazo(){
    // TODO
}

// PRE:
// POST: dependiento el tipo de carta, realizar la accion correspondiente
void Partida::activarCarta(Carta carta){
    // TODO
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

// PRE: 
// POST: Se juega el siguiente turno de la partida, añade uno a la cantidad de turnos
void Partida::siguienteTurno(){
    // TODO
    unsigned int nroJugadorEnTurno = this->getTurno() % this->getCantidadJugadores();
    this->exportarTablero(nroJugadorEnTurno);
    this->realizarDisparosJugador(nroJugadorEnTurno)
    // check si termino el juego (luego de cada disparo?)
    this->moverUnidad(nroJugador);
    // check si termino el juego
    this->sacarCartaDelMazo(nroJugador);
    // check si termino el juego
    // sumar uno a la cantidad de turnos
}

void Partida::setCantidadJugadores(int cantidadNueva){
    this->cantidadDeJugadores = cantidadNueva;
}

void Partida::pedirCoordenadasUnidad(unsigned int& largo, unsigned int& ancho , unsigned int& alto, TipoDeUnidad tipo){
    cout << endl << "Ingrese largo: ";
    largo = this->ingresarNumeroYValidar(1,this->tablero->getLargo());
    cout << endl << "Ingrese ancho: ";
    ancho = this->ingresarNumeroYValidar(1,this->tablero->getAncho());
    if(tipo == soldado){
        while(this->tablero->getCasillero(largo, ancho, 1)->getTipoDeTerreno() == agua){
            cout << endl << "Posicion Invalida. La posicion corresponde a agua.";
            cout << endl << "Ingrese largo: ";
            largo = this->ingresarNumeroYValidar(1,tablero->getLargo());
            cout << endl << "Ingrese ancho: ";
            ancho = this->ingresarNumeroYValidar(1,tablero->getAncho());
        }
    }else if(tipo == barco){
        while(this->tablero->getCasillero(largo, ancho, 1)->getTipoDeTerreno() == tierra){
            cout << endl << "Posicion Invalida. La posicion corresponde a tierra firme.";
            cout << endl << "Ingrese largo: ";
            largo = this->ingresarNumeroYValidar(1,tablero->getLargo());
            cout << endl << "Ingrese ancho: ";
            ancho = this->ingresarNumeroYValidar(1,tablero->getAncho());
        }
    }
    alto = 1;
    if(tipo != soldado && tipo != barco){
        cout << "Ingrese altura: ";
        alto = this->ingresarNumeroYValidar(2, tablero->getAlto());
    }
}

void Partida::asignarUnidadAlCasillero(Jugador* jugador, int nroUnidad, TipoDeUnidad tipo){
    unsigned int largo, ancho, alto;
    cout << endl << "Jugador #" << jugador->getNumeroJugador() << ", ingrese coordenadas para un nuevo " << Unidad::imprimirTipo(tipo)
        << " #" << nroUnidad << "";
    pedirCoordenadasUnidad(largo, ancho, alto, tipo);
    Casillero * casillero = this->tablero->getCasillero(largo, ancho, alto);
    while(casillero->getEstado() == inhabilitado){
        cout << endl << "El casillero ingresado se encuentra inhabilitado. Intente nuevamente";
        pedirCoordenadasUnidad(largo, ancho, alto, tipo);
        casillero = this->tablero->getCasillero(largo, ancho, alto);
    }
    if(casillero->getEstado() == ocupado){
        cout << endl << "El soldado #" << nroUnidad << " del jugador #" << jugador->getNumeroJugador() << "ha muerto en combate cuerpo a cuerpo";
        if(!casillero->getUnidad()){
            throw "el puntero de la unidad que ocupa el casillero es NULL";
        }
        cout << endl << "El soldado #" << casillero->getUnidad()->getNroUnidad() << " del jugador #" << casillero->getJugador() << "ha muerto en combate cuerpo a cuerpo";
        casillero->getJugador()->removerUnidad(casillero->getUnidad());
        delete casillero->getUnidad();
        casillero->inhabilitar();
        return;
    }
    Unidad* unidad = new Unidad(tipo, nroUnidad, casillero->getCoordenada());
    jugador->asignarUnidad(unidad);    
    casillero->setUnidad(unidad);
    casillero->setJugador(jugador);
    casillero->setEstado(ocupado);
}

bool Partida::esSoldado(Unidad unidad){
    return (unidad.getTipoDeUnidad() == soldado);
}

void Partida::inicializarSoldadosAJugadores(){
    for(unsigned int i = 1; i <= this->cantidadDeJugadores; i++){
        for(unsigned int j = 1; j <= this->getCantidadDeSoldadosPorJugador(); j++){
            asignarUnidadAlCasillero(this->jugadores[i], j, soldado);
        }
    }   
}

// PRE: 
// POST: jugador realiza disparos dependiendo del a cantidad de unidades y del tipo de unidades que posea
void Partida::realizarDisparosJugador(){
    // TODO
}

// PRE: 
// POST: jugador elije una unidad y realiza un movimiento con ella
// Jugador ingresa el numero de unidad para obtener su posicion, luego
// usar pedirCoordenadasUnidad() y asignarUnidadAlCasillero()
void Partida::moverUnidad(){
    // TODO
}

// PRE: 
// POST: se crea un archivo bitmap con el mapa de la partida
// al comenzar el turno para un jugador se exporta el tablero para el solo
void Partida::exportarTablero(){
    // TODO
}

// PRE
// POST: chequea si el juego ha terminado
// recorre el arreglo de jugadores y observa si existe como maximo 1 jugador con soldados, caso contrario: false
bool Partida::haTerminado(){
    // TODO
}

// PRE:
// POST: devuelve el jugador ganador de la partida, en caso de que haya terminado en empate retorna 0;
unsigned int Partida::jugadorGanador(){
    // TODO
}

Partida::~Partida(){
    // TODO
}