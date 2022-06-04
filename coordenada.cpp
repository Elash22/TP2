#include "coordenada.hpp"
#include <iostream>

using namespace std;

Coordenada::Coordenada(int fila, int columna, int altura){
    this->fila = fila;
    this->columna = columna;
    this->altura = altura;
}

Coordenada::Coordenada(){
    this->fila = 0;
    this->columna = 0;
    this->altura = 0;
}

void Coordenada::setFila(int fila){
    this->fila = fila;
}

void Coordenada::setColumna(int columna){
    this->columna = columna;
}

void Coordenada::setAltura(int altura){
    this->altura = altura;
}


int Coordenada::getFila(){
    return (this->fila);
}

int Coordenada::getColumna(){
    return (this->columna);
}

int Coordenada::getAltura(){
    return (this->altura);
}

