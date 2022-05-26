#include "casillero.hpp"
#include "coordenada.hpp"
#include <iostream>

using namespace std;

Casillero::Casillero(int fila, int columna, int altura, TipoTerreno terreno){
    this->posicion->setFila(fila);
    this->posicion->setColumna(columna);
    this->posicion->setAltura(altura);
    this->tipoTerreno = terreno;
}

