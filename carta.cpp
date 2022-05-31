#include "carta.hpp"
#include <iostream>

using namespace std;

Carta::Carta(TipoDeCarta tipo){
    if( (tipo != Misil) || (tipo != Avion) || (tipo != Barco) || (tipo != Somnifero) || (tipo != Francotirador) || (tipo != Harakiri) ){
        throw "Error al intentar crear un tipo de carta distinto a los válidos.";
    }
    this->tipo = tipo;
}