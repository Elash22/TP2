#ifndef PARTIDA_H_
#define PARTIDA_H_

#include <cstdlib>
#include "tablero.hpp"
#include "jugador.hpp"

const int MINIMO_JUGADORES= 2;
const int MAXIMO_JUGADORES= 10;
const int MINIMO_SOLDADOS= 2;
const int MAXIMO_SOLDADOS= 10;
const int MINIMO_LARGO_ANCHO_TABLERO= 2;
const int MAXIMO_LARGO_ANCHO_TABLERO= 20;
const int MINIMO_ALTO_TABLERO= 2;
const int MAXIMO_ALTO_TABLERO= 10;
const int CANTIDAD_MAPAS= 4;
const int CANTIDAD_CARTAS_POR_JUGADOR= 4;

class Partida{
private:
    Tablero* tablero;
    Jugador** jugadores;
    Carta** mazoDeCartas;

    unsigned int cantidadDeJugadores;
    unsigned int cantidadDeSoldadosPorJugador;
    unsigned int turno;
    unsigned int nroMapa;

    // PRE: 
    // POST: Solicita al usuario los datos necesarios de la partida
    void pedirDatos(int& largo, int& ancho, int& alto);

    // PRE: Ingreso de entero sin signo mayor o igual a 2
    // POST: solicita y valida si el dato ingresado es un entero sin signo, y lo retorna
    unsigned int ingresarNumeroYValidar(unsigned int minimo, unsigned int maximo);

    // PRE:
    // POST: crea punteros a Carta. Agrega cartas en forma aleatoria al vector de punteros a carta.
    void inicializarMazo();

    // PRE: haya cartas en el mazo
    // POST: saca una carta en orden y coloca el puntero a NULL (libera memoria)
    Carta sacarCartaDelMazo();

    // PRE:
    // POST: 
    void activarCarta(Carta carta);

    // PRE: 
    // POST: Asigna soldados al iniciar la partida, pidiendo al usuario las coordenadas correspondientes.
    void inicializarSoldadosAJugadores();

public:
    // PRE: -
    // POST: Crea una partida
    Partida();

    // PRE:
    // POST: 
    void inicializarPartida();

    // PRE: - 
    // POST: Devuelve la cantidad de jugadores con soldados en la partida
    unsigned int getCantidadJugadores();

    // PRE:
    // POST
    unsigned int getCantidadDeSoldadosPorJugador();

    // PRE:
    // POST: Devuelve el turno actual de la partida
    int getTurno();

    // PRE: 
    // POST: Añade uno a la cantidad de turnos de la partida
    void siguienteTurno();

    // PRE: La nueva cantidad de jugadores no puede ser mayor a la anterior
    // POST: En caso de tener que cambiar o reducir la cantidad de jugadores, cambiamos la cantidad de jugadores por una nueva
    // es necesario?
    void setCantidadJugadores(int cantidadNueva);

    //Pre: Las coordenadas deben ser validas, entre 1 y el tamaño del tablero.
    //Post: Solicita datos de una la coordenada para colocar una unidad
    void pedirCoordenadasUnidad(unsigned int& largo, unsigned int& ancho , unsigned int& alto, TipoDeUnidad tipo);

    // PRE:
    // POST:
    void asignarUnidadAlCasillero(Jugador* jugador, int nroUnidad, TipoDeUnidad tipo);

    // PRE:
    // POST:
    bool esSoldado(Unidad unidad);

    // PRE: 
    // POST: jugador realiza disparos dependiendo del a cantidad de unidades y del tipo de unidades que posea
    void realizarDisparosJugador();

    // PRE: 
    // POST: jugador elije una unidad y realiza un movimiento con ella
    // Jugador ingresa el numero de unidad para obtener su posicion, luego
    // usar pedirCoordenadasUnidad() y asignarUnidadAlCasillero()
    void moverUnidad();
    
    // PRE: 
    // POST: se crea un archivo bitmap con el mapa de la partida
    // al comenzar el turno para un jugador se exporta el tablero para el solo
    void exportarTablero();

    // PRE
    // POST: chequea si el juego ha terminado
    // recorre el arreglo de jugadores y observa si existe como maximo 1 jugador con soldados, caso contrario: false
    bool haTerminado();

    // PRE:
    // POST: devuelve el jugador ganador de la partida, en caso de que haya terminado en empate retorna 0;
    unsigned int jugadorGanador();

    // PRE:
    // POST: Destruye la partida
    virtual ~Partida();
};

#endif