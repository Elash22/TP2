#ifndef PARTIDA_H_
#define PARTIDA_H_

#include "tablero.hpp"
#include "jugador.hpp"

class Partida{
private:
    Tablero terrenoDeJuego;
    Jugador* jugadores;
};


#endif