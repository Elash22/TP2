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

    void setFila(int fila);
    void setColumna(int columna);
    void setAltura(int altura);

    int getFila();
    int getColumna();
    int getAltura();

    //Pre:
    //Post:
    virtual ~Coordenada();
    
};

#endif