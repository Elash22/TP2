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

    //int turno;
public:

    //Pre: largo, ancho y alto deben ser mayores a 0
    //Post: Crea un tablero de juego
    Tablero(int largo, int ancho, int alto, int nroMapa);

    //Pre.
    //Post: Destruye el tablero
    virtual ~Tablero();

    //Pre:
    //Post: Devuelve el largo del tablero
    int getLargo();

    //Pre:
    //Post: Devuelve el ancho del tablero
    int getAncho();

    //Pre.
    //Post: Devuelve el alto del tablero
    int getAlto();

    //POST: devuelve un puntero a casillero según las coordenadas que se indiquen
    Casillero* getCasillero(int largo, int ancho, int alto);


};




#endif /* TABLERO_H_ */