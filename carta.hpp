#ifndef CARTAS_H_
#define CARTAS_H_

enum TipoDeCarta{
    Misil,
    Avion, 
    Barco,
    Somnifero,
    Robo,
    Harakiri
};

class Carta{
private:
    TipoDeCarta tipo;
public:
    //Pre:  TipoDeCarta pasado por parámetro debe ser Misil, Avion, Barco, Somnifero, Robo, o Harakiri.
    //Post: Crea una carta del tipo pasado por parámetro
    Carta(TipoDeCarta tipo);
};

#endif