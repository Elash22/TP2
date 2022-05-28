#include "casillero.hpp"
#include "coordenada.hpp"
#include <iostream>

using namespace std;

Casillero::Casillero(int fila, int columna, int altura){
    this->posicion->setFila(fila);
    this->posicion->setColumna(columna);
    this->posicion->setAltura(altura);
}

