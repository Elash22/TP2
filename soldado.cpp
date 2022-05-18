#include "soldado.hpp"
#include "coordenada.hpp"
#include "jugador.hpp"
#include <iostream>

using namespace std;

Soldado::Soldado(Coordenada posicion, int numero){
    this->estado = Vivo;
    this->posicion = posicion;
    this->jugador = NULL; //Dudoso
    this->nroSoldado = numero;
}