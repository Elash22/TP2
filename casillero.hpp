#ifndef CASILLERO_H_
#define CASILLERO_H_

#include "coordenada.hpp"
#include <iostream>

enum EstadoDeCasilla{
    Inactiva,
    Vacia,
    Ocupada
};

class Casillero{
private:
    EstadoDeCasilla estado;
    Coordenada posicion;

public:

    //Pre:
    //Post:
    Casillero(Coordenada posicion);

    //Pre:
    //Post:
    virtual ~Casillero();

};


#endif