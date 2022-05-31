#include <iostream>
#include "unidad.hpp"
#include "coordenada.hpp"

Unidad::Unidad(TipoDeUnidad tipo, int nroUnidad, Coordenada* posicion){
    this->tipo = tipo;
    this->nroUnidad = nroUnidad;
    this->posicion = posicion;
}

TipoDeUnidad Unidad::getTipoDeUnidad(){
    return this->tipo;
}

int Unidad::getNroUnidad(){
    return this->nroUnidad;
}

Coordenada* Unidad::getPosicion(){
    return this->posicion;
}

void Unidad::setPosicionUnidad(Coordenada* posicion){
    this->posicion = posicion;
}
