#ifndef PARTIDA_H_
#define PARTIDA_H_

#include "tablero.hpp"
#include "jugador.hpp"

class Partida{
private:
    Tablero* tablero;
    Jugador** jugadores;
    int cantidadDeJugadores;
    int turno;
    int estado; // 1 en juego, -1 finalizado, 0 sin iniciar
public:

    //Pre: La cantidad de jugadores debe ser mayor a 1
    //Post: Crea una partida
    Partida(int cantidadDeJugadores);

    //Pre:
    //Post: Destruye la partida
    virtual ~Partida();

    //Pre: - 
    //Post: Devuelve la cantidad de jugadores en la partida
    int getCantidadJugadores();

    //Pre:
    //Post: Nos devuelve el turno actual de la partida
    int getTurno();

    //Pre: El turno debe ser diferente al anterior y valido (concuerda con el nro de jugador)
    //Post: Cambia el turno de la partida por uno nuevo
    void setTurno(int turnoNuevo);

    //Pre: La nueva cantidad de jugadores no puede ser mayor a la anterior
    //Post: En caso de tener que cambiar o reducir la cantidad de jugadores, cambiamos la cantidad de jugadores por una nueva
    void setCantidadJugadores(int cantidadNueva);

    //Pre: - 
    //Post: Cambia el turno automaticamente al siguiente
    void cambiarTurno();
    
};


#endif