#ifndef SOLDADO_H_
#define SOLDADO_H_

#include <iostream>
#include "coordenada.hpp"

enum EstadoSoldado{
    Vivo,
    Muerto
};

class Soldado{
private:
    EstadoSoldado estado;
    Coordenada posicion;
    int nroSoldado;
//  Jugador* jugador;

public:
    Soldado(Coordenada posicion, int nroSoldado);    
    EstadoSoldado getEstadoSoldado();
    Coordenada getPosicionSoldado();
    int getNroSoldado();

    //Pre:  El estado pasado por parámetro debe ser 'Vivo' o 'Muerto'
    //Post: Cambia el estado del soldado.
    void setEstadoSoldado(EstadoSoldado estado);
    //Pre: Los componentes de la posicion pasada por parámetro debe ser mayores que cero y... menores que el máximo
    //¿Como hago para agarrar el error donde se le pase una posicion con alguna componente mas alta que la máxima?
    //Post: Cambia la posicion del Soldado.
    void setPosicionSoldado(Coordenada posicion);
};


#endif