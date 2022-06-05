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
// POST: Añade uno a la cantidad de turnos de la partida
void Partida::siguienteTurno(){
    // TODO
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

    // Si el casillero tiene esta inhabilitado pedir nuevamente coordenadas
    // Si el casillero esta ocupado, ambas unidades mueren, liberar la que esta en el casillero y retornar

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