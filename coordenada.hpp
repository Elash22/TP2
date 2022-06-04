#ifndef COORDENADA_H_
#define COORDENADA_H_

#include <iostream>

class Coordenada{
private:
    int fila;
    int columna;
    int altura;

public:

    //Pre:
    //Post:
    Coordenada(int fila, int columna, int altura);

    //Pre:
    //Post:
    Coordenada();

    //Pre:
    //Post:
    void setFila(int fila);

    //Pre:
    //Post:
    void setColumna(int columna);

    //Pre:
    //Post:
    void setAltura(int altura);

    //Pre:
    //Post:
    int getFila();

    //Pre:
    //Post:
    int getColumna();

    //Pre:
    //Post:
    int getAltura();

    //Pre:
    //Post:
    virtual ~Coordenada();
    
};

#endif