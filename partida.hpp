#ifndef PARTIDA_H_
#define PARTIDA_H_

#include "tablero.hpp"
#include "jugador.hpp"

class Partida{
private:
    Tablero* tablero;
    Jugador** jugadores;
    Carta* mazoDeCartas;

    unsigned int cantidadDeJugadores;
    unsigned int cantidadDeSoldadosPorJugador;
    unsigned int turno;
    unsigned int nroMapa;

public:
    // PRE: La cantidad de jugadores debe ser mayor a 1
    // POST: Crea una partida
    Partida(int cantidadDeJugadores, int nroMapa, int largo, int ancho, int alto);

    // PRE: - 
    // POST: Devuelve la cantidad de jugadores con soldados en la partida
    int getCantidadJugadores();

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

    // PRE: 
    // POST: Pide los datos necesarios de los jugadores para iniciar el juego
    void pedirDatos(int& cantidadJugadores, int& cantidadSoldados, int& largo, int& ancho, int& alto, int& nroMapa);

    // PRE:
    // POST: Pide los datos del mapa para iniciar el juego
    void pedirDatosMapa(int& largo, int&ancho, int& alto)

    // PRE:
    // POST:
    void generarTablero();

    // PRE: La coordenada debe ser previamente declarada
    // POST: Asigna los datos a la coordenada
    // Para el grupo: hice las funciones con tipo de unidad por si en un futuro las necesitamos para asignar barcos y aviones
    void pedirDatosUnidad(Coordenada* posicion, string tipoUnidad);

    // PRE: 
    // POST: Asigna soldados al iniciar la partida, pidiendo al usuario las coordenadas correspondientes.
    void inicializarSoldadosAJugadores();

    // PRE: 
    // POST: jugador realiza disparos
    void realizarDisparosJugador();

    // PRE: 
    // POST:
    void moverUnidad();
    
    // PRE: 
    // POST:
    void exportarTablero();

    // PRE
    // POST: chequea si el juego ha terminado
    bool haTerminado();

    // PRE:
    // POST: devuelve el jugador ganador de la partida, en caso de que haya terminado en empate retorna 0;
    unsigned int jugadorGanador();

    // PRE:
    // POST: Destruye la partida
    virtual ~Partida();
};

#endif