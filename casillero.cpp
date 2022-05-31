#include <iostream>
#include "casillero.hpp"
#include "coordenada.hpp"

Casillero::Casillero(int fila, int columna, int altura, TipoTerreno tipo){
    this->posicion = new Coordenada(fila, columna, altura);
    this->estado = vacia;
    this->tipoTerreno = tipo;
    this->jugador = NULL;
    this->unidad = NULL;
}

Coordenada* Casillero::getCoordenada(){
    return this->posicion;
}

EstadoDeCasillero Casillero::getEstado(){
    return this->estado;
}

void Casillero::setEstado(EstadoDeCasillero e){
    this->estado = e;
    return;
}

TipoTerreno Casillero::getTipoDeTerreno(){
    return this->tipoTerreno;
}

void Casillero::setJugador(Jugador* jugador){
    if(jugador != NULL){
        this->jugador = jugador;
    }
    return;
}

Jugador* Casillero::getJugador(){
    return this->jugador;
}

void Casillero::setUnidad(Unidad* unidad){
    if(unidad != NULL){
        this->unidad = unidad;
    }
    return;
}

Casillero::~Casillero(){
    delete(this->posicion);
}