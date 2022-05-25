#ifndef CASILLERO_H_
#define CASILLERO_H_

#include "coordenada.hpp"
#include <iostream>

enum EstadoDeCasillero{
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
    EstadoDeCasillero estado;
    TipoTerreno tipoTerreno;

public:
    // PRE: posicion de coordenada valida
    // POST: se crea un casillero en una posicion valida con un tipo de terreno
    Casillero(Coordenada posicion);

    // PRE
    // POST: retorna el estado del casillero
    EstadoDeCasillero getEstado();
    
    // PRE: 
    // POST: cambia el estado del casillero
    void setEstado(EstadoDeCasillero);
   
    // PRE: 
    // POST: devuelve el tipo de terreno
    TipoTerreno getTipoDeTerreno();
    
    // PRE: 
    // POST: retorna la coordenada del casillero
    Coordenada getCoordenada();

    // PRE: exista un casillero
    // POST: -
    virtual ~Casillero();
};


#endif