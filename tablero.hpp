#ifndef TABLERO_H_
#define TABLERO_H_

#include "lista.hpp"
#include "casillero.hpp"

class Tablero{
private:
    int largo;
    int ancho;
    int alto;
    //Cubo de listas
    //Puntero a la estructura de casilleros
    Lista<Lista<Lista<Casillero*>*>*>* tablero; 

    int turno;
public:
    Tablero(int largo, int ancho, int alto);
    ~Tablero();
    int getLargo();
    int getAncho();
    int getAlto();
    //POST: devuelve un puntero a casillero según las coordenadas que se indiquen
    Casillero* getCasillero(int largo, int ancho, int alto);
};




#endif /* TABLERO_H_ */