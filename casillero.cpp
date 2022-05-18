#include "casillero.hpp"
#include "coordenada.hpp"
#include <iostream>


using namespace std;


Casillero::Casillero(Coordenada posicion){
    this->posicion = posicion;
    this->estado = Vacia;
}
