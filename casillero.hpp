#ifndef CASILLERO_H_
#define CASILLERO_H_

#include "coordenada.hpp"
#include <iostream>

enum EstadoDeCasilla{
    Inactiva,
    Vacia,
    Ocupada
};

enum TipoTerreno{
    tierra,
    agua,
    aire
}

class Casillero{
private:
    Coordenada posicion;
    EstadoDeCasilla estado;
    TipoTerreno tipoTerreno;

public:
    //Pre:
    //Post:
    Casillero(Coordenada posicion);

    //Pre:
    //Post:
    virtual ~Casillero();
};


#endif