#ifndef JUGADOR_H_
#define JUGADOR_H_

#include "cartas.hpp"
#include "soldado.hpp"


class Jugador{
private:
    Soldado* soldados;
    Cartas* cartas;
    int cantidadSoldados;
    int nroJugador;
};


#endif