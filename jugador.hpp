#ifndef JUGADOR_H_
#define JUGADOR_H_

#include "carta.hpp"
#include "soldado.hpp"


class Jugador{
private: 
    int nroJugador;
    Carta* cartas;
    Soldado* soldados;
    int cantidadSoldados;
    Avion * aviones;
    int cantidadAviones;
    Barco * barcos;
    int cantidadBarcos;

public:
    // PRE: 
    // POST: 
    bool poseeUnidades();
};


#endif